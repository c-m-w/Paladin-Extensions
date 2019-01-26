<?php

namespace MJ\SupportTicket\Entity;

use XF\Mvc\Entity\Entity;
use XF\Mvc\Entity\Structure;

class KnowledgeBase extends Entity implements \XF\BbCode\RenderableContentInterface
{
	public function canView(&$error = null)
	{
		return \XF::visitor()->canViewKb();
	}

	public function canCreate(&$error = null)
	{
		if(!\XF::visitor()->user_id){
			return false;
		}
		return \XF::visitor()->hasPermission('mjstKb', 'create');
	}

	public function canEdit(&$error = null)
	{
		$userId = \XF::visitor()->user_id;
		if(!$userId){
			return false;
		}

		if(\XF::visitor()->hasPermission('mjstKb', 'editAnyKb')){
			return true;
		}
		if($this->user_id == $userId && $this->canCreate()){
			return true;
		}
		return false;
	}

	public function canRate(&$error = null)
	{
		return !\XF::app()->request()->getCookie('msjtkb_' . $this->kb_id) &&
		\XF::visitor()->hasPermission('mjstKb', 'rate');
	}

	public function canDelete(&$error = null)
	{
		return \XF::visitor()->user_id && \XF::visitor()->hasPermission('mjstKb', 'editAnyKb');
	}

	public function isVisible()
	{
		return $this->is_active;
	}

	public function isAttachmentEmbedded($attachmentId)
	{
		if (!$this->embed_metadata)
		{
			return false;
		}

		if ($attachmentId instanceof \XF\Entity\Attachment)
		{
			$attachmentId = $attachmentId->attachment_id;
		}

		return isset($this->embed_metadata['attachments'][$attachmentId]);
	}

	public function getBbCodeRenderOptions($context, $type)
	{
		return [
			'entity'          => $this,
			'user'            => $this->User,
			'attachments'     => $this->attach_count ? $this->Attachments : [],
			'viewAttachments' => true
		];
	}

	public function getBreadcrumbs($includeSelf = true)
	{
		$breadcrumbs = $this->Category ? $this->Category->getBreadcrumbs() : [];
		if ($includeSelf)
		{
			$breadcrumbs[] = [
				'href' => $this->app()->router()->buildLink('support-tickets/kb', $this),
				'value' => $this->title
			];
		}

		return $breadcrumbs;
	}

	protected function _postSave()
	{
		$this->rebuildKbCaches();
	}

	protected function _postDelete()
	{
		$this->rebuildKbCaches();
	}

	protected function rebuildKbCaches()
	{
		$repo = $this->getKbRepo();

		\XF::runOnce('mjstKbCaches', function() use ($repo)
		{
			$repo->rebuildKnowledgeBaseMaterializedOrder();
		});
	}

	protected function _setupDefaults()
	{
		$this->is_active = true;
	}

	public static function getStructure(Structure $structure)
	{
		$structure->table = 'xf_mjst_kb';
		$structure->shortName = 'MJ\SupportTicket:KnowledgeBase';
		$structure->primaryKey = 'kb_id';
		$structure->contentType = 'support_kb';
		$structure->columns = [
			'kb_id'              => ['type' => self::UINT, 'nullable' => true, 'autoIncrement' => true],
			'title'              => ['type' => self::STR, 'required' => true],
			'user_id'            => ['type' => self::UINT, 'required' => true],
			'username'           => ['type' => self::STR, 'required' => true, 'maxLength' => 50],
			'message'            => ['type' => self::STR, 'required' => true],
			'kb_category_id'     => ['type' => self::UINT, 'required' => true],
			'view_count'         => ['type' => self::UINT, 'default' => 0],
			'attach_count'       => ['type' => self::UINT, 'default' => 0],
			'rating_count'       => ['type' => self::UINT, 'default' => 0],
			'rating_sum'         => ['type' => self::UINT, 'default' => 0],
			'kb_date'            => ['type' => self::UINT, 'default' => \XF::$time],
			'is_active'          => ['type' => self::BOOL, 'default' => 1],
			'display_order'      => ['type' => self::UINT, 'default' => 0],
			'materialized_order' => ['type' => self::UINT, 'default' => 0],
			'embed_metadata'     => ['type' => self::JSON_ARRAY, 'nullable' => true, 'default' => null]
		];
		$structure->relations = [
			'Category' => [
				'entity'     => 'MJ\SupportTicket:KnowledgeBaseCategory',
				'type'       => self::TO_ONE,
				'conditions' => 'kb_category_id',
				'primary'    => true
			],
			'User' => [
				'entity'     => 'XF:User',
				'type'       => self::TO_ONE,
				'conditions' => 'user_id',
				'primary'    => true
			],
			'Attachments' => [
				'entity' => 'XF:Attachment',
				'type' => self::TO_MANY,
				'conditions' => [
					['content_type', '=', 'support_kb'],
					['content_id', '=', '$kb_id']
				],
				'with' => 'Data',
				'order' => 'attach_date'
			],
		];
		$structure->getters = [];

		return $structure;
	}

	/**
	 * @return \MJ\SupportTicket\Repository\KnowledgeBase
	 */
	protected function getKbRepo()
	{
		return $this->repository('MJ\SupportTicket:KnowledgeBase');
	}
}
