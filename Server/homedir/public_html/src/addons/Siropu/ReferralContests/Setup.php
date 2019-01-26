<?php

namespace Siropu\ReferralContests;

use XF\AddOn\AbstractSetup;
use XF\AddOn\StepRunnerInstallTrait;
use XF\AddOn\StepRunnerUninstallTrait;
use XF\AddOn\StepRunnerUpgradeTrait;
use XF\Db\Schema\Alter;
use XF\Db\Schema\Create;
use XF\Util\File;

class Setup extends AbstractSetup
{
	use StepRunnerInstallTrait;
	use StepRunnerUpgradeTrait;
	use StepRunnerUninstallTrait;

	public function installStep1()
	{
		$this->schemaManager()->alterTable('xf_user', function(Alter $table)
		{
			$table->addColumn('siropu_referrer_id', 'int')->setDefault(0);
			$table->addColumn('siropu_referral_count', 'int')->setDefault(0);
			$table->addColumn('siropu_referrer_credit', 'tinyint', 1)->setDefault(0);

			$table->addKey('siropu_referrer_id', 'referrer_id');
			$table->addKey('siropu_referral_count', 'referral_count');
		});
	}
	public function installStep2()
	{
		$sm = $this->schemaManager();

		$sm->createTable('xf_siropu_referral_contests_contest', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('contest_id', 'int')->autoIncrement();
			$table->addColumn('name', 'varchar', 255);
			$table->addColumn('description', 'text');
			$table->addColumn('minimum_posts', 'int')->setDefault(0);
			$table->addColumn('end_date', 'int')->setDefault(0);
			$table->addColumn('prizes', 'blob');
			$table->addColumn('referral_count', 'int')->setDefault(0);
			$table->addColumn('winner_user_id', 'int')->setDefault(0);
			$table->addColumn('start_date', 'int');
			$table->addColumn('enabled', 'tinyint', 1)->setDefault(1);
			$table->addKey('start_date');
			$table->addKey('end_date');
			$table->addKey('winner_user_id');
			$table->addKey('enabled');
		});

