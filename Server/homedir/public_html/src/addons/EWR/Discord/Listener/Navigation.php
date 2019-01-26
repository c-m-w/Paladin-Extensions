<?php

namespace EWR\Discord\Listener;

class Navigation
{
    public static function navigationSetup(\XF\Pub\App $app, array &$navigationFlat, array &$navigationTree)
    {
		if (\XF::options()->EWRdiscord_navtab == 'online' &&
			\XF::visitor()->hasPermission('EWRdiscord', 'viewDiscord'))
		{
			$cache = \XF::app()->simpleCache()->getValue('EWR/Discord', 'discord');
			$navigationTree['EWRdiscord']['counter'] = $cache['online'];
		}
    }
}