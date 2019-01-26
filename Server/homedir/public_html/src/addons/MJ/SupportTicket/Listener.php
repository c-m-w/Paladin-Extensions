<?php

namespace MJ\SupportTicket;

use XF\App;
use XF\Entity\User;
use XF\Service\User\ContentChange;
use XF\Service\User\DeleteCleanUp;
use XF\Service\User\Merge;
use XF\Searcher\User as SearcherUser;
use XF\Template\Templater;
use XF\Container;
use XF\Mvc\Entity\Manager;
use XF\Mvc\Entity\Structure;
use XF\Mvc\Entity\Entity;

class Listener
{
	public static function appSetup(App $app)
	{
		$container = $app->container();

		$container['prefixes.support_ticket'] = $app->fromRegistry(
			'mjstPrefixes',
			function(\XF\Container $c) { return $c['em']->getRepository('MJ\SupportTicket:TicketPrefix')->rebuildPrefixCache();
			}
		);
		$container['mjstStatusStyles'] = $app->fromRegistry(
			'mjstStatusStyles',
			function(\XF\Container $c) { return $c['em']->getRepository('MJ\SupportTicket:TicketStatus')->rebuildStatusStyleCache();
			}
		);
		$container['mjstTicketStatus'] = $app->fromRegistry(
			'mjstTicketStatus',
			function(\XF\Container $c) { return $c['em']->getRepository('MJ\SupportTicket:TicketStatus')->rebuildStatusCache();
			}
		);

		$container['customFields.tickets'] = $app->fromRegistry(
			'mjstTicketFields',
			function(\XF\Container $c) { return $c['em']->getRepository('MJ\SupportTicket:TicketField')->rebuildFieldCache();
			},
			function(array $fields)
			{
				return new \XF\CustomField\DefinitionSet($fields);
			}
		);
	}

	public static function criteriaUser($rule, array $data, User $user, &$returnValue)
	{
		switch ($rule)
		{
			case 'mjst_ticket_count':
				if (isset($user->mjst_ticket_count) && $user->mjst_ticket_count >= $data['tickets'])
				{
					$returnValue = true;
				}
				break;
		}
	}

	public static function templaterMacroPreRender(Templater $templater, &$type, &$template, &$name, array &$arguments, array &$globalVars)
	{
		if ($arguments['group']->group_id == 'mjstSupport')
		{
			$template = 'mjst_option_macros_option_form_block';
		}
	}

	public static function templaterSetup(Container $container, Templater &$templater)
	{
		$templater->addDefaultParam('mjstStatusStyles', $container['mjstStatusStyles']);
	}

	public static function templaterTemplatePreRender(Templater $templater, &$type, &$template, array &$params)
	{
		$container = \XF::app()->container();
		$params['mjstPreReplyEditor'] = isset($container['mjstPreReplyEditor']) ? $container['mjstPreReplyEditor'] : false;
		$params['mjstTicket'] = isset($container['mjstTicket']) ? $container['mjstTicket'] : false;
	}

	public static function userContentChangeInit(ContentChange $changeService, array &$updates)
	{
		$updates['xf_mjst_department_watch']     = ['user_id', 'emptyable' => false];
		$updates['xf_mjst_ticket']               = [
			['user_id', 'username'],
			['last_message_user_id', 'last_message_username'],
			['creator_user_id', 'creator_username'],
		];
		$updates['xf_mjst_ticket_message']       = ['user_id', 'username'];
		$updates['xf_mjst_ticket_watch']         = ['user_id', 'emptyable' => false];
		$updates['xf_mjst_ticket_read']          = ['user_id', 'emptyable' => false];
		$updates['xf_mjst_department_watch']     = ['user_id', 'emptyable' => false];
		$updates['xf_mjst_kb']                   = ['user_id', 'username'];
	}

	public static function userDeleteCleanInit(DeleteCleanUp $deleteService, array &$deletes)
	{
		$deletes['xf_mjst_department_watch'] = 'user_id = ?';
		$deletes['xf_mjst_ticket_read'] = 'user_id = ?';
		$deletes['xf_mjst_ticket_watch'] = 'user_id = ?';
	}

	public static function userMergeCombine(User $target, User $source, Merge $mergeService)
	{
		$target->mjst_ticket_count += $source->mjst_ticket_count;
	}

	public static function userSearcherOrders(SearcherUser $userSearcher, array &$sortOrders)
	{
		$sortOrders['mjst_ticket_count'] = \XF::phrase('mjst_ticket_count');
	}

	public static function visitorGuestSetup(array &$defaultData)
	{
		$defaultData['mjst_department_ids'] = '';
		$defaultData['mjst_ticket_count'] = 0;
	}

	public static function userOptionEntityStructure(Manager $em, Structure &$structure)
	{
		$structure->columns += [
			'disable_email_on_support_ticket' => ['type' => Entity::BOOL, 'default' => 1],
			'email_on_support_ticket' => ['type' => Entity::BOOL, 'default' => 1]
		];
	}
}