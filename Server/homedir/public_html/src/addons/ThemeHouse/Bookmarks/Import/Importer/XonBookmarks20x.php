<?php

namespace ThemeHouse\Bookmarks\Import\Importer;

class XonBookmarks20x extends XonBookmarks17x
{
    public static function getListInfo()
    {
        return [
            'target' => '[TH] Bookmarks',
            'source' => 'Bookmarks by Xon 2.0.x',
        ];
    }
}