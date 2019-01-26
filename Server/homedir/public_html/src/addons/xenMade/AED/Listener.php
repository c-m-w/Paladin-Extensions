<?php

namespace xenMade\AED;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Manager;
use XF\Mvc\Entity\Structure;

class Listener
{
    public static function entity_structur(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
    {
    }

    public static function templater_template_pre_render(\XF\Template\Templater $templater, &$type, &$template, array &$params)
    {
        if($template == 'login')
        {
            $params['uuid'] = \XF::generateRandomString(32, false);
        }
    }
}