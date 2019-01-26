<?php

namespace NF\GiftUpgrades\Stats;

use XF\Stats\AbstractHandler;

class GiftUpgrade extends AbstractHandler
{
    public function getStatsTypes()
    {
        return [
            'nixfifty_gift_upgrade' => \XF::phrase('nixfifty_giftupgrades_gift_upgrade'),
        ];
    }

    public function getData($start, $end)
    {
        $db = $this->db();

        $giftUpgrades = $db->fetchPairs(
            $this->getBasicDataQuery('xf_nixfifty_gift_upgrade_statistics', 'stat_date'),
            [$start, $end]
        );

        return [
            'nixfifty_gift_upgrade' => $giftUpgrades,
        ];
    }
}