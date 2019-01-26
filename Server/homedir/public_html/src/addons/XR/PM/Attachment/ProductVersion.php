<?php

namespace XR\PM\Attachment;

use XF\Attachment\AbstractHandler;
use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class ProductVersion extends AbstractHandler
{
	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		/** @var \XR\PM\Entity\Version $container */
		return $container->canViewVersionFile();
	}

	public function canManageAttachments(array $context, &$error = null)
	{
		return \XF::visitor()->hasAdminPermission('xr_pm_products');
	}

	public function onAttachmentDelete(Attachment $attachment, Entity $container = null)
	{
		return;
	}

	public function getConstraints(array $context)
	{
		$constraints = \XF::repository('XF:Attachment')->getDefaultAttachmentConstraints();

		// only one file per product allowed
		$constraints['count'] = 1;

		return $constraints;
	}

	public function getContainerIdFromContext(array $context)
	{
		return isset($context['product_version_id']) ? intval($context['product_version_id']) : null;
	}

	public function getContainerLink(Entity $container, array $extraParams = [])
	{
		return \XF::app()->router('public')->buildLink('products', $container, $extraParams);
	}

	public function getContext(Entity $entity = null, array $extraContext = [])
	{
		if (isset($entity->product_version_id))
		{
			$extraContext['product_version_id'] = $entity->product_version_id;
		}

		return $extraContext;
	}
}