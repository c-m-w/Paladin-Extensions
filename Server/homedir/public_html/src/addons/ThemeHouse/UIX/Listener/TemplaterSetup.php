<?php

namespace ThemeHouse\UIX\Listener;

use ThemeHouse\UIX\Util\UIX;
use XF\Entity\StyleProperty;
use XF\Entity\StylePropertyGroup;
use XF\Template\Templater;

/**
 * Class TemplaterSetup
 * @package ThemeHouse\UIX\Listener
 */
class TemplaterSetup
{
    public static function run(\XF\Container $container, Templater &$templater)
    {
        $templater->addFunction('uix_style_property_prefix',
            ['\ThemeHouse\UIX\Listener\TemplaterSetup', 'fnStylePropertyPrefix']);
        $templater->addFunction('uix_style_property_documentation',
            ['\ThemeHouse\UIX\Listener\TemplaterSetup', 'fnStylePropertyDocumentation']);
        $templater->addFunction('uix_extra_css_urls', ['\ThemeHouse\UIX\Listener\TemplaterSetup', 'fnExtraCssUrls']);
    }

    public static function macroPreRender(
        Templater $templater,
        &$type,
        &$template,
        &$name,
        array &$arguments,
        array &$globalVars
    ) {
        if ($template == 'helper_js_global' && $name == 'body') {
            $uix = new UIX();

            $globalVars['uix_backstretchImages'] = $uix->getBackstretchImages($templater);
        }
    }

    public static function optionMacroPreRender(
        Templater $templater,
        &$type,
        &$template,
        &$name,
        array &$arguments,
        array &$globalVars
    ) {
        if ($arguments['group']->group_id == 'th_uix') {
            $template = 'thuix_options';
        }
    }

    public static function fnStylePropertyPrefix(Templater $templater, &$escape, $entity)
    {
        $key = '';
        if ($entity instanceof StylePropertyGroup) {
            $key = $entity->group_name;
        }
        if ($entity instanceof StyleProperty) {
            $key = $entity->property_name;
        }

        if (strpos($key, 'uix_') === 0) {
            $escape = false;
            return $templater->renderTemplate('admin:th_style_property_prefix_uix');
        }
    }

    public static function fnStylePropertyDocumentation(Templater $templater, &$escape, $entity)
    {
        $propKey = '';
        $groupKey = '';
        $version = '';
        if ($entity instanceof StyleProperty) {
            $style = \XF::app()->style($entity->style_id);

            $propKey = $entity->property_name;
            $groupKey = $entity->group_name;
            $version = urlencode($style->getProperty('uix_version'));
        }

        if (strpos($propKey, 'uix_') === 0) {
            $escape = false;
            $params = [
                'groupKey' => $groupKey,
                'propKey' => $propKey,
                'version' => $version,
            ];
            return $templater->renderTemplate('admin:th_style_property_documentation_uix', $params);
        }
    }

    public static function fnExtraCssUrls(Templater $templater, &$escape, array $cssUrls = [])
    {
        $additionalCss = $templater->getStyle()->getProperty('uix_additionalCss');
        if (!empty($additionalCss)) {
            $additionalCss = explode(',', $templater->getStyle()->getProperty('uix_additionalCss'));
            foreach ($additionalCss as $cssFile) {
                if (strpos($cssFile, 'public:') === false) {
                    $cssUrls[] = 'public:' . $cssFile;
                } else {
                    $cssUrls[] = $cssFile;
                }
            }
        }

        return $cssUrls;
    }
}