<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Job;

use XF\Job\AbstractRebuildJob;

/**
 * Rebuilds content mentions.
 */
class ContentMentionsAll extends AbstractRebuildJob
{
    /**
     * @var array
     */
    protected $defaultData = [
        'types' => null,
        'typeIndex'  => null,
        'batch' => 1000,
        'reset' => null,
        'preload' => false,
    ];

    /**
     * @param int $start
     * @param int $batch
     * @return array
     */
    protected function getNextIds($start, $batch)
    {
        /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
        $mentionsRepo = $this->app->repository('SV\UserEssentials:ContentMentions');
        if ($this->data['types'] === null)
        {
            $this->data['types'] = array_keys($mentionsRepo->getSupportedContentTypes());

        }

        if ($this->data['typeIndex'] === null)
        {
            $this->data['typeIndex'] = 0;
        }

        if ($this->data['typeIndex'] >= count($this->data['types']))
        {
            return null;
        }

        $this->data['type'] = $this->data['types'][$this->data['typeIndex']];
        $entity = $this->app->getContentTypeEntity($this->data['type']);
        $structure = $this->app->em()->getEntityStructure($entity);

        $db = $this->app->db();
        $table = $structure->table;
        $primaryKey = $structure->primaryKey;

        $end = isset($this->data['end']) ? intval($this->data['end']) : 0;
        $endSql = $end ? " AND {$primaryKey} < $end " : '';

        $ids = $db->fetchAllColumn($db->limit(
            "SELECT {$primaryKey}
                FROM {$table}
                WHERE {$primaryKey} > ? {$endSql}
                ORDER BY {$primaryKey}",
            $batch
        ), $start);

        if (!$ids)
        {
            $this->data['typeIndex'] += 1;
            $this->data['start'] = 0;
            $ids = $this->getNextIds($this->data['start'], $batch);
        }
        if (!$ids)
        {
            \XF::registry()->delete('svUserEssMentionRebuild');
            /** @var \XF\Entity\Option $option */
            $option = \XF::em()->find('XF:Option', 'svSendEditedInMentions');
            if ($option && !$option->option_value)
            {
                $option->option_value = true;
                $option->save();
            }
        }

        if ($ids && $this->data['type'] && $this->data['preload'])
        {
            /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
            $mentionsRepo = $this->app->repository('SV\UserEssentials:ContentMentions');
            $contentType = $this->data['type'];
            // preload content to reduce N+1 queries
            \XF::app()->findByContentType($contentType, $ids, $mentionsRepo->getContentTypeWith($contentType));
        }

        return $ids;
    }

    /**
     * @param int $id
     */
    protected function rebuildById($id)
    {
        /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
        $mentionsRepo = $this->app->repository('SV\UserEssentials:ContentMentions');
        $contentType = $this->data['type'];
        $mentionsRepo->rebuildContentMentions($contentType, $id);
    }

    public function run($maxRunTime)
    {
        try
        {
            return parent::run($maxRunTime);
        }
        finally
        {
            // Collaborative Threads can trigger a *lot* of permissions to be loaded
            \XF::app()->container()->decache('permission.cache');
        }
    }

    /**
     * @return string
     */
    protected function getStatusType()
    {
        return \XF::phrase('sv_ue_content_mentions', ['type' => $this->data['type'] ? \XF::app()->getContentTypePhrase($this->data['type']) : 'n/a']);
    }
}
