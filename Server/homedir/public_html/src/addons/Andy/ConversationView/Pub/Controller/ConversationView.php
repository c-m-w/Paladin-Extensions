<?php

namespace Andy\ConversationView\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class ConversationView extends AbstractController
{
	public function actionIndex()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Conversation view -> Limit
		$limit = $options->conversationViewLimit;
		
		// get username
		$username = $this->filter('username', 'str');
		
		// get db
		$db = \XF::db();
		
		if ($username == '')
		{
			// run query
			$results = $db->fetchAll("
			SELECT conversation_id,
			title,
			user_id,
			username,
			last_message_date,
			reply_count,
			recipients
			FROM xf_conversation_master
			ORDER BY last_message_date DESC
			LIMIT ?
			", $limit);	
		}
		
		if ($username != '')
		{
			// run query
			$results = $db->fetchAll("
			SELECT conversation_id,
			title,
			user_id,
			username,
			last_message_date,
			reply_count,
			recipients
			FROM xf_conversation_master
			WHERE username = ?
			ORDER BY last_message_date DESC
			LIMIT ?
			", array($username, $limit));	
		}
		
		if (!empty($results))
		{
			// get users
			foreach ($results as $k => $v)
			{		
				// get user
				$user = array(
					'user_id' => $v['user_id'],
					'username' => $v['username']
				);
				
				//########################################
				// get recipients
				
				// define variable
				$recipients = '';

				$var = $v['recipients'];
				
				if ($var != '')
				{
					// unserialize blob data
					$varArray = unserialize($var);

					foreach ($varArray AS $value)
					{
						$recipients = $recipients . ', ' . $value['username'];
					}
					
					$recipients = ltrim($recipients, ',');
				} 				

				// create resultsNew array
				$resultsNew[] = array(
					'conversation_id' => $v['conversation_id'],
					'title' => $v['title'],
					'user' => $user,
					'recipients' => $recipients,
					'last_message_date' => $v['last_message_date'],
					'reply_count' => $v['reply_count']
				);
			}

			// rename variable
			$results = $resultsNew;
		}

		// prepare viewParams
		$viewParams = [
			'username' => $username,
			'limit' => $limit,
			'results' => $results
		];
		
		// send to template	
		return $this->view('Andy\ConversationView:Index', 'andy_conversationview', $viewParams);
	}
	
	public function actionConversation()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get conversationId
		$conversationId = $this->filter('conversation_id', 'uint');
		
		// verify conversationId
		if ($conversationId == '')
		{
			return $this->error(\XF::phrase('conversationview_conversation_id_missing'));
		}
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Conversation view -> Limit
		$limit = $options->conversationViewLimit;
		
		// get db
		$db = \XF::db();
		
		// run query
		$data = $db->fetchRow("
		SELECT title,
		username,
		recipients
		FROM xf_conversation_master
		WHERE conversation_id = ?
		", $conversationId);
		
		if (empty($data))
		{
			return $this->error(\XF::phrase('conversationview_conversation_id_not_found'));
		}
		
		// get title
		$conversationTitle = $data['title'];
		
		// get starter
		$starter = $data['username'];
		
		//########################################
		// get recipients
		
		// define variable
		$recipients = '';

		$var = $data['recipients'];

		if ($var != '')
		{
			// unserialize blob data
			$varArray = unserialize($var);

			foreach ($varArray AS $value)
			{
				$recipients = $recipients . ', ' . $value['username'];
			}

			$recipients = ltrim($recipients, ',');
		}
		
		//########################################
		// run query		

		$messages = $db->fetchAll("
			SELECT xf_conversation_message.message_id,
			xf_conversation_message.message_date,
			xf_conversation_message.username,
			xf_conversation_message.message,
			xf_conversation_message.attach_count
			FROM xf_conversation_master
			INNER JOIN xf_conversation_message ON xf_conversation_message.conversation_id = xf_conversation_master.conversation_id
			WHERE xf_conversation_master.conversation_id = ?
			GROUP BY xf_conversation_message.message_id
		", $conversationId);

		// prepare viewParams
		$viewParams = [
			'conversationId' => $conversationId,
			'conversationTitle' => $conversationTitle,
			'starter' => $starter,
			'recipients' => $recipients,
			'messages' => $messages
		];

		// send to template
		return $this->view('Andy\ConversationSearch:Conversation', 'andy_conversationview_conversation', $viewParams);
	}
	
	public function actionViewAttachments()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get messageId
		$messageId = $this->filter('message_id', 'uint');
		
		// verify messageId
		if ($messageId == '')
		{
			return $this->error(\XF::phrase('conversationview_message_id_missing'));
		}
		
		// get db
		$db = \XF::db();
		
		// run query
		$attachmentIds = $db->fetchAll("
			SELECT xf_attachment.attachment_id,
			xf_attachment_data.data_id,
			xf_attachment_data.filename,
			xf_attachment_data.file_hash,
			xf_attachment_data.thumbnail_width
			FROM xf_attachment_data
			INNER JOIN xf_attachment ON xf_attachment.data_id = xf_attachment_data.data_id
			WHERE xf_attachment.content_type = ?
			AND xf_attachment.content_id = ?
		", array('conversation_message', $messageId));
		
		$results = '';
		
		foreach ($attachmentIds as $value)
		{
			if ($value['thumbnail_width'] > 0)
			{
				// get dataId
				$dataId = $value['data_id'];

				// get path
				$path = sprintf('attachments/%d/%d-%s.jpg',
					floor($dataId / 1000),
					$dataId,
					$value['file_hash']
				);

				// get $thumbUrl
				$thumbUrl = $this->app()->applyExternalDataUrl($path);
				
				// get dataId
				$dataId = $value['data_id'];

				// get fileHash
				$fileHash = $value['file_hash'];			

				// get last folder
				$lastFolder = floor($dataId / 1000);

				// define full attachment file path
				$attachmentPath = 'internal_data/attachments/' . $lastFolder . '/' . $dataId . '-' . $fileHash . '.data';				

				// get options
				$options = \XF::options();

				// get options from Admin CP -> Options -> Basic board information -> Board Url
				$boardUrl = $options->boardUrl;				

				// get results			
				$results = $results . '<a href="' . $boardUrl . '/conversationview/image/?attachment_id=' . $value['attachment_id'] . '">' . $value['filename'] . '</a>' . '<br />';
				$results = $results . '<img src="' . $thumbUrl . '">' . '<br /><br />';
	
			}

			if ($value['thumbnail_width'] == 0)
			{
				// get dataId
				$dataId = $value['data_id'];
				
				// get fileHash
				$fileHash = $value['file_hash'];			

				// get last folder
				$lastFolder = floor($dataId / 1000);

				// define full attachment file path
				$attachmentPath = 'internal_data/attachments/' . $lastFolder . '/' . $dataId . '-' . $fileHash . '.data';				

				// get options
				$options = \XF::options();

				// get options from Admin CP -> Options -> Basic board information -> Board Url
				$boardUrl = $options->boardUrl;

				// get results
				$results = $results . '<a href="' . $boardUrl . '/conversationview/download/?attachment_id=' . $value['attachment_id'] . '">' . $value['filename'] . '</a>' . '<br /><br />';
			}
		}

		// prepare viewParams
		$viewParams = [
			'messageId' => $messageId,
			'results' => $results
		];

		// send to template
		return $this->view('Andy\ConversationSearch:View', 'andy_conversationview_attachments', $viewParams);
	}
	
	public function actionDownload()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get attachmentId
		$attachmentId = $this->filter('attachment_id', 'uint');
		
		// verify messageId
		if ($attachmentId == '')
		{
			return $this->error(\XF::phrase('conversationview_attachment_id_missing'));
		}
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Conversation view -> Board path
		$boardPath = $options->conversationViewBoardPath;
		
		// verify boardPath
		if ($boardPath == '')
		{
			return $this->error(\XF::phrase('conversationview_board_path_missing_in_options_page'));
		}
		
		// get db
		$db = \XF::db();
		
		// run query
		$data = $db->fetchRow("
			SELECT xf_attachment_data.data_id,
			xf_attachment_data.filename,
			xf_attachment_data.file_hash
			FROM xf_attachment
			INNER JOIN xf_attachment_data ON xf_attachment_data.data_id = xf_attachment.data_id
			WHERE xf_attachment.content_type = ?
			AND xf_attachment.attachment_id = ?
		", array('conversation_message', $attachmentId));
		
		// get dataId
		$dataId = $data['data_id'];

		// get fileHash
		$fileHash = $data['file_hash'];			

		// get last folder
		$lastFolder = floor($dataId / 1000);

		// define full attachment file path
		$attachmentPath = '/internal_data/attachments/' . $lastFolder . '/' . $dataId . '-' . $fileHash . '.data';

		// get filePath
		$filePath = $boardPath . $attachmentPath;

		// set content-type
		header("Content-type:application/octet-stream");
		
		// get fileName
		$fileName = str_replace(' ', '-', $data['filename']);

		// set content-disposition
		header('Content-Disposition: attachment; filename=' . $fileName);
		
		// read file
		readfile($filePath);
		
		// exit
		exit();
	}
	
	public function actionImage()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get attachmentId
		$attachmentId = $this->filter('attachment_id', 'uint');
		
		// verify messageId
		if ($attachmentId == '')
		{
			return $this->error(\XF::phrase('conversationview_attachment_id_missing'));
		}
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Conversation view -> Board path
		$boardPath = $options->conversationViewBoardPath;
		
		// verify boardPath
		if ($boardPath == '')
		{
			return $this->error(\XF::phrase('conversationview_board_path_error_in_options_page'));
		}
		
		if (!file_exists($boardPath))
		{
			return $this->error(\XF::phrase('conversationview_board_path_error_in_options_page'));
		}	
		
		// get db
		$db = \XF::db();
		
		// run query
		$data = $db->fetchRow("
			SELECT xf_attachment_data.data_id,
			xf_attachment_data.filename,
			xf_attachment_data.file_hash
			FROM xf_attachment
			INNER JOIN xf_attachment_data ON xf_attachment_data.data_id = xf_attachment.data_id
			WHERE xf_attachment.content_type = ?
			AND xf_attachment.attachment_id = ?
		", array('conversation_message', $attachmentId));
		
		// get dataId
		$dataId = $data['data_id'];

		// get fileHash
		$fileHash = $data['file_hash'];			

		// get last folder
		$lastFolder = floor($dataId / 1000);

		// define full attachment file path
		$attachmentPath = '/internal_data/attachments/' . $lastFolder . '/' . $dataId . '-' . $fileHash . '.data';

		// get filePath
		$filePath = $boardPath . $attachmentPath;

		// get extension
		$extension = \XF\Util\File::getFileExtension($data['filename']);
		
		// set header
		if ($extension == 'jpg')
		{
			header("Content-type:image/jpg");
		}
		
		// set header
		if ($extension == 'jpeg')
		{
			header("Content-type:image/jpeg");
		}
		
		// set header
		if ($extension == 'gif')
		{
			header("Content-type:image/gif");
		}
		
		// set header
		if ($extension == 'png')
		{
			header("Content-type:image/png");
		}
		
		// get fileName
		$fileName = str_replace(' ', '-', $data['filename']);
		
		// display image
		echo file_get_contents($filePath);
		
		// exit
		exit();
	}
	
	public function actionFilter()
	{
		// get visitor
		$visitor = \XF::visitor();
		
		// get permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// send to template	
		return $this->view('Andy\ConversationView:Filter', 'andy_conversationview_filter');
	}
	
    public function actionDelete()
    {
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('conversationView', 'view'))
		{
			return $this->noPermission();
		}
		
		// get conversationId
		$conversationId = $this->filter('conversation_id', 'uint');
		
		// verify conversationId
		if ($conversationId == '')
		{
			return $this->error(\XF::phrase('conversationview_conversation_id_missing'));
		}
		
		// get db
		$db = \XF::db();
			
		//########################################
		// delete attachments
		//########################################

		$messageIds = $db->fetchAllColumn("
			SELECT message_id
			FROM xf_conversation_message
			WHERE conversation_id = ?
		", $conversationId);			

		if (!empty($messageIds))
		{
			// create whereclause
			$whereclause = 'AND (content_id = ' . implode(' OR content_id = ', $messageIds);
			$whereclause = $whereclause . ')';

			// delete row
			$db->query("
				DELETE FROM xf_attachment
				WHERE content_type = ?
				$whereclause
			", 'conversation_message');
		}

		//########################################
		// delete conversations
		//########################################

		// delete row
		$db->query("
			DELETE FROM xf_conversation_master
			WHERE conversation_id = ?
		", $conversationId);

		// delete row
		$db->query("
			DELETE FROM xf_conversation_message
			WHERE conversation_id = ?
		", $conversationId);

		// delete row
		$db->query("
			DELETE FROM xf_conversation_recipient
			WHERE conversation_id = ?
		", $conversationId);					

		// delete row
		$db->query("
			DELETE FROM xf_conversation_user
			WHERE conversation_id = ?
		", $conversationId);

		// delete row
		$db->query("
			DELETE FROM xf_user_alert
			WHERE content_type = ?
			AND content_id = ?
		", array('conversation_message', $conversationId));
		
		// return redirect
		return $this->redirect($this->buildLink('conversationview'));
    }
}