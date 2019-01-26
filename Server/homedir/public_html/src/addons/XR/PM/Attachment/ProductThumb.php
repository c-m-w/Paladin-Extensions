<?php

namespace XR\PM\Attachment;

use XF\Attachment\AbstractHandler;
use XF\Entity\Attachment;
use XF\Mvc\Entity\Entity;

class ProductThumb extends AbstractHandler
{
	public function canView(Attachment $attachment, Entity $container, &$error = null)
	{
		// Full size image only visible via Admin CP and thumb
		// will be served on the front end via thumbnail_url
		return \XF::visitor()->hasAdminPermission('xr_pm_products');
	}

	public function canManageAttachments(array $context, &$error = null)
	{
		return \XF::visitor()->hasAdminPermission('xr_pm_products');
	}

	public function onAssociation(Attachment $attachment, Entity $container = null)
	{
		if (!$container)
		{
			return;
		}

		/** @var \XR\PM\Service\Product\Thumbnailer $thumbnailer */
		$thumbnailer = \XF::service('XR\PM:Product\Thumbnailer', $container);
		$thumbnailer->thumbnail();
	}

	public function onAttachmentDelete(Attachment $attachment, Entity $container = null)
	{
		/** @var \XR\PM\Entity\Product $container */
		\XF::fs()->delete($container->getAbstractedThumbnailPath());
		$container->fastUpdate('thumbnail_date', 0);
	}

	public function getConstraints(array $context)
	{
		$constraints = \XF::repository('XF:Attachment')->getDefaultAttachmentConstraints();

		// only one thumb per product allowed
		$constraints['count'] = 1;
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

		return $extraContext;
	}
}