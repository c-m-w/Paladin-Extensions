<?php

namespace XR\PM\Install\Data;

use XF\Db\Schema\Create;

class MySql
{
	public function getTables()
	{
		$tables = [];

		$tables['xf_xr_pm_category'] = function(Create $table)
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
		};

		$tables['xf_xr_pm_coupon'] = function(Create $table)
		{
			$table->addColumn('coupon_id', 'int')->autoIncrement();
			$table->addColumn('coupon_code', 'varchar', 50);
			$table->addColumn('coupon_title', 'varchar', 50)->setDefault('');
			$table->addColumn('coupon_description', 'text');
			$table->addColumn('coupon_type', 'blob')->nullable();
			$table->addColumn('coupon_usable_by', 'blob');
			$table->addColumn('coupon_auto_assign_to', 'blob');
			$table->addColumn('coupon_product_ids', 'blob')->nullable();
			$table->addColumn('coupon_extra_ids')->type('blob')->nullable()->after('coupon_product_ids');
			$table->addColumn('coupon_reduction', 'int')->setDefault(0);
			$table->addColumn('coupon_unit', 'enum')->values(['currency', 'percent']);
			$table->addColumn('coupon_valid_to', 'int')->setDefault(0);
			$table->addColumn('coupon_set_limit', 'tinyint')->setDefault(0);
			$table->addColumn('coupon_limit', 'int')->setDefault(0);
			$table->addColumn('active', 'tinyint')->setDefault(1);
			$table->addUniqueKey('coupon_code');
		};

		$tables['xf_xr_pm_download'] = function(Create $table)
		{
			$table->addColumn('download_id', 'int')->autoIncrement();
			$table->addColumn('purchase_key', 'varchar', 50);
			$table->addColumn('version_id', 'int')->setDefault(0);
			$table->addColumn('user_id', 'int')->setDefault(0);
			$table->addColumn('product_id', 'int')->setDefault(0);
			$table->addColumn('last_download_date', 'int')->setDefault(0);
			$table->addUniqueKey(['purchase_key', 'version_id', 'user_id'], 'purchase_version_user_id');
		};

		$tables['xf_xr_pm_license_assoc'] = function(Create $table)
		{
			$table->addColumn('assoc_license_id', 'int');
			$table->addColumn('assoc_user_id', 'int');
			$table->addColumn('assoc_username', 'varchar', 50)->setDefault('');
			$table->addColumn('assoc_change_id', 'int')->setDefault(0);
			$table->addPrimaryKey(['assoc_license_id', 'assoc_user_id']);
		};

		$tables['xf_xr_pm_optional_extra'] = function(Create $table)
		{
			$table->addColumn('extra_id', 'int')->autoIncrement();
			$table->addColumn('extra_title', 'varchar', 100)->setDefault('');
			$table->addColumn('extra_description', 'mediumtext');
			$table->addColumn('extra_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('extra_renew_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('extra_reward', 'varbinary',255)->setDefault('user_group');
			$table->addColumn('extra_user_group_id', 'int')->setDefault(0);
			$table->addColumn('instructions', 'mediumtext');
		};

		$tables['xf_xr_pm_product'] = function(Create $table)
		{
			$table->addColumn('product_id', 'int')->autoIncrement();
			$table->addColumn('product_hash', 'varchar', 32)->nullable();
			$table->addColumn('category_id', 'int')->setDefault(0);
			$table->addColumn('product_title', 'varchar', 100)->setDefault('');
			$table->addColumn('product_tag_line', 'varchar', 100)->setDefault('');
			$table->addColumn('product_details', 'mediumtext');
			$table->addColumn('features', 'mediumblob');
			$table->addColumn('optional_extras', 'mediumblob');
			$table->addColumn('product_date', 'int')->setDefault(0);
			$table->addColumn('last_update', 'int')->unsigned()->setDefault(0);
			$table->addColumn('user_id', 'int')->setDefault(0);
			$table->addColumn('username', 'varchar', 50)->setDefault('');
			$table->addColumn('active', 'tinyint')->setDefault(1);
			$table->addColumn('current_version_id', 'int')->setDefault(0);
			$table->addColumn('price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('currency', 'varchar', 3)->setDefault('');
			$table->addColumn('renew_price', 'decimal', '10,2')->setDefault(0.00);
			$table->addColumn('duration', 'int')->setDefault(0);
			$table->addColumn('duration_unit', 'enum')->values(['days', 'months', 'years'])->setDefault('months');
			$table->addColumn('allow_early_extension', 'tinyint')->setDefault(1);
			$table->addColumn('user_group_ids', 'mediumblob')->nullable();
			$table->addColumn('terms_conditions', 'text')->nullable();
			$table->addColumn('confirm_license', 'tinyint')->setDefault(0);
			$table->addColumn('requires_activation', 'tinyint')->setDefault(0);
			$table->addColumn('download_count', 'int')->setDefault(0);
			$table->addColumn('attach_count', 'int')->setDefault(0);
			$table->addColumn('embed_metadata', 'blob')->nullable();
			$table->addColumn('thumbnail_date', 'int')->unsigned()->setDefault(0);
			$table->addColumn('payment_profile_ids', 'varbinary', 255)->setDefault('');
			$table->addColumn('custom_fields', 'blob')->nullable();

			$table->addUniqueKey('product_hash');
			$table->addKey(['category_id', 'last_update'], 'category_last_update');
			$table->addKey('product_date');
			$table->addKey('last_update');
		};

		$tables['xf_xr_pm_product_extra_map'] = function(Create $table)
		{
			$table->addColumn('product_id', 'int');
			$table->addColumn('extra_id', 'int');
			$table->addPrimaryKey(['product_id', 'extra_id']);
			$table->addKey('extra_id');
		};

		$tables['xf_xr_pm_product_field'] = function(Create $table)
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
		};

		$tables['xf_xr_pm_product_field_value'] = function(Create $table)
		{
			$table->addColumn('product_id', 'int');
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addColumn('field_value', 'mediumtext');
			$table->addPrimaryKey(['product_id', 'field_id']);
			$table->addKey('field_id');
		};

		$tables['xf_xr_pm_product_key_item_map'] = function(Create $table)
		{
			$table->addColumn('license_id', 'int')->setDefault(0);
			$table->addColumn('item_id', 'int')->setDefault(0);
			$table->addColumn('purchase_key', 'varchar', 50);
		};

		$tables['xf_xr_pm_product_purchase'] = function(Create $table)
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
		};

		$tables['xf_xr_pm_version'] = function(Create $table)
		{
			$table->addColumn('product_version_id', 'int')->autoIncrement();
			$table->addColumn('product_id', 'int')->setDefault(0);
			$table->addColumn('version_string', 'varchar', 50)->setDefault('');
			$table->addColumn('version_details', 'mediumtext');
			$table->addColumn('is_unsupported', 'tinyint')->setDefault(0);
			$table->addColumn('release_date', 'int')->setDefault(0);
			$table->addColumn('changelog', 'mediumblob');
			$table->addColumn('download_count', 'int')->setDefault(0);
			$table->addKey(['product_id', 'release_date']);
			$table->addKey('release_date');
		};

		return $tables;
	}

	public function getData()
	{
		$data = [];

		$data['xf_xr_pm_category'] = "
			INSERT IGNORE INTO xf_xr_pm_category
				(category_id, title, description, parent_category_id, depth, lft, rgt, display_order, breadcrumb_data)
			VALUES
				('1', 'Example category', 'An example category', '0', '0', '1', '2', '100', 'a:0:{}')
		";

		return $data;
	}
}