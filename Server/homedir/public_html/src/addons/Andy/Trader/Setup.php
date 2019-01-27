<?php

namespace Andy\Trader;

use XF\AddOn\AbstractSetup;

class Setup extends AbstractSetup
{
	public function install(array $stepParams = [])
	{
		$this->query("
			CREATE TABLE xf_andy_trader (
			trader_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
			timestamp INT(10) UNSIGNED NOT NULL,
			rating INT(10) UNSIGNED NOT NULL,
			seller_id INT(10) UNSIGNED NOT NULL,
			buyer_id INT(10) UNSIGNED NOT NULL,
			seller_comment TEXT NOT NULL,
			buyer_comment TEXT NOT NULL,
			PRIMARY KEY (trader_id)
			) ENGINE = InnoDB CHARACTER SET utf8 COLLATE utf8_general_ci
		");
		
		$this->query(
			"ALTER TABLE xf_user
				ADD andy_trader_seller_count INT(10) UNSIGNED NOT NULL DEFAULT 0
		");
		
		$this->query(
			"ALTER TABLE xf_user
				ADD andy_trader_buyer_count INT(10) UNSIGNED NOT NULL DEFAULT 0
		");
	}

	public function upgrade(array $stepParams = [])
	{
		// TODO: Implement upgrade() method.
	}

	public function uninstall(array $stepParams = [])
	{
		$this->query("
			DROP TABLE xf_andy_trader
		");
		
		$this->query(
			"ALTER TABLE xf_user
				DROP andy_trader_seller_count
		");
		
		$this->query(
			"ALTER TABLE xf_user
				DROP andy_trader_buyer_count
		");
	}
}