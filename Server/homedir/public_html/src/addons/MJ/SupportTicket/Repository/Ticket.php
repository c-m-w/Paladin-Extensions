<?php

namespace MJ\SupportTicket\Repository;

use XF\Mvc\Entity\Finder;
use XF\Mvc\Entity\Repository;

class Ticket extends Repository
{
	public function findTicketsForOverviewList(array $viewableDepartmentIds = null)
	{
		/** @var \MJ\SupportTicket\Finder\Ticket $ticketFinder */
		$ticketFinder = $this->finder('MJ\SupportTicket:Ticket');

		if (is_array($viewableDepartmentIds))
		{
			$ticketFinder->where('department_id', $viewableDepartmentIds);
		}
		else
		{
			$ticketFinder->with('Department.Permissions|' . \XF::visitor()->permission_combination_id);
		}

		$ticketFinder
			->forFullView(true)
			->useDefaultOrder();

		return $ticketFinder;
	}

	public function randomTicketId($length = 8)
	{
		$string = strtoupper(\XF\Util\Random::getRandomString($length+10));
		$string = str_replace(array('-', '_'), array('', ''), $string);
		if(strlen($string) < $length){
			return $this->randomTicketId($length);
		}
		$string = substr($string, 0, $length);
		$existing = $this->em->findOne('MJ\SupportTicket:Ticket', ['ticket_id' => $string]);
		if($existing){
			return $this->randomTicketId($length);
		}
		return $string;
	}

	public function markTicketReadByVisitor(\MJ\SupportTicket\Entity\Ticket $ticket, $newRead = null)
	{
		$visitor = \XF::visitor();
		if (!$visitor->user_id)
		{
			return false;
		}

		if ($newRead === null)
		{
			$newRead = max(\XF::$time, $ticket->last_message_date);
		}

		$cutOff = $this->getReadMarkingCutOff();
		if ($newRead <= $cutOff)
		{
			return false;
		}

		$readDate = $ticket->getVisitorReadDate();
		if ($newRead <= $readDate)
		{
			return false;
		}

		$this->db()->insert('xf_mjst_ticket_read', [
			'support_ticket_id'        => $ticket->support_ticket_id,
			'user_id'                  => $visitor->user_id,
			'support_ticket_read_date' => $newRead
		], false, 'support_ticket_read_date = VALUES(support_ticket_read_date)');

		if ($newRead < $ticket->last_message_date)
		{
			// ticket no fully viewed
			return false;
		}

		return true;
	}

	public function getReadMarkingCutOff()
	{
		return \XF::$time - $this->options()->readMarkingDataLifetime * 86400;
	}

	public function rebuildTicketUserMessageCounters($ticketId)
	{
		$db = $this->db();

		$db->beginTransaction();
		$db->delete('xf_mjst_ticket_user_message', 'support_ticket_id = ?', $ticketId);
		$db->query("
			INSERT INTO xf_mjst_ticket_user_message (support_ticket_id, user_id, message_count)
			SELECT support_ticket_id, user_id, COUNT(*)
			FROM xf_mjst_ticket_message
			WHERE support_ticket_id = ?
				AND message_state = 'visible'
				AND user_id > 0
			GROUP BY user_id
		", $ticketId);
		$db->commit();
	}

	public function rebuildTicketMessagePositions($ticketId)
	{
		$db = $this->db();
		$db->query('SET @position := -1');
		$db->query("
			UPDATE xf_mjst_ticket_message
			SET position = (@position := IF(message_state = 'visible', @position + 1, GREATEST(@position, 0)))
			WHERE support_ticket_id = ?
			ORDER BY message_date
		", $ticketId);
	}

	/**
	 * @param bool|false $unreadOnly
	 *
	 * @return \MJ\SupportTicket\Finder\Ticket
	 */
	public function findTicketsForWatchedList($unreadOnly = false)
	{
		$visitor = \XF::visitor();
		$userId = $visitor->user_id;

		/** @var \MJ\SupportTicket\Finder\Ticket $finder */
		$finder = $this->finder('MJ\SupportTicket:Ticket');
		$finder
			->forFullView(true)
			->with('Watch|' . $userId, true)
			->setDefaultOrder('last_message_date', 'DESC');

		if ($unreadOnly)
		{
			$finder->unreadOnly($userId);
		}

		return $finder;
	}

	public function sendModeratorActionAlert(\MJ\SupportTicket\Entity\Ticket $ticket, $action, $reason = '', array $extra = [])
	{
		if (!$ticket->user_id || !$ticket->User)
		{
			return false;
		}

		$extra = array_merge([
			'title'     => $ticket->title,
			'prefix_id' => $ticket->prefix_id,
			'link'      => $this->app()->router('public')->buildLink('nopath:support-tickets', $ticket),
			'reason'    => $reason
		], $extra);

		/** @var \XF\Repository\UserAlert $alertRepo */
		$alertRepo = $this->repository('XF:UserAlert');
		$alertRepo->alert(
			$ticket->User,
			0, '',
			'user', $ticket->user_id,
			"mjst_ticket_{$action}", $extra
		);

		return true;
	}

	public function getTicketResourceCount($userId)
	{
		return $this->db()->fetchOne("
			SELECT COUNT(*)
			FROM xf_mjst_ticket
			WHERE user_id = ?
		", $userId);
	}

	/**
	 * @param $url
	 * @param null $type
	 * @param null $error
	 *
	 * @return null|\XF\Mvc\Entity\Entity
	 */
	public function getTicketFromUrl($url, $type = null, &$error = null)
	{
		$routePath = $this->app()->request()->getRoutePathFromUrl($url);
		$routeMatch = $this->app()->router($type)->routeToController($routePath);
		$params = $routeMatch->getParameterBag();

		if (!$params->support_ticket_id)
		{
			$error = \XF::phrase('mjst_no_ticket_id_could_be_found_from_that_url');
			return null;
		}

		$ticket = $this->app()->find('MJ\SupportTicket:Ticket', $params->support_ticket_id);
		if (!$ticket)
		{
			$error = \XF::phrase('mjst_no_ticket_could_be_found_with_id_x', ['support_ticket_id' => $params->support_ticket_id]);
			return null;
		}

		return $ticket;
	}
}
