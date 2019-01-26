<?php

namespace MJ\SupportTicket\Sitemap;

use XF\Sitemap\Entry;

class KnowledgeBase extends \XF\Sitemap\AbstractHandler
{
	public function getRecords($start)
	{
		$app = $this->app;
		$user = \XF::visitor();

		$ids = $this->getIds('xf_mjst_kb', 'kb_id', $start);

		$productFinder = $app->finder('MJ\SupportTicket:KnowledgeBase');
		$products = $productFinder
			->where('kb_id', $ids)
			->with(['Category'])
			->order('kb_id')
			->fetch();

		return $products;
	}

	public function getEntry($record)
	{
		$url = $this->app->router('public')->buildLink('canonical:support-tickets/knowledge-base', $record);
		return Entry::create($url, [
			'lastmod' => $record->kb_date
		]);
	}

	public function isIncluded($record)
	{
		/** @var $record \MJ\SupportTicket\Entity\KnowledgeBase */
		return $record->canView() && $record->isVisible();
	}
}
