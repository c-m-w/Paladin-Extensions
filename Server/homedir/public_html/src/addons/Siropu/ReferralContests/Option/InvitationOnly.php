<?php

namespace Siropu\ReferralContests\Option;

class InvitationOnly extends \XF\Option\AbstractOption
{
	public static function verifyOption(&$value)
	{
		$invitationUserField = \XF::em()->find('XF:UserField', 'siropu_invitation');

		if ($value)
		{
			$invitationUserField->user_editable = 'once';
			$invitationUserField->required = 1;
			$invitationUserField->show_registration = 1;
		}
		else
		{
			$invitationUserField->user_editable = 'never';
			$invitationUserField->required = 0;
			$invitationUserField->show_registration = 0;
		}

		$invitationUserField->saveIfChanged();

		return true;
	}
}
