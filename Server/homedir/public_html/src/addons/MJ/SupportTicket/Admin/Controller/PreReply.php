<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class PreReply extends AbstractController
{
	public function actionIndex()
	{
		$viewParams = $this->getPreReplyRepo()->getPreReplyListData(true);
		return $this->view('MJ\SupportTicket:PreReply\Listing', 'mjst_pre_reply_list', $viewParams);
	}

	protected function replyAddEditResponse(\MJ\SupportTicket\Entity\PreReply $reply)
	{
		$repo = $this->getPreReplyRepo();

		$viewParams = [
			'reply'         => $reply,
			'replyGroups'   => $repo->findPreReplyGroups()->fetch()->pluckNamed('title', 'reply_group_id')
		];
		return $this->view('MJ\SupportTicket:PreReply\Edit', 'mjst_pre_reply_edit', $viewParams);
	}

	public function actionToggle()
	{
		/** @var \XF\ControllerPlugin\Toggle $plugin */
		$plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('MJ\SupportTicket:PreReply', 'is_active');
	}

	public function actionEdit(ParameterBag $params)
	{
		$reply = $this->assertPreReplyExists($params->reply_id);
		return $this->replyAddEditResponse($reply);
	}

	public function actionAdd()
	{
		$reply = $this->em()->create('MJ\SupportTicket:PreReply');
		return $this->replyAddEditResponse($reply);
	}

	protected function replySaveProcess(\MJ\SupportTicket\Entity\PreReply $reply)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title'          => 'str',
			'reply_group_id' => 'uint',
			'is_active'      => 'bool',
			'display_order'  => 'uint'
		]);

		$message = $this->plugin('XF:Editor')->fromInput('message');

		$usableUserGroups = $this->filter('usable_user_group', 'str');
		if ($usableUserGroups == 'all')
		{
			$input['allowed_user_group_ids'] = [-1];
		}
		else
		{
			$input['allowed_user_group_ids'] = $this->filter('usable_user_group_ids', 'array-uint');
		}

		$reply->message = $message;

		$form->basicEntitySave($reply, $input);

		return $form;
	}

	public function actionSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->reply_id)
		{
			$reply = $this->assertPreReplyExists($params->reply_id);
		}
		else
		{
			$reply = $this->em()->create('MJ\SupportTicket:PreReply');
		}

		$this->replySaveProcess($reply)->run();

		return $this->redirect($this->buildLink('mjst-support/predefined-replies'));
	}

	public function actionDelete(ParameterBag $params)
	{
		$reply = $this->assertPreReplyExists($params->reply_id);
		if ($this->isPost())
		{
			$reply->delete();
			return $this->redirect($this->buildLink('mjst-support/predefined-replies'));
		}
		else
		{
			$viewParams = [
				'reply' => $reply
			];
			return $this->view('MJ\SupportTicket:PreReply\Delete', 'mjst_pre_reply_delete', $viewParams);
		}
	}

	protected function groupAddEditResponse(\MJ\SupportTicket\Entity\PreReplyGroup $replyGroup)
	{
		$viewParams = [
			'replyGroup' => $replyGroup
		];
		return $this->view('MJ\SupportTicket:PreReplyGroup\Edit', 'mjst_pre_reply_group_edit', $viewParams);
	}

	public function actionGroupEdit(ParameterBag $params)
	{
		$replyGroup = $this->assertGroupExists($params->reply_group_id);
		return $this->groupAddEditResponse($replyGroup);
	}

	public function actionGroupAdd()
	{
		$replyGroup = $this->em()->create('MJ\SupportTicket:PreReplyGroup');
		return $this->groupAddEditResponse($replyGroup);
	}

	protected function replyGroupSaveProcess(\MJ\SupportTicket\Entity\PreReplyGroup $replyGroup)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title'         => 'str',
			'display_order' => 'uint'
		]);

		$form->basicEntitySave($replyGroup, $input);

		return $form;
	}

	public function actionGroupSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->reply_group_id)
		{
			$replyGroup = $this->assertGroupExists($params->reply_group_id);
		}
		else
		{
			$replyGroup = $this->em()->create('MJ\SupportTicket:PreReplyGroup');
		}

		$this->replyGroupSaveProcess($replyGroup)->run();

		return $this->redirect($this->buildLink('mjst-support/predefined-replies'));
	}

	public function actionGroupDelete(ParameterBag $params)
	{
		$replyGroup = $this->assertGroupExists($params->reply_group_id);
		if ($this->isPost())
		{
			$replyGroup->delete();
			return $this->redirect($this->buildLink('mjst-support/predefined-replies'));
		}
		else
		{
			$viewParams = [
				'replyGroup' => $replyGroup
			];
			return $this->view('MJ\SupportTicket:PreReplyGroup\Delete', 'mjst_pre_reply_group_delete', $viewParams);
		}
	}

	/**
	 * @return \MJ\SupportTicket\Entity\PreReply
	 */
	protected function assertPreReplyExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:PreReply', $id, $with, $phraseKey);
	}

	/**
	 * @return \MJ\SupportTicket\Entity\PreReplyGroup
	 */
	protected function assertGroupExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:PreReplyGroup', $id, $with, $phraseKey);
	}

	/**
	 * @return \MJ\SupportTicket\Repository\PreReply
	 */
	protected function getPreReplyRepo()
	{
		return $this->repository('MJ\SupportTicket:PreReply');
	}
}
