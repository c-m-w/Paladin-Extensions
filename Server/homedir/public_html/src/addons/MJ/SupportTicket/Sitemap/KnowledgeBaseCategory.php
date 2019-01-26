<?php

namespace MJ\SupportTicket\Sitemap;

use XF\Sitemap\Entry;

class KnowledgeBaseCategory extends \XF\Sitemap\AbstractHandler
{
	public function getRecords($start)
	{
		$app = $this->app;
		$user = \XF::visitor();

		$ids = $this->getIds('xf_mjst_kb_category', 'kb_category_id', $start);

		$categoryFinder = $app->finder('MJ\SupportTicket:KnowledgeBaseCategory');
		$categories = $categoryFinder
			->where('kb_category_id', $ids)
			->order('kb_category_id')
			->fetch();

		return $categories;
	}

	public function getEntry($record)
	{
		$url = $this->app->router('public')->buildLink('canonical:support-tickets/knowledge-base/category', $record);
		return Entry::create($url);
	}

	public function isIncluded($record)
	{
		/** @var $record \MJ\SupportTicket\Entity\KnowledgeBase */
		return $record->canView();
	}
}
