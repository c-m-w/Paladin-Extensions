<?php

namespace ThemeHouse\Bookmarks\Listener;

use XF\Mvc\Entity\Entity;

class EntityStructure
{
    protected static function bookmarkRelation(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {

        $visitor = \XF::visitor();
        $structure->relations['Bookmark'] = [
            'type' => Entity::TO_ONE,
            'entity' => 'ThemeHouse\Bookmarks:Bookmark',
            'conditions' => [
                ['content_type', '=', $structure->contentType],
                ['content_id', '=', '$' . $structure->primaryKey],
                ['user_id', '=', $visitor->user_id],
            ],
        ];
    }

    public static function xfPost(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
        self::bookmarkRelation($em, $structure);
    }

    public static function xfThread(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
        self::bookmarkRelation($em, $structure);
    }

    public static function xfNode(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
        $structure->contentType = 'node';

        self::bookmarkRelation($em, $structure);
    }

    public static function xfrmResourceItem(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
        self::bookmarkRelation($em, $structure);
    }

    public static function xfmgMediaItem(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
        self::bookmarkRelation($em, $structure);
    }
}