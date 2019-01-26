<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\XF\Admin\Controller;

use XF\Mvc\ParameterBag;
use XF\Util\IP;

/**
 * Extends \XF\Admin\Controller\Log
 */
class Log extends XFCP_Log
{
    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUser(ParameterBag $params)
    {
        /** @var int $user_log_id */
        /** @noinspection PhpUndefinedFieldInspection */
        $user_log_id = $params->user_log_id;
        if ($user_log_id)
        {
            $entry = $this->assertUserLogExists(
                $user_log_id,
                null,
                'requested_log_entry_not_found'
            );

            $viewParams = [
                'entry' => $entry
            ];

            return $this->view(
                'XF:Log\User\View',
                'sv_ue_log_user_view',
                $viewParams
            );
        }

        $page = $this->filterPage();
        $perPage = 20;

        $userLogRepo = $this->getUserLogRepo();
        $logFinder = $userLogRepo->findLogsForList()
                                 ->limitByPage($page, $perPage);

        if ($username = $this->filter('username', 'str'))
        {
            /** @var \SV\UserEssentials\XF\Entity\User $limitUser */
            $limitUser = $this->em()->findOne(
                'XF:User',
                ['username' => $username]
            );
            if (!$limitUser)
            {
                return $this->error(\XF::phrase('requested_user_not_found'));
            }
        }
        elseif ($userId = $this->filter('user_id', 'uint'))
        {
            $limitUser = $this->em()->find('XF:User', $userId);
            if (!$limitUser)
            {
                return $this->error(\XF::phrase('requested_user_not_found'));
            }
        }
        else
        {
            $limitUser = null;
        }

        $linkFilters = [];
        if ($limitUser)
        {
            $linkFilters['user_id'] = $limitUser->user_id;
            $logFinder->where('user_id', $limitUser->user_id);
        }

        if ($this->isPost())
        {
            // redirect to give a linkable page
            return $this->redirect($this->buildLink(
                'logs/user',
                null,
                $linkFilters
            ));
        }

        $viewParams = [
            'limitUser' => $limitUser,

            'entries' => $logFinder->fetch(),

            'page'        => $page,
            'perPage'     => $perPage,
            'total'       => $logFinder->total(),
            'linkFilters' => $linkFilters
        ];

        return $this->view(
            'XF:Log\User\Listing',
            'sv_ue_log_user_list',
            $viewParams
        );
    }

    /**
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionUserClear()
    {
        if ($this->isPost())
        {
            $this->getUserLogRepo()->clearUserLog();

            return $this->redirect($this->buildLink('logs/user'));
        }

        return $this->view('XF:Log\User\Clear', 'sv_ue_log_user_clear');
    }

    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\AbstractReply
     */
    public function actionLoginAttempt(ParameterBag $params)
    {
        /** @noinspection PhpUndefinedFieldInspection */
        $attempt_id = $params->attempt_id;
        if ($attempt_id)
        {
            $entry = $this->assertLoginAttemptExists(
                $attempt_id,
                null,
                'requested_log_entry_not_found'
            );

            if ($this->isPost())
            {
                $this->assertAdminPermission('user');
                $entry->delete();

                if ($this->filter('delete_login', 'bool'))
                {
                    $this->app->db()->delete(
                        'xf_login_attempt',
                        'login = ?',
                        $entry->login
                    );
                }
                if ($this->filter('delete_ip', 'bool'))
                {
                    $this->app->db()->delete(
                        'xf_login_attempt',
                        'ip_address = ?',
                        $entry->ip_address
                    );
                }

                return $this->redirect($this->getDynamicRedirect());
            }

            $viewParams = [
                'entry' => $entry
            ];

            return $this->view(
                'XF:Log\LoginAttempt\View',
                'sv_ue_log_login_attempt_view',
                $viewParams
            );
        }

        $page = $this->filterPage();
        $perPage = 20;

        $loginAttemptRepo = $this->getLoginAttemptRepo();
        $logFinder = $loginAttemptRepo->findLoginAttemptsForList()
                                      ->limitByPage($page, $perPage);

        $linkFilters = [];
        if ($login = $this->filter('login', 'str'))
        {
            $linkFilters['login'] = $login;
            $logFinder->where('login', $login);
        }
        if ($ipAddress = $this->filter('ip_address', 'str'))
        {
            $linkFilters['ip_address'] = $ipAddress;
            $logFinder->where(
                'ip_address',
                IP::convertIpStringToBinary($ipAddress)
            );
        }

        if ($this->isPost())
        {
            // redirect to give a linkable page
            return $this->redirect($this->buildLink(
                'logs/login-attempt',
                null,
                $linkFilters
            ));
        }

        $viewParams = [
            'entries' => $logFinder->fetch(),

            'page'        => $page,
            'perPage'     => $perPage,
            'total'       => $logFinder->total(),
            'linkFilters' => $linkFilters
        ];

        return $this->view(
            'XF:Log\LoginAttempt\Listing',
            'sv_ue_log_login_attempt_list',
            $viewParams
        );
    }

    /**
     * @param string            $id
     * @param array|string|null $with
     * @param null|string       $phraseKey
     * @return \SV\UserEssentials\Entity\UserLog|\XF\Mvc\Entity\Entity
     */
    protected function assertUserLogExists(
        $id,
        $with = null,
        $phraseKey = null
    )
    {
        return $this->assertRecordExists(
            'SV\UserEssentials:UserLog',
            $id,
            $with,
            $phraseKey
        );
    }

    /**
     * @param string            $id
     * @param array|string|null $with
     * @param null|string       $phraseKey
     * @return \XF\Entity\LoginAttempt|\XF\Mvc\Entity\Entity
     */
    protected function assertLoginAttemptExists(
        $id,
        $with = null,
        $phraseKey = null
    )
    {
        return $this->assertRecordExists(
            'XF:LoginAttempt',
            $id,
            $with,
            $phraseKey
        );
    }

    /**
     * @return \SV\UserEssentials\Repository\UserLog|\XF\Mvc\Entity\Repository
     */
    protected function getUserLogRepo()
    {
        return $this->repository('SV\UserEssentials:UserLog');
    }

    /**
     * @return \XF\Mvc\Entity\Repository|\XF\Repository\LoginAttempt|\SV\UserEssentials\XF\Repository\LoginAttempt
     */
    protected function getLoginAttemptRepo()
    {
        return $this->repository('XF:LoginAttempt');
    }
}
