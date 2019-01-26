<?php

namespace XR\PM\Payment;

use XF\Payment\CallbackState;
use XF\Payment\PayPal;

class LegacyPayPal extends PayPal
{
	public function validatePurchasableHandler(CallbackState $state)
	{
		$purchasable = \XF::em()->find('XF:Purchasable', 'xr_pm_product');
		$state->purchasableHandler = $purchasable->handler;

		if (!$state->getPurchasableHandler())
		{
			$state->logType = 'error';
			$state->logMessage = 'Could not find handler for purchasable type \'' . $state->getPurchaseRequest()->purchasable_type_id  . '\'.';
			return false;
		}
		return true;
	}

	public function validatePurchaser(CallbackState $state)
	{
		// The custom data in legacy calls is <user_id>,<cart_key>,<validation_type>,<validation>.
		// We only need the user_id and cart_key but we can at least verify it's a familiar format.
		$itemParts = explode(',', $state->requestKey, 4);
		if (count($itemParts) != 4)
		{
			$state->logType = 'error';
			$state->logMessage = 'Invalid item (custom)';
			return false;
		}

		$user = \XF::em()->find('XF:User', $itemParts[0]);
		if (!$user)
		{
			$state->logType = 'error';
			$state->logMessage = 'Could not find user with user_id ' . $itemParts[0] . '.';
			return false;
		}
		$state->purchaser = $user;

		$state->cart = \XF::em()->findOne('XR\PM:Cart', ['cart_key' => $itemParts[1]]);
		if (!$state->cart)
		{
			$state->logType = 'error';
			$state->logMessage = 'Could not find cart with cart_key ' . $itemParts[1] . '.';
			return false;
		}

		// We need to make sure this actually is a legacy transaction
		try
		{
			$db = \XF::db();
			$exists = $db->fetchRow('
				SELECT *
				FROM xf_xr_pm_transaction_log
				WHERE cart_id = ?
				LIMIT 1
			', $state->cart->cart_id);
		}
		catch (\XF\Db\Exception $e)
		{
			$exists = false;
		}
		if (!(bool)$exists)
		{
			$state->logType = 'error';
			$state->logMessage = 'Could not find legacy transaction with cart_id ' . $state->cart->cart_id . '.';
			return false;
		}

		return true;
	}

	public function validateCost(CallbackState $state)
	{
		// We don't provide any subscriptions so there should be little chance of this being called
		// and this will mostly be used to catch refunds/chargebacks so for brevity let's just skip it entirely.
		return true;
	}
}