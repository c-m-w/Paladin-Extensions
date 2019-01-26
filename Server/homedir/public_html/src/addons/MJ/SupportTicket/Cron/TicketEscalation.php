<?php

namespace MJ\SupportTicket\Cron;

/**
 * Cron entry for cleaning up bans.
 */
class TicketEscalation
{
	/**
	 * Deletes expired bans.
	 */
	public static function runEscalations()
	{
		$ticketEscalations = \XF::app()->finder('MJ\SupportTicket:TicketEscalation')
			->with('User')
			->fetch();

		$escalationRepo = \XF::app()->repository('MJ\SupportTicket:TicketEscalation');
		foreach($ticketEscalations as $escalationId => $escalation){
			$updateData = [];
			if($escalation->new_department_id){
				$updateData['department_id'] = $escalation->new_department_id;
			}
			if($escalation->new_priority){
				$updateData['urgency'] = $escalation->new_priority;
			}
			if($escalation->new_ticket_status_id){
				$updateData['ticket_status_id'] = $escalation->new_ticket_status_id;
			}
			if(!$updateData && (!$escalation->reply_message || !$escalation->User->user_id)){
				continue;
			}

			$ticketFinder = \XF::app()->finder('MJ\SupportTicket:Ticket');
			if($escalation->department_ids){
				$ticketFinder->where('department_id', $escalation->department_ids);
			}
			if($escalation->ticket_status_ids){
				$ticketFinder->where('ticket_status_id', $escalation->ticket_status_ids);
			}
			if($escalation->priorities){
				$ticketFinder->where('urgency', $escalation->priorities);
			}
			if($escalation->time_elapsed){
				$ticketFinder->where('last_update', '<=', \XF::$time - ($escalation->time_elapsed * 60));
			}
			$ticketFinder->where('EscalationLog|' . $escalationId . '.escalation_id', '=', null);

			$tickets = $ticketFinder->fetch();
			if(!$tickets->count()){
				continue;
			}
			foreach ($tickets as $ticketId => $ticket) {
				if($escalation->reply_message && $escalation->User->user_id){
					/** @var \XF\Service\Ticket\Replier $replier */
					$replier = \XF::app()->service('MJ\SupportTicket:Ticket\Replier', $ticket, $escalation->User);
					$replier->setIsAutomated();
					$replier->setMessage($escalation->reply_message, false);
					$replier->setUser($escalation->User);

					if ($replier && $replier->validate())
					{
						$message = $replier->save();
					}
				}
				$ticket->bulkSet($updateData);
				$ticket->save();

				$escalationRepo->logEscalationRun($escalationId, $ticketId);
			}
		}
	}

	protected static function setupTicketReply(\MJ\SupportTicket\Entity\Ticket $ticket)
	{
		/** @var \XF\Service\Ticket\Replier $replier */
		$replier = $this->service('MJ\SupportTicket:Ticket\Replier', $ticket);
		$replier->setMessage($message);

		return $replier;
	}
}
