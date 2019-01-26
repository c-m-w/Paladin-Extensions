<?php

namespace Siropu\ReferralContests\Option;

class ReferrerField extends \XF\Option\AbstractOption
{
	public static function verifyOption(&$value)
	{
		$referrerUserField = \XF::em()->find('XF:UserField', 'siropu_referrer');

		if ($value)
		{
			$referrerUserField->show_registration = 1;
			$referrerUserField->user_editable = 'once';
		}
		else
		{
			$referrerUserField->show_registration = 0;
			$referrerUserField->user_editable = 'never';
		}

		$referrerUserField->saveIfChanged();

		return true;
	}
}
