<?php

namespace MJ\SupportTicket;

use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;

class Setup extends \XF\AddOn\AbstractSetup
{
	use \XF\AddOn\StepRunnerInstallTrait;
	use \XF\AddOn\StepRunnerUpgradeTrait;
	use \XF\AddOn\StepRunnerUninstallTrait;

	/** #################### INSTALLATION #################### */
	public function installStep1()
	{
		$sm = $this->schemaManager();

		foreach ($this->getTables() as $tableName => $closure)
		{
			$sm->createTable($tableName, $closure);
		}
	}

	public function installStep2()
	{
		$sm = $this->schemaManager();
		foreach ($this->getAlters() as $tableName => $closure)
		{
			$sm->alterTable($tableName, $closure);
		}
	}

	public function installStep3()
	{
		foreach ($this->getData() as $dataSql)
		{
			$this->query($dataSql);
		}

		$statuses = [
			1 => 'Open',
			2 => 'Answered',
			3 => 'Customer-Reply',
			4 => 'Closed',
			5 => 'Awaiting Client Response',
		];

		foreach ($statuses as $statusId => $title)
		{
			$phrase = \XF::em()->create('XF:Phrase');
			$phrase->addon_id = '';
			$phrase->title = 'mjst_status.' . $statusId;
			$phrase->phrase_text = $title;
			$phrase->language_id = 0;
			$phrase->global_cache = false;
			$phrase->save(false);
		}
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

		\XF::repository('MJ\SupportTicket:TicketPrefix')->rebuildPrefixCache();
		\XF::repository('MJ\SupportTicket:TicketField')->rebuildFieldCache();
		\XF::repository('MJ\SupportTicket:TicketStatus')->rebuildStatusCache();
		\XF::repository('MJ\SupportTicket:TicketStatus')->rebuildStatusStyleCache();
	}

	/**  #################### UNINSTALL #################### */
	public function uninstallStep1()
	{
		$sm = $this->schemaManager();

		foreach (array_keys($this->getTables()) as $tableName)
		{
			$sm->dropTable($tableName);
		}
	}

	public function uninstallStep2()
	{
		$sm = $this->schemaManager();

		foreach ($this->getDropAlters() as $tableName => $closure)
		{
			$sm->alterTable($tableName, $closure);
		}
	}

