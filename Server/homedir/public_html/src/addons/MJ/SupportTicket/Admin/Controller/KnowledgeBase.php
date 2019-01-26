<?php

namespace MJ\SupportTicket\Admin\Controller;

use XF\Admin\Controller\AbstractController;
use XF\Mvc\Entity\ArrayCollection;
use XF\Mvc\ParameterBag;
use XF\Mvc\FormAction;

class KnowledgeBase extends AbstractController
{
	public function actionIndex()
	{
		$viewParams = $this->getKnowledgeBaseRepo()->getKnowledgeBaseListData();
		return $this->view('MJ\SupportTicket:KnowledgeBase\Listing', 'mjst_kb_list', $viewParams);
	}

	protected function kbAddEditResponse(\MJ\SupportTicket\Entity\KnowledgeBase $kb)
	{
		$repo = $this->getKnowledgeBaseRepo();

		/** @var \XF\Repository\Attachment $attachmentRepo */
		$attachmentRepo = $this->repository('XF:Attachment');
		$attachmentData = $attachmentRepo->getEditorData('support_kb', $kb);

		$viewParams = [
			'kb'             => $kb,
			'attachmentData' => $attachmentData,
			'kbCategories'       => $repo->findKnowledgeBaseCategories()->fetch()->pluckNamed('title', 'kb_category_id')
		];
		return $this->view('MJ\SupportTicket:KnowledgeBase\Edit', 'mjst_kb_edit', $viewParams);
	}

	public function actionToggle()
	{
		/** @var \XF\ControllerPlugin\Toggle $plugin */
		$plugin = $this->plugin('XF:Toggle');
		return $plugin->actionToggle('MJ\SupportTicket:KnowledgeBase', 'is_active');
	}

	public function actionEdit(ParameterBag $params)
	{
		$kb = $this->assertKnowledgeBaseExists($params->kb_id);
		return $this->kbAddEditResponse($kb);
	}

	public function actionAdd()
	{
		$kb = $this->em()->create('MJ\SupportTicket:KnowledgeBase');
		return $this->kbAddEditResponse($kb);
	}

	protected function setupKbEdit(\MJ\SupportTicket\Entity\KnowledgeBase $kb)
	{
		$input = $this->filter([
			'title'         => 'str',
			'kb_category_id'   => 'uint',
			'is_active'     => 'bool',
			'display_order' => 'uint'
		]);

		/** @var \MJ\SupportTicket\Service\KnowledgeBase\Editor $editor */
		$editor = $this->service('MJ\SupportTicket:KnowledgeBase\Editor', $kb);

		$description = $this->plugin('XF:Editor')->fromInput('description');

		$kb = $editor->getKb();
		$kb->bulkSet($input);

		$message = $this->plugin('XF:Editor')->fromInput('message');

		$kb->message = $message;

		$username = $this->filter('username', 'str');
		$userId = 0;
		if ($username)
		{
			$user = $this->finder('XF:User')->where('username', $username)->fetchOne();
			if ($user)
			{
				$userId = $user->user_id;
				$kb->user_id = $user->user_id;
				$kb->username = $user->username;
			}else{
				throw $this->exception($this->notFound(\XF::phrase('requested_user_not_found')));
			}
		}
		$editor->setAttachmentHash($this->filter('attachment_hash', 'str'));

		return $editor;
	}

	public function actionSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->kb_id)
		{
			$kb = $this->assertKnowledgeBaseExists($params->kb_id);
		}
		else
		{
			$kb = $this->em()->create('MJ\SupportTicket:KnowledgeBase');
		}

		$editor = $this->setupKbEdit($kb);

		$kb = $editor->getKb();

		if (!$editor->validate($errors))
		{
			return $this->error($errors);
		}

		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $kb */
		$kb = $editor->save();

		return $this->redirect($this->buildLink('mjst-support/kb') . $this->buildLinkHash($kb->kb_id));
	}

	public function actionDelete(ParameterBag $params)
	{
		$kb = $this->assertKnowledgeBaseExists($params->kb_id);
		if ($this->isPost())
		{
			$kb->delete();
			return $this->redirect($this->buildLink('mjst-support/kb'));
		}
		else
		{
			$viewParams = [
				'kb' => $kb
			];
			return $this->view('MJ\SupportTicket:KnowledgeBase\Delete', 'mjst_kb_delete', $viewParams);
		}
	}

	protected function categoryAddEditResponse(\MJ\SupportTicket\Entity\KnowledgeBaseCategory $kbCategory)
	{
		$viewParams = [
			'kbCategory' => $kbCategory
		];
		return $this->view('MJ\SupportTicket:KnowledgeBaseCategory\Edit', 'mjst_kb_category_edit', $viewParams);
	}

	public function actionCategoryEdit(ParameterBag $params)
	{
		$kbCategory = $this->assertCategoryExists($params->kb_category_id);
		return $this->categoryAddEditResponse($kbCategory);
	}

	public function actionCategoryAdd()
	{
		$kbCategory = $this->em()->create('MJ\SupportTicket:KnowledgeBaseCategory');
		return $this->categoryAddEditResponse($kbCategory);
	}

	protected function kbCategorySaveProcess(\MJ\SupportTicket\Entity\KnowledgeBaseCategory $kbCategory)
	{
		$form = $this->formAction();

		$input = $this->filter([
			'title'         => 'str',
			'description'   => 'str',
			'display_order' => 'uint'
		]);

		$form->basicEntitySave($kbCategory, $input);

		return $form;
	}

	public function actionCategorySave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->kb_category_id)
		{
			$kbCategory = $this->assertCategoryExists($params->kb_category_id);
		}
		else
		{
			$kbCategory = $this->em()->create('MJ\SupportTicket:KnowledgeBaseCategory');
		}

		$this->kbCategorySaveProcess($kbCategory)->run();

		return $this->redirect($this->buildLink('mjst-support/kb'));
	}

	public function actionCategoryDelete(ParameterBag $params)
	{
		$kbCategory = $this->assertCategoryExists($params->kb_category_id);
		if ($this->isPost())
		{
			$kbCategory->delete();
			return $this->redirect($this->buildLink('mjst-support/kb'));
		}
		else
		{
			$viewParams = [
				'kbCategory' => $kbCategory
			];
			return $this->view('MJ\SupportTicket:KnowledgeBaseCategory\Delete', 'mjst_kb_category_delete', $viewParams);
		}
	}

	/**
	 * @return \MJ\SupportTicket\Entity\KnowledgeBase
	 */
	protected function assertKnowledgeBaseExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:KnowledgeBase', $id, $with, $phraseKey);
	}

	/**
	 * @return \MJ\SupportTicket\Entity\KnowledgeBaseCategory
	 */
	protected function assertCategoryExists($id, $with = null, $phraseKey = null)
	{
		return $this->assertRecordExists('MJ\SupportTicket:KnowledgeBaseCategory', $id, $with, $phraseKey);
	}

	/**
	 * @return \MJ\SupportTicket\Repository\KnowledgeBase
	 */
	protected function getKnowledgeBaseRepo()
	{
		return $this->repository('MJ\SupportTicket:KnowledgeBase');
	}
}
