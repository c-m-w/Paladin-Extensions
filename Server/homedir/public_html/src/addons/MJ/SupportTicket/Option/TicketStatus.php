<?php

namespace MJ\SupportTicket\Option;

class TicketStatus extends \XF\Option\AbstractOption
{
	public static function renderSelect(\XF\Entity\Option $option, array $htmlParams)
	{
		$data = self::getSelectData($option, $htmlParams);

		return self::getTemplater()->formSelectRow(
			$data['controlOptions'],
			$data['choices'],
			$data['rowOptions']
		);
	}

	protected static function getSelectData(\XF\Entity\Option $option, array $htmlParams)
	{
		/** @var \MJ\SupportTicket\Repository\TicketStatus $ticketStatusRepo */
		$ticketStatusRepo = \XF::repository('MJ\SupportTicket:TicketStatus');

		foreach ($ticketStatusRepo->findTicketStatusForList()->fetch() as $status)
		{
			$choices[$status->ticket_status_id] = $status->title;
		}

		$choices = self::convertChoicesToTemplaterForm($choices);

		return [
			'choices' => $choices,
			'controlOptions' => self::getControlOptions($option, $htmlParams),
			'rowOptions' => self::getRowOptions($option, $htmlParams)
		];
	}
}
