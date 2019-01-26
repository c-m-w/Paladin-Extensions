<?php

namespace SV\TitleEditHistory\XF\Entity;

use SV\TitleEditHistory\Entity\IHistoryTrackedTitle;
use XF\Mvc\Entity\Structure;

/**
 *
 * @property int conversation_last_edit_date
 * @property int conversation_last_edit_user_id
 * @property int conversation_edit_count
 */
class ConversationMaster extends XFCP_ConversationMaster implements IHistoryTrackedTitle
{
    public function getTitleEditKeys()
    {
        return [
            'edit_date' => 'start_date',
            'last_edit_date' => 'conversation_last_edit_date',
            'last_edit_user_id' => 'conversation_last_edit_user_id',
            'edit_count' => 'conversation_edit_count',
            'content_type' => 'conversation',
            'content_id' => 'conversation_id',
            'title' => 'title',
            'editor' => null, // why XF why
        ];
    }

    /**
     * @return int
     */
    public function getTitleEditCount()
    {
        return $this->conversation_edit_count;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canViewTitleHistory(/** @noinspection PhpUnusedParameterInspection */
        &$error = null)
    {
        if (!\XF::visitor()->user_id)
        {
            return false;
        }

        if (!\XF::options()->editHistory['enabled'])
        {
            return false;
        }

        if (\XF::visitor()->hasPermission('conversation', 'editAnyMessage'))
        {
            return true;
        }

        return false;
    }

    /**
     * @param Structure $structure
     * @return Structure
     */
    public static function getStructure(Structure $structure)
    {
        $structure = parent::getStructure($structure);

        $structure->columns['conversation_last_edit_date'] = ['type' => self::UINT, 'default' => 0];
        $structure->columns['conversation_last_edit_user_id'] = ['type' => self::UINT, 'default' => 0];
        $structure->columns['conversation_edit_count'] = ['type' => self::UINT, 'forced' => true, 'default' => 0];

        return $structure;
    }

    /**
     * @param string|null $error
     * @return bool
     */
    public function canEditTitle(&$error = null)
    {
        return $this->canEdit();
    }
}
