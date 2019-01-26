<?php

namespace Siropu\ReferralContests;

class Callback
{
	 public static function validateInvitation(\XF\CustomField\Definition $definition, &$value, &$error)
	 {
		 if (\XF::visitor()->user_id)
		 {
			 return $value;
		 }

		 $invitation = \XF::em()->find('Siropu\ReferralContests:Invitation', $value);

		 if (!($invitation && $invitation->isValid()))
		 {
			 $error = \XF::phrase('siropu_referral_contests_please_enter_valid_invitation_code');
			 return false;
		 }

		 return $value;
	 }
	 public static function validateReferrer(\XF\CustomField\Definition $definition, &$value, &$error)
	 {
		 if ($value)
		 {
			 $referrer = \XF::em()->findOne('XF:User', ['username' => $value]);

			 if (!($referrer && $referrer->hasPermission('siropuReferralContests', 'refer')))
			 {
				 $error = \XF::phrase('siropu_referral_contests_please_enter_valid_referrer');
				 return false;
			 }
		 }

		 return $value;
	 }
}
