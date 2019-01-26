<?php

namespace XR\PM;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;
use XR\PM\Install\Data\MySql;

class Setup extends AbstractSetup
{
	use StepRunnerInstallTrait;
	use StepRunnerUpgradeTrait;
	use StepRunnerUninstallTrait;

	public function installStep1()
	{
		$sm = $this->schemaManager();

		foreach ($this->getTables() AS $tableName => $closure)
		{
			$sm->createTable($tableName, $closure);
		}
	}

	public function installStep2()
	{
		foreach ($this->getData() AS $dataSql)
		{
			$this->query($dataSql);
		}
	}

	public function installStep3()
	{
		$this->query("
			REPLACE INTO xf_purchasable
				(purchasable_type_id, purchasable_class, addon_id)
			VALUES
				('xr_pm_product', 'XR\\\\PM:Product', 'XR/PM')
		");
	}

	public function installStep4()
	{
		$this->schemaManager()->alterTable('xf_user_option', function(Alter $table)
		{
			$table->addColumn('xr_pm_receive_update_email', 'tinyint')->setDefault(1);
		});
	}

	public function postInstall(array &$stateChanges)
	{
		if ($this->applyDefaultPermissions())
		{
			// since we're running this after data imports, we need to trigger a permission rebuild
			// if we changed anything
			$this->app->jobManager()->enqueueUnique(
				'permissionRebuild',
				'XF:PermissionRebuild',
				[],
				false
			);
		}

		/** @var \XF\Service\RebuildNestedSet $service */
		$service = \XF::service('XF:RebuildNestedSet', 'XR\PM:Category', [
			'parentField' => 'parent_category_id'
		]);
		$service->rebuildNestedSetInfo();

		\XF::repository('XR\PM:ProductField')->rebuildFieldCache();
	}

	public function upgrade1000032Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_product
				ADD early_renew_from INT(10) UNSIGNED NOT NULL DEFAULT '0',
				ADD early_renew_from_unit ENUM('days','months','years') NOT NULL DEFAULT 'months'
		");
	}

	public function upgrade1000033Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_product
				ADD product_thumbnail INT(10) UNSIGNED NOT NULL DEFAULT '0'
		");

		$this->query("
			ALTER TABLE xenproduct_optional_extra
				CHANGE extra_reward extra_reward VARBINARY(255) NOT NULL DEFAULT 'user_group'
		");

		$this->query("
			ALTER TABLE xenproduct_cart
				ADD total_cart_value DECIMAL(10,2) UNSIGNED NOT NULL DEFAULT 0.00
		");

		$this->query("
			ALTER TABLE xenproduct_cart_item
				ADD extras_total DECIMAL(10,2) UNSIGNED NOT NULL DEFAULT 0.00
		");
	}

	public function upgrade1000052Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_coupon
				ADD coupon_renewal_only TINYINT(3) UNSIGNED NOT NULL DEFAULT 0
		");
	}

	public function upgrade1000053Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_license
				ADD notify_near_expiry TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
				ADD notify_has_expired TINYINT(3) UNSIGNED NOT NULL DEFAULT '0'
		");
	}

