<?php

namespace Andy\EmailLog;

use XF\AddOn\AbstractSetup;

class Setup extends AbstractSetup
{
	public function install(array $stepParams = [])
	{
		$this->query("
			CREATE TABLE xf_andy_email_log (
			email_log_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
			email_date INT(10) UNSIGNED NOT NULL,
			email_address TEXT NOT NULL,
			email_subject TEXT NOT NULL,
			PRIMARY KEY (email_log_id)
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
			DROP TABLE xf_andy_email_log
		");
	}
}