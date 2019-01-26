<?php

namespace ThemeHouse\Reactions\Listener;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Manager;
use XF\Mvc\Entity\Structure;

/**
 * Class EntityStructure
 * @package ThemeHouse\Reactions\Listener
 */
class EntityStructure
{
    public static function reactEntityHandlers(Manager $em, Structure &$structure)
    {
        /** @noinspection PhpUndefinedMethodInspection */
        if (isset($structure->contentType) && $reactionHandler = \XF::Repository('ThemeHouse\Reactions:ReactHandler')->getReactHandlerByType($structure->contentType)) {
            /** @noinspection PhpUndefinedMethodInspection */
            if ($stateField = $reactionHandler->getStateField()) {
                $structure->behaviors['ThemeHouse\Reactions:Reactable'] = ['stateField' => $stateField];
            }

            $structure->getters['react_users'] = true;

            $structure->columns['react_users'] = ['type' => Entity::SERIALIZED_ARRAY, 'default' => []];

            $structure->relations['Reacts'] = [
                'entity' => 'ThemeHouse\Reactions:ReactedContent',
                'type' => Entity::TO_MANY,
                'conditions' => [
                    ['content_type', '=', $structure->contentType],
                    ['content_id', '=', '$' . $structure->primaryKey]
                ],
                'key' => 'react_user_id',
                'order' => 'react_date'
            ];
        }
    }

    public static function xfPost(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function xfConversationMessage(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function xfProfilePost(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function xfProfilePostComment(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function reactFirstEntity(Manager $em, Structure &$structure)
    {
        $structure->columns['first_react_users'] = [
            'type' => Entity::SERIALIZED_ARRAY,
            'default' => [],
            // since XF has no setters as of writing this, this will do nicely.
            'verify' => function (&$value) {
                $value = $value === null ? [] : $value;
                return true;
            }
        ];
    }

    public static function xfThread(Manager $em, Structure &$structure)
    {
        self::reactFirstEntity($em, $structure);
    }

    public static function xfConversationMaster(Manager $em, Structure &$structure)
    {
        self::reactFirstEntity($em, $structure);
    }

    public static function xfUser(Manager $em, Structure &$structure)
    {
        $structure->columns['react_count'] = ['type' => Entity::SERIALIZED_ARRAY, 'default' => []];
    }

    public static function xfrmResourceUpdate(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
        $structure->getters['user_id'] = true;
    }

    public static function xfmgMediaItem(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function xfmgMediaComment(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }

    public static function xfmgAlbum(Manager $em, Structure &$structure)
    {
        self::reactEntityHandlers($em, $structure);
    }
}