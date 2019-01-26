<?php

namespace Siropu\ReferralContests\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Account extends XFCP_Account
{
     public function actionReferrals()
     {
          $visitor = \XF::visitor();
		$page    = $this->filterPage();
		$perPage = 20;

          $finder = $this->finder('XF:User')
               ->where('siropu_referrer_id', $visitor->user_id)
               ->order('register_date', 'desc');

		$total = $finder->total();
		$this->assertValidPage($page, $perPage, $total, 'account/referrals');

		$referrals = $finder->limitByPage($page, $perPage)->fetch();

          $viewParams = [
               'referrals' => $referrals,
               'total'     => $total,
               'page'      => $page,
               'perPage'   => $perPage
          ];

          $view = $this->view('XF:Account\Referrals', 'siropu_referral_contests_account_referrals', $viewParams);
          return $this->addAccountWrapperParams($view, 'referrals');
     }
     public function actionReferralTools()
     {
          $finder = $this->getReferralToolRepo()
               ->findToolsForList()
               ->where('enabled', 1);

          $viewParams = [
               'tools' => $finder->fetch()->groupBy('type'),
               'count' => $finder->total()
          ];

          $view = $this->view('XF:Account\ReferralTools', 'siropu_referral_contests_account_referral_tools', $viewParams);
          return $this->addAccountWrapperParams($view, 'referral_tools');
     }
     public function actionReferralToolsPreview(ParameterBag $params)
     {
          $tool = $this->assertReferralToolExists($params->tool_id);

          $viewParams = [
               'tool' => $tool
          ];

          return $this->view('XF:Account\ReferralToolsPreview', 'siropu_referral_contests_referral_tool_preview', $viewParams);
     }
     public function actionReferralToolsGenerate()
     {
          $url = $this->filter('url', 'str');

          if (strpos($url, \XF::options()->boardUrl) === false)
          {
               return $this->message(\XF::phrase('please_enter_valid_url'));
          }

          $urlParameter = \XF::options()->siropuReferralContestsReferralUrlParameter;
          $affiliateUrl = $url . (strpos($url, '?') === false ? '?' : '&') . $urlParameter . '=' . \XF::visitor()->user_id;

          $reply = $this->view();
          $reply->setJsonParams(['affiliateUrl' => $affiliateUrl]);

          return $reply;
     }
     public function actionInvitations(ParameterBag $params)
     {
          $visitor = \XF::visitor();
          $options = \XF::options();

          $sendInvitations     = $visitor->hasPermission('siropuReferralContests', 'sendInvitations');
          $invitationsPerDay   = $visitor->hasPermission('siropuReferralContests', 'invitationsPerDay');
          $invitationsPerMonth = $visitor->hasPermission('siropuReferralContests', 'invitationsPerMonth');

          if ($sendInvitations == 0)
          {
               return $this->noPermission();
          }

          $totalInvitationsSent = -1;

          if ($sendInvitations > 0)
          {
               $totalInvitationsSent = $this->finder('Siropu\ReferralContests:Invitation')
                    ->where('user_id', $visitor->user_id)
                    ->total();
          }

          $invitationsSentPast24h = $invitationsSentThisMonth = -1;
          $timeZone = new \DateTimeZone($options->guestTimeZone);

          if ($invitationsPerDay > 0)
          {
               $dateTime = new \DateTime('today 00:00', $timeZone);

               $invitationsSentPast24h = $this->finder('Siropu\ReferralContests:Invitation')
                    ->where('user_id', $visitor->user_id)
                    ->dateBetween($dateTime->format('U'), \XF::$time)
                    ->total();
          }

          if ($invitationsPerMonth > 0)
          {
               $dateTime = new \DateTime('first day of this month 00:00', $timeZone);

               $invitationsSentThisMonth = $this->finder('Siropu\ReferralContests:Invitation')
                    ->where('user_id', $visitor->user_id)
                    ->dateBetween($dateTime->format('U'), \XF::$time)
                    ->total();
          }

          if ($this->isPost())
          {
               if ($sendInvitations > 0 && $sendInvitations >= $totalInvitationsSent)
               {
                    return $this->message(\XF::phrase('siropu_referral_contests_you_cannot_send_more_than_x_invitations', [
                         'limit' => $sendInvitations
                    ]));
               }

               if ($invitationsPerDay > 0 && $invitationsSentPast24h >= $invitationsPerDay)
               {
                    return $this->message(\XF::phrase('siropu_referral_contests_you_cannot_send_more_than_x_invitations_per_day', [
                         'limit' => $invitationsPerDay
                    ]));
               }

               if ($invitationsPerMonth > 0 && $invitationsSentThisMonth >= $invitationsPerMonth)
               {
                    return $this->message(\XF::phrase('siropu_referral_contests_you_cannot_send_more_than_x_invitations_per_month', [
                         'limit' => $invitationsPerMonth
                    ]));
               }

               if ($visitor->hasPermission('siropuReferralContests', 'createInvitations') && !empty($params['create']))
               {
                    $count       = $this->filter('count', 'uint');
                    $invitations = [];

                    for ($i = 0; $i < $count; $i++)
                    {
                         if ($invitationsPerDay > 0 && ($invitationsSentPast24h + $i) == $invitationsPerDay)
                         {
                              continue;
                         }

                         if ($invitationsPerMonth > 0 && ($invitationsSentThisMonth + $i) == $invitationsPerMonth)
                         {
                              continue;
                         }

                         $invitation = $this->em()->create('Siropu\ReferralContests:Invitation');
                         $invitation->generateCode($i);
                         $invitation->save();

                         $invitations[] = $invitation;
                    }

                    $viewParams = [
                         'invitations' => $invitations
                    ];

                    return $this->view('XF:Account\Invitations', 'siropu_referral_contests_account_invitation_result', $viewParams);
               }
               else
               {
                    $name    = $options->siropuReferralContestsSenderName ?: $this->filter('name', 'str');
                    $emails  = array_filter($this->filter('email', 'array'));
                    $subject = $this->filter('subject', 'str');
                    $message = $this->filter('message', 'str');

                    if (empty($name))
                    {
                         return $this->message(\XF::phrase('please_enter_valid_name'));
                    }

                    if (empty($emails))
                    {
                         return $this->message(\XF::phrase('siropu_referral_contests_please_provide_recipient_email'));
                    }

                    if (empty($subject))
                    {
                         return $this->message(\XF::phrase('siropu_referral_contests_please_provide_valid_subject'));
                    }

                    if (empty($message))
                    {
                         return $this->message(\XF::phrase('siropu_referral_contests_please_provide_valid_message'));
                    }

                    $sent = $i = 0;

                    foreach ($emails as $email)
                    {
                         $i++;

                         if (filter_var($email, FILTER_VALIDATE_EMAIL) && !$this->em()->findOne('XF:User', ['email' => $email]))
                         {
                              if ($invitationsPerDay > 0 && ($invitationsSentPast24h + $sent) == $invitationsPerDay)
     					{
     						continue;
     					}

                              if ($invitationsPerMonth > 0 && ($invitationsSentThisMonth + $sent) == $invitationsPerMonth)
                              {
                                   continue;
                              }

                              $invitation = $this->em()->create('Siropu\ReferralContests:Invitation');
                              $invitation->generateCode($i);
                              $invitation->recipient = $email;
                              $invitation->message = $message;
                              $invitation->save();

                              \XF::app()->mailer()->newMail()
                                   ->setTo($email)
                                   ->setFrom($options->siropuReferralContestsSenderEmail ?: $visitor->email, $name)
               				->setTemplate('siropu_referral_contests_invitation', [
                                        'subject'    => $subject,
                                        'message'    => $message,
                                        'invitation' => $invitation
                                   ])
               				->send();

                              $sent++;

                              if ($sendInvitations == $sent)
                              {
                                   continue;
                              }
                         }
                    }

                    if ($sent)
                    {
                         $phrase = \XF::phrase('siropu_referral_contests_x_invitations_sent', ['count' => $sent]);

                         if ($options->siropuReferralContestsInvitationOnly)
                         {
                              return $this->redirect($this->buildLink('account/invitations/sent'), $phrase);
                         }
                         else
                         {
                              return $this->message($phrase);
                         }
                    }
                    else
                    {
                         return $this->message(\XF::phrase('siropu_referral_contests_no_invitations_sent'));
                    }
               }
          }

          $viewParams = [
               'sendInvitations'          => $sendInvitations,
               'invitationsPerDay'        => $invitationsPerDay,
               'totalInvitationsSent'     => $totalInvitationsSent,
               'invitationsSentPast24h'   => $invitationsSentPast24h,
               'invitationsSentThisMonth' => $invitationsSentThisMonth
          ];

          $view = $this->view('XF:Account\Invitations', 'siropu_referral_contests_account_invitation_send', $viewParams);
          return $this->addAccountWrapperParams($view, 'invitations');
     }
     public function actionInvitationsCreate()
     {
          if (!\XF::visitor()->hasPermission('siropuReferralContests', 'createInvitations'))
          {
               return $this->noPermission();
          }

          if ($this->isPost())
          {
               return $this->rerouteController('XF:Account', 'invitations', ['create' => true]);
          }

          $view = $this->view('XF:Account\Invitations', 'siropu_referral_contests_account_invitation_create');
          return $this->addAccountWrapperParams($view, 'invitations');
     }
     public function actionInvitationsList()
     {
          $page    = $this->filterPage();
          $perPage = 20;

          $finder = $this->finder('Siropu\ReferralContests:Invitation')
               ->where('user_id', \XF::visitor()->user_id)
               ->order('invitation_date', 'desc');

          $total = $finder->total();
          $this->assertValidPage($page, $perPage, $total, 'account/invitations');

          $invitations = $finder->limitByPage($page, $perPage)->fetch();

          $viewParams = [
               'invitations' => $invitations,
               'total'       => $total,
               'page'        => $page,
               'perPage'     => $perPage
          ];

          $view = $this->view('XF:Account\Invitations', 'siropu_referral_contests_account_invitation_list', $viewParams);
          return $this->addAccountWrapperParams($view, 'invitations');
     }
     public function actionInvitationsLink(ParameterBag $params)
     {
          $invitation = $this->assertInvitationExists($params->invitation_code);

          $viewParams = [
               'invitation' => $invitation
          ];

          $view = $this->view('XF:Account\Invitations', 'siropu_referral_contests_invitation_link', $viewParams);
          return $this->addAccountWrapperParams($view, 'invitations');
     }
     public function actionReferralFaq()
     {
          $view = $this->view('XF:Account\ReferralFaq', 'siropu_referral_contests_account_referral_faq');
          return $this->addAccountWrapperParams($view, 'referral_faq');
     }
     public function getReferralToolRepo()
     {
          return $this->repository('Siropu\ReferralContests:Tool');
     }
     protected function assertReferralToolExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Tool', $id, $with, 'siropu_referral_contests_tool_not_found');
     }
     protected function assertInvitationExists($id, $with = null)
     {
          return $this->assertRecordExists('Siropu\ReferralContests:Invitation', $id, $with, 'siropu_referral_contests_invitation_not_found');
     }
}
