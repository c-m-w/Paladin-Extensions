<?php

namespace BlackTea\SteamAuth\Admin\Controller;

use XF\Mvc\ParameterBag;

class Steam extends \XF\Admin\Controller\AbstractController
{

    public function actionMigrate()
    {
        $db = \XF::db();

        $connectedAccounts = $db->fetchAll('
          SELECT * FROM xf_user_connected_account
          WHERE provider = "steam"
          AND extra_data IN ("N;", "")
        ');

        foreach ($connectedAccounts as $connectedAccount) {
            $update = array(
                'extra_data' => serialize(array(
                    'token' => $connectedAccount['provider_key']
                ))
            );

            $where = 'provider = "steam" && user_id = "' . $connectedAccount['user_id'] . '"';

            $db->update('xf_user_connected_account', $update, $where);
        }

        $redirectUrl = $this->buildLink('index');
        return $this->redirect($redirectUrl);
    }

    public function actionList(ParameterBag $params)
    {
        $db = \XF::db();
        $userFinder = \XF::finder('XF:User');

        $perPage = 15;
        $page = $this->filterPage($params->page);
        $offset = ($page - 1) * $perPage;

        $criteria = $this->filter('criteria', 'array');
        $filter = $this->filter('_xfFilter', [
            'text' => 'str',
            'prefix' => 'bool'
        ]);

        $search = '%%';

        if (strlen($filter['text'])) {
            $search = $filter['prefix'] ? $filter['text'] . '%' : '%' . $filter['text'] . '%';
        }

        $connectedAccountsCount = $db->fetchOne('
          SELECT COUNT(*) FROM xf_user_connected_account AS xuca
          JOIN xf_user AS xu
          ON xuca.user_id = xu.user_id
          WHERE xuca.provider = "steam"
          AND (xuca.provider_key LIKE ?
          OR xu.username LIKE ?
          OR xu.email LIKE ?)
        ', array($search, $search, $search));

        $connectedAccounts = $db->fetchAllKeyed("
          SELECT xuca.provider_key, xuca.user_id FROM xf_user_connected_account AS xuca
          JOIN xf_user AS xu
          ON xuca.user_id = xu.user_id
          WHERE xuca.provider = 'steam'
          AND (xuca.provider_key LIKE ?
          OR xu.username LIKE ?
          OR xu.email LIKE ?)
          LIMIT ?, ?
        ", 'user_id', array($search, $search, $search, $offset, $perPage));

        $users = $userFinder
            ->where('user_id', array_keys($connectedAccounts))
            ->fetch();

        $viewParams = array(
            'connectedAccounts' => $connectedAccounts,
            'total' => $connectedAccountsCount,
            'items' => $users,
            'perPage' => $perPage,
            'page' => $page,
            'criteria' => $criteria,
            'filter' => $filter['text']
        );

        return $this->view('BlackTea\SteamAuth:List', 'blacktea_steamauth_steam_list', $viewParams);
    }

    public function actionGetsummaries(ParameterBag $params)
    {
        header('Content-Type: application/json');

        $app = $this->app();
        $em = $app->em();

        $profiles = array();
        $steamIds = $params->get('steamids');
        preg_match('/[^0-9-]/', $steamIds, $matches);

        if (empty($matches)) {
            $provider = $em->find('XF:ConnectedAccountProvider', 'steam');
            $options = $provider->getValue('options');

            if (!empty($options) && isset($options['client_secret'])) {
                $apiKey = $options['client_secret'];
                $steamIds = explode('-', $steamIds);

                try {
                    $steamApi = new \BlackTea\SteamAuth\Helper\Steam($apiKey);
                    $profiles = $steamApi->getPlayerSummaries($steamIds);
                } catch (\Exception $e) {
                    if ($app->options()->blacktea_steamauth_verbose_log) {
                        \XF::logException($e, false);
                    }
                }
            }
        }

        echo json_encode(array('profiles' => $profiles));
        die;
    }

}