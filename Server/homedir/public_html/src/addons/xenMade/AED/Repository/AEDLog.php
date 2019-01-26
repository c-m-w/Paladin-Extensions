<?php

namespace xenMade\AED\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class AEDLog extends Repository
{
	public function findLogsForList()
	{
		return $this->finder('xenMade\AED:AEDLog')
			->setDefaultOrder('login_date', 'DESC');
	}

    public function clearLog()
    {
        $this->db()->emptyTable('xf_xenmade_aed_log');
    }
}