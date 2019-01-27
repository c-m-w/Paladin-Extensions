<?php

namespace MJ\SupportTicket\Pub\Controller;

use XF\Mvc\ParameterBag;
use XF\Pub\Controller\AbstractController;

class KnowledgeBase extends AbstractController
{
	protected function preDispatchController($action, ParameterBag $params)
	{
		/** @var \XF\Entity\User $visitor */
		$visitor = \XF::visitor();

		if (!$visitor->canViewKb($error))
		{
			throw $this->exception($this->noPermission($error));
		}
	}

	public function actionIndex(ParameterBag $params)
	{
		if ($params->kb_id)
		{
			return $this->rerouteController(__CLASS__, 'view', $params);
		}

		$kbRepo = $this->getKnowledgeBaseRepo();
		$kbCategoryFinder = $kbRepo->findKnowledgeBaseCategories();

		$kbs = [];
		$limit = $this->app->options->mjstNumberFrequently;
		if($limit){
			$kbFinder = $kbRepo->findKbsForList();
			$kbFinder
				->where('is_active', true)
				->order('view_count', 'DESC')
				->limit($limit);
			$kbs = $kbFinder->fetch();
		}

		$viewParams = [
			'kbCategories' => $kbCategoryFinder->fetch(),
			'kbs'          => $kbs
		];

		return $this->view('MJ\SupportTicket:KnowledgeBase\Index', 'mjst_kb_index', $viewParams);
	}

	public function actionCategory(ParameterBag $params)
	{
		$kbCategory = $this->assertViewableKbCategory($params->kb_category_id);

		$kbRepo = $this->getKnowledgeBaseRepo();
		$kbFinder = $kbRepo->findKbsForList();

		$page = $this->filterPage();
		$perPage = $this->options()->mjstKbsPerPage;

		$kbFinder
			->where('is_active', true)
			->where('kb_category_id', $kbCategory->kb_category_id)
			->limitByPage($page, $perPage);

		$viewParams = [
			'kbs'        => $kbFinder->fetch(),
			'kbCategory' => $kbCategory,

			'total'      => $kbFinder->total(),
			'page'       => $page,
			'perPage'    => $perPage,
		];

		return $this->view('MJ\SupportTicket:KnowledgeBase\Category', 'mjst_kb_category_view', $viewParams);
	}

