<?php

namespace ThemeHouse\Reactions\XFRM\Entity;

/**
 * Class ResourceUpdate
 * @package ThemeHouse\Reactions\XFRM\Entity
 */
class ResourceUpdate extends XFCP_ResourceUpdate
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
                        'content_user_id' => $this->Resource->user_id,
                        'reaction_id' => $reactUser['reaction_id']
                    ]);

                    $reacts[] = $react;
                }
            }

            return $reacts;
        }
    }

    public function getUserId()
    {
        return $this->Resource->user_id;
    }
}