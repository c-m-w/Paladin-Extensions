<?php

namespace EWR\Discord\Service\Conversation;

use XF\Service\AbstractService;

class Notifier extends XFCP_Notifier
{
	protected function _sendNotifications(
		$actionType, array $notifyUsers, \XF\Entity\ConversationMessage $message = null, \XF\Entity\User $sender = null
	)
	{
		$parent = parent::_sendNotifications($actionType, $notifyUsers, $message, $sender);
		
		foreach ($notifyUsers AS $user)
		{
			if ($user->user_id != $message->user_id)
			{
				if (!empty($user->ConnectedAccounts['discord']['provider_key']) &&
					empty($user->Option['discord_options']['alert']))
				{
					$phrase = 'EWRdiscord_x_posted_in_conversation_y_'.$actionType;
					$channel = $this->repository('EWR\Discord:Discord')
						->createDMChannel($user->ConnectedAccounts['discord']['provider_key']);
					
					$data = [
						'content' => \XF::phrase($phrase, [
								'user' => $message->username,
								'title' => str_replace('@', '@ð…³', $this->conversation->title),
								'url' => \XF::app()->router('public')->buildLink('canonical:conversations', $this->conversation)
							])->render('raw'),
					];
					
					$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
				}
			}
		}

		return $parent;
	}
}