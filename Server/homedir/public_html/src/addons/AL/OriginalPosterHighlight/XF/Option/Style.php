<?php

namespace AL\OriginalPosterHighlight\XF\Option;

class Style extends \XF\Option\Style
{


    public static  function renderCheckbox(\XF\Entity\Option $option, array $htmlParams)
    {
        /** @var \XF\Repository\Style $styleRepo */
        $styleRepo = \XF::repository('XF:Style');

        $choices = [];
        if ($option->option_id == 'defaultEmailStyleId')
        {
            $choices[0] = \XF::phrase('use_default_style');
        }
        foreach ($styleRepo->getStyleTree(false)->getFlattened() AS $entry)
        {
            if ($entry['record']->user_selectable)
            {
                $choices[$entry['record']->style_id] = $entry['record']->title;
            }
        }

        return self::getCheckboxRow($option, $htmlParams, $choices);
    }


}