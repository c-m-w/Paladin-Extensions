<?php

namespace Siropu\ReferralContests\Widget;

class Contest extends \XF\Widget\AbstractWidget
{
     protected $defaultOptions = [
          'tools' => true
	];

	public function render()
	{
		if (\XF::options()->siropuReferralContestsContestWidget && \XF::visitor()->hasPermission('siropuReferralContests', 'viewContests'))
		{
			$contests = $this->app->repository('Siropu\ReferralContests:Contest')
				->findContestsForPublicDisplay()
				->fetch();

			if ($contests->count())
			{
				return $this->renderer('siropu_referral_contests_contest_widget', [
					'contests' => $contests,
					'title'    => $this->getTitle() ?: \XF::phrase('siropu_referral_contests')
				]);
			}
		}
	}
     public function verifyOptions(\XF\Http\Request $request, array &$options, &$error = null)
	{
		$options = $request->filter([
			'tools' => 'bool'
		]);

		return true;
	}
}
