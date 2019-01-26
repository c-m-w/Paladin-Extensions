<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class TicketStatus extends Repository
{
	/**
	 * @return Finder
	 */
	public function findTicketStatusForList()
	{
		return $this->finder('MJ\SupportTicket:TicketStatus');
	}

	public function findTicketStatusList()
	{
		return $this->findTicketStatusForList()->fetch();
	}

	public function getStatusCacheData()
	{
		$entries = $this->finder('MJ\SupportTicket:TicketStatus')
			->order('ticket_status_id')
			->fetch();

		$output = [];
		foreach ($entries as $entry)
		{
			/** @var $entry \XF\Entity\AdminTicketStatus */
			$output[$entry->ticket_status_id] = [
				'ticket_status_id' => $entry->ticket_status_id,
				'status_color' => $entry->status_color,
				'group_active' => $entry->group_active,
				'group_waiting_reply' => $entry->group_waiting_reply,
				'phrase' => $entry->getPhraseName(),
			];
		}

		return $output;
	}

	public function rebuildStatusCache()
	{
		$cache = $this->getStatusCacheData();
		\XF::registry()->set('mjstTicketStatus', $cache);
		return $cache;
	}

	public function getStatusStyleCacheData()
	{
		$data = [];
		foreach ($this->finder('MJ\SupportTicket:TicketStatus')->fetch() as $status)
		{
			$data[$status->ticket_status_id] = $status->status_color;
		}

		return $data;
	}

	public function rebuildStatusStyleCache()
	{
		$cache = $this->getStatusStyleCacheData();
		\XF::registry()->set('mjstStatusStyles', $cache);

		/** @var \XF\Repository\Style $styleRepo */
		$styleRepo = $this->repository('XF:Style');
		$styleRepo->updateAllStylesLastModifiedDate();

		return $cache;
	}

	public function getStatusTypesCache()
	{
		$ticketStatuses = $this->app()->container('mjstTicketStatus');
		$activeIds = [];
		$waitReplyIds = [];
		foreach($ticketStatuses as $statusId => $status){
			if(!empty($status['group_active'])){
				$activeIds[] = $statusId;
			}
			if(!empty($status['group_waiting_reply'])){
				$waitReplyIds[] = $statusId;
			}
		}

		return [$activeIds, $waitReplyIds];
	}
}
