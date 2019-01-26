<?php

namespace Andy\EmailLog\XF\Mail;

class Queue extends XFCP_Queue
{
	public function queue(\Swift_Mime_Message $message)
	{
		// get parent		
		$parent = parent::queue($message);
		
		// get emailMessage object
		$emailMessage = $message->getTo();
		
		// get emailDate
		$emailDate = time();
		
		// get emailAddress
		$emailAddress = key($emailMessage);
		
		// get emailSubject
		$emailSubject = $message->getSubject();
		
		$emailSubject = utf8_unhtml($emailSubject, true);
		$emailSubject = preg_replace('/[\xF0-\xF7].../', '', $emailSubject);
		$emailSubject = preg_replace('/[\xF8-\xFB]..../', '', $emailSubject);

		$emailSubject = html_entity_decode($emailSubject, ENT_QUOTES | ENT_HTML5, 'UTF-8');
		$emailSubject = utf8_unhtml($emailSubject);
		$emailSubject = str_replace("\n", ' ', trim($emailSubject));
		$emailSubject = \XF::cleanString($emailSubject);

		if (!strlen($emailSubject))
		{
			return $parent;
		}

		// get db
		$db = \XF::db();
		
		// insert row
		$db->query("
			INSERT INTO xf_andy_email_log
				(email_date, email_address, email_subject)
			VALUES 
				(?,?,?)
		", array($emailDate, $emailAddress, $emailSubject));	
		
		// return parent
		return $parent;
	}
}