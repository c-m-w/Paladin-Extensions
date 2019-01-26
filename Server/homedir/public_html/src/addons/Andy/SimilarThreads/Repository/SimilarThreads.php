<?php

namespace Andy\SimilarThreads\Repository;

use XF\Mvc\Entity\Repository;

class SimilarThreads extends Repository
{
	public function getSimilarThreads($currentNodeId, $currentThreadId, $threadTitle)
	{
		//########################################
		// get similar threads
		//########################################

		// get options
		$options = \XF::options();	
		
		// get options from Admin CP -> Options -> Similar threads -> Exclude days
		$excludeDays = $options->similarThreadsExcludeDays;

		// get options from Admin CP -> Options -> Similar threads -> Exclude forums
		$excludeForums = $options->similarThreadsExcludeForums;
		
		// get options from Admin CP -> Options -> Similar threads -> Miniumum common word length
		$minimumCommonWordLength = $options->similarThreadsMinimumCommonWordLength;
		
		// get options from Admin CP -> Options -> Similar threads -> Maximum results
		$maximumResults = $options->similarThreadsMaximumResults;
		
		// get options from Admin CP -> Options -> Similar threads -> Multibyte
		$multibyte = $options->similarThreadsMultibyte;
		
		// get options from Admin CP -> Options -> Similar threads -> Same forum
		$sameForum = $options->similarThreadsSameForum;
		
		// get options from Admin CP -> Options -> Similar threads -> Stop characters
		$stopCharacters = $options->similarThreadsStopCharacters;
		
		// get options from Admin CP -> Options -> Similar threads -> Stop words
		$stopWords = $options->similarThreadsStopWords;

		//########################################
		// define variables
		//########################################
		
		// set other variables
		$searchWords = array();
		$searchWord1 = '';
		$searchWord2 = '';
		$searchWord3 = '';
		$results1 = array();
		$results2 = array();
		$results3 = array();
		$results4 = array();
		$results5 = array();
		
		//########################################
		// return if currentNodeId is excluded
		//########################################

		// check for excluded forums
		if (in_array($currentNodeId, $excludeForums))
		{
			return;
		}

		//########################################
		// prepare search words
		//########################################
		
		// get stopCharactersArray
		$stopCharactersArray = explode(' ', $stopCharacters);			
		
		// remove characters			
		$threadTitle = str_replace($stopCharactersArray, ' ', $threadTitle);

		if (!$multibyte)
		{
			// put into array
			$threadTitleArray = explode(' ', $threadTitle);
		}
		
		if ($multibyte)
		{			
			// put into array
			$threadTitleArray = mb_split(' ', $threadTitle);
		} 
		
		// create stopWordsArray
		$stopWordsArray = explode(' ', $stopWords);								
 		
		// remove words from array
		foreach ($threadTitleArray as $var)
		{
			if (!$multibyte)
			{
				if (!in_array(strtolower($var), $stopWordsArray))
				{		
					// verify minimumCommonWordLength			
					if (strlen($var) >= $minimumCommonWordLength)
					{
						$searchWords[] = $var;
					}
				}
			}

			if ($multibyte)
			{
				if (!in_array(mb_strtolower($var), $stopWordsArray))
				{	
					// verify minimumCommonWordLength				
					if (mb_strlen($var) >= $minimumCommonWordLength)
					{
						$searchWords[] = $var;
					}
				}
			}
		}

		// get count
		$count = count($searchWords);

		// return if no searchWords
		if ($count == 0)
		{
			return;
		}			
		
		// continue we have a search word
		if ($count > 0)
		{				
			// get first search word
			$searchWord1 = $searchWords[0];
			
			if ($count > 1)
			{	
				// get second search word
				$searchWord2 = $searchWords[1];	
			}
			
			if ($count > 2)
			{	
				// get third search word
				$searchWord3 = $searchWords[2];	
			}							
		}
		
		//########################################
		// exclude by age
		//########################################	
		
		if ($excludeDays > 0)
		{
			// convert to Unix timestamp
			$gte = time() - (86400 * $excludeDays);
		}
		else
		{
			$gte = 0;
		}
	
		//########################################
		// create conditions variable for nodes
		//########################################
		
		if (!$sameForum)
		{
			// get all viewable nodes
			$nodeRepo = $this->repository('XF:Node');
			$nodes = $nodeRepo->getNodeList();
			$nodeIds = $nodes->keys();
			
			$arr = array_diff($nodeIds, $excludeForums);
			$result = array_values($arr);
			
			foreach ($result AS $k => $v)
			{
				$conditionsOr[] = ['node_id', '=', $v];
			}
		}
		
		if ($sameForum)
		{
			// get array
			$currentNodeIdArray = $currentNodeId;
			
			$conditionsOr[] = ['node_id', '=', $currentNodeIdArray];
		}				

		//########################################
		// search 1
		//########################################

		if ($searchWord1 != '' AND $searchWord2 != '' AND $searchWord3 != '')
		{
			$maximumResults1 = $maximumResults;	
	
			$finder = \XF::finder('XF:Thread');
			$threads1 = $finder
				->where('title', 'LIKE', $finder->escapeLike($searchWord1, '%?%'))
				->where('title', 'LIKE', $finder->escapeLike($searchWord2, '%?%'))
				->where('title', 'LIKE', $finder->escapeLike($searchWord3, '%?%'))
				->where('discussion_state', '=', 'visible')
				->where('discussion_type', '<>', 'redirect')
				->where('post_date', '>=', $gte)
				->where('thread_id', '<>', $currentThreadId)
				->whereOr($conditionsOr)
				->order('post_date', 'DESC')
				->limit($maximumResults1)
				->fetch();

			// convert object to array
			foreach ($threads1 as $k => $v)
			{
				$results1[] = array(
					'thread_id' => $v->thread_id
				);
			}

			// prepare results for return
			$results = $results1;
		}

		//########################################
		// search 2
		//########################################		
		
		if ($searchWord1 != '' AND $searchWord2 != '')
		{				
			foreach ($results1 AS $k => $v)
			{
				$threadId = $v['thread_id'];
				$conditions[] = ['thread_id', '<>', $threadId];
			}
			
			if (empty($conditions))
			{
				$conditions = [];
			}

			$count = count($results1);	

			if ($count < $maximumResults AND is_numeric($count))
			{
				$maximumResults2 = $maximumResults - $count;

				$finder = \XF::finder('XF:Thread');
				$threads2 = $finder
					->where('title', 'LIKE', $finder->escapeLike($searchWord1, '%?%'))
					->where('title', 'LIKE', $finder->escapeLike($searchWord2, '%?%'))
					->where('discussion_state', '=', 'visible')
					->where('discussion_type', '<>', 'redirect')
					->where('post_date', '>=', $gte)
					->where('thread_id', '<>', $currentThreadId)
					->where($conditions)
					->whereOr($conditionsOr)
					->order('post_date', 'DESC')
					->limit($maximumResults2)
					->fetch();

				// convert object to array
				foreach ($threads2 as $k => $v)
				{
					$results2[] = array(
						'thread_id' => $v->thread_id
					);
				}	

				// prepare results for return
				$results = array_merge($results1, $results2);
			}
		}		
		
		//########################################
		// search 3
		//########################################

		if ($searchWord1 != '')
		{	
			foreach ($results2 AS $k => $v)
			{
				$threadId = $v['thread_id'];
				$conditions[] = ['thread_id', '<>', $threadId];
			}
			
			if (empty($conditions))
			{
				$conditions = [];
			}
			
			$count = count($results1) + count($results2);

			if ($count < $maximumResults AND is_numeric($count))
			{
				$maximumResults3 = $maximumResults - $count;

				$finder = \XF::finder('XF:Thread');
				$threads3 = $finder
					->where('title', 'LIKE', $finder->escapeLike($searchWord1, '%?%'))
					->where('discussion_state', '=', 'visible')
					->where('discussion_type', '<>', 'redirect')
					->where('post_date', '>=', $gte)
					->where('thread_id', '<>', $currentThreadId)
					->where($conditions)
					->whereOr($conditionsOr)
					->order('post_date', 'DESC')
					->limit($maximumResults3)
					->fetch();

				// convert object to array
				foreach ($threads3 as $k => $v)
				{
					$results3[] = array(
						'thread_id' => $v->thread_id
					);
				}

				// prepare results for return
				$results = array_merge($results1, $results2, $results3);
			}
		}

		//########################################
		// search 4
		//########################################
		
		if ($searchWord2 != '')
		{
			foreach ($results3 AS $k => $v)
			{
				$threadId = $v['thread_id'];
				$conditions[] = ['thread_id', '<>', $threadId];
			}
			
			if (empty($conditions))
			{
				$conditions = [];
			}
			
			$count = count($results1) + count($results2) + count($results3);

			if ($count < $maximumResults AND is_numeric($count))
			{
				$maximumResults4 = $maximumResults - $count;
				
				$finder = \XF::finder('XF:Thread');
				$threads4 = $finder
					->where('title', 'LIKE', $finder->escapeLike($searchWord2, '%?%'))
					->where('discussion_state', '=', 'visible')
					->where('discussion_type', '<>', 'redirect')
					->where('post_date', '>=', $gte)
					->where('thread_id', '<>', $currentThreadId)
					->where($conditions)
					->whereOr($conditionsOr)
					->order('post_date', 'DESC')
					->limit($maximumResults4)
					->fetch();

				// convert object to array
				foreach ($threads4 as $k => $v)
				{
					$results4[] = array(
						'thread_id' => $v->thread_id
					);
				}	
				
				// get results
				$results = array_merge($results1, $results2, $results3, $results4);
			} 
		}
		
		//########################################
		// search 5
		//########################################
		
		if ($searchWord3 != '')
		{
			foreach ($results4 AS $k => $v)
			{
				$threadId = $v['thread_id'];
				$conditions[] = ['thread_id', '<>', $threadId];
			}
			
			if (empty($conditions))
			{
				$conditions = [];
			}
			
			$count = count($results1) + count($results2) + count($results3) + count($results4);

			if ($count < $maximumResults AND is_numeric($count))
			{
				$maximumResults5 = $maximumResults - $count;
				
				$finder = \XF::finder('XF:Thread');
				$threads5 = $finder
					->where('title', 'LIKE', $finder->escapeLike($searchWord2, '%?%'))
					->where('discussion_state', '=', 'visible')
					->where('discussion_type', '<>', 'redirect')
					->where('post_date', '>=', $gte)
					->where('thread_id', '<>', $currentThreadId)
					->where($conditions)
					->whereOr($conditionsOr)
					->order('post_date', 'DESC')
					->limit($maximumResults5)
					->fetch();

				// convert object to array
				foreach ($threads5 as $k => $v)
				{
					$results5[] = array(
						'thread_id' => $v->thread_id
					);
				}	
				
				// get results
				$results = array_merge($results1, $results2, $results3, $results4, $results5);
			} 
		}	

		//########################################
		// prepare similarThreads
		//########################################
		
		// return if no similarThreads
		if (empty($results))
		{
			return;
		}
		
		// unset array
		unset($conditions);
		
		// get conditions
		foreach ($results AS $k => $v)
		{
			$threadId = $v['thread_id'];
			$conditions[] = ['thread_id', '=', $threadId];
		}

		// continue if not empty
		if (!empty($conditions))
		{
			// create similarThreads object
			$finder = \XF::finder('XF:Thread');
			$similarThreads = $finder
				->whereOr($conditions)
				->order('post_date', 'DESC')
				->fetch();
		}
		else
		{
			$similarThreads = array();
		}

		// return similarThreads
		return $similarThreads;
	}
	
