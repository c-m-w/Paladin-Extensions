<?php

namespace xenMade\LAU\Admin\Controller;

use XF\Mvc\Entity\Finder;
use XF\Mvc\ParameterBag;
use XF\Admin\Controller\AbstractController;

class LauLog extends AbstractController
{
	public function actionIndex()
	{
		$page = $this->filterPage();
		$perPage = 20;

		$lauLogRepo = $this->getLauLogRepo();

		/** @var \xenMade\LAU\Repository\LauLog $lauLogFinder */
		$lauLogFinder = $lauLogRepo->findLauLogForList()
            ->limitByPage($page, $perPage);

		$total = $lauLogFinder->total();

		$this->assertValidPage($page, $perPage, $total, 'laulog');

		$viewParams = [
			'laulogs' => $lauLogFinder->fetch(),
			'page' => $page,
			'perPage' => $perPage,
			'total' => $total,
		];

		return $this->view('xenMade\LAU:List', 'lau_login_list', $viewParams);
	}

	public function actionDelete(ParameterBag $params)
	{
        $laulog = $this->assertLauLogExists($params->log_id);

		if ($this->isPost())
		{
            $laulog->delete();

			return $this->redirect($this->buildLink('laulogs'));
		}
		else
		{
			$viewParams = [
				'laulog' => $laulog
			];

			return $this->view('xenMade\LAU:Delete', 'lau_login_delete', $viewParams);
		}
	}

    public function actionMassDelete()
    {
        $this->assertPostOnly();

        $deletes = $this->filter('delete', 'array-str');

        $lauLogs = $this->em()->findByIds('xenMade\LAU:LauLog', $deletes);
        foreach ($lauLogs AS $lauLog)
        {
            $lauLog->delete();
        }

        return $this->redirect($this->buildLink('laulogs'));
    }

	protected function assertLauLogExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('xenMade\LAU:LauLog', $id, $with, 'requested_log_entry_not_found');
	}

	/**
	 * @return \xenMade\LAU\Repository\LauLog
	 */
	protected function getLauLogRepo()
	{
		return $this->repository('xenMade\LAU:LauLog');
	}
}
