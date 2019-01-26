<?php

namespace XR\PM\Search\Data;

use XF\Mvc\Entity\Entity;
use XF\Search\Data\AbstractData;
use XF\Search\IndexRecord;
use XF\Search\MetadataStructure;

class Version extends AbstractData
{
	public function getEntityWith($forView = false)
	{
		$get = ['Product', 'Product.Category'];
		if ($forView)
		{
			$get[] = 'Product.User';

			$visitor = \XF::visitor();
			$get[] = 'Product.Category.Permissions|' . $visitor->permission_combination_id;
		}

		return $get;
	}

	public function getIndexData(Entity $entity)
	{
		/** @var \XR\PM\Entity\Version $entity */

		if (!$entity->Product)
		{
			return null;
		}

		/** @var \XR\PM\Entity\Product $product */
		$product = $entity->Product;

		$index = IndexRecord::create('xr_pm_product_version', $entity->product_version_id, [
			'title' => $entity->version_string,
			'message' => $entity->version_details . ' ' . implode("\n", $entity->changelog),
			'date' => $entity->release_date,
			'user_id' => $product->user_id,
			'discussion_id' => $entity->product_id,
			'metadata' => $this->getMetaData($entity)
		]);

		if (!$product->active)
		{
			$index->setHidden();
		}

		return $index;
	}

	protected function getMetaData(\XR\PM\Entity\Version $entity)
	{
		/** @var \XR\PM\Entity\Product $product */
		$product = $entity->Product;

		$metadata = [
			'cat' => $product->category_id,
			'product' => $product->product_id
		];

		return $metadata;
	}

	public function setupMetadataStructure(MetadataStructure $structure)
	{
		$structure->addField('cat', MetadataStructure::INT);
		$structure->addField('product', MetadataStructure::INT);
	}

	public function getResultDate(Entity $entity)
	{
		return $entity->release_date;
	}

	public function getTemplateData(Entity $entity, array $options = [])
	{
		return [
			'version' => $entity,
			'product' => $entity->Product,
			'options' => $options
		];
	}

	public function canViewContent(Entity $entity, &$error = null)
	{
		/** @var \XR\PM\Entity\Version $entity */
		$product = $entity->Product;

		return ($product->active && $product->canView());
	}
}