	/**
	 * #################### UPGRADE ####################
	 *
	 * #################### 2000000 ####################
	 * ONLY SUPPORT UPGRADE FROM 2.0.0
	 */
	protected function upgrade2000000Step1()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_user', function(Alter $table)
		{
			$table->addColumn('mjst_department_ids', 'varbinary', 255)->nullable();
		});

		$sm->alterTable('xf_brivium_support_ticket_message', function(Alter $table)
		{
			$table->addColumn('last_edit_date', 'int')->setDefault(0);
			$table->addColumn('last_edit_user_id', 'int')->setDefault(0);
			$table->addColumn('edit_count', 'int')->setDefault(0);
		});

		$sm->alterTable('xf_brivium_support_department', function(Alter $table)
		{
			$table->addColumn('short_description', 'text');
		});
	}

	/** #################### 3000030 #################### */
	protected function upgrade3000030Step1()
	{
		$sm = $this->schemaManager();

		$renameTables = [
			'xf_brivium_support_department'              => 'xf_mjst_department',
			'xf_brivium_support_knowledge_base'          => 'xf_mjst_kb',
			'xf_brivium_support_knowledge_base_category' => 'xf_mjst_kb_category',
			'xf_brivium_support_pre_reply'               => 'xf_mjst_pre_reply',
			'xf_brivium_support_pre_reply_group'         => 'xf_mjst_pre_reply_group',
			'xf_brivium_support_ticket'                  => 'xf_mjst_ticket',
			'xf_brivium_support_ticket_assigned'         => 'xf_mjst_ticket_assigned',
			'xf_brivium_support_ticket_email_piping'     => 'xf_mjst_ticket_email_piping',
			'xf_brivium_support_ticket_email_piping_log' => 'xf_mjst_ticket_email_piping_log',
			'xf_brivium_support_ticket_escalation'       => 'xf_mjst_ticket_escalation',
			'xf_brivium_support_ticket_field'            => 'xf_mjst_ticket_field',
			'xf_brivium_support_ticket_field_department' => 'xf_mjst_department_field',
			'xf_brivium_support_ticket_field_value'      => 'xf_mjst_ticket_field_value',
			'xf_brivium_support_ticket_message'          => 'xf_mjst_ticket_message',
			//'xf_brivium_support_ticket_participant'      => '',
			'xf_brivium_support_ticket_read'             => 'xf_mjst_ticket_read',
			'xf_brivium_support_ticket_status'           => 'xf_mjst_ticket_status',
		];
		foreach ($renameTables as $from => $to)
		{
			$sm->renameTable($from, $to);
		}

		foreach ($this->getTables() as $tableName => $closure)
		{
			$sm->createTable($tableName, $closure);
		}

		$sm->alterTable('xf_user', function(Alter $table)
		{
			$table->renameColumn('brsts_ticket_count', 'mjst_ticket_count');
			$table->renameColumn('brsts_department_ids', 'mjst_department_ids');
			$table->renameColumn('brsts_active_ticket_department', 'mjst_active_ticket');
			$table->renameColumn('brsts_support_ticket_unread', 'mjst_ticket_unread');
		});
	}

	protected function upgrade3000030Step2()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_user', function(Alter $table){
			$table->addColumn('mjst_ticket_count', 'int')->setDefault(0);
			$table->addColumn('mjst_department_ids', 'varbinary', 255)->nullable();
		});
	}

	protected function upgrade3000030Step3()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_department', function(Alter $table)
		{
			$table->renameColumn('department_title', 'title');
			$table->renameColumn('support_ticket_count', 'ticket_count');
			$table->addColumn('prefix_cache', 'mediumblob');
			$table->addColumn('require_prefix', 'tinyint')->setDefault(0);
			$table->addColumn('message_count', 'int')->setDefault(0);
		});

		$sm->alterTable('xf_mjst_kb', function(Alter $table)
		{
			$table->renameColumn('knowledge_base_id', 'kb_id');
			$table->renameColumn('knowledge_base_category_id', 'kb_category_id');
			$table->addColumn('is_active', 'tinyint')->setDefault(1);
			$table->addColumn('materialized_order', 'int')->setDefault(0);
			$table->addColumn('embed_metadata', 'blob')->nullable();
			$table->addKey(['kb_category_id', 'kb_date', 'is_active', 'materialized_order'], 'kb_group_id');
		});

		$sm->alterTable('xf_mjst_kb_category', function(Alter $table)
		{
			$table->renameColumn('knowledge_base_category_id', 'kb_category_id');
			$table->renameColumn('category_title', 'title');
			$table->renameColumn('category_description', 'description');
		});
	}

	protected function upgrade3000030Step4()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_pre_reply', function(Alter $table)
		{
			$table->addColumn('is_active', 'tinyint')->setDefault(1);
			$table->addColumn('materialized_order', 'int')->setDefault(0);
		});

		$sm->alterTable('xf_mjst_pre_reply_group', function(Alter $table)
		{
			$table->renameColumn('reply_group_tilte', 'title');
		});
	}

	protected function upgrade3000030Step5()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_ticket', function(Alter $table)
		{
			$table->renameColumn('custom_support_ticket_fields', 'custom_fields');
			$table->addColumn('prefix_id', 'int')->setDefault(0);
		});
	}

	protected function upgrade3000030Step6()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_ticket_message', function(Alter $table)
		{
			$table->addColumn('embed_metadata', 'blob')->nullable();
		});
	}

	/** PERMISSIONS */
	protected function upgrade3000030Step7()
	{
		$db = $this->db();

		$tablesToUpdate = [
			'xf_permission',
			'xf_permission_entry',
			'xf_permission_entry_content'
		];

		foreach ($tablesToUpdate as $table)
		{
			$db->update($table, [
				'permission_group_id' => 'mjstSupport'
			], 'permission_group_id = ?', 'BR_SupportTicket');
			$db->update($table, [
				'permission_group_id' => 'mjstKb'
			], 'permission_group_id = ?', 'BRSTS_KnowledgeBase');
		}

		$renames = [
			'mjstKb' => [
				'createKnowledgeBase' => 'create',
				'rateKnowledge'       => 'rate',
				'viewKnowledge'       => 'view'
			],
			'mjstSupport' => [
				'deleteTicket' => 'deleteOwnTicket',
			]
		];

		foreach ($tablesToUpdate as $table)
		{
			foreach ($renames['mjstKb'] as $old => $new)
			{
				$db->update($table, [
					'permission_id' => $new
				], 'permission_id = ? AND permission_group_id = ?', [$old, 'mjstKb']);
			}
			foreach ($renames['mjstSupport'] as $old => $new)
			{
				$db->update($table, [
					'permission_id' => $new
				], 'permission_id = ? AND permission_group_id = ?', [$old, 'mjstSupport']);
			}
		}
	}

	/** TICKET FIELD */
	protected function upgrade3000030Step8()
	{
		$sm = $this->schemaManager();
		$db = $this->db();

		$sm->alterTable('xf_mjst_ticket_field', function (Alter $table)
		{
			$table->changeColumn('field_type')->resetDefinition()->type('varbinary', 25)->setDefault('textbox');
			$table->changeColumn('match_type')->resetDefinition()->type('varbinary', 25)->setDefault('none');
			$table->addColumn('match_params', 'blob')->after('match_type');
			$table->addColumn('display_template', 'text');
			$table->addKey(['display_group', 'display_order'], 'display_group_order');
		});

		foreach ($db->fetchAllKeyed("SELECT * FROM xf_mjst_ticket_field", 'field_id') as $fieldId => $field)
		{
			if (!isset($field['match_regex']))
			{
				// column removed already, this has been run
				continue;
			}

			$update = [];
			$matchParams = [];

			switch ($field['match_type'])
			{
				case 'regex':
					if ($field['match_regex'])
					{
						$matchParams['regex'] = $field['match_regex'];
					}
					break;

				case 'callback':
					if ($field['match_callback_class'] && $field['match_callback_method'])
					{
						$matchParams['callback_class'] = $field['match_callback_class'];
						$matchParams['callback_method'] = $field['match_callback_method'];
					}
					break;
			}

			if (!empty($matchParams))
			{
				$update['match_params'] = json_encode($matchParams);
			}

			if ($field['field_choices'] && $fieldChoices = @unserialize($field['field_choices']))
			{
				$update['field_choices'] = json_encode($fieldChoices);
			}

			if (!empty($update))
			{
				$db->update('xf_mjst_ticket_field', $update, 'field_id = ?', $fieldId);
			}
		}

		$sm->alterTable('xf_mjst_ticket_field', function(Alter $table)
		{
			$table->dropColumns(['match_regex', 'match_callback_class', 'match_callback_method']);
		});

		$sm->alterTable('xf_mjst_department_field', function (Alter $table)
		{
			$table->changeColumn('department_id')->length(10)->unsigned();
			$table->addPrimaryKey(['department_id', 'field_id']);
			$table->addKey('field_id', 'field_id');
		});
	}

	/** OPTIONS */
	protected function upgrade3000030Step9()
	{
		$optionMap = [
			'BRSTS_contactUsAsTicket'                => 'mjstContactAsTicket',
			'BRSTS_defautDepartment'                 => 'mjstDefautDepartment',
			'BRSTS_defautPriority'                   => 'mjstDefautPriority',
			//'BRSTS_disableEmail'                     => '',DELETE
			'BRSTS_displayFullKb'                    => 'mjstDisplayFullKb',
			//'BRSTS_displayOption'                    => 'mjstDisplayOption',
			'BRSTS_displaySubmitterIp'               => 'mjstDisplaySubmitterIp',
			'BRSTS_emailSupportTicketIncludeMessage' => 'mjstFirstMessageInEmail',
			//'BRSTS_guestPasswordLength'              => 'mjstGuestPasswordLength',
			'BRSTS_knowledgePreLength'               => 'mjstKbPreLength',
			//'BRSTS_moveableForum'                    => '',
			//'BRSTS_navigationLink'                   => '',
			//'BRSTS_noUpdateLifetime'                 => '',
			'BRSTS_numberFrequently'                 => 'mjstNumberFrequently',
			'BRSTS_numberSuggestKb'                  => 'mjstNumberSuggestKb',
			'BRSTS_openTicketOverlay'                => 'mjstOpenTicketOverlay',
			'BRSTS_quickUpdate'                      => 'mjstQuickUpdate',
			//'BRSTS_replyAlertMember'                 => '',
			'BRSTS_replySnippetLength'               => 'mjstReplySnippetLength',
			//'BRSTS_requireCaptcha'                   => 'mjstRequireCaptcha',
			'BRSTS_searchKbMessage'                  => 'mjstUseKbMessage',
			//'BRSTS_ticketIdLength'                   => '',
			'BRSTS_ticketStatistic'                  => 'mjstTicketStatistic',
			'BRSTS_ticketsPerPage'                   => 'mjstTicketsPerPage',
			//'BRSTS_useDisallowedNames'               => '',
		];

		$db = $this->db();
		$db->beginTransaction();

		foreach ($optionMap as $from => $to)
		{
			$db->update('xf_option', ['option_id' => $to], 'option_id = ?', $from);
		}

		$db->commit();
	}

	/** FIELD PHRASE */
	protected function upgrade3000030Step10()
	{
		$map = [
			'BRSTS_field_*_choice_*' => 'mjst_ticket_field_choice.$1_$2',
			'BRSTS_field_*_desc' => 'mjst_ticket_field_desc.*',
			'BRSTS_field_*' => 'mjst_ticket_field_title.*',
		];

		$db = $this->db();

		foreach ($map as $from => $to)
		{
			$mySqlRegex = '^' . str_replace('*', '[a-zA-Z0-9_]+', $from) . '$';
			$phpRegex = '/^' . str_replace('*', '([a-zA-Z0-9_]+)', $from) . '$/';
			$replace = str_replace('*', '$1', $to);

			$results = $db->fetchPairs("
				SELECT phrase_id, title
				FROM xf_phrase
				WHERE title RLIKE ?
					AND addon_id = ''
			", $mySqlRegex);
			if ($results)
			{
				/** @var \XF\Entity\Phrase[] $phrases */
				$phrases = \XF::em()->findByIds('XF:Phrase', array_keys($results));
				foreach ($results as $phraseId => $oldTitle)
				{
					if (isset($phrases[$phraseId]))
					{
						$newTitle = preg_replace($phpRegex, $replace, $oldTitle);

						$phrase = $phrases[$phraseId];
						$phrase->title = $newTitle;
						$phrase->global_cache = false;
						$phrase->save(false);
					}
				}
			}
		}
	}

	/** STATUS */
	protected function upgrade3000030Step11()
	{
		$db = $this->db();
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_ticket_status', function(Alter $table)
		{
			$table->renameColumn('status_active_ticket', 'group_active');
			$table->renameColumn('status_waiting_reply_ticket', 'group_waiting_reply');
		});

		$results = $db->fetchPairs("
			SELECT ticket_status_id, status_title
			FROM xf_mjst_ticket_status
		");
		if($results){
			foreach ($results as $statusId => $title)
			{
				$phrase = \XF::em()->create('XF:Phrase');
				$phrase->addon_id = '';
				$phrase->title = 'mjst_status.' . $statusId;
				$phrase->phrase_text = $title;
				$phrase->language_id = 0;
				$phrase->global_cache = false;
				$phrase->save(false);
			}
		}
	}

	/** #################### 3000032 #################### */

	protected function upgrade3000032Step1()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_department', function(Alter $table)
		{
			$table->addColumn('active_count', 'int')->setDefault(0);
			$table->addColumn('wait_reply_count', 'int')->setDefault(0);
		});
	}

	/** #################### 3000033 #################### */

	protected function upgrade3000033Step1()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_ticket', function(Alter $table)
		{
			$table->renameColumn('openner_user_id', 'creator_user_id');
			$table->renameColumn('openner_username', 'creator_username');
		});
	}

	/** #################### 3000034 #################### */

	protected function upgrade3000034Step1()
	{
		$sm = $this->schemaManager();

		$tables = $this->getTables();
		$sm->createTable('xf_mjst_ticket_escalation_log', $tables['xf_mjst_ticket_escalation_log']);
	}

	/** #################### 3000250 #################### */

	protected function upgrade3000250Step1()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_user_option', function(Alter $table){
			$table->addColumn('disable_email_on_support_ticket', 'tinyint')->setDefault(1);
			$table->addColumn('email_on_support_ticket', 'tinyint')->setDefault(1);
		});
	}

	/** #################### 3000251 #################### */

	protected function upgrade3000251Step1()
	{
		$sm = $this->schemaManager();

		$sm->alterTable('xf_mjst_ticket_field', function(Alter $table){
			$table->addColumn('choice_callback_class', 'varchar', 100)->setDefault('');
			$table->addColumn('choice_callback_method', 'varchar', 75)->setDefault('');
		});
	}

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

		if ($previousVersion && $previousVersion < 3000030)
		{
			$this->app->jobManager()->enqueueUnique(
				'mjstUpgradeMessageEmbedMetadataRebuild',
				'MJ\SupportTicket:TicketMessageEmbedMetadata',
				['types' => 'attachments'],
				false
			);
		}

		\XF::repository('MJ\SupportTicket:TicketPrefix')->rebuildPrefixCache();
		\XF::repository('MJ\SupportTicket:TicketField')->rebuildFieldCache();
		\XF::repository('MJ\SupportTicket:TicketStatus')->rebuildStatusCache();
		\XF::repository('MJ\SupportTicket:TicketStatus')->rebuildStatusStyleCache();

		$this->app->jobManager()->enqueueUnique(
			'mjstRebuildDepartmentCounter',
			'MJ\SupportTicket:Department'
		);
	}

	/** #################### DATA DEFINITIONS #################### */

	protected function getData()
	{
		$data = [];

		$data['xf_mjst_department'] = "
			INSERT IGNORE INTO `xf_mjst_department`
				(`department_id`,
				`title`, `short_description`,
				`hidden_department`, `field_cache`, `prefix_cache`,
				`require_prefix`, `ticket_count`, `message_count`,
				`active_count`, `wait_reply_count`, `department_date`, `display_order`)
			VALUES
				(1,
				'Example department', 'This is an example Support department. You can manage the Support departments via the ".
				"<a href=\"admin.php?mjst-support/departments/\" target=\"_blank\">Admin control panel</a>. ".
				"From there, you can setup more departments or change the Support options.',
				0, '', '',
				0, 0, 0,
				0, 0, 0, 0);
		";

		$data['xf_mjst_ticket_status'] = "
			INSERT IGNORE INTO `xf_mjst_ticket_status`
				(`ticket_status_id`, `status_color`, `group_active`, `group_waiting_reply`)
			VALUES
				(1, '#779500', 1, 1),
				(2, '#000', 1, 0),
				(3, '#F60', 1, 1),
				(4, '#888', 0, 0),
				(5, '#FFDA2F', 1, 0);
		";
		return $data;
	}

	protected function getTables()
	{
		$tables = [];

		$tables['xf_mjst_department'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('department_id', 'int')->autoIncrement();
			$table->addColumn('title', 'varchar', 50);
			$table->addColumn('short_description', 'text');
			$table->addColumn('hidden_department', 'tinyint')->setDefault(0);
			$table->addColumn('field_cache', 'mediumblob');
			$table->addColumn('prefix_cache', 'mediumblob');
			$table->addColumn('require_prefix', 'tinyint')->setDefault(0);
			$table->addColumn('ticket_count', 'int')->setDefault(0);
			$table->addColumn('message_count', 'int')->setDefault(0);
			$table->addColumn('active_count', 'int')->setDefault(0);
			$table->addColumn('wait_reply_count', 'int')->setDefault(0);
			$table->addColumn('department_date', 'int')->setDefault(0);
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addPrimaryKey('department_id');
		};

		$tables['xf_mjst_department_field'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('department_id', 'int');
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addPrimaryKey(['department_id', 'field_id']);
			$table->addKey('field_id', 'field_id');
		};

		$tables['xf_mjst_department_prefix'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('department_id', 'int');
			$table->addColumn('prefix_id', 'int');
			$table->addPrimaryKey(['department_id', 'prefix_id']);
			$table->addKey('prefix_id', 'prefix_id');
		};

		$tables['xf_mjst_department_watch'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('user_id', 'int');
			$table->addColumn('department_id', 'int');
			$table->addColumn('notify_on', 'enum')->values(['', 'ticket', 'message']);
			$table->addColumn('send_alert', 'tinyint');
			$table->addColumn('send_email', 'tinyint');
			$table->addColumn('include_children', 'tinyint');
			$table->addPrimaryKey(['user_id', 'department_id']);
			$table->addKey(['department_id', 'notify_on'], 'department_id_notify_on');
		};

		$tables['xf_mjst_kb'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('kb_id', 'int')->autoIncrement();
			$table->addColumn('title', 'text');
			$table->addColumn('user_id', 'int');
			$table->addColumn('username', 'varchar', 50);
			$table->addColumn('message', 'mediumtext');
			$table->addColumn('kb_category_id', 'int');
			$table->addColumn('view_count', 'int')->setDefault(0);
			$table->addColumn('attach_count', 'int')->setDefault(0);
			$table->addColumn('rating_count', 'int')->setDefault(0);
			$table->addColumn('rating_sum', 'int')->setDefault(0);
			$table->addColumn('kb_date', 'int')->setDefault(0);
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addColumn('is_active', 'tinyint')->setDefault(1);
			$table->addColumn('materialized_order', 'int')->setDefault(0);
			$table->addColumn('embed_metadata', 'blob')->nullable();
			$table->addPrimaryKey('kb_id');
			$table->addKey('user_id', 'user_id');
			$table->addKey('view_count', 'view_count');
			$table->addKey('display_order', 'display_order');
			$table->addKey(['kb_category_id', 'kb_date', 'is_active', 'materialized_order'], 'kb_group_id');
		};

		$tables['xf_mjst_kb_category'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('kb_category_id', 'int', 1)->autoIncrement();
			$table->addColumn('title', 'text');
			$table->addColumn('description', 'text');
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addPrimaryKey('kb_category_id');
			$table->addKey('display_order', 'display_order');
		};

		$tables['xf_mjst_pre_reply'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('reply_id', 'int')->autoIncrement();
			$table->addColumn('title', 'text');
			$table->addColumn('message', 'text');
			$table->addColumn('reply_group_id', 'int')->setDefault(0);
			$table->addColumn('is_active', 'tinyint')->setDefault(1);
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addColumn('materialized_order', 'int')->setDefault(0);
			$table->addColumn('allowed_user_group_ids', 'blob');
			$table->addPrimaryKey('reply_id');
			$table->addKey('reply_group_id', 'reply_group_id');
		};

		$tables['xf_mjst_pre_reply_group'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('reply_group_id', 'int')->autoIncrement();
			$table->addColumn('title', 'text');
			$table->addColumn('display_order', 'int')->setDefault(0);
			$table->addPrimaryKey('reply_group_id');
		};

		$tables['xf_mjst_ticket'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('support_ticket_id', 'int')->autoIncrement();
			$table->addColumn('ticket_id', 'varchar', 25)->setDefault('');
			$table->addColumn('title', 'text');
			$table->addColumn('user_id', 'int');
			$table->addColumn('username', 'varchar', 50);
			$table->addColumn('user_email', 'varchar', 120);
			$table->addColumn('user_name', 'varchar', 50);
			$table->addColumn('creator_user_id', 'int');
			$table->addColumn('creator_username', 'varchar', 50);
			$table->addColumn('open_date', 'int')->setDefault(0);
			$table->addColumn('urgency', 'enum')->values(['1', '2', '3'])->setDefault('2');
			$table->addColumn('guest_password', 'varchar', 50)->setDefault('');
			$table->addColumn('reply_count', 'int')->setDefault(0);
			$table->addColumn('participant_count', 'int')->setDefault(0);
			$table->addColumn('department_id', 'int');
			$table->addColumn('assigned_user_id', 'int')->setDefault(0);
			$table->addColumn('ticket_status_id', 'int');
			$table->addColumn('is_primary_close', 'tinyint')->setDefault(0);
			$table->addColumn('first_message_id', 'int')->setDefault(0);
			$table->addColumn('last_update', 'int')->setDefault(0);
			$table->addColumn('last_message_date', 'int')->setDefault(0);
			$table->addColumn('last_message_id', 'int')->setDefault(0);
			$table->addColumn('last_message_user_id', 'int')->setDefault(0);
			$table->addColumn('last_message_username', 'varchar', 50)->setDefault('');
			$table->addColumn('submitter_rating', 'float')->setDefault('0');
			$table->addColumn('prefix_id', 'int')->setDefault(0);
			$table->addColumn('custom_fields', 'mediumblob');
			$table->addColumn('participants', 'mediumblob');
			$table->addColumn('is_piping_email', 'tinyint')->setDefault(0);
			$table->addPrimaryKey('support_ticket_id');
			$table->addKey('creator_user_id', 'openner_user_id');
			$table->addKey('department_id', 'department_id');
			$table->addKey('ticket_status_id', 'ticket_status_id');
			$table->addKey('last_message_date', 'last_message_date');
			$table->addKey('open_date', 'open_date');
			$table->addKey('urgency', 'urgency');
			$table->addKey(['department_id', 'ticket_status_id'], 'department_ticket_status');
			$table->addKey(['department_id', 'open_date'], 'department_open_date');
		};

		$tables['xf_mjst_ticket_escalation'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('ticket_escalation_id', 'int')->autoIncrement();
			$table->addColumn('title', 'text');
			$table->addColumn('department_ids', 'varbinary', 255);
			$table->addColumn('ticket_status_ids', 'varbinary', 255);
			$table->addColumn('priorities', 'varbinary', 255);
			$table->addColumn('time_elapsed', 'int')->setDefault(0);
			$table->addColumn('new_department_id', 'int')->setDefault(0);
			$table->addColumn('new_priority', 'tinyint')->setDefault(0);
			$table->addColumn('new_ticket_status_id', 'int')->setDefault(0);
			$table->addColumn('reply_message', 'mediumtext');
			$table->addColumn('reply_user_id', 'int')->setDefault(0);
			$table->addPrimaryKey('ticket_escalation_id');
			$table->addKey('time_elapsed', 'time_elapsed');
			$table->addKey('new_department_id', 'new_department_id');
		};

		$tables['xf_mjst_ticket_escalation_log'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('escalation_log_id', 'int')->autoIncrement();
			$table->addColumn('escalation_id', 'int');
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('log_date', 'int')->setDefault(0);
			$table->addPrimaryKey('escalation_log_id');
			$table->addUniqueKey(['escalation_id', 'support_ticket_id'], 'escalation_id');
		};

		$tables['xf_mjst_ticket_field'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addColumn('display_group', 'varchar', 25)->setDefault('above_info');
			$table->addColumn('display_order', 'int')->setDefault(1);
			$table->addColumn('field_type', 'varbinary', 25)->setDefault('textbox');
			$table->addColumn('field_choices', 'blob');
			$table->addColumn('match_type', 'varbinary', 25)->setDefault('none');
			$table->addColumn('match_params', 'blob');
			$table->addColumn('max_length', 'int')->setDefault(0);
			$table->addColumn('required', 'tinyint')->setDefault(0);
			$table->addColumn('display_template', 'text');
			$table->addColumn('choice_callback_class', 'varchar', 100)->setDefault('');
			$table->addColumn('choice_callback_method', 'varchar', 75)->setDefault('');
			$table->addPrimaryKey('field_id');
			$table->addKey(['display_group', 'display_order'], 'display_group_order');
		};

		$tables['xf_mjst_ticket_field_value'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('field_id', 'varbinary', 25);
			$table->addColumn('field_value', 'mediumtext');
			$table->addKey(['support_ticket_id', 'field_id'], 'support_ticket_field');
			$table->addKey('field_id', 'field_id');
		};

		$tables['xf_mjst_ticket_message'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('message_id', 'int')->autoIncrement();
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('user_id', 'int');
			$table->addColumn('username', 'varchar', 50);
			$table->addColumn('user_email', 'varchar', 120);
			$table->addColumn('user_name', 'varchar', 50);
			$table->addColumn('message_date', 'int');
			$table->addColumn('message', 'mediumtext');
			$table->addColumn('ip_id', 'int')->setDefault(0);
			$table->addColumn('message_state', 'enum')->values(['visible', 'moderated', 'deleted'])->setDefault('visible');
			$table->addColumn('attach_count', 'smallint', 5)->setDefault(0);
			$table->addColumn('position', 'int')->setDefault(0);
			$table->addColumn('last_edit_date', 'int')->setDefault(0);
			$table->addColumn('last_edit_user_id', 'int')->setDefault(0);
			$table->addColumn('edit_count', 'int')->setDefault(0);
			$table->addColumn('embed_metadata', 'blob')->nullable();
			$table->addPrimaryKey('message_id');
			$table->addKey(['support_ticket_id', 'message_date'], 'support_ticket_id_message_date');
			$table->addKey(['support_ticket_id', 'position'], 'support_ticket_id_position');
			$table->addKey('user_id', 'user_id');
			$table->addKey('message_date', 'message_date');
		};

		$tables['xf_mjst_ticket_prefix'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('prefix_id', 'int')->autoIncrement();
			$table->addColumn('prefix_group_id', 'int');
			$table->addColumn('display_order', 'int');
			$table->addColumn('materialized_order', 'int')->comment('Internally-set order, based on prefix_group.display_order, prefix.display_order');
			$table->addColumn('css_class', 'varchar', 50)->setDefault('');
			$table->addColumn('allowed_user_group_ids', 'blob');
			$table->addPrimaryKey('prefix_id');
			$table->addKey('materialized_order', 'materialized_order');
		};

		$tables['xf_mjst_ticket_prefix_group'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('prefix_group_id', 'int')->autoIncrement();
			$table->addColumn('display_order', 'int');
			$table->addPrimaryKey('prefix_group_id');
		};

		$tables['xf_mjst_ticket_read'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('support_ticket_read_id', 'int')->autoIncrement();
			$table->addColumn('user_id', 'int');
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('support_ticket_read_date', 'int');
			$table->addPrimaryKey('support_ticket_read_id');
			$table->addUniqueKey(['user_id', 'support_ticket_id'], 'user_id_support_ticket_id');
			$table->addKey('support_ticket_id', 'support_ticket_id');
			$table->addKey('support_ticket_read_date', 'support_ticket_read_date');
		};

		$tables['xf_mjst_ticket_status'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('ticket_status_id', 'int')->autoIncrement();
			$table->addColumn('status_color', 'varchar', 255)->setDefault('');
			$table->addColumn('group_active', 'tinyint')->setDefault(0);
			$table->addColumn('group_waiting_reply', 'tinyint')->setDefault(0);
			$table->addPrimaryKey('ticket_status_id');
			$table->addKey('group_waiting_reply', 'status_waiting_reply_ticket');
			$table->addKey('group_active', 'status_active_ticket');
		};

		$tables['xf_mjst_ticket_user_message'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('user_id', 'int');
			$table->addColumn('message_count', 'int');
			$table->addPrimaryKey(['support_ticket_id', 'user_id']);
			$table->addKey('user_id', 'user_id');
		};

		$tables['xf_mjst_ticket_watch'] = function(Create $table) {
			$table->checkExists(true);
			$table->addColumn('user_id', 'int');
			$table->addColumn('support_ticket_id', 'int');
			$table->addColumn('email_subscribe', 'tinyint')->setDefault(0);
			$table->addPrimaryKey(['user_id', 'support_ticket_id']);
			$table->addKey(['support_ticket_id', 'email_subscribe'], 'ticket_id_email_subscribe');
		};

		return $tables;
	}

	protected function getAlters()
	{
		$alters = [];

		$alters['xf_user'] = function(Alter $table) {
			$table->addColumn('mjst_ticket_count', 'int')->setDefault(0);
			$table->addColumn('mjst_department_ids', 'varbinary', 255)->nullable();
		};

		$alters['xf_user_option'] = function(Alter $table) {
			$table->addColumn('disable_email_on_support_ticket', 'tinyint')->setDefault(1);
			$table->addColumn('email_on_support_ticket', 'tinyint')->setDefault(1);
		};

		return $alters;
	}

	protected function getDropAlters()
	{
		$alters = [];

		$alters['xf_user'] = function(Alter $table) {
			$table->dropColumns(['mjst_ticket_count', 'mjst_department_ids']);
		};

		$alters['xf_user_option'] = function(Alter $table) {
			$table->dropColumns(['disable_email_on_support_ticket', 'email_on_support_ticket']);
		};

		return $alters;
	}

	/** ############################################################ */

	protected function applyDefaultPermissions($previousVersion = null)
	{
		$applied = false;

		if (!$previousVersion)
		{
			$applied = true;
		}

		if (!$previousVersion || $previousVersion < 3000000)
		{
			$applied = true;
		}

		return $applied;
	}
}
