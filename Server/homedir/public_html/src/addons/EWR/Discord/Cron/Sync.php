<?php

namespace EWR\Discord\Cron;

class Sync
{
	public static function syncDiscord()
	{
		\XF::app()->repository('EWR\Discord:Discord')->syncDiscord();
	}
}