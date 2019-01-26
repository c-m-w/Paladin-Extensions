<?php

namespace ThemeHouse\Reactions\Job;

use XF\Job\AbstractRebuildJob;

class RemoveUnassociatedReactions extends AbstractRebuildJob
{
    protected $defaultData = [
        'type' => null,
        'ids' => null,
    ];

    protected function getNextIds($start, $batch)
    {
        $db = $this->app->db();

        return $db->fetchAllColumn($db->limit("
            SELECT react_id
            FROM xf_th_reacted_content
            WHERE react_id > ?
            ORDER BY react_id
            ", $batch
        ), array(
            $start,
        ));
    }

    protected function rebuildById($id)
    {
        /** @var \ThemeHouse\Reactions\Entity\ReactedContent $react */
        $react = $this->app->em()->find('ThemeHouse\Reactions:ReactedContent', $id);
        if (!$react->Content) {
            \XF::app()->db()->delete('xf_th_reacted_content', 'react_id = ' . \XF::app()->db()->quote($react->react_id));
        }
    }

    protected function getStatusType()
    {
        return \XF::phrase('th_content_react_count_reactions');
    }
}