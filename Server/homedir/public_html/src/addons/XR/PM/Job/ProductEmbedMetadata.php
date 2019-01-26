<?php

namespace XR\PM\Job;

use XF\Job\AbstractEmbedMetadataJob;
use XF\Mvc\Entity\Entity;

class ProductEmbedMetadata extends AbstractEmbedMetadataJob
{
	protected function getIdsToRebuild(array $types)
	{
		$db = $this->app->db();

		// Note: only attachments are supported currently, so we filter based on attach count for efficiency.
		// If other types become available, this condition will need to change.
		return $db->fetchAllColumn($db->limit(
			"
				SELECT product_id
				FROM xf_xr_pm_product
				WHERE product_id > ?
					AND attach_count > 0
				ORDER BY product_id
			", $this->data['batch']
		), $this->data['start']);
	}

	protected function getRecordToRebuild($id)
	{
		return $this->app->em()->find('XR\PM:Product', $id);
	}

	protected function getPreparerContext()
	{
		return 'xr_pm_product';
	}

	protected function getMessageContent(Entity $record)
	{
		return $record->product_details;
	}

	protected function rebuildAttachments(Entity $record, \XF\Service\Message\Preparer $preparer, array &$embedMetadata)
	{
		$embedMetadata['attachments'] = $preparer->getEmbeddedAttachments();
	}

	protected function getActionDescription()
	{
		$rebuildPhrase = \XF::phrase('rebuilding');
		$type = \XF::phrase('xr_pm_products');
		return sprintf('%s... %s', $rebuildPhrase, $type);
	}
}