<?php

namespace Andy\Countdown\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class Countdown extends AbstractController
{
    public function actionAdmin()
    {
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('countdown', 'admin'))
		{
			return $this->noPermission();
		}
		
		// get db
		$db = \XF::db();
		
		// run query
		$value = $db->fetchRow("
		SELECT title,
		link,
		year,
		month,
		day,
		hour,
		minute,
		active
		FROM xf_andy_countdown
		");
		
		// get activeChecked
		if ($value['active'] == 1)
		{
			$activeChecked = 'checked';
		}	
		else
		{
			$activeChecked = '';
		}

		// prepare viewParams
		$viewParams = [
			'title' => $value['title'],
			'link' => $value['link'],
			'year' => $value['year'],
			'month' => $value['month'],
			'day' => $value['day'],
			'hour' => $value['hour'],
			'minute' => $value['minute'],
			'activeChecked' => $activeChecked
		]; 
		
		// send to template	
		return $this->view('Andy\Countdown:Admin', 'andy_countdown_admin', $viewParams);
	}
	
	public function actionSave()
	{
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('countdown', 'admin'))
		{
			return $this->noPermission();
		}
		
		// get title
		$title = $this->filter('title', 'str');
		
		// get link
		$link = $this->filter('link', 'str');
		
		// get year
		$year = $this->filter('year', 'uint');
		
		// get month
		$month = $this->filter('month', 'uint');
		
		// get day
		$day = $this->filter('day', 'uint');
		
		// get hour
		$hour = $this->filter('hour', 'uint');
		
		// get minute
		$minute = $this->filter('minute', 'uint');
		
		// get active
		$active = $this->filter('active', 'uint');
		
		// get db
		$db = \XF::db();
		
		// truncate table
		$db->query('
			TRUNCATE TABLE xf_andy_countdown
		');	

		// insert new row
		$db->query("
			INSERT INTO xf_andy_countdown
				(title, link, year, month, day, hour, minute, active)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?)
		", array($title, $link, $year, $month, $day, $hour, $minute, $active));

		// return redirect
		return $this->redirect($this->buildLink('countdown/admin'));		
	}
}		