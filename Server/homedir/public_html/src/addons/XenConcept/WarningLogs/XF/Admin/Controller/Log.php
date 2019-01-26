<?php
/**
 * Created by PhpStorm.
 * User: Rémi
 * Date: 22/12/2017
 * Time: 23:08
 */

namespace XenConcept\WarningLogs\XF\Admin\Controller;

use XF\Mvc\ParameterBag;

class Log extends XFCP_Log
{

    public function actionWarning(ParameterBag $params)
    {
        $this->setSectionContext('warning_log');

        $page = $this->filterPage();
        $perPage = 20;

        if ($username = $this->filter('username', 'str'))
        {
            $limitUser = $this->em()->findOne('XF:User', ['username' => $username]);

            if (!$limitUser)
            {
                return $this->error(\XF::phrase('requested_user_not_found'));
            }
        }
        else
        {
            $limitUser = null;
        }

        $entries = $this->finder('XF:Warning');

        if ($limitUser)
        {
            $entries->where('warning_user_id', $limitUser->user_id);
        }

        $entries
            ->order('warning_date', 'DESC')
            ->limitByPage($page, $perPage);

        $viewParams = [

            'entries' => $entries->fetch(),
            'page'    => $page,
            'perPage' => $perPage,
            'total'   => $entries->total(),
            'limitUser' => $limitUser
        ];

        return $this->view('XF:Log\Warning_List', 'xc_warning_logs_log_warning_list', $viewParams);
    }

    public function actionWarningClear()
    {
        if ($this->isPost())
        {
            $this->getWarningRepo()->clearWarningLog();

            return $this->redirect($this->buildLink('logs/warning'));
        }
        else
        {
            return $this->view('XF:Log\Warning\Clear', 'xc_warning_logs_log_warning_clear');
        }
    }

    /**
     * @return \XenConcept\WarningLogs\XF\Repository\Warning
     */
    protected function getWarningRepo()
    {
        return $this->repository('XF:Warning');
    }
}