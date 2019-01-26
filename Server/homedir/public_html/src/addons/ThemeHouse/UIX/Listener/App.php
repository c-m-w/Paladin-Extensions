<?php

namespace ThemeHouse\UIX\Listener;

use ThemeHouse\UIX\Util\UIX;

class App
{
    public static function pubRenderPage(\XF\Pub\App $app, array &$params, \XF\Mvc\Reply\AbstractReply $reply, \XF\Mvc\Renderer\AbstractRenderer $renderer)
    {
        $visitor = \XF::visitor();
        $templater = $app->templater();
        $style = $templater->getStyle();
        $session = \XF::session();

        $uix = new UIX();

        $params['uix_footerWidgets'] = $uix->getFooterWidgets($templater);
        $params['uix_sidebarNavWidgets'] = $uix->getSidebarNavWidgets($templater);

        if(!isset($params['uix_showWelcomeSection'])) {
            $params['uix_showWelcomeSection'] = $uix->showWelcomeSection($templater, $params['template']);
        }
        else {
            $params['uix_showWelcomeSection'] = $uix->showWelcomeSection($templater, $params['template'], false);
        }
        $params['uix_additionalHtmlClasses'] = $uix->getAdditionalHtmlClasses($templater, $params);

        if ($pageWidth = $uix->getPageWidth($templater)) {
            $params['uix_canTogglePageWidth'] = $pageWidth['canTogglePageWidth'];
            $params['uix_pageWidth'] = $pageWidth['pageWidth'];
        }

        if ($style->getProperty('uix_categoryCollapse') && $visitor->hasPermission('th_uix', 'collapseCategories')) {
            $collapsedCategories = $session->get('th_uix_collapsedCategories');
            if (empty($collapsedCategories)) {
                $collapsedCategories = [];
            }

            $params['uix_canCollapseCategories'] = $visitor->hasPermission('th_uix', 'collapseCategories');
            $params['uix_collapsedCategories'] = $collapsedCategories;
            $params['uix_collapsedCategories'] = json_encode($collapsedCategories);
        }

        if ($style->getProperty('uix_collapsibleSidebar') && $visitor->hasPermission('th_uix', 'collapseSidebar')) {
            $sidebarCollapsed = $session->get('th_uix_sidebarCollapsed');
            if (empty($sidebarCollapsed)) {
                if (isset(\XF::options()->th_sidebarCollapseDefault_uix)) {
                    $sidebarCollapseDefault = \XF::options()->th_sidebarCollapseDefault_uix;
                    if ($visitor->user_id) {
                        $sidebarCollapsed = (in_array($sidebarCollapseDefault, ['unregistered', 'all']));
                    } else {
                        $sidebarCollapsed = (in_array($sidebarCollapseDefault, ['registered', 'all']));
                    }
                } else {
                    $sidebarCollapsed = false;
                }
            }

            $params['uix_canCollapseSidebar'] = $visitor->hasPermission('th_uix', 'collapseSidebar');
            $params['uix_sidebarCollapsed'] = $sidebarCollapsed;
        }

        if ($style->getProperty('uix_navigationType') === 'sidebarNav') {
            $sidebarNavCollapsed = $session->get('th_uix_sidebarNavCollapsed');
            if (empty($sidebarNavCollapsed)) {
                if (isset(\XF::options()->th_sidebarNavCollapseDefault_uix)) {
                    $sidebarNavCollapseDefault = \XF::options()->th_sidebarNavCollapseDefault_uix;
                    if ($visitor->user_id) {
                        $sidebarNavCollapsed = (in_array($sidebarNavCollapseDefault, ['unregistered', 'all']));
                    } else {
                        $sidebarNavCollapsed = (in_array($sidebarNavCollapseDefault, ['registered', 'all']));
                    }
                } else {
                    $sidebarNavCollapsed = false;
                }
            }

            $params['uix_canCollapseSidebarNav'] = true;
            $params['uix_sidebarNavCollapsed'] = $sidebarNavCollapsed;
        }
    }
}
