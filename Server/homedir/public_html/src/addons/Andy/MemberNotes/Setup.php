<?php

namespace Andy\MemberNotes;

use XF\AddOn\AbstractSetup;

class Setup extends AbstractSetup
{
	public function install(array $stepParams = [])
	{
		$this->query("
			CREATE TABLE xf_andy_member_notes (
			user_id INT(10) UNSIGNED NOT NULL,
			notes TEXT NOT NULL,
			PRIMARY KEY (user_id)
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
			DROP TABLE xf_andy_member_notes
		");
	}
}