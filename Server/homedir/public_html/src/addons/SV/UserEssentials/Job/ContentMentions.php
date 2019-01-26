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
class ContentMentions extends AbstractRebuildJob
{
    /**
     * @var array
     */
    protected $defaultData = [
        'type' => null,
        'batch' => 1000,
    ];

    /**
     * @param int $start
     * @param int $batch
     *
     * @return array
     */
    protected function getNextIds($start, $batch)
    {
        $contentType = $this->data['type'];
        if (!$contentType)
        {
            return null;
        }
        $entity = $this->app->getContentTypeEntity($contentType);
        $structure = $this->app->em()->getEntityStructure($entity);

        $db = $this->app->db();
        $table = $structure->table;
        $primaryKey = $structure->primaryKey;

        return $db->fetchAllColumn($db->limit(
            "SELECT {$primaryKey}
                FROM {$table}
                WHERE {$primaryKey} > ?
                ORDER BY {$primaryKey}",
            $batch
        ), $start);
    }

    /**
     * @param int $id
     */
    protected function rebuildById($id)
    {
        try {
            /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
            $mentionsRepo = $this->app->repository(
                'SV\UserEssentials:ContentMentions'
            );
            $contentType = $this->data['type'];
            $mentionsRepo->rebuildContentMentions($contentType, $id);
        } catch (\Exception $e) {
            $this->app->jobManager()->cancelJob(['job_id' => $this->getJobId()]);
            throw $e;
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
