<?php

/*
 * This file is part of a XenForo add-on.
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace SV\UserEssentials\Entity;

use SV\UserEssentials\XF\Logger;
use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null user_log_id
 * @property int log_date
 * @property int user_id
 * @property string ip_address
 * @property string content_type
 * @property int content_id
 * @property int content_user_id
 * @property string content_username
 * @property string content_title_
 * @property string content_url
 * @property string discussion_content_type
 * @property int discussion_content_id
 * @property string action
 * @property array action_params
 *
 * GETTERS
 * @property string content_title
 * @property \XF\Phrase|string action_text
 *
 * RELATIONS
 * @property \XF\Entity\User User
 * @property \XF\Entity\User ContentUser
 */
class UserLog extends Entity
{
    /**
     * @return string
     */
    public function getContentTitle()
    {
        /** @var Logger $xfLogger */
        $xfLogger = $this->app()->logger();
        $logger = $xfLogger->userLogger();
        if ($logger->isValidContentType($this->content_type))
        {
            return $logger->getContentTitle($this);
        }

        return $this->app()->stringFormatter()->censorText($this->content_title_);
    }

    /**
     * @return \XF\Phrase|string
     */
    public function getActionText()
    {
        /** @var Logger $xfLogger */
        $xfLogger = $this->app()->logger();
        $logger = $xfLogger->userLogger();
        if ($logger->isValidContentType($this->content_type))
        {
            return $logger->getAction($this);
        }
        else
        {
            return "{$this->content_type} {$this->action}";
        }
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure->table = 'xf_sv_user_log';
        $structure->shortName = 'SV\UserEssentials:UserLog';
        $structure->primaryKey = 'user_log_id';
        $structure->columns = [
            'user_log_id'             => [
                'type'          => self::UINT,
                'autoIncrement' => true,
                'nullable'      => true
            ],
            'log_date'                => [
                'type'    => self::UINT,
                'default' => \XF::$time
            ],
            'user_id'                 => [
                'type'     => self::UINT,
                'required' => true
            ],
            'ip_address'              => [
                'type'      => self::BINARY,
                'maxLength' => 16,
                'default'   => ''
            ],
            'content_type'            => [
                'type'      => self::STR,
                'required'  => true,
                'maxLength' => 25
            ],
            'content_id'              => [
                'type'     => self::UINT,
                'required' => true
            ],
            'content_user_id'         => [
                'type'     => self::UINT,
                'required' => true
            ],
            'content_username'        => [
                'type'      => self::STR,
                'required'  => true,
                'maxLength' => 50
            ],
            'content_title'           => [
                'type'      => self::STR,
                'default'   => '',
                'maxLength' => 150
            ],
            'content_url'             => [
                'type'    => self::STR,
                'default' => ''
            ],
            'discussion_content_type' => [
                'type'      => self::STR,
                'required'  => true,
                'maxLength' => 25
            ],
            'discussion_content_id'   => [
                'type'     => self::UINT,
                'required' => true
            ],
            'action'                  => [
                'type'      => self::STR,
                'required'  => true,
                'maxLength' => 25
            ],
            'action_params'           => [
                'type'    => self::JSON_ARRAY,
                'default' => ''
            ]
        ];
        $structure->getters = [
            'content_title' => true,
            'action_text'   => true
        ];
        $structure->relations = [
            'User'        => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => 'user_id',
                'primary'    => true
            ],
            'ContentUser' => [
                'entity'     => 'XF:User',
                'type'       => self::TO_ONE,
                'conditions' => [['user_id', '=', '$content_user_id']],
                'primary'    => true
            ],
        ];

        return $structure;
    }
}
