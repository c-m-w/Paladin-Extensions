<?php

namespace Andy\Countdown;

use XF\AddOn\AbstractSetup;

class Setup extends AbstractSetup
{
	public function install(array $stepParams = [])
	{
		$this->query("
			CREATE TABLE xf_andy_countdown (
			coundown_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
			title TEXT NOT NULL,
			link TEXT NOT NULL,
			year INT(10) UNSIGNED NOT NULL,
			month INT(10) UNSIGNED NOT NULL,
			day INT(10) UNSIGNED NOT NULL,
			hour INT(10) UNSIGNED NOT NULL,
			minute INT(10) UNSIGNED NOT NULL,
			active TINYINT(1) UNSIGNED NOT NULL,
			PRIMARY KEY (coundown_id)
			) ENGINE = InnoDB CHARACTER SET utf8 COLLATE utf8_general_ci
		");
	}

	public function upgrade(array $stepParams = [])
	{
		// TODO: Implement upgrade() method.
	}

	public function uninstall(array $stepParams = [])
	{
		$this->query("
			DROP TABLE xf_andy_countdown
		");
	}
}