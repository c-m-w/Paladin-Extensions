<?php

namespace Andy\SimilarThreads\Widget;

use \XF\Widget\AbstractWidget;

class SimilarThreads extends AbstractWidget
{
    public function render()
    {
		//########################################
		// show similar threads in thread view
		// in a widget
		//########################################
	
		// get visitor
		$visitor = \XF::visitor();				

		// check for user group permission
		if (!$visitor->hasPermission('similarThreads', 'view'))
		{
			return;
		}
		
		// get options
		$options = \XF::options();	
		
		// get options from Admin CP -> Options -> Similar threads -> Enhanced search
		$enhancedSearch = $options->similarThreadsEnhancedSearch;
		
		// get thread
		$thread = $this->contextParams['thread'];
		
		// get currentNodeId
		$currentNodeId = $thread->node_id;

		// get currentThreadId
		$currentThreadId = $thread->thread_id;
		
		// get thread title
		$threadTitle = $thread->title;
	
		// use standard search
		if (!$enhancedSearch)
		{
			$similarThreads = $this->getSimilarThreadsRepo()->getSimilarThreads($currentNodeId, $currentThreadId, $threadTitle);
		}
		
		// use enhanced search
		if ($enhancedSearch)
		{
			$similarThreads = $this->getSimilarThreadsRepo()->getSimilarThreadsEnhanced($currentNodeId, $currentThreadId, $threadTitle);
		}
		
		// prepare viewParams
		$viewParams = [
			'similarThreads' => $similarThreads
		];
		
		// send to template
		return $this->renderer('andy_similarthreads_widget', $viewParams);
    }

	public function getOptionsTemplate()
	{
	   return null;
	}
	
	protected function getSimilarThreadsRepo()
	{
	   return $this->repository('Andy\SimilarThreads:SimilarThreads');
	}
}