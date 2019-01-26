<?php

/*************************************************************************
 * Maintenance Page - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

namespace XenConcept\MaintenancePage;

use XF\Mvc\Reply\View;
use XF\Pub\Controller\AbstractController;

class Listener
{


    public static function preRender(\XF\Template\Templater $templater, &$type, &$template, &$name, array &$arguments, array &$globalVars)
    {
        if ($arguments['group']->group_id == 'xc_maintenance_page')
        {
            // Override template name
            $template = 'xc_maintenance_page_tabbed_options';
        }
    }

    public static function controllerPostDispatch(\XF\Mvc\Controller $controller, $action, \XF\Mvc\ParameterBag $params, \XF\Mvc\Reply\AbstractReply &$reply)
    {
        if ($controller instanceof AbstractController)
        {
            if (!$reply instanceof View)
            {
                return;
            }

            $userGroupId  = \XF::visitor()->user_group_id;
            $userGroupIds = \XF::options()->xc_maintenance_page_usergroup_exclude;

            if (\XF::$versionId != \XF::options()->currentVersionId)
            {
                $reply->setPageParam('template', 'xc_maintenance_page_container');
                $reply->setTemplateName('xc_maintenance_page_view');
            }

            if (\XF::options()->xc_maintenance_page_enable_maintenance_page && !in_array($userGroupId, $userGroupIds))
            {
                $reply->setPageParam('template', 'xc_maintenance_page_container');
                $reply->setTemplateName('xc_maintenance_page_view');
            }

            return;
        }
    }

    public static function templaterPreRender(\XF\Template\Templater $templater, &$type, &$template, array &$params)
    {

        if (isset($params['groups']['xc_maintenance_page']))
        {
            $template = 'xc_maintenance_page__addon_option_tabbed_macros';
        }
    }



}