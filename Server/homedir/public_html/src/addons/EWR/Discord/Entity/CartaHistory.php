<?php

namespace EWR\Discord\Entity;

use XF\Mvc\Entity\Structure;

class CartaHistory extends XFCP_CartaHistory
{
	protected function _postSave()
	{
		$parent = parent::_postSave();
		
		if ($this->isInsert())
		{
			if (!empty(\XF::options()->EWRdiscord_channels['ewrcarta']))
			{
				$channel = \XF::options()->EWRdiscord_channels['ewrcarta'];
				
				$data = [
					'content' => \XF::phrase('EWRdiscord_x_edited_the_wiki_page_y', [
							'user' => $this->username,
							'title' => str_replace('@', '@𝅳', $this->Page->page_name),
							'url' => \XF::app()->router('public')->buildLink('canonical:ewr-carta', $this->Page)
						])->render('raw'),
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return $parent;
	}
}