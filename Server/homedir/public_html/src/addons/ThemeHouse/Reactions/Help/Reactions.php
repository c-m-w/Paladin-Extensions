<?php

namespace ThemeHouse\Reactions\Help;

use XF\Mvc\Controller;
use XF\Mvc\Reply\View;

class Reactions
{
    public static function renderReactions(Controller $controller, View &$response)
    {
        /** @var \ThemeHouse\Reactions\Repository\Reaction $reactionsRepo */
        $reactionsRepo = $controller->repository('ThemeHouse\Reactions:Reaction');
        $reactions = $reactionsRepo->findReactionsForList()
            ->where('enabled', '=',1)
            ->order('display_order')
            ->fetch()
            ->groupBy('reaction_type_id');


        /** @var \ThemeHouse\Reactions\Repository\ReactionType $reactionTypesRepo */
        $reactionTypesRepo = $controller->repository('ThemeHouse\Reactions:ReactionType');
        $reactionTypes = $reactionTypesRepo->findReactionTypesForList()->fetch();

        $response->setParam('reactions', $reactions);
        $response->setParam('reaction_types', $reactionTypes);
    }
}