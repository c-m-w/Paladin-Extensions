<?php

namespace Siropu\Shoutbox\Cron;

class Shout
{
	public static function deleteOlderShouts()
	{
		if ($days = \XF::options()->siropuShouboxDeleteShoutsOlderThan)
		{
			\XF::app()->repository('Siropu\Shoutbox:Shout')->deleteShoutsOlderThan(strtotime("-$days Days"));
		}
     }
	public static function pruneShouts()
	{
		$app = \XF::app();

		if ($pruneInterval = \XF::options()->siropuShoutboxAutoPrune)
		{
			$simpleCache = $app->simpleCache();
			$lastPrune   = round((\XF::$time - (int) $simpleCache['Siropu/Shoutbox']['lastPrune']) / 3600);

			if ($lastPrune >= $pruneInterval)
			{
				$app->repository('Siropu\Shoutbox:Shout')->prune();
				$simpleCache['Siropu/Shoutbox']['lastPrune'] = \XF::$time;

				if ($message = \XF::options()->siropuShoutboxAutoPruneMessage)
				{
					$shout = $app->em()->create('Siropu\Shoutbox:Shout');
					$shout->shout_user_id = \XF::options()->siropuShoutboxBotUserId ?: 1;
			          $shout->shout_message = $message;
			          $shout->save();
				}
			}
		}
	}
}
