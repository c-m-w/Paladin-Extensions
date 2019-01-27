<?php

namespace Andy\Trader\XF\Cron;

class Trader
{
	public static function runTrader()
	{	
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Results limit
		$resultsLimit = $options->traderResultsLimit;
		
		// get db
		$db = \XF::db();
		
		// run query
		$db->query("
		UPDATE xf_user SET
			andy_trader_seller_count = ?
			WHERE andy_trader_seller_count > ?
		", array(0,0));
		
		// run query
		$results = $db->fetchAll("
		SELECT seller_id, 
		COUNT(*) AS sellerCount
		FROM xf_andy_trader
		WHERE buyer_comment <> ''
		GROUP BY seller_id
		");

		// update xf_user
		foreach ($results as $k => $v)
		{
			// run query
			$db->query("
			UPDATE xf_user SET
				andy_trader_seller_count = ?
				WHERE user_id = ?
			", array($v['sellerCount'],$v['seller_id']));
		}
		
		// run query
		$db->query("
		UPDATE xf_user SET
			andy_trader_buyer_count = ?
			WHERE andy_trader_buyer_count > ?
		", array(0,0));
		
		// run query
		$results = $db->fetchAll("
		SELECT buyer_id, 
		COUNT(*) AS buyerCount
		FROM xf_andy_trader
		WHERE seller_comment <> ''
		GROUP BY buyer_id
		");

		// update xf_user
		foreach ($results as $k => $v)
		{
			// run query
			$db->query("
			UPDATE xf_user SET
				andy_trader_buyer_count = ?
				WHERE user_id = ?
			", array($v['buyerCount'],$v['buyer_id']));
		}
	}
}