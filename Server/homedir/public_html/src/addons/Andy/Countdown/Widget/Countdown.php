<?php

namespace Andy\Countdown\Widget;

use \XF\Widget\AbstractWidget;

class Countdown extends AbstractWidget
{
    public function render()
    {
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
		
		// if not active return null
		if (!$value['active'])
		{
			return null;
		}

		// prepare viewParams variable
		$viewParams = [
			'title' => $value['title'],
			'link' => $value['link'],
			'year' => $value['year'],
			'month' => $value['month'],
			'day' => $value['day'],
			'hour' => $value['hour'],
			'minute' => $value['minute']
		];		
		
		return $this->renderer('andy_countdown', $viewParams);
    }

	public function getOptionsTemplate()
	{
	   return null;
	}
}