<?php

namespace ThemeHouse\Reactions\Entity;

use ThemeHouse\Reactions\React\AbstractHandler;
use ThemeHouse\Reactions\XF\Entity\User;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;
use XF\Repository;

/**
 * Class ReactedContent
 * @package ThemeHouse\Reactions\Entity#
 *
 * @property integer react_id
 * @property integer reaction_id
 * @property string content_type
 * @property integer content_id
 * @property integer react_user_id
 * @property integer react_date
 * @property integer content_user_id
 * @property boolean is_counted
 *
 * @property mixed Content
 * @property mixed NewReactCount
 *
 * @property User User
 * @property UserReactionCount UserReactorCount
 * @property UserReactionCount UserReactedCount
 * @property User Owner
 * @property Reaction Reaction
 */
class ReactedContent extends Entity
{
    /**
     * @param null $error
     * @return bool
     * @throws \Exception
     */
    public function canView(&$error = null)
    {
        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content) {
            return $handler->canViewContent($content, $this, $error);
        } else {
            return false;
        }
    }

    /**
     * @param null $error
     * @return bool
     * @throws \Exception
     */
    public function canReact(&$error = null)
    {
        $handler = $this->getHandler();
        $content = $this->Content;

        if ($handler && $content) {
            return $handler->canReactContent($content, $this, $error);
        } else {
            return false;
        }
    }

    /**
     * @param null $error
     * @return bool
     * @throws \Exception
     */
    public function canUnreact(&$error = null)
    {
        $handler = $this->getHandler();
        $content = $this->getContent();

        if ($handler && $content) {
            return $handler->canUnreactContent($content, $this, $error);
        } else {
            return false;
        }
    }

    /**
     * @return AbstractHandler
     * @throws \Exception
     */
    public function getHandler()
    {
        return $this->getReactHandlerRepo()->getReactHandlerByType($this->content_type);
    }

    /**
     * @return null|Entity
     * @throws \Exception
     */
    public function getContent()
    {
        $handler = $this->getHandler();
        return $handler ? $handler->getContent($this->content_id) : null;
    }

    /**
     * @param Entity|null $content
     */
    public function setContent(Entity $content = null)
    {
        $this->_getterCache['Content'] = $content;
    }

    /**
     * @return bool
     */
    public function getNewReactCount()
    {
        if (array_key_exists('NewReactCount', $this->_getterCache)) {
            return $this->_getterCache['NewReactCount'];
        }

        return false;
    }

    /**
     * @param array $newReactCount
     */
    public function setNewReactCount(array $newReactCount = [])
    {
        $this->_getterCache['NewReactCount'] = $newReactCount;
    }

    /**
     * @return bool|string
     * @throws \Exception
     */
    public function render()
    {
        $handler = $this->getHandler();
        return $handler ? $handler->render($this) : '';
    }

    protected function _postSave()
    {
		if ($this->isInsert()) {
			if ($this->is_counted) {
				$this->adjustReactCount($this->react_user_id, $this->content_user_id, $this->reaction_id, $this->content_id, $this->content_type, 1);
			}

			$this->toggleLike();
		} else {
			if ($this->isChanged('content_user_id')) {
				if ($this->getExistingValue('is_counted')) {
					$this->adjustReactCount($this->react_user_id, $this->getExistingValue('content_user_id'), $this->reaction_id, $this->content_id, $this->content_type, -1);
				}
				if ($this->is_counted) {
					$this->adjustReactCount($this->react_user_id, $this->content_user_id, $this->reaction_id, $this->content_id, $this->content_type, 1);
				}
			} else if ($this->isChanged('is_counted')) {
				$this->adjustReactCount($this->react_user_id, $this->content_user_id, $this->reaction_id, $this->content_id, $this->content_type, $this->is_counted ? 1 : -1);
			}
		}

        if ($this->isChanged(['reaction_id', 'content_type', 'content_id', 'content_user_id', 'react_date', 'react_user_id'])) {
            $this->rebuildContentReactCache();
        }
    }

    /**
     * @throws \Exception
     */
    protected function _postDelete()
    {
		if ($this->is_counted) {
			$this->adjustReactCount($this->react_user_id, $this->content_user_id, $this->reaction_id, $this->content_id, $this->content_type, -1);
		}

        $this->rebuildContentReactCache();

        $handler = $this->getHandler();
        if ($handler) {
            $handler->removeReactAlert($this);
            $handler->unpublishReactNewsFeed($this);
        }

        $this->toggleLike(false);
    }

    /**
     * @param bool $isCreate
     * @return bool
     * @throws \XF\PrintableException
     */
    public function toggleLike($isCreate = true)
    {
        if (!$this->Reaction) {
            return false;
        }

        $reaction = $this->Reaction;
        if ($reaction->like_wrapper) {
            /** @var \XF\Repository\LikedContent $likeRepo */
            $likeRepo = $this->repository('XF:LikedContent');

            $existingLike = $likeRepo->getLikeByContentAndLiker($this->content_type, $this->content_id, $this->react_user_id);

            if ($isCreate && !$existingLike && $this->Reactor instanceof \XF\Entity\User) {
                try {
                    $likeRepo->insertLike($this->content_type, $this->content_id, $this->Reactor, false);
                } catch (\Exception $e) {}
            }

            if (!$isCreate && $existingLike) {
                $existingLike->delete(false);
            }
        }
    }

    /**
     * @param $reactorUserId
     * @param $reactedUserId
     * @param $reactionId
     * @param $contentId
     * @param $contentType
     * @param $amount
     */
    protected function adjustReactCount($reactorUserId, $reactedUserId, $reactionId, $contentId, $contentType, $amount)
	{
		if (!$reactorUserId && !$reactedUserId) {
			return;
		}

        $this->adjustUserReactCount($reactionId, $amount);

		$this->db()->query("
            INSERT INTO xf_th_reaction_user_count (user_id, reaction_id, content_type, count_given) VALUES
                (?, ?, ?, 1)
            ON DUPLICATE KEY UPDATE
                count_given = GREATEST(0, count_given + ?)
        ", [
            $reactorUserId, $reactionId, $contentType, $amount,
        ]);

		$this->db()->query("
            INSERT INTO xf_th_reaction_user_count (user_id, reaction_id, content_type, count_received) VALUES
                (?, ?, ?, 1)
            ON DUPLICATE KEY UPDATE
                count_received = GREATEST(0, count_received + ?)
        ", [
            $reactedUserId, $reactionId, $contentType, $amount
        ]);

		$this->db()->query("
		    INSERT INTO xf_th_reaction_content_count (content_id, content_type, reaction_id) VALUES
		        (?, ?, ?)
            ON DUPLICATE KEY UPDATE
                count = GREATEST(0, count + ?)
        ", [
            $contentId, $contentType, $reactionId, $amount
        ]);
	}

    /**
     * @param $reactionId
     * @param $amount
     */
    protected function adjustUserReactCount($reactionId, $amount)
    {
        if (empty($this->Owner)) {
            return;
        }

        $reaction = $this->getReactionRepo()->getReactionById($reactionId);

        if (!$reactCount = $this->getNewReactCount()) {
            $reactCount = $this->Owner->react_count;
        }

        $reactCount[$reaction['reaction_type_id']] = max(0, (isset($reactCount[$reaction['reaction_type_id']]) ? $reactCount[$reaction['reaction_type_id']] : 0) + $amount);
        $this->setNewReactCount($reactCount);

		$this->db()->query("
			UPDATE xf_user
			SET react_count = ?
			WHERE user_id = ?
		", [serialize($reactCount), $this->content_user_id]);
    }

    protected function rebuildContentReactCache()
    {
        $repo = $this->getReactRepo();
        $repo->rebuildContentReactCache($this->content_type, $this->content_id, $this->reaction_id);
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_th_reacted_content';
        $structure->shortName = 'ThemeHouse\Reactions:ReactedContent';
        $structure->primaryKey = 'react_id';
        $structure->columns = [
            'react_id' => ['type' => self::UINT, 'autoIncrement' => true],
            'reaction_id' => ['type' => self::UINT, 'required' => true],
            'content_type' => ['type' => self::STR, 'maxLength' => 25, 'required' => true],
            'content_id' => ['type' => self::UINT, 'required' => true],
            'react_user_id' => ['type' => self::UINT, 'required' => true],
            'react_date' => ['type' => self::UINT, 'default' => \XF::$time],
            'content_user_id' => ['type' => self::UINT, 'required' => true],
            'is_counted' => ['type' => self::BOOL, 'default' => true],
        ];
        $structure->getters = [
            'Content' => true,
            'NewReactCount' => true
        ];
        $structure->relations = [
            'Reactor' => [
                'entity' => 'XF:User',
                'type' => self::TO_ONE,
                'conditions' => [['user_id', '=', '$react_user_id']],
                'primary' => true
            ],
            'UserReactorCount' => [
                'entity' => 'ThemeHouse\Reactions:UserReactionCount',
                'type' => self::TO_ONE,
                'conditions' => [
                    ['user_id', '=', '$react_user_id'],
                    ['reaction_id', '=', '$reaction_id'],
                    ['content_type', '=', '$content_type'],
                ],
                'primary' => true
            ],
            'UserReactedCount' => [
                'entity' => 'ThemeHouse\Reactions:UserReactionCount',
                'type' => self::TO_ONE,
                'conditions' => [
                    ['user_id', '=', '$content_user_id'],
                    ['reaction_id', '=', '$reaction_id'],
                    ['content_type', '=', '$content_type'],
                ],
                'primary' => true
            ],
            'Owner' => [
                'entity' => 'XF:User',
                'type' => self::TO_ONE,
                'conditions' => [['user_id', '=', '$content_user_id']],
                'primary' => true
            ],
            'Reaction' => [
                'entity' => 'ThemeHouse\Reactions:Reaction',
                'type' => self::TO_ONE,
                'conditions' => [['reaction_id', '=', '$reaction_id']],
                'primary' => true
            ],
        ];

        $structure->defaultWith[] = 'Owner';

        return $structure;
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactedContent
     */
    protected function getReactRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->repository('ThemeHouse\Reactions:ReactedContent');
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\Reaction
     */
    protected function getReactionRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->repository('ThemeHouse\Reactions:Reaction');
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactionType
     */
    protected function getReactionTypeRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->repository('ThemeHouse\Reactions:ReactionType');
    }

    /**
     * @return \ThemeHouse\Reactions\Repository\ReactHandler
     */
    protected function getReactHandlerRepo()
    {
        /** @noinspection PhpIncompatibleReturnTypeInspection */
        return $this->repository('ThemeHouse\Reactions:ReactHandler');
    }
}