	public function actionView(ParameterBag $params)
	{
		$kb = $this->assertViewableKb($params->kb_id);

		$this->getKnowledgeBaseRepo()->logKbView($kb->kb_id);

		$viewParams = [
			'kb' => $kb
		];

		return $this->view('MJ\SupportTicket:KnowledgeBase\View', 'mjst_kb_view', $viewParams);
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
			'kbCategories'   => $repo->findKnowledgeBaseCategories()->fetch()->pluckNamed('title', 'kb_category_id')
		];
		return $this->view('MJ\SupportTicket:KnowledgeBase\Edit', 'mjst_kb_edit', $viewParams);
	}

	public function actionEdit(ParameterBag $params)
	{
		$kb = $this->assertViewableKb($params->kb_id);
		if (!$kb->canEdit($error))
		{
			return $this->noPermission($error);
		}
		return $this->kbAddEditResponse($kb);
	}

	public function actionCreate()
	{
		$kb = $this->em()->create('MJ\SupportTicket:KnowledgeBase');
		if (!$kb->canCreate($error))
		{
			return $this->noPermission($error);
		}
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

		$visitor = \XF::visitor();

		$kb->user_id = $visitor->user_id;
		$kb->username = $visitor->username;

		$editor->setAttachmentHash($this->filter('attachment_hash', 'str'));

		return $editor;
	}

	public function actionSave(ParameterBag $params)
	{
		$this->assertPostOnly();

		if ($params->kb_id)
		{
			$kb = $this->assertViewableKb($params->kb_id);
			if (!$kb->canEdit($error))
			{
				return $this->noPermission($error);
			}
		}
		else
		{
			$kb = $this->em()->create('MJ\SupportTicket:KnowledgeBase');
			if (!$kb->canCreate($error))
			{
				return $this->noPermission($error);
			}
		}

		$editor = $this->setupKbEdit($kb);

		$kb = $editor->getKb();

		if (!$editor->validate($errors))
		{
			return $this->error($errors);
		}

		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $kb */
		$kb = $editor->save();

		if ($this->request->exists('exit'))
		{
			$redirect = $this->buildLink('support-tickets/knowledge-base') . $this->buildLinkHash($kb->kb_id);
		}
		else
		{
			$redirect = $this->buildLink('support-tickets/knowledge-base/view', $kb);
		}
		return $this->redirect($redirect);
	}

	public function actionDelete(ParameterBag $params)
	{
		$kb = $this->assertViewableKb($params->kb_id);

		if (!$kb->canDelete($error))
		{
			return $this->noPermission($error);
		}

		if($this->isPost()){
			$kb->delete();
			return $this->redirect($this->buildLink('support-tickets/knowledge-base'));
		}else{
			$viewParams = [
				'kb' => $kb
			];
			return $this->view('MJ\SupportTicket:KnowledgeBase\Delete', 'mjst_kb_delete', $viewParams);
		}
	}

	public function actionRate(ParameterBag $params)
	{
		$kb = $this->assertViewableKb($params->kb_id);

		if (!$kb->canRate($error))
		{
			return $this->noPermission($error);
		}
		if($this->isPost()){
			if(!\XF::app()->request()->getCookie('msjtkb_' . $kb->kb_id)){
				$useful = $this->filter('useful', 'str');
				$kb->rating_count++;
				$kb->rating_sum += $useful ? 1 : 0;
				$kb->save();
				$this->app->response()->setCookie('msjtkb_' . $kb->kb_id, 1);
			}

			return $this->redirect($this->buildLink('support-tickets/knowledge-base', $kb));
		}else{
			$viewParams = [
				'kb' => $kb
			];
			return $this->view('MJ\SupportTicket:KnowledgeBase\Delete', 'mjst_kb_rate', $viewParams);
		}
	}

	public function actionSuggest()
	{
		$q = ltrim($this->filter('q', 'str', ['no-trim']));

		$limit = $this->options()->mjstNumberSuggestKb;
		if ($q !== '' && utf8_strlen($q) >= 2 && $limit > 0)
		{
			/** @var \MJ\SupportTicket\Finder\KnowledgeBase $kbFinder */
			$kbFinder = $this->finder('MJ\SupportTicket:KnowledgeBase');

			$kbs = $kbFinder
				->where('title', 'like', $kbFinder->escapeLike($q, '%?%'))
				->fetch($limit);
		}
		else
		{
			$kbs = [];
			$q   = '';
		}

		$viewParams = [
			'q'   => $q,
			'kbs' => $kbs
		];
		return $this->view('MJ\SupportTicket:KnowledgeBase\Suggest', 'mjst_kb_suggest', $viewParams);
	}

	/**
	 * @param $messageId
	 * @param array $extraWith
	 *
	 * @return \MJ\SupportTicket\Entity\TicketMessage
	 *
	 * @throws \XF\Mvc\Reply\Exception
	 */
	protected function assertViewableKb($kbId, array $extraWith = [])
	{
		$extraWith[] = 'Category';
		$extraWith[] = 'User';

		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $kb */
		$kb = $this->em()->find('MJ\SupportTicket:KnowledgeBase', $kbId, $extraWith);
		if (!$kb)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_kb_not_found')));
		}
		if (!$kb->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		return $kb;
	}

	protected function assertViewableKbCategory($kbCategoryId, array $extraWith = [])
	{
		/** @var \MJ\SupportTicket\Entity\KnowledgeBase $kb */
		$kbCategory = $this->em()->find('MJ\SupportTicket:KnowledgeBaseCategory', $kbCategoryId, $extraWith);
		if (!$kbCategory)
		{
			throw $this->exception($this->notFound(\XF::phrase('mjst_requested_kb_category_not_found')));
		}
		if (!$kbCategory->canView($error))
		{
			throw $this->exception($this->noPermission($error));
		}

		return $kbCategory;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\KnowledgeBase
	 */
	protected function getKnowledgeBaseRepo()
	{
		return $this->repository('MJ\SupportTicket:KnowledgeBase');
	}
}