<?php

namespace ThemeHouse\Reactions\Entity;

use ThemeHouse\Reactions\React\AbstractHandler;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * Class Reaction
 * @package ThemeHouse\Reactions\Entity
 *
 *
 * @property integer reaction_id
 * @property string title
 * @property string reaction_type_id
 * @property string styling_type
 * @property string reaction_text
 * @property string image_url
 * @property string image_url_2x
 * @property string image_type
 * @property string|array styling
 * @property AbstractHandler|array|string react_handler
 * @property string|array user_criteria
 * @property string|array $options
 * @property integer display_order
 * @property boolean like_wrapper
 * @property boolean random
 * @property boolean enabled
 * @property boolean is_default
 */
class Reaction extends Entity
{
    /**
     * @return array|mixed|null
     * @throws \Exception
     */
    public function getReactHandler()
    {
        if (isset($this->react_handler)) {
            if (in_array('all', $this->react_handler_)) {
                return array_keys($this->getReactHandlerRepo()->getReactHandlersList());
            }

            return $this->react_handler_;
        }
    }

    /**
     * @param $options
     * @param $key
     * @return bool
     * @throws \Exception
     */
    protected function verifyOptions(&$options, $key)
    {
        foreach ($this->getReactHandler() as $reactHandler) {
            $reactHandler = $this->getReactHandlerRepo()->getReactHandlerByType($reactHandler);
            if ($reactHandler) {
                $reactHandler->verifyOptions($this, $options, $error);
                if ($error) {
                    $this->error($error, $key);
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * @param $reactionParams
     * @return bool
     */
    protected function verifyReactionParams(&$reactionParams)
    {
        array_walk($reactionParams, function ($value, $key) {
            if ($key != 'bs') {
                $value = intval($value);
            }

            return $value;
        });

        return true;
    }

    /**
     * @param $criteria
     * @return bool
     */
    protected function verifyUserCriteria(&$criteria)
    {
        $userCriteria = $this->app()->criteria('XF:User', $criteria);
        $criteria = $userCriteria->getCriteria();
        return true;
    }

    /**
     * @param $value
     * @param $key
     * @return bool
     */
    protected function verifyLikeWrapper($value, $key)
    {
        if ($value && \XF::finder('ThemeHouse\Reactions:Reaction')->where([
                'like_wrapper' => 1,
                ['reaction_id', '!=', $this->reaction_id]
            ])->fetch()->count()) {
            $this->error(\XF::phrase('th_only_one_reaction_can_like_wrapper_reactions'), $key);
            return false;
        }

        return true;
    }

    /**
     * @param $value
     * @param $key
     * @return bool
     */
    protected function verifyIsDefault($value, $key)
    {
        if ($value && \XF::Finder('ThemeHouse\Reactions:Reaction')->where([
                'is_default' => 1,
                ['reaction_id', '!=', $this->reaction_id]
            ])->fetch()->count()) {
            $this->error(\XF::phrase('threact_only_one_reaction_can_be_selected_as_the_default'), $key);
            return false;
        }

        return true;
    }

    /**
     * @param $value
     * @param $key
     * @return bool
     */
    protected function verifyRandom($value, $key)
    {
        if ($value && \XF::finder('ThemeHouse\Reactions:Reaction')->limit(5)->fetch()->count() < 3) {
            $this->error(\XF::phrase('th_at_least_x_reactions_needed_for_random_reactions', ['amount' => 3]), $key);
            return false;
        }

        return true;
    }

    protected function _preSave()
    {
        if (!$this->random && empty($this->reaction_type_id)) {
            $this->error(\XF::phrase('th_please_choose_valid_reaction_type_reactions'), 'reaction_type_id');
            return false;
        }

        if ($this->image_type == 'sprite') {
            $this->image_url_2x = '';
        }

        if ($this->styling_type == 'image') {
            if (empty($this->image_url)) {
                $this->error(\XF::phrase('please_enter_valid_url'), 'image_url');
                return false;
            }
        }

        if ($this->styling_type == 'text') {
            if (empty($this->reaction_text)) {
                $this->error(\XF::phrase('th_please_enter_text_for_reaction_reactions'), 'reaction_text');
                return false;
            }
        }

        if ($this->styling_type == 'css_class') {
            if (empty($this->reaction_text)) {
                $this->error(\XF::phrase('th_please_enter_css_class_for_reaction_reactions'), 'reaction_text');
                return false;
            }
        }

        return parent::_preSave();
    }

    protected function _postSave()
    {
        $this->rebuildReactionCache();

        return parent::_postSave();
    }

    protected function _postDelete()
    {
        $this->rebuildReactionCache();

        $this->db()->delete('xf_th_reacted_content',
            'reaction_id = ?', [$this->reaction_id]
        );

        $this->db()->delete('xf_th_reaction_user_count',
            'reaction_id = ?', [$this->reaction_id]
        );

        $this->db()->delete('xf_th_reaction_content_count',
            'reaction_id = ?', [$this->reaction_id]
        );
    }

    protected function rebuildReactionCache()
    {
        $repo = $this->getReactionRepo();

        \XF::runOnce('reactionCache', function () use ($repo) {
            $repo->rebuildReactionCache();
        });
    }

    protected function _setupDefaults()
    {
        $this->like_wrapper = false;

        $this->styling = [
            'text' => ['s' => '22px'],
            'image_normal' => ['w' => 22, 'h' => 22, 'u' => 'px'],
            'image_sprite' => ['w' => 22, 'h' => 22, 'x' => 0, 'y' => 0, 'bs' => '', 'u' => 'px'],
            'css_class' => 'fa fa-fw fa-smile-o',
            'html_css' => [
                'css' => '',
                'html' => ''
            ]
        ];

        $this->options = [
            'alerts' => true,
            'newsfeed' => true,
            'prevent_unreact' => false,
            'user_max_per_day' => 0
        ];
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_th_reaction';
        $structure->shortName = 'ThemeHouse\Reactions:Reaction';
        $structure->primaryKey = 'reaction_id';
        $structure->columns = [
            'reaction_id' => ['type' => self::UINT, 'autoIncrement' => true],
            'title' => [
                'type' => self::STR,
                'maxLength' => 50,
                'required' => 'please_enter_valid_title'
            ],
            'reaction_type_id' => ['type' => self::STR, 'maxLength' => 25, 'match' => 'alphanumeric'],
            'styling_type' => [
                'type' => self::STR,
                'default' => 'image',
                'allowedValues' => [
                    'image',
                    'text',
                    'css_class',
                    'html_css'
                ]
            ],
            'reaction_text' => ['type' => self::STR, 'maxLength' => 10, 'default' => ''],
            'image_url' => ['type' => self::STR, 'maxLength' => 200],
            'image_url_2x' => ['type' => self::STR, 'maxLength' => 200, 'default' => ''],
            'image_type' => ['type' => self::STR, 'maxLength' => 25, 'default' => 'normal'],
            'styling' => ['type' => self::SERIALIZED_ARRAY, 'default' => []],
            'user_criteria' => [
                'type' => self::SERIALIZED_ARRAY,
                'default' => [],
                'verify' => 'verifyUserCriteria'
            ],
            'react_handler' => [
                'type' => self::LIST_COMMA,
                'default' => ['all'],
                'list' => ['type' => 'str', 'unique' => true, 'sort' => SORT_STRING],
            ],
            'options' => [
                'type' => self::SERIALIZED_ARRAY,
                'default' => [],
                'verify' => 'verifyOptions',
            ],
            'display_order' => ['type' => self::UINT, 'default' => 10],
            'like_wrapper' => [
                'type' => self::BOOL,
                'default' => false,
                'verify' => 'verifyLikeWrapper',
            ],
            'random' => [
                'type' => self::BOOL,
                'default' => false,
                'verify' => 'verifyRandom',
            ],
            'enabled' => ['type' => self::BOOL, 'default' => true],
            'is_default' => [
                'type' => self::BOOL,
                'default' => false,
                'verify' => 'verifyIsDefault',
            ],
        ];
        $structure->getters = [
            'react_handler' => true
        ];
        $structure->relations = [
            'ReactionType' => [
                'entity' => 'ThemeHouse\Reactions:ReactionType',
                'type' => self::TO_ONE,
                'conditions' => 'reaction_type_id',
                'primary' => true
            ],
        ];

        return $structure;
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