<?php

namespace ThemeHouse\Reactions\Listener;

class Criteria
{
    public static function user($rule, array $data, \XF\Entity\User $user, &$returnValue)
    {
        switch ($rule) {
            case 'threact_min_reactions':
                if ($user->getReactTotalCount() >= $data['reactions']) {
                    $returnValue = true;
                }
                break;

            case 'threact_max_reactions':
                if ($user->getReactTotalCount() <= $data['reactions']) {
                    $returnValue = true;
                }
                break;
        }
    }
}