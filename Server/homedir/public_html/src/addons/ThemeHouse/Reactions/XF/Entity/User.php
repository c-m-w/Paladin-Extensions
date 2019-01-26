<?php

namespace ThemeHouse\Reactions\XF\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * Class User
 * @package ThemeHouse\Reactions\XF\Entity
 */
class User extends XFCP_User
{
    protected function _postDelete()
    {
        $this->app()
            ->jobManager()
            ->enqueueUnique(
                "pruneReactCache-{$this->user_id}",
                'ThemeHouse\Reactions:DeleteUserReactions',
                ['userId' => $this->user_id]
            );

        return parent::_postDelete();
    }

    public function getReactTotalCount()
    {
        if ($this->react_count) {
            $total = 0;
            foreach ($this->react_count as $reactionTypeId => $reactCount) {
                $total = $total + $reactCount;
            }

            return $total;
        }

        return 0;
    }
}