<?php

namespace MJ\SupportTicket\Attachment;

use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class KnowledgeBase extends \XF\Attachment\AbstractHandler
{
	public function getContainerWith()
	{
		$visitor = \XF::visitor();

		return ['Category'];
	}

	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $container */
		if (!$container->canView())
		{
			return false;
		}

		return true;
	}

	public function canManageAttachments(array $context, &$error = null)
	{
		return true;
	}

	public function onAttachmentDelete(Attachment $attachment, Entity $container = null)
	{
		if (!$container)
		{
			return;
		}

		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $container */
		$container->attach_count--;
		$container->save();
	}

	public function getConstraints(array $context)
	{
		return \XF::repository('XF:Attachment')->getDefaultAttachmentConstraints();
	}

	public function getContainerIdFromContext(array $context)
	{
		return isset($context['kb_id']) ? intval($context['kb_id']) : null;
	}

	public function getContainerLink(Entity $container, array $extraParams = [])
	{
		return \XF::app()->router('public')->buildLink('support-tickets/knowledge-base', $container, $extraParams);
	}

	public function getContext(Entity $entity = null, array $extraContext = [])
	{
		if ($entity instanceof \MJ\SupportTicket\Entity\KnowledgeBase)
		{
			$extraContext['kb_id'] = $entity->kb_id;
		}
		else
		{
			throw new \InvalidArgumentException("Entity must be knowledge base");
		}

		return $extraContext;
	}
}
