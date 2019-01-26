<?php

namespace Andy\SimilarThreads\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Thread extends XFCP_Thread
{
	public function actionIndex(ParameterBag $params)
	{
		//########################################
		// show similar threads in thread view
		//########################################

		// get parent		
		$parent = parent::actionIndex($params);
		
        // return parent action if this is a redirect or other non View response 
        if (!$parent instanceof \XF\Mvc\Reply\View)
        {
            return $parent;
        }
	
		// get visitor
		$visitor = \XF::visitor();				

		// check for user group permission
		if (!$visitor->hasPermission('similarThreads', 'view'))
		{
			return $parent;
		}
		
		// get options
		$options = \XF::options();	
		
		// get options from Admin CP -> Options -> Similar threads -> Enhanced search
		$enhancedSearch = $options->similarThreadsEnhancedSearch;
		
		// get thread
		$thread = $this->assertViewableThread($params->thread_id);		
		
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
		
		// set parent
		$parent->setParams([
		   'similarThreads' => $similarThreads
		]);	

		// return parent
		return $parent;	
	}
	
	protected function getSimilarThreadsRepo()
	{
	   return $this->repository('Andy\SimilarThreads:SimilarThreads');
	}
}