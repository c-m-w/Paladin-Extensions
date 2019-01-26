<?php

namespace Siropu\ReferralContests\Widget;

class ReferralLink extends \XF\Widget\AbstractWidget
{
     protected $defaultOptions = [
          'currentPageLink' => true,
          'invitationsSent' => false
	];

	public function render()
	{
          $options = \XF::options();
          $visitor = \XF::visitor();

		if ($options->siropuReferralContestsReferralLinkWidget
               && !$options->siropuReferralContestsInvitationOnly
               && $visitor->hasPermission('siropuReferralContests', 'refer'))
		{
			return $this->renderer('siropu_referral_contests_referral_link_widget', [
				'title' => $this->getTitle() ?: \XF::phrase('siropu_referral_contests_referral_link')
			]);
		}
	}
     public function verifyOptions(\XF\Http\Request $request, array &$options, &$error = null)
	{
		$options = $request->filter([
			'currentPageLink' => 'bool',
               'invitationsSent' => 'bool'
		]);

		return true;
	}
}
