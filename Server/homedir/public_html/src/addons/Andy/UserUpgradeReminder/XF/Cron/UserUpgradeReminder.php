<?php

namespace Andy\UserUpgradeReminder\XF\Cron;

class UserUpgradeReminder
{
	public static function runUserUpgradeReminder()
	{
		//########################################
		// Email a reminder to all users that
		// have an upgrade about to exire.
		// The cron runs every day at 9:00am
		// and will send email reminders.
		//########################################
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> User upgrade reminder -> Days   
		$days = $options->userUpgradeReminderDays;
		
		// get variables
		$days = $days - 1;
		$startOfDay = strtotime("00:00:00");
		$endOfDay = strtotime("23:59:59");
		$datelineStart = $startOfDay + (86400 * $days);
		$datelineEnd = $endOfDay + (86400 * $days);
		
		//########################################
		// create whereclause of all user upgrades
		// where recurring = 0
		//########################################
		
		// get db
		$db = \XF::db();
		
		// run query
		$data = $db->fetchAllColumn("
		SELECT user_upgrade_id
		FROM xf_user_upgrade
		WHERE recurring = 0
		");	
		
		// declare variable
		$whereclause = '';		

		// create whereclause
		if (!empty($data))
		{
			$whereclause = 'AND (xf_user_upgrade_active.user_upgrade_id = ' . implode(' OR xf_user_upgrade_active.user_upgrade_id = ', $data);
			$whereclause = $whereclause . ')';	
		}
		
		// only continue if we have upgrades which are not recurring
		if ($whereclause != '')
		{
			// run query
			$members = $db->fetchAll("
			SELECT xf_user.user_id,
			xf_user.username
			FROM xf_user
			INNER JOIN xf_user_upgrade_active ON xf_user_upgrade_active.user_id = xf_user.user_id
			WHERE xf_user_upgrade_active.end_date >= ?
			AND xf_user_upgrade_active.end_date <= ?
			$whereclause
			ORDER BY xf_user.username ASC
			", array($datelineStart, $datelineEnd));

			// send emails
			foreach ($members as $member)
			{				
				$mail = \XF::app()->mailer()->newMail();
				
				$user = \XF::app()->find('XF:User', $member['user_id']);
				$mail->setToUser($user);

				$mail->setTemplate('andy_user_upgrade_reminder', [
					'members' => $members
				]);
				
				$mail->queue();
			}
		}
	}
}