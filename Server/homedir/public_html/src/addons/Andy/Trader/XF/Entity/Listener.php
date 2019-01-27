<?php

namespace Andy\Trader\XF\Entity;

use XF\Mvc\Entity\Entity;

class Listener
{
	public static function userEntityStructure(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
	{
		$structure->columns['andy_trader_seller_count'] = ['type' => Entity::UINT, 'default' => 0];
		$structure->columns['andy_trader_buyer_count'] = ['type' => Entity::UINT, 'default' => 0];
	}	
}