<?php

namespace Andy\EmailLog\XF\Cron;

class EmailLog
{
	public static function runEmailLog()
	{	
		// create timestamp
		$timestamp = time() - (86400 * 31);		

		// get db
		$db = \XF::db();

		// delete row
		$db->query("
			DELETE FROM xf_andy_email_log
			WHERE email_date < ?
		", $timestamp);
	}
}