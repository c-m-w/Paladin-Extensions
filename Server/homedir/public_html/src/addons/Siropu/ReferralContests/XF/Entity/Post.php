<?php

namespace Siropu\ReferralContests\XF\Entity;

class Post extends XFCP_Post
{
     protected function adjustUserMessageCountIfNeeded($amount)
     {
          parent::adjustUserMessageCountIfNeeded($amount);

          $reward       = \XF::options()->siropuReferralContestsReward;
          $minimumPosts = \XF::options()->siropuReferralContestsRewardMinPosts;

          if ($this->user_id
               && !empty($this->Thread->Forum->count_messages)
               && $this->Thread->discussion_state == 'visible'
               && !empty($reward['reward_amount'])
               && !empty($reward['reward_type_id'])
               && $minimumPosts
               && $this->User->siropu_referrer_id
               && !$this->User->siropu_referrer_credit
               && $this->User->message_count + 1 >= $minimumPosts
               && $this->User->SRC_Referrer)
          {
               $rewardType = \XF::em()->find('Siropu\ReferralContests:RewardType', $reward['reward_type_id']);

               if ($rewardType)
               {
                    if ($rewardType->isTrophyPoints())
                    {
                         $referrer = $this->User->SRC_Referrer;
                         $referrer->trophy_points += $reward['reward_amount'];
                         $referrer->save();
                    }
                    else if ($rewardType->isDbTechCredits())
                    {
                         $rewardType->applyDbTechCredits($this->User->SRC_Referrer, $reward['reward_amount']);
                    }

                    $this->User->siropu_referrer_credit = 1;
                    $this->User->save();
               }
          }
     }
}
