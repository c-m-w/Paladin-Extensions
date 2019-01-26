<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property string content_type
 * @property int content_id
 * @property array mention_ids_
 * @property bool has_mentions
 *
 * GETTERS
 * @property array mention_ids
 * @property Entity Content
 */
class ContentMentions extends Entity
{
    /**
     * @var bool
     */
    protected $wasInsert = false;

    /**
     * @return array
     */
    public function getTypes()
    {
        return $this->getMentionsRepo()->getMentionTypes();
    }

    /**
     * @param array|string|null $types
     *
     * @return array
     *
     * @throws \InvalidArgumentException If an invalid mention type is provided
     */
    public function getIds($types = null)
    {
        if ($types === null) {
            return $this->mention_ids;
        }

        if (!is_array($types)) {
            $types = [$types];
        }
        $validTypes = $this->getTypes();

        $ids = [];
        foreach ($types as $type) {
            if (!isset($validTypes[$type])) {
                throw new \InvalidArgumentException(
                    "Invalid mention type: {$type}"
                );
            }

            $ids[] = isset($this->mention_ids[$type])
                ? $this->mention_ids[$type]
                : [];
        }

        return $ids ? array_unique(array_merge(...$ids)) : [];
    }

    /**
     * @return \XF\Mvc\Entity\Entity
     */
    protected function getContent()
    {
        /** @var \SV\UserEssentials\Repository\ContentMentions $mentionsRepo */
        $mentionsRepo = $this->repository('SV\UserEssentials:ContentMentions');
        return $this->app()->findByContentType($this->content_type, $this->content_id, $mentionsRepo->getContentTypeWith($this->content_type));
    }

    /**
     * @param array|string|null $types
     *
     * @return array
     *
     * @throws \InvalidArgumentException If an invalid mention type is provided
     */
    public function getNewIds($types = null)
    {
        $current = $this->mention_ids;
        $content = $this->Content;
        if ($this->wasInsert && $content && $content->isUpdate()) {
            $prior = [];
        } elseif ($this->isChanged('mention_ids')) {
            $prior = $this->getExistingValue('mention_ids');
        } else {
            $prior = $this->getPreviousValue('mention_ids');
        }

        if ($types === null) {
            return array_diff($current, $prior);
        }

        if (!is_array($types)) {
            $types = [$types];
        }
        $validTypes = $this->getTypes();

        $currents = [];
        $priors = [];
        foreach ($types as $type) {
            if (!isset($validTypes[$type])) {
                throw new \InvalidArgumentException(
                    "Invalid mention type: {$type}"
                );
            }

            $currents[] = isset($current[$type]) ? $current[$type] : [];
            $priors[] = isset($prior[$type]) ? $prior[$type] : [];
        }

        $currents = $currents ? array_unique(array_merge(...$currents)) : [];
        $priors = $priors ? array_unique(array_merge(...$priors)) : [];
        return array_diff($currents, $priors);
    }

    /**
     * @param array|string $types
     * @param array $ids
     *
     * @return array
     */
    public function filterNewIds($types, array $ids)
    {
        return array_diff($ids, $this->getIds($types));
    }

    /**
     * @param string            $type
     * @param array             $ids
     * @param array|string|null $uniqueAcrossTypes
     *
     * @throws \InvalidArgumentException If an invalid mention type is provided
     */
    public function addIds($type, array $ids, $uniqueAcrossTypes = null)
    {
        $types = $this->getTypes();
        if (!isset($types[$type])) {
            throw new \InvalidArgumentException("Invalid mention type: {$type}");
        }

        if ($uniqueAcrossTypes) {
            $ids = $this->filterNewIds($uniqueAcrossTypes, $ids);
        }
        if (!$ids) {
            return;
        }

        $mention_ids = $this->mention_ids;
        if (!isset($mention_ids[$type])) {
            $mention_ids[$type] = [];
        }
        $mention_ids[$type] = array_unique(array_merge(
            $mention_ids[$type],
            $ids
        ));
        $this->mention_ids = $mention_ids;
    }

    /**
     * @return array
     */
    public function getMentionIds()
    {
        return $this->mention_ids_ ?: [];
    }

    /**
     * Entity pre-save events.
     */
    protected function _preSave()
    {
        $this->mention_ids = array_filter($this->mention_ids);
        $this->has_mentions = ($this->getIds('m') || $this->getIds('mg')) ? true : false;
    }

    /**
     * Entity post-save events.
     */
    protected function _postSave()
    {
        $this->wasInsert = $this->isInsert();
    }

    /**
     * @param bool|null $saved
     * @param bool      $throw
     * @param bool      $newTransaction
     *
     * @return bool
     */
    public function saveIfMentionsChanged(
        &$saved = null,
        $throw = true,
        $newTransaction = true
    ) {
        if (!$this->isChanged('mention_ids')) {
            $saved = false;
            return true;
        }

        $saved = true;
        return $this->save($throw, $newTransaction);
    }

    /**
     * @param Structure $structure
     *
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_sv_content_mentions';
        $structure->shortName = 'SV\UserEssentials:ContentMentions';
        $structure->primaryKey = ['content_type', 'content_id'];
        $structure->columns = [
            'content_type' => [
                'type'      => self::STR,
                'maxLength' => 25,
                'required'  => true
            ],
            'content_id' => [
                'type'     => self::UINT,
                'required' => true
            ],
            'mention_ids' => [
                'type'     => self::JSON_ARRAY,
                'required' => true
            ],
            'has_mentions' => [
                'type'     => self::BOOL,
                'required' => true

            ]
        ];
        $structure->getters = [
            'mention_ids' => false,
            'Content' => false,
        ];
        $structure->relations = [];

        return $structure;
    }

    /**
     * @return \SV\UserEssentials\Repository\ContentMentions|\XF\Mvc\Entity\Repository
     */
    protected function getMentionsRepo()
    {
        return $this->repository('SV\UserEssentials:ContentMentions');
    }
}
