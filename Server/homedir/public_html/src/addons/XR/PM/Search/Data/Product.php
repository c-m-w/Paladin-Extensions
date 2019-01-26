<?php

namespace XR\PM\Search\Data;

use XF\Mvc\Entity\Entity;
use XF\Search\Data\AbstractData;
use XF\Search\IndexRecord;
use XF\Search\MetadataStructure;
use XF\Search\Query\MetadataConstraint;

class Product extends AbstractData
{
	public function getEntityWith($forView = false)
	{
		$get = ['Category'];
		if ($forView)
		{
			$get[] = 'User';
			$get[] = 'Version';

			$visitor = \XF::visitor();
			$get[] = 'Category.Permissions|' . $visitor->permission_combination_id;
		}

		return $get;
	}

	public function getIndexData(Entity $entity)
	{
		/** @var \XR\PM\Entity\Product $entity */

		$message = $entity->product_details . ' ' . implode("\n", $entity->features);

		$index = IndexRecord::create('xr_pm_product', $entity->product_id, [
			'title' => $entity->product_title,
			'message' => $entity->product_tag_line . ' ' . $message,
			'date' => $entity->product_date,
			'user_id' => $entity->user_id,
			'discussion_id' => $entity->product_id,
			'metadata' => $this->getMetaData($entity)
		]);

		if (!$entity->active)
		{
			$index->setHidden();
		}

		return $index;
	}

	protected function getMetaData(\XR\PM\Entity\Product $entity)
	{
		return [
			'cat' => $entity->category_id,
			'product' => $entity->product_id
		];
	}

	public function setupMetadataStructure(MetadataStructure $structure)
	{
		$structure->addField('cat', MetadataStructure::INT);
		$structure->addField('product', MetadataStructure::INT);
	}

	public function getResultDate(Entity $entity)
	{
		return $entity->product_date;
	}

	public function getTemplateData(Entity $entity, array $options = [])
	{
		return [
			'product' => $entity,
			'options' => $options
		];
	}

	public function getSearchableContentTypes()
	{
		return ['xr_pm_product', 'xr_pm_product_version'];
	}

	public function getSearchFormTab()
	{
		/** @var \XR\PM\XF\Entity\User $visitor */
		$visitor = \XF::visitor();
		if (!method_exists($visitor, 'canViewProducts') || !$visitor->canViewProducts())
		{
			return null;
		}

		return [
			'title' => \XF::phrase('xr_pm_search_products'),
			'order' => 700
		];
	}

	public function getSectionContext()
	{
		return 'xr_pm_products';
	}

	public function getSearchFormData()
	{
		return [
			'categoryTree' => $this->getSearchableCategoryTree()
		];
	}

	/**
	 * @return \XF\Tree
	 */
	protected function getSearchableCategoryTree()
	{
		/** @var \XR\PM\Repository\Category $categoryRepo */
		$categoryRepo = \XF::repository('XR\PM:Category');
		return $categoryRepo->createCategoryTree($categoryRepo->getViewableCategories());
	}

	public function applyTypeConstraintsFromInput(\XF\Search\Query\Query $query, \XF\Http\Request $request, array &$urlConstraints)
	{
		$categoryIds = $request->filter('c.categories', 'array-uint');
		$categoryIds = array_unique($categoryIds);
		if ($categoryIds && reset($categoryIds))
		{
			if ($request->filter('c.child_categories', 'bool'))
			{
				$categoryTree = $this->getSearchableCategoryTree();

				$searchCategoryIds = array_fill_keys($categoryIds, true);
				$categoryTree->traverse(function($id, $category) use (&$searchCategoryIds)
				{
					if (isset($searchCategoryIds[$id]) || isset($searchCategoryIds[$category->parent_category_id]))
					{
						$searchCategoryIds[$id] = true;
					}
				});

				$categoryIds = array_unique(array_keys($searchCategoryIds));
			}
			else
			{
				unset($urlConstraints['child_categories']);
			}

			$query->withMetadata('cat', $categoryIds);
		}
		else
		{
			unset($urlConstraints['categories']);
			unset($urlConstraints['child_categories']);
		}

		$includeVersions = $request->filter('c.include_versions', 'bool');
		if (!$includeVersions)
		{
			$query->inType('xr_pm_product');
			unset($urlConstraints['include_versions']);
		}
	}

	public function getTypePermissionConstraints(\XF\Search\Query\Query $query, $isOnlyType)
	{
		/** @var \XR\PM\Repository\Category $categoryRepo */
		$categoryRepo = \XF::repository('XR\PM:Category');

		$with = ['Permissions|' . \XF::visitor()->permission_combination_id];
		$categories = $categoryRepo->findCategoryList(null, $with)->fetch();

		$skip = [];
		foreach ($categories AS $category)
		{
			/** @var \XR\PM\Entity\Category $category */
			if (!$category->canView())
			{
				$skip[] = $category->category_id;
			}
		}

		if ($skip)
		{
			return [
				new MetadataConstraint('cat', $skip, MetadataConstraint::MATCH_NONE)
			];
		}
		else
		{
			return [];
		}
	}

	public function getGroupByType()
	{
		return 'xr_pm_product';
	}
}