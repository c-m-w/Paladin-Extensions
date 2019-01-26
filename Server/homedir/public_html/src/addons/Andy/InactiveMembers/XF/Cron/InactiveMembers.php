<?php

namespace Andy\InactiveMembers\XF\Cron;

class InactiveMembers
{
	public static function runInactiveMembers()
	{	
		// calculate dateline
		$dateline = time() - (86400 * 30);	
		
		//########################################
		// exclude forums
		//########################################	
		
		// define variable;
		$whereclause = '';	
		
		// get options
		$options = \XF::options();					
		
		// get options from Admin CP -> Options -> Inactive members -> Exclude forums
		$excludeForums = $options->inactiveMembersExcludeForums;
		
		if (!empty($excludeForums))
		{	
			foreach($excludeForums as $k => $v)
			{
				if (!is_numeric($k))
				{
					unset($excludeForums[$k]);
				}
			}		

			// create whereclause of excluded forums
			$whereclause = 'AND (xf_thread.node_id <> ' . implode(' AND xf_thread.node_id <> ', $excludeForums);
			$whereclause = $whereclause . ')';
		}	
		
		//########################################
		// get threads
		//########################################
		
		// get options from Admin CP -> Options -> Inactive members -> Limit
		$limit = $options->inactiveMembersLimit;
		
		// get options from Admin CP -> Options -> Inactive members -> Sort Forum Titles
		$sortForumTitles = $options->inactiveMembersSortForumTitles;
		
		// get db
		$db = \XF::db();				

		if (!$sortForumTitles)
		{	
			// run query
			$threads = $db->fetchAll("
			SELECT xf_thread.thread_id,
			xf_thread.title,
			xf_thread.username,
			xf_node.title AS forumTitle
			FROM xf_thread
			INNER JOIN xf_node ON xf_node.node_id = xf_thread.node_id
			WHERE xf_thread.post_date > ?
			AND xf_thread.discussion_state = 'visible'
			AND xf_thread.discussion_type <> 'redirect'
			$whereclause
			ORDER BY xf_thread.view_count DESC
			LIMIT ?
			", array($dateline, $limit));	
		}
		
		if ($sortForumTitles)
		{	
			// run query
			$threads = $db->fetchAll("
			SELECT xf_thread.thread_id,
			xf_thread.title,
			xf_thread.username,
			xf_node.title AS forumTitle
			FROM xf_thread
			INNER JOIN xf_node ON xf_node.node_id = xf_thread.node_id
			WHERE xf_thread.post_date > ?
			AND xf_thread.discussion_state = 'visible'
			AND xf_thread.discussion_type <> 'redirect'
			$whereclause
			ORDER BY forumTitle ASC, xf_thread.view_count DESC
			LIMIT ?
			", array($dateline, $limit));	
		}

		// continue only if we have threads
		if (!empty($threads))
		{
			//########################################
			// test userId
			//########################################	
			
			// define variable;
			$userId = '';			
			
			// get options from Admin CP -> Options -> Inactive members -> Test Username
			$testUsername = $options->inactiveMembersTestUsername;
			
			// get userId
			if ($testUsername != '')
			{
				$userId = $db->fetchOne("
				SELECT user_id
				FROM xf_user
				WHERE username = ?
				", $testUsername);
			}
			
			//########################################
			// get members
			//########################################
			
			if ($userId > 0)
			{
				// run query
				$members = $db->fetchAll("
				SELECT xf_user.user_id,
				xf_user.username
				FROM xf_user
				INNER JOIN xf_user_option ON xf_user_option.user_id = xf_user.user_id
				WHERE xf_user.user_id = ?
				", $userId);
			}

			if ($userId == 0)
			{			
				// get options from Admin CP -> Options -> Inactive members -> Minimum days
				$minimumDays = $options->inactiveMembersMinimumDays;
				
				// get options from Admin CP -> Options -> Inactive members -> Maximum days
				$maximumDays = $options->inactiveMembersMaximumDays;
				
				// convert to UNIX timestamp
				$datelineMin = time() - (86400 * $minimumDays);	
				$datelineMax = time() - (86400 * $maximumDays);											
				
				// run query
				$members = $db->fetchAll("
				SELECT xf_user.user_id,
				xf_user.username
				FROM xf_user
				INNER JOIN xf_user_option ON xf_user_option.user_id = xf_user.user_id
				WHERE xf_user.user_state = 'valid'
				AND xf_user.is_banned = 0
				AND xf_user.last_activity < ?
				AND xf_user.last_activity > ?
				AND xf_user_option.receive_admin_email = 1
				AND xf_user_option.is_discouraged = 0
				", array($datelineMin, $datelineMax));
			}

			//########################################
			// send email
			//########################################

			// foreach members
			foreach ($members as $member)
			{				
				$mail = \XF::app()->mailer()->newMail();
				
				$user = \XF::app()->find('XF:User', $member['user_id']);
				$mail->setToUser($user);

				$mail->setTemplate('andy_inactivemembers', [
					'username' => $member['username'],
					'threads' => $threads
				]);
				
				$mail->queue();
			}
		}	
	}
}