<?php

namespace EWR\Discord\Repository;

use XF\Mvc\Entity\AbstractCollection;
use XF\Mvc\Entity\Repository;

class RioStream extends XFCP_RioStream
{
	public function scrapeStreams()
	{
        $parent = parent::scrapeStreams();
		
		if (!empty($this->options()->EWRdiscord_channels['ewrrio']))
		{
			$channel = \XF::options()->EWRdiscord_channels['ewrrio'];
			$streams = $this->findStream()
				->where('stream_start', 0)
				->where('stream_featured', 1)
				->fetch();
				
			foreach ($streams AS $stream)
			{
				$url = \XF::app()->router('public')->buildLink('canonical:ewr-rio', $stream);
				$content = \XF::phrase('EWRdiscord_x_now_streaming_y_z', [
					'title' => str_replace('@', '@𝅳', $stream->stream_title),
					'status' => str_replace('@', '@𝅳', $stream->stream_status),
					'url' => $url
				])->render();
				
				$data = [
					'content' => $content,
					'embed' => [
						'description' => str_replace('@', '@𝅳', $stream->stream_status),
						'url' => $url,
						'image' => [
							'url' => $stream->stream_preview.'?'.\XF::$time,
						],
						'thumbnail' => [
							'url' => $stream->stream_thumb.'?'.\XF::$time,
						],
						'author' => [
							'name' => $stream->stream_title.' ('.$stream->Service->service_name.')',
							'url' => $url,
							'icon_url' => $stream->stream_thumb.'?'.\XF::$time,
						],
						'fields' => [
							[
								'name' => \XF::phrase('EWRrio_game')->render(),
								'value' => $stream->stream_game,
								'inline' => true,
							],
						],
					],
				];
				
				$this->repository('EWR\Discord:Discord')->postToChannel($channel, $data);
			}
		}
		
		return $parent;
	}
}