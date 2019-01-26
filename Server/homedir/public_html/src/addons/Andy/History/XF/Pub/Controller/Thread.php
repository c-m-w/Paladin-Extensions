<?php

namespace Andy\History\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Thread extends XFCP_Thread
{
	public function actionIndex(ParameterBag $params)
	{
		// get parent		
		$parent = parent::actionIndex($params);

        // return parent action if this is a redirect or other non View response 
        if (!$parent instanceof \XF\Mvc\Reply\View)
        {
            return $parent;
        }
		
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('history', 'view'))
		{
			return $parent;
		}
		
		// get userId
		$userId = $visitor['user_id'];
		
		// continue if member is logged in
		if ($userId > 0)
		{
			// get threadId
			$threadId = $params->thread_id;
			
			// get db
			$db = \XF::db();
			
			// run query
			$db->query("
				DELETE FROM xf_andy_history
				WHERE user_id = ?
				AND thread_id = ?
			", array($userId, $threadId));
			
			// define dateline
			$dateline = time();			
			
			// run query
			$db->query("
				INSERT INTO xf_andy_history
					(user_id, thread_id, thread_read_date)
				VALUES
					(?, ?, ?)
			", array($userId, $threadId, $dateline));
		}
		
		// return parent
		return $parent;	
	}
}