<?php

namespace Andy\History;

use XF\AddOn\AbstractSetup;

class Setup extends AbstractSetup
{
	public function install(array $stepParams = [])
	{
		$this->query("
			CREATE TABLE xf_andy_history (
			history_id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
			user_id INT(10) UNSIGNED NOT NULL, 
			thread_id INT(10) UNSIGNED NOT NULL, 
			thread_read_date INT(10) UNSIGNED NOT NULL
			) ENGINE = InnoDB
		");	
	}
	
	public function upgrade(array $stepParams = [])
	{	
	}

	public function uninstall(array $stepParams = [])
	{
		$this->query("
			DROP TABLE xf_andy_history
		");		
	}
}