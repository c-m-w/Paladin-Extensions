<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;
use MJ\SupportTicket\Entity\Ticket;

class TicketStatus extends Entity
{
	/**
	 * @return \XF\Phrase
	 */
	public function getTitle()
	{
		return \XF::phrase($this->getPhraseName());
	}

	public function getPhraseName()
	{
		return 'mjst_status.' . $this->ticket_status_id;
	}

	public function isDefault()
	{
		if(in_array($this->ticket_status_id, [
			Ticket::STATUS_OPEN,
			Ticket::STATUS_ANSWERED,
			Ticket::STATUS_CUSREPLY,
			Ticket::STATUS_CLOSED,
			Ticket::STATUS_AWAITING,
		])){
			return true;
		}
		return false;
	}

	public function getMasterPhrase()
	{
		$phrase = $this->MasterTitle;
		if (!$phrase)
		{
			$phrase = $this->_em->create('XF:Phrase');
			$phrase->addon_id = '';
			$phrase->title = $this->_getDeferredValue(function() { return $this->getPhraseName();
			});
			$phrase->language_id = 0;
		}
		return $phrase;
	}

	protected function _postSave()
	{
		$this->rebuildStatusCache();
		if ($this->isChanged('status_color'))
		{
			$this->rebuildStatusStyleCache();
		}
	}

	protected function _preDelete()
	{
		if($this->isDefault()){
			$this->error(\XF::phrase('mjst_you_may_not_delete_important_default_ticket_statuses'), 'ticket_status_id');
		}
	}

	protected function _postDelete()
	{
		/** @var Phrase $phrase */
		$phrase = $this->MasterTitle;
		if ($phrase)
		{
			$phrase->delete();
		}

		$this->rebuildStatusCache();
		$this->rebuildStatusStyleCache();
	}

	protected function rebuildStatusCache()
	{
		$repo = $this->getTicketStatusRepo();

		\XF::runOnce('mjstStatusCacheRebuild', function() use ($repo)
		{
			$repo->rebuildStatusCache();
		});
	}

	protected function rebuildStatusStyleCache()
	{
		$repo = $this->getTicketStatusRepo();

		\XF::runOnce('mjstDisplayStyleCacheRebuild', function() use ($repo)
		{
			$repo->rebuildStatusStyleCache();
		});
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_ticket_status';
		$structure->shortName = 'MJ\SupportTicket:TicketStatus';
		$structure->primaryKey = 'ticket_status_id';
		$structure->columns = [
			'ticket_status_id'    => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'status_color'        => ['type' => self::STR, 'maxLength' => 255, 'default' => ''],
			'group_active'        => ['type' => self::BOOL, 'default' => 0],
			'group_waiting_reply' => ['type' => self::BOOL, 'default' => 0]
		];
		$structure->getters = [
			'title' => true
		];
		$structure->relations = [
			'MasterTitle' => [
				'entity' => 'XF:Phrase',
				'type' => self::TO_ONE,
				'conditions' => [
					['language_id', '=', 0],
					['title', '=', 'mjst_status.', '$ticket_status_id']
				]
			]
		];

		return $structure;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\TicketStatus
	 */
	protected function getTicketStatusRepo()
	{
		return $this->repository('MJ\SupportTicket:TicketStatus');
	}
}
