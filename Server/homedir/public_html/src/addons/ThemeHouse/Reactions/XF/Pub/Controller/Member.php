<?php

namespace ThemeHouse\Reactions\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Member extends XFCP_Member
{
    /**
     * @param ParameterBag $params
     * @return \XF\Mvc\Reply\View
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionReactions(ParameterBag $params)
    {
        $reactionId = $this->filter('reaction_id', 'uint');
        $type = strtolower($this->filter('type', 'string'));
        $user = $this->assertViewableUser($params->user_id);

        /** @var \XF\Mvc\Entity\Finder $reactedContentFinder */
        $reactedContentFinder = $this->finder('ThemeHouse\Reactions:ReactedContent');
        if ($type == 'given') {
            $reactedContentFinder->where('react_user_id', '=', $user->user_id);
        } elseif ($type == 'received') {
            $reactedContentFinder->where('content_user_id', '=', $user->user_id);
        } else {
            $reactedContentFinder->whereOr([
                'content_user_id', '=', $user->user_id
            ],[
                'react_user_id', '=', $user->user_id
            ]);
        }

        $filters = [];

        if ($reactionId) {
            $filters['reaction_id'] = $reactionId;
        }
        if ($type) {
            $filters['type'] = $type;
        }

        $reaction = false;
        if ($reactionId) {
            /** @var \ThemeHouse\Reactions\Repository\Reaction $reactionRepo */
            $reactionRepo = $this->repository('ThemeHouse\Reactions:Reaction');

            $reaction = $reactionRepo->getReactionById($reactionId);
            if (!$reaction) {
                return $this->notFound();
            }

            $reactedContentFinder->where('reaction_id', '=', $reactionId);
        }

        $page = $this->filterPage();
        $perPage = 20;

        $reactedContentFinder->limitByPage($page, $perPage);
        $reactedContent = $reactedContentFinder->fetch();


        $viewParams = [
            'user' => $user,
            'type' => $type,
            'reaction' => $reaction,

            'reactedContent' => $reactedContent,

            'page' => $page,
            'perPage' => $perPage,
            'total' => $reactedContentFinder->total(),

            'filters' => $filters,
        ];

        return $this->view('ThemeHouse\Reactions:Member\Reactions', 'threact_member_reactions', $viewParams);
    }

    /**
     * @param ParameterBag $params
     * @return mixed
     * @throws \XF\Mvc\Reply\Exception
     */
    public function actionReactionStats(ParameterBag $params) {
        $user = $this->assertViewableUser($params->user_id);

        /** @noinspection PhpUndefinedMethodInspection */
        $reactionCounts = $this->repository('ThemeHouse\Reactions:UserReactionCount')->getUserReactionCounts($user->user_id);

        $viewParams = [
            'user' => $user,
            'reactionCounts' => $reactionCounts,
        ];

        return $this->view('ThemeHouse\Reactions:Member\ReactionStats', 'threactions_member_react_stats', $viewParams);
    }
}