		$sm->createTable('xf_siropu_referral_contests_referrer_log', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('log_id', 'int')->autoIncrement();
			$table->addColumn('user_id', 'int');
			$table->addColumn('url', 'text');
			$table->addColumn('date', 'int')->setDefault(0);
			$table->addKey('user_id');
		});

		$sm->createTable('xf_siropu_referral_contests_invitation', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('invitation_code', 'varchar', 40);
			$table->addColumn('user_id', 'int');
			$table->addColumn('recipient', 'varchar', 60);
			$table->addColumn('message', 'text');
			$table->addColumn('registered_user_id', 'int')->setDefault(0);
			$table->addColumn('invitation_date', 'int')->setDefault(0);
			$table->addColumn('expiration_date', 'int')->setDefault(0);
			$table->addPrimaryKey('invitation_code');
			$table->addKey('user_id');
               $table->addKey('expiration_date');
			$table->addKey('registered_user_id');
		});

		$sm->createTable('xf_siropu_referral_contests_referral_tool', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('tool_id', 'int')->autoIncrement();
			$table->addColumn('name', 'varchar', 255);
			$table->addColumn('type', 'varchar', 20);
			$table->addColumn('content', 'varchar', 255);
			$table->addColumn('size', 'varchar', 10);
			$table->addColumn('target_url', 'varchar', 255);
			$table->addColumn('click_count', 'int')->setDefault(0);
			$table->addColumn('enabled', 'tinyint', 1)->setDefault(1);
		});

          $this->addUnconfirmedTable();

		$this->addRewardTypeTable();
		$this->addDefaultRewardType();
	}
	public function installStep3()
	{
		$this->addCustomUserField('invitation');
		$this->addCustomUserField('referrer');
	}
	public function installStep4()
	{
		$this->createWidgets();
	}
	public function upgrade2000031Step1()
	{
		$sm = $this->schemaManager();

		$sm->renameTable('siropu_referral_contests', 'xf_siropu_referral_contests_contest');
		$sm->renameTable('siropu_referral_contests_referrer_log', 'xf_siropu_referral_contests_referrer_log');
		$sm->renameTable('siropu_referral_contests_invitations', 'xf_siropu_referral_contests_invitation');
		$sm->renameTable('siropu_referral_contests_referral_tools', 'xf_siropu_referral_contests_referral_tool');
	}
	public function upgrade2000031Step2()
	{
		$this->schemaManager()->alterTable('xf_siropu_referral_contests_contest', function(Alter $table)
		{
			$table->renameColumn('contest_name', 'name');
			$table->renameColumn('contest_description', 'description');
			$table->renameColumn('contest_minimum_posts', 'minimum_posts');
			$table->renameColumn('contest_date_end', 'end_date');
			$table->renameColumn('contest_trophy_points_1st', 'trophy_points_1st');
			$table->renameColumn('contest_trophy_points_2nd', 'trophy_points_2nd');
			$table->renameColumn('contest_trophy_points_3rd', 'trophy_points_3rd');
			$table->renameColumn('contest_referral_count', 'referral_count');
			$table->renameColumn('contest_winner_user_id', 'winner_user_id');
			$table->renameColumn('contest_date_start', 'start_date');
			$table->renameColumn('contest_enabled', 'enabled');
		});
	}
	public function upgrade2000031Step3()
	{
		$this->schemaManager()->alterTable('xf_siropu_referral_contests_referrer_log', function(Alter $table)
		{
			$table->renameColumn('referrer_log_id', 'log_id');
			$table->renameColumn('referrer_user_id', 'user_id');
			$table->renameColumn('referrer_url', 'url');
			$table->renameColumn('referrer_date', 'date');
		});
	}
	public function upgrade2000031Step4()
	{
		$this->schemaManager()->alterTable('xf_siropu_referral_contests_referral_tool', function(Alter $table)
		{
			$table->renameColumn('tool_type', 'type');
			$table->renameColumn('tool_name', 'name');
			$table->renameColumn('tool_text', 'content');
			$table->renameColumn('tool_size', 'size');
			$table->renameColumn('tool_url', 'target_url');
			$table->renameColumn('tool_click_count', 'click_count');
			$table->renameColumn('tool_enabled', 'enabled');
		});
	}
	public function upgrade2000031Step5()
	{
		$this->db()->query('
			UPDATE xf_siropu_referral_contests_referral_tool
			SET content = tool_image
			WHERE type = "banner"
		');

		$this->schemaManager()->alterTable('xf_siropu_referral_contests_referral_tool', function(Alter $table)
		{
			$table->dropColumns(['tool_image']);
		});
	}
	public function upgrade2000031Step6()
	{
		$results = $this->db()->fetchAll('
			SELECT *
			FROM xf_siropu_referral_contests_referral_tool
			WHERE type = "banner"
		');

		foreach ($results as $result)
		{
			$existingPath = 'data://Siropu/images/' . $result['content'];
			$newPath      = 'data://siropu/rc/' . $result['content'];

			if ($this->app->fs()->has($existingPath))
			{
				try
				{
					$temp = File::copyAbstractedPathToTempFile($existingPath);

					File::copyFileToAbstractedPath($temp, $newPath);
					File::deleteFromAbstractedPath($existingPath);
				}
				catch (\Exception $e) {}
			}
		}
	}
	public function upgrade2000031Step7()
	{
		$this->addCustomUserField('invitation');
	}
	public function upgrade2000031Step8()
	{
		$this->createWidgets();
	}
	public function upgrade2000033Step1()
	{
		$this->addRewardTypeTable();
		$this->addDefaultRewardType();
	}
	public function upgrade2000033Step2()
	{
	     $this->schemaManager()->alterTable('xf_siropu_referral_contests_contest', function(Alter $table)
	     {
	          $table->addColumn('prizes', 'blob');
	     });
	}
	public function upgrade2000033Step3()
	{
		$results = $this->db()->fetchAll('
 		    SELECT *
 		    FROM xf_siropu_referral_contests_contest
		    WHERE (trophy_points_1st > 0 OR trophy_points_2nd > 0 OR trophy_points_3rd > 0)
 	    	');

	     foreach ($results as $result)
	     {
	          $prizes = [];

	          if ($result['trophy_points_1st'])
			{
				$prizes[] = [
					'reward_amount'  => $result['trophy_points_1st'],
					'reward_type_id' => 1
				];
			}

			if ($result['trophy_points_2nd'])
			{
				$prizes[] = [
					'reward_amount'  => $result['trophy_points_2nd'],
					'reward_type_id' => 1
				];
			}

			if ($result['trophy_points_3rd'])
			{
				$prizes[] = [
					'reward_amount'  => $result['trophy_points_3rd'],
					'reward_type_id' => 1
				];
			}

			$contest = \XF::em()->find('Siropu\ReferralContests:Contest', $result['contest_id']);
			$contest->prizes = $prizes;
			$contest->save();
	     }

		$this->schemaManager()->alterTable('xf_siropu_referral_contests_contest', function(Alter $table)
	     {
	          $table->dropColumns(['trophy_points_1st', 'trophy_points_2nd', 'trophy_points_3rd']);
	     });
	}
	public function upgrade2010070Step1()
	{
		$this->schemaManager()->alterTable('xf_siropu_referral_contests_invitation', function(Alter $table)
		{
			$table->addColumn('expiration_date', 'int')->setDefault(0);
               $table->addKey('expiration_date');
		});
	}
	public function upgrade2010070Step2()
	{
		$this->addCustomUserField('referrer');
	}
     public function upgrade2013070Step1()
     {
          $this->addUnconfirmedTable();
     }
     public function upgrade2014070Step1()
     {
          $this->schemaManager()->alterTable('xf_siropu_referral_contests_unconfirmed', function(Alter $table)
		{
               $table->addPrimaryKey('user_id');
               $table->addkey('referrer_id');
               $table->addkey('invitation_code');
		});
     }
	public function uninstallStep1()
	{
		$this->schemaManager()->alterTable('xf_user', function(Alter $table)
		{
			$table->dropColumns(['siropu_referrer_id', 'siropu_referral_count', 'siropu_referrer_credit']);
		});
	}
     public function uninstallStep2(array $stepParams = [])
	{
          foreach (\XF::finder('Siropu\ReferralContests:Contest')->fetch() as $contest)
          {
               $contest->delete();
          }
	}
	public function uninstallStep3(array $stepParams = [])
	{
		$sm = $this->schemaManager();

		$sm->dropTable('xf_siropu_referral_contests_contest');
		$sm->dropTable('xf_siropu_referral_contests_referrer_log');
		$sm->dropTable('xf_siropu_referral_contests_invitation');
		$sm->dropTable('xf_siropu_referral_contests_referral_tool');
		$sm->dropTable('xf_siropu_referral_contests_reward_type');
          $sm->dropTable('xf_siropu_referral_contests_unconfirmed');
	}
	public function uninstallStep4()
	{
		$userFields = \XF::finder('XF:UserField')
               ->where('field_id', ['siropu_invitation', 'siropu_referrer'])
               ->fetch();

          foreach ($userFields as $userField)
          {
               $userField->delete();
          }

		\XF::repository('XF:UserField')->rebuildFieldCache();
	}
	protected function addCustomUserField($type)
	{
		switch ($type)
		{
			case 'invitation':
				$userField = \XF::em()->create('XF:UserField');
				$userField->field_id = 'siropu_invitation';
				$userField->field_type = 'textbox';
				$userField->match_type = 'callback';
				$userField->match_params = [
					'callback_class' => 'Siropu\ReferralContests\Callback',
					'callback_method' => 'validateInvitation'
				];
				$userField->max_length = 40;
				$userField->required = 0;
				$userField->user_editable = 'never';
				$userField->viewable_profile = 0;
				$userField->moderator_editable = 0;
				$userField->show_registration = 0;
				$userField->save();

				$title = $userField->getMasterPhrase(true);
				$title->phrase_text = 'Invitation code';
				$title->save();

				$description = $userField->getMasterPhrase(false);
				$description->phrase_text = 'Please provide a valid invitation code.';
				$description->save();
				break;
			case 'referrer':
				$userField = \XF::em()->create('XF:UserField');
				$userField->field_id = 'siropu_referrer';
				$userField->field_type = 'textbox';
				$userField->match_type = 'callback';
				$userField->match_params = [
					'callback_class' => 'Siropu\ReferralContests\Callback',
					'callback_method' => 'validateReferrer'
				];
				$userField->max_length = 50;
				$userField->required = 0;
				$userField->user_editable = 'once';
				$userField->viewable_profile = 0;
				$userField->moderator_editable = 1;
				$userField->show_registration = 0;
				$userField->save();

				$title = $userField->getMasterPhrase(true);
				$title->phrase_text = 'Referrer';
				$title->save();

				$description = $userField->getMasterPhrase(false);
				$description->phrase_text = 'The username of the member who referred you.';
				$description->save();
				break;
		}

		\XF::repository('XF:UserField')->rebuildFieldCache();
	}
	protected function createWidgets()
	{
		$this->createWidget('siropu_referral_contests', 'siropu_referral_contests', [
			'positions' => [
				'forum_list_sidebar' => 10,
			]
		]);

		$this->createWidget('siropu_referral_link', 'siropu_referral_link', [
			'positions' => [
				'forum_list_sidebar'                  => 10,
                    'siropu_referral_contests_list_below' => 10,
                    'siropu_referral_contests_view_below' => 10
			]
		]);

          $this->createWidget('siropu_referral_top_referrers', 'siropu_referral_top_ref', [
			'positions' => [
				'forum_list_sidebar' => 10
			]
		]);
	}
	protected function addRewardTypeTable()
	{
		$this->schemaManager()->createTable('xf_siropu_referral_contests_reward_type', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('reward_type_id', 'int')->autoIncrement();
			$table->addColumn('name', 'varchar', 255);
			$table->addColumn('type', 'varchar', 20);
			$table->addColumn('currency', 'varchar', 50);
		});
	}
     protected function addUnconfirmedTable()
	{
          $this->schemaManager()->createTable('xf_siropu_referral_contests_unconfirmed', function(\XF\Db\Schema\Create $table)
		{
			$table->addColumn('user_id', 'int');
			$table->addColumn('referrer_id', 'int');
               $table->addColumn('invitation_code', 'varchar', 40);
               $table->addPrimaryKey('user_id');
               $table->addkey('referrer_id');
               $table->addkey('invitation_code');
		});
     }
	protected function addDefaultRewardType()
	{
		$rewardType = \XF::em()->create('Siropu\ReferralContests:RewardType');
		$rewardType->bulkSet([
			'name' => 'Trophy Points',
			'type' => 'trophy_points'
		]);
		$rewardType->save();
	}
}
