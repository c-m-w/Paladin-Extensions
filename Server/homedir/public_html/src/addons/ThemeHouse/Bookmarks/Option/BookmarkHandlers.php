<?php

namespace ThemeHouse\Bookmarks\Option;

use XF\Option\AbstractOption;

class BookmarkHandlers extends AbstractOption
{
    public static function renderCheckbox(\XF\Entity\Option $option, array $htmlParams)
    {
        $data = self::getSelectData($option, $htmlParams);
        $data['controlOptions']['multiple'] = true;
        $data['controlOptions']['size'] = 8;
        $data['controlOptions']['listclass'] = 'listColumns';

        return self::getTemplater()->formCheckBoxRow(
            $data['controlOptions'], $data['choices'], $data['rowOptions']
        );
    }

    protected static function getSelectData(\XF\Entity\Option $option, array $htmlParams)
    {
        /** @var \ThemeHouse\Bookmarks\Repository\Bookmark $bookmarkRepo */
        $bookmarkRepo = \XF::repository('ThemeHouse\Bookmarks:Bookmark');

        $handlers = $bookmarkRepo->getBookmarkHandlers();

        $choices = [];
        foreach ($handlers as $contentType => $handler) {
            $phraseKey = \XF::app()->getContentTypePhraseName($contentType);
            $choices[$contentType] = [
                'value' => $contentType,
                'label' => \XF::phrase($phraseKey),
            ];
        }

        return [
            'choices' => $choices,
            'controlOptions' => self::getControlOptions($option, $htmlParams),
            'rowOptions' => self::getRowOptions($option, $htmlParams)
        ];
    }
}