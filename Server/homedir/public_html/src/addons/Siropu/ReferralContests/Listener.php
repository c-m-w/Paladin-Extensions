<?php

namespace Siropu\ReferralContests;

use XF\Mvc\Entity\Entity;

class Listener
{
	public static function appComplete(\XF\App $app, \XF\Http\Response &$response)
     {
		$visitor = \XF::visitor();
		$options = \XF::options();
		$request = \XF::app()->request();

		if (!($visitor->user_id || $request->isXhr()))
		{
			$invitationCode = $request->filter($options->siropuReferralContestsInvitationUrlParameter, 'str');

			if ($invitation = self::getValidInvitation($invitationCode))
			{
				$response->setCookie('invitation_code', $invitation->invitation_code);

                    if (!$options->siropuReferralContestsInvitationOnly)
                    {
                         $response->setCookie('referrer_id', $invitation->user_id);
                    }

				self::getReferrerLogRepo()->logHttpReferrer($invitation->user_id);

				if ($options->siropuReferralContestsInvitationPage)
				{
					$response->redirect(\XF::app()->router()->buildLink('invitation', '', ['code' => $invitation->invitation_code]));
				}
			}
			else if ($referrer = self::getValidReferrer(self::getReferrerId()))
			{
				$toolId = $request->filter('tool_id', 'uint');

				if ($toolId && !\XF::app()->request()->getCookie('referrer_id'))
				{
					$tool = \XF::em()->find('Siropu\ReferralContests:Tool', $toolId);

					if ($tool)
					{
						$tool->click_count++;
						$tool->save();
					}
				}

				$response->setCookie('referrer_id', $referrer->user_id);

				self::getReferrerLogRepo()->logHttpReferrer($referrer->user_id);
			}
		}
	}
	public static function templaterSetup(\XF\Container $container, \XF\Template\Templater &$templater)
     {
		$templater->addFunction('siropu_referral_link', function(
			\XF\Template\Templater $templater, &$escape, $type = 'user', \Siropu\ReferralContests\Entity\Tool $tool = null, $pageLink = false)
		{
			$options = \XF::options();
			$visitor = \XF::visitor();
			$userId  = $visitor->user_id;

			if (!$userId)
			{
				return false;
			}

			$referralUrlParameter = $options->siropuReferralContestsReferralUrlParameter;
			$referralUrlPart      = $referralUrlParameter . '=' . $userId;

			$linkParams = [
				$referralUrlParameter => $userId
			];

			$toolParams = [];

			if ($tool)
			{
				$toolParams['tool_id'] = $tool->tool_id;
			}

			$linkParams     += $toolParams;

			$requestUri      = \XF::app()->request()->getFullRequestUri();
			$userReferralUrl = \XF::app()->router()->buildLink('canonical:index', '', $linkParams);
			$pageReferralUrl = self::geneateCustomReferralUrl($requestUri, $linkParams);

			if ($options->siropuReferralContestsProfilePageAsReferralLink)
			{
				$userReferralUrl = \XF::app()->router()->buildLink('canonical:members', $visitor, $toolParams);
			}

			switch ($type)
			{
				case 'user':
					return $userReferralUrl;
					break;
				case 'page':
					return $pageReferralUrl != $userReferralUrl && $pageLink ? $pageReferralUrl : '';
					break;
				case 'tool':
					if ($tool->target_url)
					{
						return self::geneateCustomReferralUrl($tool->target_url, $linkParams);
					}
					return $userReferralUrl;
					break;
			}
		});

		$templater->addFunction('siropu_invitation_code', function(\XF\Template\Templater $templater, &$escape)
		{
			return \XF::app()->request()->getCookie('invitation_code');
		});

		$templater->addFunction('siropu_invitation_message', function(\XF\Template\Templater $templater, &$escape)
		{
               $escape = false;

			if (!\XF::options()->siropuReferralContestsGuestMessage)
			{
				return;
			}

			$params = [];

			if ($invitation = self::getValidInvitation(\XF::app()->request()->getCookie('invitation_code')))
			{
				$params['user'] = $invitation->User;
			}
			else if ($referrer = self::getValidReferrer(self::getParamReferrerId() ?: null))
			{
				$params['user'] = $referrer;
			}

			if (!empty($params))
			{
				return $templater->renderTemplate('public:siropu_referral_contests_guest_message', $params);
			}
		});

          $templater->addFunction('siropu_referrer_username', function(\XF\Template\Templater $templater, &$escape)
		{
               $escape = false;

               if ($referrer = self::getValidReferrer())
			{
				return $referrer->username;
			}
          });

          $templater->addFunction('siropu_referral_invitation_email', function(\XF\Template\Templater $templater, &$escape)
		{
               $escape = false;

               if ($invitation = self::getValidInvitation(\XF::app()->request()->getCookie('invitation_code')))
			{
				return $invitation->recipient;
			}
          });

          $templater->addFilter('siropu_message_placeholders', function(\XF\Template\Templater $templater, $value, &$escape, $invitation)
          {
               $escape = false;
               return str_ireplace(['{username}', '{boardTitle}'], [$invitation->User->username, \XF::options()->boardTitle], $value);
		});

	}
	public static function userEntityStructure(\XF\Mvc\Entity\Manager $em, \XF\Mvc\Entity\Structure &$structure)
     {
		$structure->columns['siropu_referrer_id'] = ['type' => Entity::UINT, 'default' => 0, 'changeLog' => false];
		$structure->columns['siropu_referral_count'] = ['type' => Entity::UINT, 'default' => 0, 'changeLog' => false];
		$structure->columns['siropu_referrer_credit'] = ['type' => Entity::UINT, 'default'  => 0, 'changeLog' => false];

		$structure->relations['SRC_Referrer'] = [
			'entity'     => 'XF:User',
			'type'       => Entity::TO_ONE,
			'conditions' => [['user_id', '=', '$siropu_referrer_id']]
		];

          $structure->relations['SRC_Referrals'] = [
			'entity'     => 'XF:User',
			'type'       => Entity::TO_MANY,
			'conditions' => 'siropu_referrer_id',
               'key'        => 'user_id'
		];
	}
     public static function userEntityPreSave(\XF\Mvc\Entity\Entity $entity)
     {

     }
     public static function userEntityPostSave(\XF\Mvc\Entity\Entity $entity)
     {
          if ($entity->isInsert())
          {
               $referrerId = (int) \XF::app()->request()->getCookie('referrer_id');

               if (\XF::options()->siropuReferralContestsInvitationOnly)
               {
                    $invitationCode = $entity->Profile->custom_fields->siropu_invitation;
               }
               else
               {
                    $invitationCode = \XF::app()->request()->getCookie('invitation_code');
               }

               if ($invitation = self::getValidInvitation($invitationCode))
               {
                    $invitation->registered_user_id = $entity->user_id;
                    $invitation->save();

                    $referrerId = $invitation->user_id;
               }

               if ($referrer = self::getValidReferrer($referrerId ?: $entity->Profile->custom_fields->siropu_referrer))
               {
                    if ($entity->user_state == 'valid')
                    {
                         $userData = [
                             'siropu_referrer_id' => $referrer->user_id
                         ];

                         if (self::rewardReferrer($referrer))
                         {
                              $userData['siropu_referrer_credit'] = 1;
                         }

                         self::updateUserData($userData, $entity->user_id);

                         $action = 'siropu_new_referral';

                         if ($invitation)
                         {
                              $action = 'siropu_new_invitee';
                         }

                         self::alertReferrerAndReset($referrer, $entity, $action);
                    }
                    else
                    {
                         $unconfirmed = \XF::em()->create('Siropu\ReferralContests:Unconfirmed');
                         $unconfirmed->user_id = $entity->user_id;
                         $unconfirmed->referrer_id = $referrer->user_id;
                         $unconfirmed->invitation_code = $invitationCode;
                         $unconfirmed->save();

                         if ($entity->user_state == 'moderated')
                         {
                              $superAdmins = \XF::finder('XF:Admin')
                                   ->where('is_super_admin', 1)
                                   ->fetch();

                              foreach ($superAdmins as $admin)
                              {
                                   \XF::repository('XF:UserAlert')->alert(
                                        $admin->User,
                                        $entity->user_id,
                                        $entity->username,
                                        'user',
                                        $entity->user_id,
                                        'siropu_referral_dupe'
                                   );
                              }
                         }
                    }
               }
          }

           if ($entity->isUpdate()
               && $entity->isChanged('user_state')
               && $entity->user_state == 'valid'
               && $entity->siropu_referrer_id == 0)
		 {
                $unconfirmed = \XF::em()->find('Siropu\ReferralContests:Unconfirmed', $entity->user_id);

                if ($unconfirmed)
                {
                     $userData = [
                          'siropu_referrer_id' => $unconfirmed->referrer_id
                     ];

                     if (self::rewardReferrer($unconfirmed->Referrer))
                     {
                          $userData['siropu_referrer_credit'] = 1;
                     }

                     self::updateUserData($userData, $entity->user_id);

                     $action = 'siropu_new_referral';

                     if ($unconfirmed->Invitation)
                     {
                          $action = 'siropu_new_invitee';
                     }

                     $unconfirmed->delete();

                     self::alertReferrerAndReset($unconfirmed->Referrer, $entity, $action);
                }
		 }
	 }
	 public static function userEntityPostDelete(\XF\Mvc\Entity\Entity $entity)
	 {
		 if ($entity->siropu_referrer_id && $entity->SRC_Referrer)
		 {
			 $referrer = $entity->SRC_Referrer;
			 $referrer->siropu_referral_count--;
			 $referrer->save();
		 }
	 }
	 public static function userMergeCombine(
		 \XF\Entity\User $target, \XF\Entity\User $source, \XF\Service\User\Merge $mergeService
	 )
	 {
		 $target->siropu_referral_count += $source->siropu_referral_count;
	 }
	 public static function userSearcherOrders(\XF\Searcher\User $userSearcher, array &$sortOrders)
	 {
		 $sortOrders = array_replace($sortOrders, [
			 'siropu_referral_count' => \XF::phrase('siropu_referral_contests_referral_count')
		 ]);
	 }
      public static function criteriaUser($rule, array $data, \XF\Entity\User $user, &$returnValue)
      {
		switch ($rule)
		{
			case 'siropu_referral_count':
				if (isset($user->siropu_referral_count) && $user->siropu_referral_count >= $data['referrals'])
				{
					$returnValue = true;
				}
				break;
		}
     }
	protected static function getValidReferrer($referrerId = null)
	{
		 if ($referrerId === null)
		 {
			 $referrerId = (int) \XF::app()->request()->getCookie('referrer_id');
		 }

		 if ($referrerId && is_string($referrerId))
		 {
			 $referrer = \XF::em()->findOne('XF:User', ['username' => $referrerId]);

			 if ($referrer && $referrer->hasPermission('siropuReferralContests', 'refer'))
			 {
				 return $referrer;
			 }
		 }
		 else if (($referrer = \XF::em()->find('XF:User', $referrerId)) && $referrer->hasPermission('siropuReferralContests', 'refer'))
		 {
			 return $referrer;
		 }
	 }
	 protected static function getValidInvitation($invitationCode = null)
	 {
		 if ($invitationCode
		 	&& ($invitation = \XF::em()->find('Siropu\ReferralContests:Invitation', $invitationCode))
			&& $invitation->isValid())
		 {
			 return $invitation;
		 }
	 }
	 protected static function getReferrerId()
	 {
		 $options    = \XF::options();
		 $request    = \XF::app()->request();
		 $referrerId = self::getParamReferrerId();

		 if (!$referrerId && $options->siropuReferralContestsProfilePageAsReferralLink)
		 {
			 $router = \XF::app()->router()->routeToController($request->getRoutePath());

			 if ($router->getController() == 'XF:Member' && !empty($router->getParams()['user_id']))
			 {
				 $referrerId = $router->getParams()['user_id'];
			 }
		 }

		 return (int) $referrerId;
	 }
	 protected static function geneateCustomReferralUrl($url, array $params)
	 {
		 $parts = '';
		 $delim = strpos($url, '?') === false ? '?' : '&';
		 $i     = 0;

		 foreach ($params as $key => $val)
		 {
		      $i++;

		      $parts .= ($i == 1 ? $delim : '&') . "$key=$val";
		 }

		 return $url . $parts;
	}
     protected static function rewardReferrer($referrer)
     {
          $reward       = \XF::options()->siropuReferralContestsReward;
          $minimumPosts = \XF::options()->siropuReferralContestsRewardMinPosts;
          $applyReward  = false;

          if (!empty($reward['reward_amount'])
              && !empty($reward['reward_type_id'])
              && $minimumPosts == 0
              && ($rewardType = \XF::em()->find('Siropu\ReferralContests:RewardType', $reward['reward_type_id'])))
          {
               if ($rewardType->isTrophyPoints())
               {
                    $referrer->trophy_points += $reward['reward_amount'];
               }
               else if ($rewardType->isDbTechCredits())
               {
                    $rewardType->applyDbTechCredits($referrer, $reward['reward_amount']);
               }

               $applyReward = true;
         }

         $referrer->siropu_referral_count++;
         $referrer->save();

         return $applyReward;
     }
     protected static function alertReferrerAndReset($referrer, $referral, $action)
     {
          \XF::repository('XF:UserAlert')->alert(
               $referrer,
               $referral->user_id,
               $referral->username,
               'user',
               $referral->user_id,
               $action
          );

          \XF::app()->response()->setCookie('invitation_code', false);
          \XF::app()->response()->setCookie('referrer_id', false);

          self::getReferrerRepo()->deleteTopReferrersCache();
     }
     protected static function updateUserData(array $userData, $userId)
     {
          \XF::db()->update('xf_user', $userData, 'user_id = ?', $userId);
     }
     protected static function getParamReferrerId()
     {
          return \XF::app()->request()->filter(\XF::options()->siropuReferralContestsReferralUrlParameter, 'uint');
     }
     public static function getReferrerLogRepo()
     {
          return \XF::repository('Siropu\ReferralContests:ReferrerLog');
     }
     public static function getReferrerRepo()
     {
          return \XF::repository('Siropu\ReferralContests:Referrer');
     }
}
