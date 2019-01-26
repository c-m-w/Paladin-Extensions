<?php

namespace XR\PM\Entity;

use XF\Entity\AbstractCategoryTree;
use XF\Mvc\Entity\Structure;

/**
 * COLUMNS
 * @property int|null category_id
 * @property string title
 * @property string description
 * @property int product_count
 * @property int last_update
 * @property string last_product_title
 * @property int last_product_id
 * @property int parent_category_id
 * @property int display_order
 * @property int lft
 * @property int rgt
 * @property int depth
 * @property array breadcrumb_data
 *
 * RELATIONS
 * @property \XF\Entity\PermissionCacheContent[] Permissions
 */
class Category extends AbstractCategoryTree
{
	public function canView(&$error = null)
	{
		return $this->hasPermission('view');
	}

	public function hasPermission($permission)
	{
		/** @var \XR\PM\XF\Entity\User $visitor */
		$visitor = \XF::visitor();
		return $visitor->hasXrPmCategoryPermission($this->category_id, $permission);
	}

	public function getNewProduct()
	{
		$product = $this->em()->create('XR\PM:Product');
		$product->category_id = $this->category_id;
		return $product;
	}

	public function getBreadcrumbs($includeSelf = true, $linkType = 'public')
	{
		if ($linkType == 'public')
		{
			$link = 'products/categories';
		}
		else
		{
			$link = 'product-manager/categories';
		}
		return $this->_getBreadcrumbs($includeSelf, $linkType, $link);
	}

	public function getCategoryListExtras()
	{
		return [
			'product_count' => $this->product_count,
			'last_update' => $this->last_update,
			'last_product_title' => $this->last_product_title,
			'last_product_id' => $this->last_product_id
		];
	}

	public function productAdded(Product $product)
	{
		$this->product_count++;

		if ($product->last_update >= $this->last_update)
		{
			$this->last_update = $product->product_date;
			$this->last_product_title = $product->product_title;
			$this->last_product_id = $product->product_id;
		}
	}

	public function productDataChanged(Product $product)
	{
		if ($product->isChanged(['last_update', 'title']))
		{
			if ($product->last_update >= $this->last_update)
			{
				$this->last_update = $product->last_update;
				$this->last_product_title = $product->product_title;
				$this->last_product_id = $product->product_id;
			}
			else if ($product->getExistingValue('last_update') == $this->last_update)
			{
				$this->rebuildLastProduct();
			}
		}
	}

	public function productRemoved(Product $product)
	{
		$this->product_count--;

		if ($product->last_update == $this->last_update)
		{
			$this->rebuildLastProduct();
		}
	}

	public function rebuildCounters()
	{
		$counters = $this->db()->fetchRow("
			SELECT COUNT(*) AS product_count
			FROM xf_xr_pm_product
			WHERE category_id = ?
				AND active = 1
		", $this->category_id);

		$this->product_count = $counters['product_count'];

		$this->rebuildLastProduct();
	}

	public function rebuildLastProduct()
	{
		$product = $this->db()->fetchRow("
			SELECT *
			FROM xf_xr_pm_product
			WHERE category_id = ?
				AND active = 1
			ORDER BY last_update DESC
			LIMIT 1
		", $this->category_id);
		if ($product)
		{
			$this->last_update = $product['last_update'];
			$this->last_product_title = $product['product_title'];
			$this->last_product_id = $product['product_id'];
		}
		else
		{
			$this->last_update = 0;
			$this->last_product_title = '';
			$this->last_product_id = 0;
		}
	}

	protected function _preDelete()
	{
		$count = $this->db()->fetchOne('
			SELECT COUNT(*)
			FROM xf_xr_pm_category
		');
		if ($count < 2)
		{
			$this->error(\XF::phrase('xr_pm_it_is_not_possible_to_delete_last_category'));
		}
	}

	protected function _postDelete()
	{
		if ($this->getOption('delete_products'))
		{
			$this->app()->jobManager()->enqueueUnique('xrpmCategoryDelete' . $this->category_id, 'XR\PM:CategoryDelete', [
				'category_id' => $this->category_id
			]);
		}
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_xr_pm_category';
		$structure->shortName = 'XR\PM:Category';
		$structure->primaryKey = 'category_id';
		$structure->contentType = 'xr_pm_category';
		$structure->columns = [
			'category_id' => ['type' => self::UINT, 'autoIncrement' => true, 'nullable' => true],
			'title' => ['type' => self::STR, 'maxLength' => 100,
				'required' => 'please_enter_valid_title'
			],
			'description' => ['type' => self::STR, 'default' => ''],
			'product_count' => ['type' => self::UINT, 'default' => 0, 'forced' => true],
			'last_update' => ['type' => self::UINT, 'default' => 0],
			'last_product_title' => ['type' => self::STR, 'default' => '', 'maxLength' => 100],
			'last_product_id' => ['type' => self::UINT, 'default' => 0]
		];
		$structure->getters = [];
		$structure->behaviors = [];
		$structure->relations = [];
		$structure->options = [
			'delete_products' => true
		];

		static::addCategoryTreeStructureElements($structure);

		return $structure;
	}

	/**
	 * @return \XR\PM\Repository\Category
	 */
	protected function getCategoryRepo()
	{
		return $this->repository('XR\PM:Category');
	}
}