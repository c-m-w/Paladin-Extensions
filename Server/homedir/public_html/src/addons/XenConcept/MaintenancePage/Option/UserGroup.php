<?php

/*************************************************************************
 * Maintenance Page - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\MaintenancePage\Option;

use XF\Entity\Option;
use XF\Option\AbstractOption;

class UserGroup extends AbstractOption
{


    public static function renderSelectMultiple(Option $option, array $htmlParams)
    {
        $data = self::getSelectData($option, $htmlParams);

        $data['controlOptions']['multiple'] = true;
        $data['controlOptions']['size'] = 8;


        return self::getTemplater()->formSelectRow(
            $data['controlOptions'],
            $data['choices'],
            $data['rowOptions']
        );
    }

    public static function getSelectData(Option $option, array $htmlParams)
    {
        /** @var \XF\Repository\UserGroup $userGroupRepo */
        $userGroupRepo = \XF::repository('XF:UserGroup');

        /**$choices = [0 => [

        '_type' => 'option',
        'value' => 0,
        'label' => ''

        ]];**/

        foreach ($userGroupRepo->findUserGroupsForList()->fetch() AS $group)
        {
            $choices[$group->user_group_id] = [

                '_type' => 'option',
                'value' => $group->user_group_id,
                'label' => $group->title

            ];
        }

        return [

            'choices' => $choices,
            'controlOptions' => self::getControlOptions($option, $htmlParams),
            'rowOptions' => self::getRowOptions($option, $htmlParams)

        ];
    }


}