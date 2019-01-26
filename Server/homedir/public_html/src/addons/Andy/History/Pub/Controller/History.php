<?php

namespace Andy\History\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class History extends AbstractController
{
    public function actionIndex()
    {
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('history', 'view'))
		{
			return $this->noPermission();
		}
		
		// get userId
		$userId = $visitor['user_id'];
		
		// get dateline
		$dateline = time() - (30 * 86400);		
		
        // get db
        $db = \XF::db();
		
		// run query
		$db->query('
			DELETE FROM xf_andy_history
			WHERE thread_read_date < ?
		', $dateline);
		
		// get limit
		$limit = 50;
	
		// get threads
		$finder = \XF::finder('Andy\History:History');
		$threads = $finder
			->where('user_id', '=', $userId)
			->where('Thread.discussion_state', '=', 'visible')
			->where('Thread.discussion_open', '=', '1')
			->order('thread_read_date', 'DESC')
			->limit($limit)
			->fetch();
		
		// get viewParams
		$viewParams = [
			'threads' => $threads
		];
		
		// send to template	
		return $this->view('Andy\History:Index', 'andy_history', $viewParams);
	}
}		