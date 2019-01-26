<?php

namespace ThemeHouse\Reactions\Widget;

use XF\Widget\AbstractWidget;

class MemberReactions extends AbstractWidget
{
    public function getTitle()
    {
        return \XF::phrase('th_xs_reactions_reactions', [
            'name' => $this->contextParams['user']->username,
        ]);
    }

    public function render()
    {
        if (empty($this->contextParams['user'])) {
            return '';
        }
        $user = $this->contextParams['user'];
        $reactionCounts = $this->repository('ThemeHouse\Reactions:UserReactionCount')->getUserReactionCounts($user->user_id);

        $viewParams = [
            'reactionCounts' => $reactionCounts,
        ];
        return $this->renderer('th_widget_member_reactions', $viewParams);
    }
}