<?php

namespace Andy\MemberNotes\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class MemberNotes extends AbstractController
{
	public function actionEdit()
	{
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('memberNotes', 'view'))
		{
			return $this->noPermission();
		}
		
		// get userId
		$userId = $this->filter('user_id', 'uint');

		// get db
		$db = \XF::db();		
		
		// run query
		$results = $db->fetchRow("
			SELECT user_id,
			notes 
			FROM xf_andy_member_notes
			WHERE user_id = ?
		", $userId);
		
		// prepare viewParams
		$viewParams = [
			'userId' => $userId,
			'notes' => $results['notes']
		];					

		// send to template
		return $this->view('Andy\MemberNotes:Edit', 'andy_membernotes_edit', $viewParams);
	}
	
	public function actionSave()
	{		
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('memberNotes', 'view'))
		{
			return $this->noPermission();
		}
		
		// get userId
		$userId = $this->filter('user_id', 'uint');
		
		// get notes 
		$notes = $this->filter('notes', 'str');

		// get db
		$db = \XF::db();
		
		// run query
		$results = $db->fetchRow("
			SELECT xf_andy_member_notes.user_id,
			xf_andy_member_notes.notes,
			xf_user.username
			FROM xf_andy_member_notes
			INNER JOIN xf_user ON xf_user.user_id = xf_andy_member_notes.user_id
			WHERE xf_andy_member_notes.user_id = ?
		", $userId);

		if (!empty($results))
		{
			// run query
			$db->query("
				DELETE FROM xf_andy_member_notes
				WHERE user_id = ?
			", $userId);	
		}
		
		// insert notes
		if ($notes != '')
		{
			// run query
			$db->query("
				INSERT INTO xf_andy_member_notes
					(user_id, notes)
				VALUES
					(?, ?)
			", array($userId, $notes));
		}
		
		$member = array(
			'user_id' => $userId,
			'username' => $results['username']
		);

		// return redirect
		return $this->redirect($this->buildLink('members', $member));
	}
}		