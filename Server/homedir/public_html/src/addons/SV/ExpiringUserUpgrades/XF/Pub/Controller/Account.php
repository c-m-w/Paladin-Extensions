<?php

namespace SV\ExpiringUserUpgrades\XF\Pub\Controller;

/**
 * Class Account
 *
 * @package SV\ExpiringUserUpgrades\
 */
class Account extends XFCP_Account
{
    /**
     * @return \XF\Mvc\Reply\Redirect|\XF\Mvc\Reply\View
     */
    public function actionPreferences()
    {
        $response = parent::actionPreferences();

        if ($response instanceof \XF\Mvc\Reply\View)
        {
            /** @var \SV\ExpiringUserUpgrades\XF\Entity\User $visitor */
            $visitor = \XF::visitor();
            $response->setParam('showSVExUpEmailPreferences', $visitor->canChangeSVExUpEmailPreferences());
        }

        return $response;
    }

    /**
     * @param \XF\Entity\User|\SV\ExpiringUserUpgrades\XF\Entity\User $visitor
     * @return \XF\Mvc\FormAction
     */
    protected function preferencesSaveProcess(\XF\Entity\User $visitor)
    {
        $formAction = parent::preferencesSaveProcess($visitor);

        if ($visitor->canChangeSVExUpEmailPreferences())
        {
            $input = $this->filter([
                'option' => [
                    'sv_exup_email_on_expiring_expired_upgrade' => 'bool',
                    'sv_exup_email_on_upgrade_purchase'         => 'bool',
                    'sv_exup_email_on_upgrade_reversal'         => 'bool'
                ]
            ]);

            $userOptions = $visitor->getRelationOrDefault('Option');
            $formAction->setupEntityInput($userOptions, $input['option']);
            $formAction->saveEntity($userOptions);
        }

        return $formAction;
    }
}