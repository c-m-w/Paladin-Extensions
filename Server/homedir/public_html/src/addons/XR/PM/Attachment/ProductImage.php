<?php

namespace XR\PM\Attachment;

use XF\Attachment\AbstractHandler;
use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class ProductImage extends AbstractHandler
{
	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		/** @var \XR\PM\Entity\Product $container */
		if (!$container->canView())
		{
			return false;
		}

		return $container->canViewProductImages();
	}

	public function canManageAttachments(array $context, &$error = null)
	{
		return \XF::visitor()->hasAdminPermission('xr_pm_products');
	}

	public function onAttachmentDelete(Attachment $attachment, Entity $container = null)
	{
		if (!$container)
		{
			return;
		}

		/** @var \XR\PM\Entity\Product $container */
		$container->attach_count--;
		$container->save();
	}

	public function getConstraints(array $context)
	{
		$constraints = \XF::repository('XF:Attachment')->getDefaultAttachmentConstraints();

		$constraints['extensions'] = ['jpg', 'jpeg', 'jpe', 'png', 'gif'];

		return $constraints;
	}

	public function getContainerIdFromContext(array $context)
	{
		return isset($context['product_id']) ? intval($context['product_id']) : null;
	}

	public function getContainerLink(Entity $container, array $extraParams = [])
	{
		return \XF::app()->router('public')->buildLink('products', $container, $extraParams);
	}

	public function getContext(Entity $entity = null, array $extraContext = [])
	{
		if (isset($entity->product_id))
		{
			$extraContext['product_id'] = $entity->product_id;
		}
		else
		{
			throw new \InvalidArgumentException("Entity must be a product");
		}

		return $extraContext;
	}
}