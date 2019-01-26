<?php

namespace ThemeHouse\Reactions\XF\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * Class Post
 * @package ThemeHouse\Reactions\XF\Entity
 *
 * @property array react_users
 */
class Post extends XFCP_Post
{
    public function getReactUsers()
    {
        if ($this->react_users_) {
            $reacts = [];
            foreach ($this->react_users_ as $reactUser) {
                if (array_key_exists($reactUser['reaction_id'], \XF::app()->container('reactions'))) {
                    $react = $this->em()->create('ThemeHouse\Reactions:ReactedContent');
                    $react->bulkSet([
                        'content_id' => $this->getEntityId(),
                        'content_type' => $this->getEntityContentType(),
                        'react_user_id' => $reactUser['user_id'],
                        'content_user_id' => $this->user_id,
                        'reaction_id' => $reactUser['reaction_id']
                    ]);

                    $reacts[] = $react;
                }
            }

            return $reacts;
        }

        return false;
    }

    protected function _postDelete()
    {
        parent::_postDelete();

        /** @var \ThemeHouse\Reactions\Repository\ReactedContent $repo */
        $repo = \XF::app()->repository('ThemeHouse\Reactions:ReactedContent');
        $repo->fastDeleteReacts($this->getEntityContentType(), $this->getEntityId());
    }
}