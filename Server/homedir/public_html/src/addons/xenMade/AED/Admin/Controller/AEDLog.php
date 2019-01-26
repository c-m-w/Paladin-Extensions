<?php

namespace xenMade\AED\Admin\Controller;

use XF\Mvc\Entity\Finder;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class AEDLog extends AbstractController
{
    protected function preDispatchController($action, ParameterBag $params)
    {
        $this->assertAdminPermission('viewLogs');
    }

    public function actionIndex()
    {
        $page = $this->filterPage();
        $perPage = 50;

        /** @var \xenMade\AED\Repository\AEDLog $aedLogRepo */
        $aedLogRepo = $this->repository('xenMade\AED:AEDLog');

        $aedLogs = $aedLogRepo->findLogsForList()
            ->limitByPage($page, $perPage);

        $viewParams = [
            'entries' => $aedLogs->fetch(),

            'page' => $page,
            'perPage' => $perPage,
            'total' => $aedLogs->total()
        ];

        return $this->view('xenMade\AED:LogView', 'aed_log_list', $viewParams);
    }

    public function actionClear()
    {
        if ($this->isPost())
        {
            $this->repository('xenMade\AED:AEDLog')->clearLog();

            return $this->redirect($this->buildLink('logs/aed-logs'));
        }
        else
        {
            return $this->view('xenMade\AED:LogClear', 'aed_log_clear');
        }
    }
}