<?php

namespace xenMade\LAU\Repository;

use XF\Mvc\Entity\Repository;
use XF\Mvc\Entity\Finder;

class LauLog extends Repository
{
    /**
     * @return Finder
     */
    public function findLauLogForList()
    {
        return $this->finder('xenMade\LAU:LauLog')
            ->setDefaultOrder('dateline', 'DESC');
    }
}