<?php

namespace XR\PM;

use XF\Mvc\Entity\Entity;

class Listener
{
	public static function templaterSetup(\XF\Container $container, \XF\Template\Templater &$templater)
	{
		$class = \XF::extendClass('XR\PM\TemplaterSetup');
		$templaterSetup = new $class();

		$templater->addFunction('xr_pm_thumbnail', [$templaterSetup, 'fnPmThumbnail']);
		$templater->addFunction('xr_pm_currency_data', [$templaterSetup, 'fnPmCurrencyData']);
		$templater->addFilter('xr_pm_currency', [$templaterSetup, 'filterPmCurrency']);
	}

	public static function entityStructure(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
	{
		$structure->columns['xr_pm_receive_update_email'] = ['type' => Entity::BOOL, 'default' => true];
	}

	public static function appSetup(\XF\App $app)
	{
		$container = $app->container();

		$container['customFields.xr_pm_products'] = $app->fromRegistry('xrpmProductFields',
			function(\XF\Container $c) { return $c['em']->getRepository('XR\PM:ProductField')->rebuildFieldCache(); },
			function(array $fields)
			{
				return new \XF\CustomField\DefinitionSet($fields);
			}
		);
	}
}