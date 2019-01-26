<?php

namespace Andy\SimilarThreads\XF\Pub\Controller;

use XF\Mvc\ParameterBag;

class Forum extends XFCP_Forum
{
	public function actionSimilarThreads(ParameterBag $params)
	{
		//########################################
		// show similar threads in post create
		//########################################

		// get parent		
		$parent = parent::actionIndex($params);
		
		// get visitor
		$visitor = \XF::visitor();				

		// check for user group permission
		if (!$visitor->hasPermission('similarThreads', 'view'))
		{
			return $parent;
		}

		// get options
		$options = \XF::options();	
		
		// get options from Admin CP -> Options -> Similar threads -> Show post thread
		$showPostThread = $options->similarThreadsShowPostThread;
		
		// if not showPostThread
		if (!$showPostThread)
		{
			return $parent;
		}
		
		// get options from Admin CP -> Options -> Similar threads -> Enhanced search
		$enhancedSearch = $options->similarThreadsEnhancedSearch;
		
		// get currentNodeId
		$currentNodeId = $params->node_id;
		
		// set currentThreadId
		$currentThreadId = 0;
		
		// get thread title
		$threadTitle = $this->filter('title', 'str');
		
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
		return $this->view('Andy\SimilarThreads:PostThread', 'andy_similarthreads_post_thread', $viewParams);
	}
	
	protected function getSimilarThreadsRepo()
	{
	   return $this->repository('Andy\SimilarThreads:SimilarThreads');
	}
}