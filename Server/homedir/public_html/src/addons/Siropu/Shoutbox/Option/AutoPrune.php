<?php

namespace Siropu\Shoutbox\Option;

class AutoPrune extends \XF\Option\AbstractOption
{
	public static function setLastPrune(&$value, \XF\Entity\Option $option)
	{
          $simpleCache = \XF::app()->simpleCache();

          if (!$simpleCache['Siropu/Shoutbox']['lastPrune'])
          {
               $simpleCache['Siropu/Shoutbox']['lastPrune'] = \XF::$time;
          }

          return true;
     }
}
