<?php

namespace Andy\EmailLog\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class EmailLog extends AbstractController
{
    public function actionIndex()
    {
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('emailLog', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();						
		
		// get options from Admin CP -> Options -> Email log -> Limit
		$limit = $options->emailLogLimit;
		
		// get db
		$db = \XF::db();
		
		// run query
		$results = $db->fetchAll("
		SELECT *
		FROM xf_andy_email_log
		ORDER BY email_date DESC
		LIMIT ?
		", $limit);	
		
		// declare variable
		$resultsNew = array();
		
		foreach ($results as $k => $v)
		{
			// run query
			$username = $db->fetchOne("
			SELECT username
			FROM xf_user
			WHERE email = ?
			", $v['email_address']);
			
			// create resultsNew array
			$resultsNew[] = array(
				'email_date' => $v['email_date'],
				'email_username' => $username,
				'email_address' => $v['email_address'],
				'email_subject' => $v['email_subject']
			);			
		}
		
		// rename variable
		$results = $resultsNew;
		
		// prepare viewParams
		$viewParams = [
			'limit' => $limit,
			'results' => $results
		]; 
		
		// send to template	
		return $this->view('Andy\EmailLog:Index', 'andy_emaillog', $viewParams);
	}
}		