	public function getSimilarThreadsEnhanced($currentNodeId, $currentThreadId, $threadTitle)
	{
		//########################################
		// get similar threads enhanced
		//########################################

		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Similar threads -> Exclude days
		$excludeDays = $options->similarThreadsExcludeDays;

		// get options from Admin CP -> Options -> Similar threads -> Exclude forums
		$excludeForums = $options->similarThreadsExcludeForums;
		
		// get options from Admin CP -> Options -> Similar threads -> Maximum results
		$maximumResults = $options->similarThreadsMaximumResults;
		
		// get options from Admin CP -> Options -> Similar threads -> Miniumum common word length
		$minimumCommonWordLength = $options->similarThreadsMinimumCommonWordLength;
		
		// get options from Admin CP -> Options -> Similar threads -> Multibyte
		$multibyte = $options->similarThreadsMultibyte;
		
		// get options from Admin CP -> Options -> Similar threads -> Same forum
		$sameForum = $options->similarThreadsSameForum;
		
		// get options from Admin CP -> Options -> Similar threads -> Stop characters
		$stopCharacters = $options->similarThreadsStopCharacters;
		
		// get options from Admin CP -> Options -> Similar threads -> Stop words
		$stopWords = $options->similarThreadsStopWords;
		
		// get options from Admin CP -> Options -> Debug options -> xfesEnabled
		$xfesEnabled = @$options->xfesEnabled;
		
		// return error log
		if (!$xfesEnabled)
		{
			\XF::app()->error()->logError("Please deselect Enhanced search in Similar threads options page.");
			return;
		}

		//########################################
		// define variables
		//########################################
		
		// set other variables
		$searchWords = array();
		$searchWord1 = '';
		$searchWord2 = '';
		$searchWord3 = '';
		$excludeThreadIds = array();
		$continue = true;
		$threadIds = array();
		
		//########################################
		// return if currentNodeId is excluded
		//########################################

		// check for excluded forums
		if (in_array($currentNodeId, $excludeForums))
		{
			return;
		}

		//########################################
		// prepare search words
		//########################################
		
		// get stopCharactersArray
		$stopCharactersArray = explode(' ', $stopCharacters);			
		
		// remove characters			
		$threadTitle = str_replace($stopCharactersArray, ' ', $threadTitle);

		if (!$multibyte)
		{
			// put into array
			$threadTitleArray = explode(' ', $threadTitle);
		}
		
		if ($multibyte)
		{			
			// put into array
			$threadTitleArray = mb_split(' ', $threadTitle);
		} 
		
		// create stopWordsArray
		$stopWordsArray = explode(' ', $stopWords);								
 		
		// remove words from array
		foreach ($threadTitleArray as $var)
		{
			if (!$multibyte)
			{
				if (!in_array(strtolower($var), $stopWordsArray))
				{		
					// verify minimumCommonWordLength			
					if (strlen($var) >= $minimumCommonWordLength)
					{
						$searchWords[] = $var;
					}
				}
			}

			if ($multibyte)
			{
				if (!in_array(mb_strtolower($var), $stopWordsArray))
				{	
					// verify minimumCommonWordLength				
					if (mb_strlen($var) >= $minimumCommonWordLength)
					{
						$searchWords[] = $var;
					}
				}
			}
		}

		// get count
		$count = count($searchWords);

		// return in no searchWords
		if ($count == 0)
		{
			return;
		}			
		
		// continue we have a search word
		if ($count > 0)
		{				
			// get first search word
			$searchWord1 = $searchWords[0];
			
			if ($count > 1)
			{	
				// get second search word
				$searchWord2 = $searchWords[1];	
			}
			
			if ($count > 2)
			{	
				// get third search word
				$searchWord3 = $searchWords[2];	
			}							
		}

		//########################################
		// exclude by age
		//########################################	
		
		if ($excludeDays > 0)
		{
			// convert to Unix timestamp
			$gte = time() - (86400 * $excludeDays);
		}
		else
		{
			$gte = 0;
		}

		//########################################
		// get eleasticsearch information
		//########################################
		
		// get configArray
		$configArray = $options->xfesConfig;

		// get host	
		$host = $configArray['host'];			

		// get port
		$port = $configArray['port'];

		// get index
		$index = $configArray['index'];

		// declare ch
		$ch = curl_init($host . ':' . $port . '/' . $index . '/xf/_search?pretty=true');	

		// set curl option
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

		// get results
		$results = curl_exec($ch);

		// return if no results
		if ($results == '')
		{
			return;
		}
		
		//########################################
		// get excludeNodeIds
		//########################################
		
		if (!empty($excludeForums))
		{
			foreach ($excludeForums as $value)
			{
				$excludeNodeIds[] = $value;
			}
		}
		
		if (empty($excludeForums))
		{
			$excludeNodeIds[] = 0;
		}

		//########################################
		// search 1
		//########################################

		if ($continue AND $searchWord1 AND $searchWord2 AND $searchWord3)
		{
			if ($sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1 . ' ' . $searchWord2 . ' ' . $searchWord3,
										"operator" => "and"
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"node" => $currentNodeId
											)
										),
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"term" => array(
												"discussion_id" => $currentThreadId
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);
			}
				
