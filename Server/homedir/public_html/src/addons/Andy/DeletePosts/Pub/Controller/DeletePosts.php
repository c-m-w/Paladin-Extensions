<?php

namespace Andy\DeletePosts\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class DeletePosts extends AbstractController
{
	public function actionIndex()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('deletePosts', 'view'))
		{
			return $this->noPermission();
		}

		// send to template
		return $this->view('Andy\DeletePosts:Index', 'andy_deleteposts');
	}
	
	public function actionConfirm()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('deletePosts', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Delete posts -> Limit
		$limit = $options->deletePostsLimit;
		
		// get postedBy
		$postedBy = $this->filter('posted_by', 'str');
		
		// get db
		$db = \XF::db();
		
		// run query
		$userId = $db->fetchOne("
		SELECT user_id
		FROM xf_user
		WHERE username = ?
		", $postedBy);
		
		if ($userId == '')
		{
			return $this->error(\XF::phrase('deleteposts_username_not_found'));
		}
		
		// run query
		$posts = $db->fetchAll("
		SELECT post_id
		FROM xf_post
		WHERE user_id = ?
		", $userId);
		
		$postsCount = count($posts);
		
		// get posts
		$finder = \XF::finder('XF:Post');
		$posts = $finder
			->with('Thread')
			->with('Thread.Forum')
			->where('user_id', '=', $userId)
			->order('post_id', 'DESC')
			->limit($limit)
			->fetch();		

		// prepare viewParams
		$viewParams = [
			'postedBy' => $postedBy,
			'postsCount' => $postsCount,
			'limit' => $limit,
			'userId' => $userId,
			'posts' => $posts
		];
			
		// send to template
		return $this->view('Andy\DeletePosts:Delete', 'andy_deleteposts_confirm', $viewParams);
	}
	
	public function actionDelete()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('deletePosts', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Delete posts -> Limit
		$limit = $options->deletePostsLimit;
		
		// get userId
		$userId = $this->filter('user_id', 'uint');
		
		if ($userId == '')
		{
			return $this->error(\XF::phrase('deleteposts_username_not_found'));
		}

		// get db
		$db = \XF::db();
		
		// run query
		$postedBy = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);
		
		// run query
		$posts = $db->fetchAll("
		SELECT post_id
		FROM xf_post
		WHERE user_id = ?
		", $userId);
		
		// delete posts
		foreach ($posts AS $k => $v)
		{
			$postId = $v['post_id'];
			$type = 'hard';
			$reason = '';

			$finder = \XF::finder('XF:Post');
			$post = $finder
				->where('post_id', '=', $postId)
				->fetchOne();

			$deleter = \XF::app()->service('XF:Post\Deleter', $post);

			$deleter->delete($type, $reason);
		}

		// run query
		$posts = $db->fetchAll("
		SELECT post_id
		FROM xf_post
		WHERE user_id = ?
		", $userId);
		
		// get postsCount
		$postsCount = count($posts);
		
		// prepare viewParams
		$viewParams = [
			'postedBy' => $postedBy,
			'postsCount' => $postsCount,
			'limit' => $limit,
			'userId' => $userId
		];
			
		// send to template
		return $this->view('Andy\DeletePosts:Delete', 'andy_deleteposts_confirm', $viewParams);
	}
}