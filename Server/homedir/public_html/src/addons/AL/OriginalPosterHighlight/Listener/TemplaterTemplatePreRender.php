<?php

namespace AL\OriginalPosterHighlight\Listener;

class TemplaterTemplatePreRender
{

    public static function public_thread_view(\XF\Template\Templater $templater, &$type, &$template, array &$params)
    {
        self::_setupStyleParams($params);
    }

    public static function public_thread_new_posts(\XF\Template\Templater $templater, &$type, &$template, array &$params)
    {
        self::_setupStyleParams($params);
    }

    protected static function _setupStyleParams(&$params)
    {
        $params['originalPosterActive'] = true;

        $styleId = $params['xf']['style']['style_id'];

        $checkedStyle = \XF::options()->offsetGet('aloph_disable_per_style');

        if (in_array($styleId, $checkedStyle)) {
            $params['originalPosterRibbonEnabled'] = false;
        } else {
            $params['originalPosterRibbonEnabled'] = true;
        }
    }
}

