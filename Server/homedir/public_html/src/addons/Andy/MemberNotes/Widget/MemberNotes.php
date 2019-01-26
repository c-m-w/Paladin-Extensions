<?php

namespace Andy\MemberNotes\Widget;

use \XF\Widget\AbstractWidget;

class MemberNotes extends AbstractWidget
{
    public function render()
    {
		// get visitor
		$visitor = \XF::visitor();				

		// check for user group permission
		if (!$visitor->hasPermission('memberNotes', 'view'))
		{
			return;
		}
		
		// get user
		$user = $this->contextParams['user'];

		// get userId
		$userId = $user->user_id;
		
		// get db
		$db = \XF::db();
		
		// run query
		$results = $db->fetchAll("
		SELECT user_id,
		notes
		FROM xf_andy_member_notes
		WHERE user_id = ?
		", $userId);

		// prepare viewParams
		$viewParams = [
			'results' => $results,
			'userId' => $userId
		];
		
		// send to widget
		return $this->renderer('andy_membernotes', $viewParams);
    }

	public function getOptionsTemplate()
	{
	   return null;
	}
}