			if (!$sameForum)
			{
				$dsl =  
				array(
					"from" => 0, "size" => $maximumResults,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1 . ' ' . $searchWord2 . ' ' . $searchWord3,
										"operator" => "and"
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"term" => array(
												"discussion_id" => $currentThreadId
											)
										),
										array(
											"terms" => array(
												"node" => $excludeNodeIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);			
			}
			
			$json = json_encode($dsl);

			curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

			curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
			'Content-Type: application/json',                                                                                
			'Content-Length: ' . strlen($json))                                                                       
			); 

			curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

			$results = curl_exec($ch);

			// decode json results
			$data = json_decode($results);				

			if (!empty($data->_shards->total) AND $data->_shards->total > 0)
			{
				// get threadIds
				foreach ($data->hits->hits as $var) 
				{
					$var = str_replace('thread-', '', $var->_id);
					if (is_numeric($var))
					{
						$threadIds[] = $var;
					}
				}
			}

			if ($maximumResults >= count($threadIds))
			{
				$continue = true;	
			}
			else
			{
				$continue = false;
			}
		}
		
		//########################################
		// search 2
		//########################################

		if ($continue AND $searchWord1 AND $searchWord2)
		{
			// get excludeThreadIds
			if (empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
			}

			if (!empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
				
				foreach ($threadIds as $value)
				{
					$excludeThreadIds[] = $value;
				}
			}
			
			$maximumResults2 = $maximumResults - count($threadIds);
			
			if ($sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults2,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1 . ' ' . $searchWord2,
										"operator" => "and"
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"node" => $currentNodeId
											)
										),
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                       
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);
			}
				
			if (!$sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults2,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1 . ' ' . $searchWord2,
										"operator" => "and"
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"terms" => array(
												"node" => $excludeNodeIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                      
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);			
			}
			
			$json = json_encode($dsl);

			curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

			curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
			'Content-Type: application/json',                                                                                
			'Content-Length: ' . strlen($json))                                                                       
			); 

			curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

			$results = curl_exec($ch);	

			// decode json results
			$data = json_decode($results);

			if (!empty($data->_shards->total) AND $data->_shards->total > 0)
			{
				// get threadIds
				foreach ($data->hits->hits as $var) 
				{
					$var = str_replace('thread-', '', $var->_id);
					if (is_numeric($var))
					{
						$threadIds[] = $var;
					}
				}
			}

			if ($maximumResults >= count($threadIds))
			{
				$continue = true;	
			}
			else
			{
				$continue = false;
			}				
		}

		//########################################
		// search 3
		//########################################

		if ($continue AND $searchWord1)
		{
			// get excludeThreadIds
			if (empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
			}

			if (!empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
				
				foreach ($threadIds as $value)
				{
					$excludeThreadIds[] = $value;
				}
			}
			
			$maximumResults3 = $maximumResults - count($threadIds);
			
			if ($sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults3,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"node" => $currentNodeId
											)
										),
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);
			}
				
			if (!$sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults3,
					"query" => array(
						"bool" => array(						
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord1
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"terms" => array(
												"node" => $excludeNodeIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									] 
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);			
			}

			$json = json_encode($dsl);

			curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

			curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
			'Content-Type: application/json',                                                                                
			'Content-Length: ' . strlen($json))                                                                       
			); 

			curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

			$results = curl_exec($ch);			

			// decode json results
			$data = json_decode($results);		

			if (!empty($data->_shards->total) AND $data->_shards->total > 0)
			{
				// get threadIds
				foreach ($data->hits->hits as $var) 
				{
					$var = str_replace('thread-', '', $var->_id);
					if (is_numeric($var))
					{
						$threadIds[] = $var;
					}
				}
			}	

			if ($maximumResults >= count($threadIds))
			{
				$continue = true;	
			}
			else
			{
				$continue = false;
			}				
		}			

		//########################################
		// search 4
		//########################################

		if ($continue AND $searchWord2)
		{
			// get excludeThreadIds
			if (empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
			}

			if (!empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
				
				foreach ($threadIds as $value)
				{
					$excludeThreadIds[] = $value;
				}
			}
			
			$maximumResults4 = $maximumResults - count($threadIds);
			
			if ($sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults4,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord2
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"node" => $currentNodeId
											)
										),
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                       
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);
			}
				
			if (!$sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults4,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord2
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"terms" => array(
												"node" => $excludeNodeIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                        
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);			
			}
			
			$json = json_encode($dsl);

			curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

			curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
			'Content-Type: application/json',                                                                                
			'Content-Length: ' . strlen($json))                                                                       
			); 

			curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

			$results = curl_exec($ch);			

			// decode json results
			$data = json_decode($results);

			if (!empty($data->_shards->total) AND $data->_shards->total > 0)
			{
				// get threadIds
				foreach ($data->hits->hits as $var) 
				{
					$var = str_replace('thread-', '', $var->_id);
					if (is_numeric($var))
					{
						$threadIds[] = $var;
					}
				}
			}

			if ($maximumResults >= count($threadIds))
			{
				$continue = true;	
			}
			else
			{
				$continue = false;
			}				
		}

		//########################################
		// search 5
		//########################################

		if ($continue AND $searchWord3)
		{
			// get excludeThreadIds
			if (empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
			}

			if (!empty($threadIds))
			{
				$excludeThreadIds[] = $currentThreadId;
				
				foreach ($threadIds as $value)
				{
					$excludeThreadIds[] = $value;
				}
			}
			
			$maximumResults5 = $maximumResults - count($threadIds);
			
			if ($sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults5,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord3
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"node" => $currentNodeId
											)
										),
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                      
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);
			}
				
			if (!$sameForum)
			{
				$dsl = 
				array(
					"from" => 0, "size" => $maximumResults5,
					"query" => array(
						"bool" => array(
							"must" => array(
								"match" => array(
									"title" => array(
										"query" => $searchWord3
									)
								)
							),
							"filter" => array(
								"bool" => array(
									"must" => [
										array(
											"term" => array(
												"type" => 'thread'
											)
										),
										array(
											"range" => array(
												"date" => array(
													"gte" => $gte
												)
											)										
										)
									],
									"must_not" => [
										array(
											"terms" => array(
												"discussion_id" => $excludeThreadIds
											)
										),
										array(
											"terms" => array(
												"node" => $excludeNodeIds
											)
										),
										array(
											"term" => array(
												"hidden" => 'true'
											)
										)
									]                                       
								)
							)
						)
					),
					"sort" => array(
						"date" => array("order" => "desc" )
					)
				);			
			}
			
			$json = json_encode($dsl);

			curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

			curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
			'Content-Type: application/json',                                                                                
			'Content-Length: ' . strlen($json))                                                                       
			); 

			curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');

			$results = curl_exec($ch);			

			// decode json results
			$data = json_decode($results);

			if (!empty($data->_shards->total) AND $data->_shards->total > 0)
			{
				// get threadIds
				foreach ($data->hits->hits as $var) 
				{
					$var = str_replace('thread-', '', $var->_id);
					if (is_numeric($var))
					{
						$threadIds[] = $var;
					}
				}
			}	
		}

		//########################################
		// prepare similarThreads
		//########################################

		// return if no threadIds
		if (empty($threadIds))
		{
			return;
		}
		
		// re-index array 
		$threadIds = array_values($threadIds);		

		// return if all threadIds are 0
		if ($threadIds[0] == 0 AND $threadIds[1] == 0 AND $threadIds[2] == 0 AND $threadIds[3] == 0 AND $threadIds[4] == 0)
		{
			return;
		}
		
		// define variable
		$conditions = array();
		
		// get conditions
		foreach ($threadIds AS $threadId)
		{
			$conditions[] = ['thread_id', '=', $threadId];
		}

		// continue if not empty
		if (!empty($conditions))
		{
			// create similarThreads object
			$finder = \XF::finder('XF:Thread');
			$similarThreads = $finder
				->whereOr($conditions)
				->order('post_date', 'DESC')
				->fetch();
		}
		else
		{
			$similarThreads = array();
		}

		// return similarThreads
		return $similarThreads;
	}
}