	public function upgrade1010070Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_product
				ADD confirm_license TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
				ADD requires_activation TINYINT(3) UNSIGNED NOT NULL DEFAULT '1'
		");
	}

	public function upgrade1020070Step1()
	{
		$this->query("
			ALTER TABLE xenproduct_product
				ADD display_order SMALLINT UNSIGNED NOT NULL DEFAULT '0',
				ADD INDEX product_date (product_date),
				ADD INDEX display_order (display_order)
		");

		$this->query("
			ALTER TABLE xenproduct_version
				ADD INDEX release_date (release_date)
		");

		$this->query("
			ALTER TABLE xenproduct_license
				ADD associated_users BLOB NOT NULL
		");
	}

	public function upgrade1021270Step1()
	{
		self::_runQuery("
			ALTER TABLE `xenproduct_version`
				ADD COLUMN `is_unsupported` TINYINT(1) NOT NULL DEFAULT '0' AFTER `version_details`
		");
	}

	public function upgrade2000010Step1()
	{
		$sm = $this->schemaManager();

		$renameTables = [
			'cart',
			'cart_item',
			'coupon',
			'download',
			'license',
			'license_assoc',
			'optional_extra',
			'product',
			'transaction_log',
			'version'
		];

		foreach ($renameTables AS $renameTable)
		{
			$sm->renameTable("xenproduct_{$renameTable}", "xf_xr_pm_{$renameTable}");
		}
	}

	public function upgrade2000010Step2()
	{
		$this->schemaManager()->alterTable('xf_user', function(Alter $table)
		{
			$table->renameColumn('xenproduct_active_licenses', 'xr_pm_active_purchases');
			$table->renameColumn('xenproduct_inactive_licenses', 'xr_pm_inactive_purchases');
			$table->renameColumn('xenproduct_expired_licenses', 'xr_pm_expired_purchases');
		});

		$this->schemaManager()->alterTable('xf_user_option', function(Alter $table)
		{
			$table->addColumn('xr_pm_receive_update_email', 'tinyint')->setDefault(1);
		});
	}

	public function upgrade2000010Step3()
	{
		$this->schemaManager()->createTable('xf_xr_pm_category', function(Create $table)
		{
			$table->addColumn('category_id', 'int')->autoIncrement();
			$table->addColumn('title', 'varchar', 100);
			$table->addColumn('description', 'text');
			$table->addColumn('parent_category_id', 'int')->setDefault(0);
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addColumn('lft', 'int')->setDefault(0);
			$table->addColumn('rgt', 'int')->setDefault(0);
			$table->addColumn('depth', 'smallint')->setDefault(0);
			$table->addColumn('breadcrumb_data', 'blob');
			$table->addColumn('product_count', 'int')->setDefault(0);
			$table->addColumn('last_update', 'int')->setDefault(0);
			$table->addColumn('last_product_title', 'varchar', 100)->setDefault('');
			$table->addColumn('last_product_id', 'int')->setDefault(0);
			$table->addKey(['parent_category_id', 'lft']);
			$table->addKey(['lft', 'rgt']);
		});

		$this->db()->query("
			INSERT IGNORE INTO xf_xr_pm_category
				(category_id, title, description, parent_category_id, depth, lft, rgt, display_order, breadcrumb_data)
			VALUES
				('1', 'Example category', 'An example category', '0', '0', '1', '2', '100', 'a:0:{}')
		");
	}

	public function upgrade2000010Step4()
	{
		$this->query("
			UPDATE xf_attachment
			SET content_type = 'xr_pm_product_image'
			WHERE content_type = 'xenproduct_product'
		");

		$this->query("
			UPDATE xf_attachment
			SET content_type = 'xr_pm_product_version'
			WHERE content_type = 'xenproduct_version'
		");

		$this->query("
			UPDATE xf_attachment
			SET content_type = 'xr_pm_product_extra'
			WHERE content_type = 'xenproduct_optional_extra'
		");

		$thumbAttachIds = $this->db()->fetchAllColumn('
			SELECT product_thumbnail FROM xf_xr_pm_product
		');

		if ($thumbAttachIds)
		{
			$this->query("
				UPDATE xf_attachment
				SET content_type = 'xr_pm_product_thumb'
				WHERE attachment_id IN(" . $this->db()->quote($thumbAttachIds) . ")
				AND content_type = 'xr_pm_product_image'
			");
		}
	}

	public function upgrade2000010Step5()
	{
		$this->schemaManager()->alterTable('xf_xr_pm_product', function(Alter $table)
		{
			$table->changeColumn('user_group_id')->resetDefinition()->type('mediumblob')->renameTo('user_group_ids')->nullable();
			$table->renameColumn('product_thumbnail', 'thumbnail_date');

			$table->addColumn('category_id', 'int')->setDefault(0)->after('product_id');
			$table->addColumn('product_hash', 'varchar', 32)->nullable()->after('product_id');
			$table->addColumn('last_update', 'int')->unsigned()->setDefault(0)->after('product_date');
			$table->addColumn('allow_early_extension', 'tinyint')->setDefault(1)->after('duration_unit');
			$table->addColumn('terms_conditions', 'text')->nullable()->after('user_group_ids');
			$table->addColumn('payment_profile_ids', 'varbinary', 255)->setDefault('');
			$table->addColumn('embed_metadata', 'blob')->nullable()->after('attach_count');

			$table->addUniqueKey('product_hash');
			$table->addKey(['category_id', 'last_update'], 'category_last_update');
			$table->addKey('last_update');

			$table->dropColumns([
				'early_renew_from',
				'early_renew_from_unit',
				'maximum_per_cart',
				'display_order',
				'renew_currency'
			]);
		});

		$products = $this->db()->fetchAllKeyed('
			SELECT product.*, version.release_date 
			FROM xf_xr_pm_product AS product
			INNER JOIN xf_xr_pm_version AS version ON
				(product.current_version_id = version.product_version_id)
			ORDER BY product_id
		', 'product_id');

		foreach ($products AS $productId => $product)
		{
			$this->db()->update('xf_xr_pm_product', [
				'user_group_ids' => is_numeric($product['user_group_ids'])
					? json_encode([$product['user_group_ids']])
					: '[]',
				'last_update' => $product['release_date'] // release_date is the most recent version release date
			], 'product_id = ?', $productId);
		}

		$this->query("
			UPDATE xf_xr_pm_product
			SET product_hash = MD5(CONCAT(product_id, ?))
		", \XF::generateRandomString(8, true));

		$this->query("
			UPDATE xf_xr_pm_product
			SET category_id = 1
		");
	}

	public function upgrade2000010Step6()
	{
		$this->query("
			REPLACE INTO xf_purchasable
				(purchasable_type_id, purchasable_class, addon_id)
			VALUES
				('xr_pm_product', 'XR\\\\PM:Product', 'XR/PM')
		");
	}

	public function upgrade2000010Step7(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0,
			'thumbnail_date_reset' => false
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		if ($stepParams['thumbnail_date_reset'] === false)
		{
			$db->update('xf_xr_pm_product', ['thumbnail_date' => 0], null);
			$stepParams['thumbnail_date_reset'] = true;
		}

		$productIds = $db->fetchAllColumn($db->limit(
			'
				SELECT product_id
				FROM xf_xr_pm_product
				WHERE product_id > ?
				ORDER BY product_id
			', $perPage
		), $stepParams['position']);
		if (!$productIds)
		{
			return true;
		}

		foreach ($productIds AS $productId)
		{
			$product = $db->fetchRow('
				SELECT product.*, att.*, attdat.*
				FROM xf_xr_pm_product AS product
				LEFT JOIN xf_attachment AS att ON
					(att.content_id = product.product_id AND att.content_type IN(\'xr_pm_product_thumb\'))
				LEFT JOIN xf_attachment_data AS attdat ON
					(attdat.data_id = att.data_id)
				WHERE product_id = ?
			', $productId);

			if ($product)
			{
				$fs = $this->app->fs();

				$oldThumbAbsPath = sprintf(
					'data://attachments/%d/%d-%s.jpg',
					floor($product['data_id'] / 1000), $product['data_id'], $product['file_hash']
				);
				$newThumbAbsPath = sprintf(
					'data://xrpm/thumbnail/%d/%d-%s.jpg',
					floor($productId / 1000), $productId, $product['product_hash']
				);

				if ($fs->has($oldThumbAbsPath))
				{
					$moved = $fs->move($oldThumbAbsPath, $newThumbAbsPath);
					if ($moved)
					{
						$db->update('xf_xr_pm_product', ['thumbnail_date' => time()], 'product_id = ?', $productId);
					}
				}
			}

			$stepParams['position'] = $productId;

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	public function upgrade2000010Step8(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		$productIds = $db->fetchAllColumn($db->limit(
			'
				SELECT product_id
				FROM xf_xr_pm_product
				WHERE product_id > ?
				ORDER BY product_id
			', $perPage
		), $stepParams['position']);
		if (!$productIds)
		{
			return true;
		}

		foreach ($productIds AS $productId)
		{
			$product = $db->fetchRow('
				SELECT *
				FROM xf_xr_pm_product
				WHERE product_id = ?
			', $productId);

			if ($product)
			{
				$features = @unserialize($product['features']);
				if ($features)
				{
					$i = 0;
					$newFeatures = [];
					foreach ($features AS $feature)
					{
						$i++;
						if ($feature['item'])
						{
							$newFeatures[] = $feature['item'];
						}
					}
					$this->query("
						UPDATE xf_xr_pm_product
						SET features = ?
						WHERE product_id = ?
					", [json_encode($newFeatures), $productId]);
				}
			}

			$stepParams['position'] = $productId;

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	public function upgrade2000010Step9()
	{
		$this->schemaManager()->createTable('xf_xr_pm_product_purchase', function(Create $table)
		{
			$table->addColumn('purchase_id', 'int')->autoIncrement();
			$table->addColumn('purchase_key', 'varchar', 50);
			$table->addColumn('old_cart_key', 'varchar', 50)->setDefault('');
			$table->addColumn('product_id', 'int');
			$table->addColumn('purchase_date', 'int')->setDefault(0);
			$table->addColumn('expiry_date', 'int')->setDefault(0);
			$table->addColumn('purchase_state', 'varbinary', 25)->setDefault('pending');
			$table->addColumn('purchase_type', 'varbinary', 25)->setDefault('product');
			$table->addColumn('parent_purchase_key', 'varchar', 50)->setDefault('');
			$table->addColumn('user_id', 'int')->setDefault(0);
			$table->addColumn('username', 'varchar', 50)->setDefault('');
			$table->addColumn('license_name', 'varchar', 100)->setDefault('');
			$table->addColumn('license_url', 'text');
			$table->addColumn('purchase_currency', 'varchar', 3)->setDefault('');
			$table->addColumn('product_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('extras_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('discount_total', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('total_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('extras', 'blob')->nullable();
			$table->addColumn('coupons', 'blob')->nullable();

			$table->addUniqueKey('purchase_key');
		});

		$this->schemaManager()->createTable('xf_xr_pm_product_key_item_map', function(Create $table)
		{
			$table->addColumn('license_id', 'int')->setDefault(0);
			$table->addColumn('item_id', 'int')->setDefault(0);
			$table->addColumn('purchase_key', 'varchar', 50);
		});
	}

	public function upgrade2000010Step10(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		$cartIds = $db->fetchAllColumn($db->limit(
			'
				SELECT cart_id
				FROM xf_xr_pm_cart
				WHERE cart_id > ?
				ORDER BY cart_id
			', $perPage
		), $stepParams['position']);
		if (!$cartIds)
		{
			return true;
		}

		foreach ($cartIds AS $cartId)
		{
			$cart = $db->fetchRow("
				SELECT *
				FROM xf_xr_pm_cart
				WHERE cart_id = ?
			", $cartId);

			$licenses = $db->fetchAll("
				SELECT i.*, l.*, c.*, i.item_id AS item_id
				FROM xf_xr_pm_cart_item AS i
				LEFT JOIN xf_xr_pm_license AS l ON
					(i.item_id = l.item_id)
				INNER JOIN xf_xr_pm_cart AS c ON
					(i.cart_id = c.cart_id)
				WHERE c.cart_state = 'purchased'
				AND c.cart_id = ?
			", $cart['cart_id']);

			$insertPurchase = [];
			$insertMap = [];

			foreach ($licenses AS $license)
			{
				$purchase = [
					'purchase_key' => $this->generatePurchaseKey(),
					'old_cart_key' => $license['cart_key'],
					'product_id' => $license['product_id'],
					'purchase_date' => $license['update_date'],
					'expiry_date' => $license['expiry_date'] ?: 0,
					'purchase_state' => $license['license_state'] ?: 'complete',
					'purchase_type' => $license['license_state'] ? 'product' : 'renewal',
					'user_id' => $license['user_id'],
					'username' => $license['username'],
					'license_name' => $license['license_alias'] ?: '',
					'license_url' => $license['license_url'] ?: '',
					'purchase_currency' => strtoupper($license['cart_currency']),
					'product_price' => floatval($license['unit_price']),
					'extras_price' => floatval($license['extras_total']),
					'discount_total' => 0,
					'total_price' => 0,
					'extras' => $license['item_optional_extras'],
					'coupons' => $license['cart_coupons']
				];

				$purchase['total_price'] = $purchase['product_price'] + $purchase['extras_price'];

				$extras = @unserialize($purchase['extras']) ?: [];

				// we only really care about what the extra is, and the price paid rather than a
				// snapshot in time, the other details should be current and queried for.
				$purchase['extras'] = json_encode(array_map(function($extra)
				{
					if (isset($extra['extra_id'], $extra['extra_price']))
					{
						return [
							'extra_id' => $extra['extra_id'],
							'extra_price' => $extra['extra_price']
						];
					}
					else
					{
						return [];
					}
				}, $extras));

				$coupons = @unserialize($purchase['coupons']) ?: [];
				if ($coupons)
				{
					foreach ($coupons AS $coupon)
					{
						$type = $coupon['coupon_applies_to'];
						$reduction = $coupon['coupon_reduction'];
						$reductionUnit = $coupon['coupon_unit']; // currency or percent
						if ($type == 'product' && $coupon['coupon_product_id'] != $purchase['product_id'])
						{
							continue;
						}
						if ($type == 'cart' && $license['cart_items'] > 1 && $reductionUnit == 'currency')
						{
							$reduction /= $license['cart_items'];
						}
						if ($reductionUnit == 'percent')
						{
							$reduction = ($purchase['total_price'] / 100) * $reduction;
						}

						$purchase['discount_total'] += floatval($reduction);
						$purchase['total_price'] = max(0, $purchase['total_price'] - $purchase['discount_total']);
					}
				}
				$purchase['coupons'] = json_encode($coupons);

				$insertPurchase[] = $purchase;
				$insertMap[] = ['item_id' => $license['item_id'] ?: 0, 'license_id' => $license['license_id'] ?: 0, 'purchase_key' => $purchase['purchase_key']];
			}

			if ($insertPurchase)
			{
				$db->insertBulk('xf_xr_pm_product_purchase', $insertPurchase);
			}

			if ($insertMap)
			{
				$db->insertBulk('xf_xr_pm_product_key_item_map', $insertMap);
			}

			$stepParams['position'] = $cartId;

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	protected function generatePurchaseKey($length = 12)
	{
		return strtoupper(substr(md5(uniqid(mt_rand() . microtime(), true)), 0, $length));
	}

	public function upgrade2000010Step11()
	{
		$this->schemaManager()->alterTable('xf_xr_pm_license_assoc', function(Alter $table)
		{
			$table->renameTo('xf_xr_pm_purchase_assoc');

			$table->renameColumn('assoc_license_id', 'purchase_key')->type('varchar')->length(50)->unsigned(false);
			$table->renameColumn('assoc_user_id', 'user_id');
			$table->renameColumn('assoc_username', 'username');
			$table->dropColumns('assoc_change_id');

			$table->dropPrimaryKey();
			$table->addPrimaryKey('purchase_key');
		});

		$this->schemaManager()->alterTable('xf_xr_pm_download', function(Alter $table)
		{
			$table->renameColumn('license_id', 'purchase_key')->type('varchar')->length(50)->unsigned(false);

			$table->dropIndexes('license_version_user_id');
			$table->addUniqueKey(['purchase_key', 'version_id', 'user_id'], 'purchase_version_user_id');
		});

		$this->schemaManager()->alterTable('xf_xr_pm_transaction_log', function(Alter $table)
		{
			$table->renameColumn('cart_id', 'purchase_key')->type('varchar')->length(50)->unsigned(false);
		});
	}

	public function upgrade2000010Step12(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		$itemIds = $db->fetchAllColumn($db->limit(
			'
				SELECT item_id
				FROM xf_xr_pm_cart_item
				WHERE item_id > ?
				ORDER BY item_id
			', $perPage
		), $stepParams['position']);
		if (!$itemIds)
		{
			$this->query("
				DELETE FROM xf_user_change_temp
				WHERE action_modifier LIKE('product_%_%')
			");

			$this->query("
				DELETE FROM xf_user_group_change
				WHERE change_key LIKE('product_%_%')
			");

			$this->query("
				DELETE FROM xf_user_change_temp
				WHERE action_modifier LIKE('license_assoc_%_%')
			");

			$this->query("
				DELETE FROM xf_user_group_change
				WHERE change_key LIKE('license_assoc_%_%')
			");

			$this->query("
				DELETE FROM xf_user_change_temp
				WHERE action_modifier LIKE('optional_extra_%_%')
			");

			$this->query("
				DELETE FROM xf_user_group_change
				WHERE change_key LIKE('optional_extra_%_%')
			");

			return true;
		}

		$map = $db->fetchAllKeyed('
			SELECT item_id, license_id, purchase_key
			FROM xf_xr_pm_product_key_item_map
			WHERE item_id IN(' . $db->quote($itemIds) . ')
		', 'item_id');

		foreach ($itemIds AS $itemId)
		{
			if (!isset($map[$itemId]))
			{
				continue;
			}

			$purchaseKey = $map[$itemId]['purchase_key'];
			$licenseId = $map[$itemId]['license_id'];

			$purchase = $db->fetchRow("
				SELECT p.product_id, c.cart_id
				FROM xf_xr_pm_product_purchase AS p
				INNER JOIN xf_xr_pm_cart AS c ON
					(p.old_cart_key = c.cart_key)
				WHERE p.purchase_key = ?
			", $purchaseKey);

			$this->query("
				UPDATE xf_xr_pm_purchase_assoc
				SET purchase_key = ?
				WHERE purchase_key = ?
			", [$purchaseKey, $licenseId]);

			$this->query("
				UPDATE xf_xr_pm_download
				SET purchase_key = ?
				WHERE purchase_key = ?
			", [$purchaseKey, $licenseId]);

			$this->query("
				UPDATE xf_user_change_temp
				SET action_modifier = CONCAT('xr_pm_purchase_assoc_', ?, '_', user_id),
					change_key = action_modifier
				WHERE action_modifier = CONCAT('license_assoc_', ?, '_', user_id)
			", [$purchaseKey, $licenseId]);

			$this->query("
				UPDATE xf_user_group_change
				SET change_key = CONCAT('xr_pm_purchase_assoc_', ?, '_', user_id)
				WHERE change_key = CONCAT('license_assoc_', ?, '_', user_id)
			", [$purchaseKey, $licenseId]);

			$this->query("
				UPDATE xf_user_change_temp
				SET action_modifier = CONCAT('xr_pm_purchase_', ?),
					change_key = action_modifier
				WHERE action_modifier = CONCAT('product_', ?, '_', ?)
			", [$purchaseKey, $purchase['product_id'], $purchase['cart_id']]);

			$this->query("
				UPDATE xf_user_group_change
				SET change_key = CONCAT('xr_pm_purchase_', ?)
				WHERE change_key = CONCAT('product_', ?, '_', ?)
			", [$purchaseKey, $purchase['product_id'], $purchase['cart_id']]);

			$this->query("
				UPDATE xf_user_change_temp
				SET action_modifier = REPLACE(action_modifier, 'optional_extra_', 'xr_pm_extra_'),
					change_key = action_modifier
				WHERE action_modifier LIKE('optional_extra_%')
			");

			$this->query("
				UPDATE xf_user_group_change
				SET change_key = REPLACE(change_key, 'optional_extra_', 'xr_pm_extra_')
				WHERE change_key LIKE('optional_extra_%')
			");

			$this->query("
				UPDATE xf_user_change_temp
				SET action_modifier = REPLACE(action_modifier, CONCAT('_', ?), CONCAT('_', ?)),
					change_key = action_modifier
				WHERE action_modifier LIKE(CONCAT('xr_pm_extra_%_', ?))
			", [$purchase['cart_id'], $purchaseKey, $purchase['cart_id']]);

			$this->query("
				UPDATE xf_user_group_change
				SET change_key = REPLACE(change_key, CONCAT('_', ?), CONCAT('_', ?))
				WHERE change_key LIKE(CONCAT('xr_pm_extra_%_', ?))
			", [$purchase['cart_id'], $purchaseKey, $purchase['cart_id']]);

			$this->query("
				UPDATE xf_xr_pm_transaction_log
				SET purchase_key = ?
				WHERE purchase_key = ?
			", [$purchaseKey, $purchase['cart_id']]);

			$stepParams['position'] = $itemId;

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	public function upgrade2000010Step13(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		$versionIds = $db->fetchAllColumn($db->limit(
			'
				SELECT product_version_id
				FROM xf_xr_pm_version
				WHERE product_version_id > ?
				ORDER BY product_version_id
			', $perPage
		), $stepParams['position']);
		if (!$versionIds)
		{
			return true;
		}

		foreach ($versionIds AS $versionId)
		{
			$version = $db->fetchRow("
				SELECT *
				FROM xf_xr_pm_version
				WHERE product_version_id = ?
			", $versionId);

			$changelogs = array_filter(@unserialize($version['changelog']) ?: []);

			if ($changelogs)
			{
				$changelogItems = \XF\Util\Arr::arrayColumn($changelogs, 'item');
				$this->query("
					UPDATE xf_xr_pm_version
					SET changelog = ?
					WHERE product_version_id = ?
				", [json_encode($changelogItems), $versionId]);
			}

			$stepParams['position'] = $versionId;

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	public function upgrade2000010Step14()
	{
		$this->schemaManager()->alterTable('xf_xr_pm_optional_extra', function(Alter $table)
		{
			$table->dropColumns(['extra_currency', 'extra_renew_currency']);
		});

		$this->schemaManager()->createTable('xf_xr_pm_product_extra_map', function(Create $table)
		{
			$table->addColumn('product_id', 'int');
			$table->addColumn('extra_id', 'int');
			$table->addPrimaryKey(['product_id', 'extra_id']);
			$table->addKey('extra_id');
		});
	}

	public function upgrade2000010Step15(array $stepParams)
	{
		$stepParams = array_replace([
			'position' => 0
		], $stepParams);

		$perPage = 250;
		$db = $this->db();
		$startTime = microtime(true);
		$maxRunTime = $this->app->config('jobMaxRunTime');

		$productIds = $db->fetchAllColumn($db->limit(
			'
				SELECT product_id
				FROM xf_xr_pm_product
				WHERE product_id > ?
				ORDER BY product_id
			', $perPage
		), $stepParams['position']);
		if (!$productIds)
		{
			return true;
		}

		foreach ($productIds AS $productId)
		{
			$stepParams['position'] = $productId;

			$product = $db->fetchRow("
				SELECT *
				FROM xf_xr_pm_product
				WHERE product_id = ?
			", $productId);

			$extraIds = @unserialize($product['optional_extras'])
				?: json_decode($product['optional_extras'], true);

			if (!$extraIds)
			{
				$this->query("
					UPDATE xf_xr_pm_product
					SET optional_extras = '[]'
					WHERE product_id = ?
				", $productId);

				continue;
			}

			$extras = $db->fetchAllKeyed('
				SELECT *
				FROM xf_xr_pm_optional_extra
				WHERE extra_id IN(' . $db->quote($extraIds) . ')
			', 'extra_id');

			$insert = [];

			foreach ($extraIds AS $key => $extraId)
			{
				if (!isset($extras[$extraId]))
				{
					unset($extraIds[$key]);
					continue;
				}

				$insert[] = [
					'product_id' => $productId,
					'extra_id' => $extraId
				];
			}

			$this->query("
				UPDATE xf_xr_pm_product
				SET optional_extras = ?
				WHERE product_id = ?
			", [json_encode(array_combine($extraIds, $extraIds)), $productId]);

			if ($insert)
			{
				$db->insertBulk('xf_xr_pm_product_extra_map', $insert, true);
			}

			if ($maxRunTime && microtime(true) - $startTime > $maxRunTime)
			{
				break;
			}
		}

		return $stepParams;
	}

	public function upgrade2000010Step16()
	{
		$this->schemaManager()->alterTable('xf_xr_pm_coupon', function(Alter $table)
		{
			$table->changeColumn('coupon_applies_to')->renameTo('coupon_type')->resetDefinition()->type('blob')->nullable();
			$table->changeColumn('coupon_product_id')->renameTo('coupon_product_ids')->resetDefinition()->type('blob')->nullable();
			$table->addColumn('coupon_extra_ids')->type('blob')->nullable()->after('coupon_product_ids');
		});

		$this->query("
			UPDATE xf_xr_pm_coupon
			SET coupon_type = 'renewal'
			WHERE coupon_renewal_only = '1'
		");

		$this->query("
			UPDATE xf_xr_pm_coupon
			SET coupon_type = 'purchase'
			WHERE coupon_type = 'cart'
		");

		$this->query("
			UPDATE xf_xr_pm_coupon
			SET coupon_product_ids = IF(coupon_product_ids > 0, CONCAT('[', coupon_product_ids, ']'), NULL)
		");

		$this->schemaManager()->alterTable('xf_xr_pm_coupon', function(Alter $table)
		{
			$table->dropColumns('coupon_renewal_only');
		});
	}

	public function upgrade2000010Step17()
	{
		// Products are now managed in the Admin CP so deleted/moderated states seem superfluous.
		// Let's swap these to an active boolean state
		$this->schemaManager()->alterTable('xf_xr_pm_product', function(Alter $table)
		{
			$table->changeColumn('product_state')->resetDefinition()->renameTo('active')->type('varbinary', 50)->setDefault(1);
		});

		$this->query("
			UPDATE xf_xr_pm_product
			SET active = 1
			WHERE active = 'visible'
		");

		$this->query("
			UPDATE xf_xr_pm_product
			SET active = 0
			WHERE active IN('deleted', 'moderated')
		");

		$this->query("
			UPDATE xf_xr_pm_product
			SET active = 0
			WHERE active NOT IN(0, 1)
		");

		$this->schemaManager()->alterTable('xf_xr_pm_product', function(Alter $table)
		{
			$table->changeColumn('active')->type('tinyint', 3)->unsigned(true);
		});
	}

	public function upgrade2000010Step18()
	{
		// this was reportedly missed from a previous version so ensure it's added if it doesn't yet exist.
		if (!$this->schemaManager()->columnExists('xf_xr_pm_version','is_unsupported'))
		{
			$this->schemaManager()->alterTable('xf_xr_pm_version', function(Alter $table)
			{
				$table->addColumn('is_unsupported', 'tinyint')->setDefault(0);
			});
		}
	}

	public function upgrade2000010Step19()
	{
		$paymentProfiles = $this->db()->fetchAll('
			SELECT *
			FROM xf_payment_profile
			WHERE provider_id = \'paypal\'
		');

		if (!$paymentProfiles)
		{
			$this->logPaymentProfileError();
			return;
		}

		$paymentProfileId = null;
		foreach ($paymentProfiles AS $paymentProfile)
		{
			$options = @json_decode($paymentProfiles['options'], true);
			if ($options && !empty($options['legacy']))
			{
				$paymentProfileId = $paymentProfile['payment_profile_id'];
				break;
			}
		}

		if (!$paymentProfileId)
		{
			$this->logPaymentProfileError();
			return;
		}

		$this->query('
			UPDATE xf_xr_pm_product
			SET payment_profile_ids = ?
			WHERE payment_profile_ids = \'\'
		', $paymentProfileId);
	}

	protected function logPaymentProfileError()
	{
		\XF::logError('XR Product Manager: Could not ascertain legacy payment profile. Existing products must be updated to use a desired payment profile.', true);
	}

	public function upgrade2000033Step1()
	{
		$this->schemaManager()->createTable('xf_xr_pm_product_field', function(Create $table)
		{
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addColumn('display_group', 'varchar', 25)->setDefault('tab_content');
			$table->addColumn('display_order', 'int')->setDefault(1);
			$table->addColumn('field_type', 'varbinary', 25)->setDefault('textbox');
			$table->addColumn('field_choices', 'blob');
			$table->addColumn('match_type', 'varbinary', 25)->setDefault('none');
			$table->addColumn('match_params', 'blob');
			$table->addColumn('max_length', 'int')->setDefault(0);
			$table->addColumn('required', 'tinyint')->setDefault(0);
			$table->addColumn('display_template', 'text');
			$table->addPrimaryKey('field_id');
			$table->addKey(['display_group', 'display_order'], 'display_group_order');
		});

		$this->schemaManager()->createTable('xf_xr_pm_product_field_value', function(Create $table)
		{
			$table->addColumn('product_id', 'int');
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addColumn('field_value', 'mediumtext');
			$table->addPrimaryKey(['product_id', 'field_id']);
			$table->addKey('field_id');
		});

		$this->schemaManager()->alterTable('xf_xr_pm_product', function(Alter $table)
		{
			$table->addColumn('custom_fields', 'blob')->nullable();
		});
	}

	public function upgrade2000034Step1()
	{
		// note: missed from clean installs of beta 3
		if (!$this->schemaManager()->columnExists('xf_xr_pm_product', 'custom_fields'))
		{
			$this->schemaManager()->alterTable('xf_xr_pm_product', function(Alter $table)
			{
				$table->addColumn('custom_fields', 'blob')->nullable();
			});
		}
	}

	public function upgrade2000036Step1()
	{
		// query was bugged in the initial 2.0 upgrade
		$this->query("
			REPLACE INTO xf_purchasable
				(purchasable_type_id, purchasable_class, addon_id)
			VALUES
				('xr_pm_product', 'XR\\\\PM:Product', 'XR/PM')
		");
	}

	public function upgrade2000070Step1()
	{
		$this->schemaManager()->alterTable('xf_user', function(Alter $table)
		{
			$table->dropColumns([
				'xr_pm_active_purchases',
				'xr_pm_inactive_purchases',
				'xr_pm_expired_purchases'
			]);
		});
	}

	public function upgrade2000070Step2()
	{
		$sm = $this->schemaManager();

		if ($sm->columnExists('xf_xr_pm_download', 'license_id'))
		{
			// if license_id exists then it missed the correct table definition on install
			$sm->alterTable('xf_xr_pm_download', function(Alter $table)
			{
				$table->renameColumn('license_id', 'purchase_key')->type('varchar')->length(50)->unsigned(false);

				$table->dropIndexes('license_version_user_id');
				$table->addUniqueKey(['purchase_key', 'version_id', 'user_id'], 'purchase_version_user_id');
			});
		}
	}

	// ############################################ FINAL UPGRADE ACTIONS ##########################

	public function postUpgrade($previousVersion, array &$stateChanges)
	{
		if ($this->applyDefaultPermissions($previousVersion))
		{
			// since we're running this after data imports, we need to trigger a permission rebuild
			// if we changed anything
			$this->app->jobManager()->enqueueUnique(
				'permissionRebuild',
				'XF:PermissionRebuild',
				[],
				false
			);
		}

		if ($previousVersion && $previousVersion < 2000010)
		{
			$this->app->jobManager()->enqueueUnique(
				'xrpmUpgradeProductEmbedMetadataRebuild',
				'XR\PM:ProductEmbedMetadata',
				['types' => 'attachments'],
				false
			);

			/** @var \XF\Service\RebuildNestedSet $service */
			$service = \XF::service('XF:RebuildNestedSet', 'XR\PM:Category', [
				'parentField' => 'parent_category_id'
			]);
			$service->rebuildNestedSetInfo();
		}

		if ($previousVersion && $previousVersion < 2000070)
		{
			$this->app->jobManager()->enqueueUnique(
				'xrpmUpgradeCategoryRebuild',
				'XR\PM:Category',
				[],
				false
			);
		}

		\XF::repository('XR\PM:ProductField')->rebuildFieldCache();
	}

	public function uninstallStep1()
	{
		$sm = $this->schemaManager();

		foreach (array_keys($this->getTables()) AS $tableName)
		{
			$sm->dropTable($tableName);
		}
	}

	protected function applyDefaultPermissions($previousVersion = null)
	{
		$applied = false;

		if (!$previousVersion || $previousVersion < 2000034)
		{
			$this->applyGlobalPermission('xr_pm', 'view', 'general', 'viewNode');
			$this->applyGlobalPermission('xr_pm', 'view_product_image', 'general', 'viewNode');
			$this->applyGlobalPermission('xr_pm', 'buy', 'forum', 'viewNode');
			$this->applyGlobalPermission('xr_pm', 'use_coupons', 'forum', 'viewNode');
			$this->applyGlobalPermissionInt('xr_pm', 'use_coupons_limit', 1);

			$applied = true;
		}

		return $applied;
	}

	protected function getTables()
	{
		$data = new MySql();
		return $data->getTables();
	}

	protected function getData()
	{
		$data = new MySql();
		return $data->getData();
	}
}