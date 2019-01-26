<?php

namespace XR\PM\Attachment;

use XF\Attachment\AbstractHandler;
use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class ProductExtra extends AbstractHandler
{
	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		/** @var \XR\PM\Entity\Extra $container */
		return $container->canViewExtraFile();
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

		// only one file per extra allowed
		$constraints['count'] = 1;

		return $constraints;
	}

	public function getContainerIdFromContext(array $context)
	{
		return isset($context['extra_id']) ? intval($context['extra_id']) : null;
	}

	public function getContainerLink(Entity $container, array $extraParams = [])
	{
		return \XF::app()->router('admin')->buildLink('product-manager/products/extras', $container, $extraParams);
	}

	public function getContext(Entity $entity = null, array $extraContext = [])
	{
		if (isset($entity->extra_id))
		{
			$extraContext['extra_id'] = $entity->extra_id;
		}

		return $extraContext;
	}
}