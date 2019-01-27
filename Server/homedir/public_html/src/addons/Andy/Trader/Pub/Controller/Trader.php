<?php

namespace Andy\Trader\Pub\Controller;

use XF\Pub\Controller\AbstractController;

class Trader extends AbstractController
{
	public function actionHistory()
	{
		//########################################
		// history
		//########################################
		
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'view'))
		{
			return $this->noPermission();
		}
		
		// get userId
		$userId = $this->filter('user_id', 'uint');
		
		// get db
		$db = \XF::db();			
		
		// run query
		$username = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);	
		
		// run query
		$result = $db->fetchAllColumn("
			SELECT trader_id
			FROM xf_andy_trader
			WHERE seller_id = ?
			AND buyer_comment <> ''
		", $userId);	
		
		// get sellerCount
		$sellerCount = count($result);
		
		// run query
		$result = $db->fetchAllColumn("
			SELECT trader_id
			FROM xf_andy_trader
			WHERE buyer_id = ?
			AND seller_comment <> ''
		", $userId);	
		
		// get buyerCount
		$buyerCount = count($result);			
		
		// get viewParams
		$viewParams = [
			'userId' => $userId,
			'username' => $username,
			'sellerCount' => $sellerCount,
			'buyerCount' => $buyerCount
		];				
				
		// send to template
		return $this->view('Andy\Trader:History', 'andy_trader_history', $viewParams);
	}	
	
	public function actionRateSeller()
	{
		//########################################
		// rate seller
		//########################################
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}				
		
		// get userId
		$userId = $this->filter('user_id', 'uint');	
		
		// get buyer_id
		$buyer_id = $visitor['user_id'];
		
		// prevent self rating 
		if ($userId == $buyer_id)
		{
			// return error
			return $this->error(\XF::phrase('trader_cannot_rate_oneself'));
		}				
		
		// get db
		$db = \XF::db();			
		
		// run query
		$username = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);			
		
		// prepare viewParams
		$viewParams = [
			'userId' => $userId,
			'username' => $username
		];			
						
		// send to template
		return $this->view('Andy\Trader:RateSeller', 'andy_trader_rate_seller', $viewParams);
	}
	
	public function actionRateBuyer()
	{
		//########################################
		// rate buyer
		//########################################
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}		
		
		// get userId
		$userId = $this->filter('user_id', 'uint');		
		
		// get seller_id
		$seller_id = $visitor['user_id'];
		
		// prevent self rating 
		if ($userId == $seller_id)
		{
			// return error
			return $this->error(\XF::phrase('trader_cannot_rate_oneself'));
		}
		
		// get db
		$db = \XF::db();			
		
		// run query
		$username = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);			
		
		// prepare viewParams
		$viewParams = [
			'userId' => $userId,
			'username' => $username
		];			
						
		// send to template
		return $this->view('Andy\Trader:RateBuyer', 'andy_trader_rate_buyer', $viewParams);
	}
	
	public function actionRatingSeller()
	{
		//########################################
		// rating seller
		//########################################
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Results limit
		$resultsLimit = $options->traderResultsLimit;	
		
		// get options from Admin CP -> Options -> Trader -> Edit limit
		$editLimit = $options->traderEditLimit;			
		
		// define editLimit
		$editLimit = time() - ($editLimit * 60);	
		
		// get userId
		$userId = $this->filter('user_id', 'uint');				
		
		// get db
		$db = \XF::db();	
		
		// run query
		$seller_name = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);				
		
		// run query
		$results = $db->fetchAll("
		SELECT xf_andy_trader.trader_id,
		xf_andy_trader.timestamp,
		xf_andy_trader.rating,
		xf_andy_trader.seller_id,
		xf_andy_trader.seller_id AS user_id,
		xf_andy_trader.buyer_id,
		xf_andy_trader.buyer_comment,
		a.username AS seller_name,
		b.username AS buyer_name
		FROM xf_andy_trader
		INNER JOIN xf_user a ON a.user_id = xf_andy_trader.seller_id
		INNER JOIN xf_user b ON b.user_id = xf_andy_trader.buyer_id
		WHERE xf_andy_trader.seller_id = ?
		AND xf_andy_trader.buyer_comment <> ''
		ORDER BY xf_andy_trader.timestamp DESC
		LIMIT ?
		", array($userId, $resultsLimit));

		// prepare viewParams
		$viewParams = [
			'userId' => $userId,
			'seller_name' => $seller_name,
			'results' => $results,
			'editLimit' => $editLimit
		];			
						
		// send to template
		return $this->view('Andy\Trader:RatingSeller', 'andy_trader_rating_seller', $viewParams);
	}
	
	public function actionRatingBuyer()
	{
		//########################################
		// rating buyer
		//########################################
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'view'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Results limit
		$resultsLimit = $options->traderResultsLimit;	
		
		// get options from Admin CP -> Options -> Trader -> Edit Limit
		$editLimit = $options->traderEditLimit;			
		
		// define editLimit
		$editLimit = time() - ($editLimit * 60);			
		
		// get userId
		$userId = $this->filter('user_id', 'uint');				
		
		// get db
		$db = \XF::db();
		
		// run query
		$buyer_name = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $userId);						
		
		// run query
		$results = $db->fetchAll("
		SELECT xf_andy_trader.trader_id,
		xf_andy_trader.timestamp,
		xf_andy_trader.rating,
		xf_andy_trader.seller_id,
		xf_andy_trader.buyer_id,
		xf_andy_trader.seller_comment,
		a.username AS seller_name,
		b.username AS buyer_name
		FROM xf_andy_trader
		INNER JOIN xf_user a ON a.user_id = xf_andy_trader.seller_id
		INNER JOIN xf_user b ON b.user_id = xf_andy_trader.buyer_id
		WHERE xf_andy_trader.buyer_id = ?
		AND xf_andy_trader.seller_comment <> ''
		ORDER BY xf_andy_trader.timestamp DESC
		LIMIT ?
		", array($userId, $resultsLimit));	
		
		// prepare viewParams
		$viewParams = [
			'userId' => $userId,
			'buyer_name' => $buyer_name,
			'results' => $results,
			'editLimit' => $editLimit
		];			
						
		// send to template
		return $this->view('Andy\Trader:RatingBuyer', 'andy_trader_rating_buyer', $viewParams);
	}	
	
	public function actionEditSeller()
	{
		//########################################
		// edit seller
		//########################################
		
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Edit limit
		$editLimit = $options->traderEditLimit;		
		
		// get traderId
		$traderId = $this->filter('trader_id', 'uint');

		// get db
		$db = \XF::db();		
		
		// run query
		$results = $db->fetchRow("
			SELECT xf_andy_trader.trader_id,
			xf_andy_trader.timestamp,
			xf_andy_trader.seller_id,
			xf_andy_trader.buyer_id,  
			xf_andy_trader.rating, 
			xf_andy_trader.buyer_comment,
			xf_user.username
			FROM xf_andy_trader
			INNER JOIN xf_user ON xf_user.user_id = xf_andy_trader.seller_id
			WHERE xf_andy_trader.trader_id = ?
		", $traderId);
		
		// get options from Admin CP -> Options -> Trader -> Edit limit
		$editLimit = $options->traderEditLimit;
		
		// define variable
		$timeNow = time();
		
		// continue after checks 
		if (!$visitor->hasPermission('trader', 'admin'))
		{		
			if ($results['buyer_id'] != $visitor['user_id'])
			{
				// return error
				return $this->error(\XF::phrase('trader_error'));
			}			

			if ($results['timestamp'] < ($timeNow - ($editLimit * 60)))
			{
				// return error
				return $this->error(\XF::phrase('trader_edit_time_limit_expired'));
			}
		}
		
		// define variables
		$checked1 = '';
		$checked2 = '';
		$checked3 = '';
		
		if ($results['rating'] == '0')
		{
			$checked1 = 'checked';
		}
		
		if ($results['rating'] == '1')
		{
			$checked2 = 'checked';
		}
		
		if ($results['rating'] == '2')
		{
			$checked3 = 'checked';
		}
		
		// define username
		$username = $results['username'];						
		
		// prepare viewParams
		$viewParams = [
			'results' => $results,
			'checked1' => $checked1,
			'checked2' => $checked2,
			'checked3' => $checked3,
			'traderId' => $traderId,
			'username' => $username
		];					

		// send to template
		return $this->view('Andy\Trader:EditSeller', 'andy_trader_edit_seller', $viewParams);
	}
	
	public function actionEditBuyer()
	{
		//########################################
		// edit buyer
		//########################################
		
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Trader -> Edit limit
		$editLimit = $options->traderEditLimit;		
		
		// get traderId
		$traderId = $this->filter('trader_id', 'uint');		

		// get db
		$db = \XF::db();		
		
		// run query
		$results = $db->fetchRow("
			SELECT xf_andy_trader.trader_id,
			xf_andy_trader.timestamp, 
			xf_andy_trader.rating, 
			xf_andy_trader.seller_id,
			xf_andy_trader.buyer_id,
			xf_andy_trader.seller_comment,
			xf_user.username
			FROM xf_andy_trader
			INNER JOIN xf_user ON xf_user.user_id = xf_andy_trader.buyer_id
			WHERE xf_andy_trader.trader_id = ?
		", $traderId);
		
		// get options from Admin CP -> Options -> Trader -> Edit Limit
		$editLimit = $options->traderEditLimit;
		
		// define variable
		$timeNow = time();
		
		// continue after checks 
		if (!$visitor->hasPermission('trader', 'admin'))
		{
			if ($results['seller_id'] != $visitor['user_id'])
			{
				// return error
				return $this->error(\XF::phrase('trader_error'));			
			}			

			if ($results['timestamp'] < ($timeNow - ($editLimit * 60)))
			{
				// return error
				return $this->error(\XF::phrase('trader_edit_time_limit_expired'));			
			}
		}
		
		// define variables
		$checked1 = '';
		$checked2 = '';
		$checked3 = '';
		
		if ($results['rating'] == '0')
		{
			$checked1 = 'checked';
		}
		
		if ($results['rating'] == '1')
		{
			$checked2 = 'checked';
		}
		
		if ($results['rating'] == '2')
		{
			$checked3 = 'checked';
		}
		
		// define username
		$username = $results['username'];			
		
		// prepare viewParams
		$viewParams = [
			'results' => $results,
			'checked1' => $checked1,
			'checked2' => $checked2,
			'checked3' => $checked3,
			'traderId' => $traderId,
			'username' => $username
		];					

		// send to template
		return $this->view('Andy\Trader:EditBuyer', 'andy_trader_edit_buyer', $viewParams);
	}	
	
	public function actionDeleteSeller()
	{
		//########################################
		// delete seller
		//########################################
			
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'admin'))
		{
			return $this->noPermission();
		}
		
		// get traderId
		$traderId = $this->filter('trader_id', 'uint');

		// get db
		$db = \XF::db();
		
		// run query
		$sellerId = $db->fetchOne("
			SELECT seller_id
			FROM xf_andy_trader
			WHERE trader_id = ?
		", $traderId);

		// delete row
		$db->query("
			DELETE FROM xf_andy_trader
			WHERE trader_id = ?
		", $traderId);

		// return to ratingseller
		return $this->redirect($this->buildLink('trader/ratingseller', '', array('user_id' => $sellerId)));
	}
	
	public function actionDeleteBuyer()
	{
		//########################################
		// delete buyer
		//########################################		
			
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'admin'))
		{
			return $this->noPermission();
		}

		// get traderId
		$traderId = $this->filter('trader_id', 'uint');		

		// get db
		$db = \XF::db();
		
		// run query
		$buyerId = $db->fetchOne("
			SELECT buyer_id
			FROM xf_andy_trader
			WHERE trader_id = ?
		", $traderId);

		// delete row
		$db->query("
			DELETE FROM xf_andy_trader
			WHERE trader_id = ?
		", $traderId);
			

		// return to ratingbuyer
		return $this->redirect($this->buildLink('trader/ratingbuyer', '', array('user_id' => $buyerId)));
	}		
	
	public function actionSaveSeller()
	{
		//########################################
		// save seller
		//########################################	
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// assert post only
		$this->assertPostOnly();		
		
		// get userId
		$userId = $this->filter('user_id', 'uint');		

		// get username 
		$username = $this->filter('username', 'str');
		
		// verify username
		if ($username == '')
		{
			return $this->error(\XF::phrase('trader_username_missing'));
		}
		
		// get db
		$db = \XF::db();			
		
		// run query
		$user = $db->fetchRow("
		SELECT user_id, email
		FROM xf_user
		WHERE username = ?
		", $username);					
		
		// get rating 
		$rating = $this->filter('rating', 'str');
		
		// make sure a rating was selected
		if ($rating == '')
		{
			return $this->error(\XF::phrase('trader_rating_missing'));
		}
		
		// get buyer_comment
		$buyer_comment = $this->filter('buyer_comment', 'str');

		// make sure a buyer comment was made
		if ($buyer_comment == '')
		{
			return $this->error(\XF::phrase('trader_buyer_comment_missing'));
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Multibyte
		$multibyte = $options->traderMultibyte;	
		
		if (!$multibyte)
		{
			// limit to 200 characters
			$buyer_comment = substr($buyer_comment, 0, 200);
		}
		
		if ($multibyte)
		{
			// limit to 200 characters
			$buyer_comment = mb_substr($buyer_comment, 0, 200);
		}

		// get timestamp
		$timestamp = time();
		
		// get buyer_id
		$buyer_id = $visitor['user_id'];
		
		// run query
		$buyerName = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $buyer_id);		
		
		// define variable
		$seller_comment = '';
		
		// insert new row
		$db->query("
			INSERT INTO xf_andy_trader
				(timestamp, rating, seller_id, buyer_id, seller_comment, buyer_comment)
			VALUES
				(?, ?, ?, ?, ?, ?)
		", array($timestamp, $rating, $userId, $buyer_id, $seller_comment, $buyer_comment));	
		
		// get link to forum index
		$webRoot = \XF::app()->router()->buildLink('index');	
		
		// remove index.php if not using full friendly url's
		$replace_src = 'index.php';
		$replace_str = 'index.php?';
		$text = $webRoot;					
		$webRoot = str_replace($replace_src, $replace_str, $text);
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Basic board information -> Use full friendly URLs
		$useFriendlyUrls = $options->useFriendlyUrls;			
		
		if ($useFriendlyUrls)
		{
			$linkSeller = $webRoot . 'trader/history?user_id=' . $userId;
			$linkBuyer = $webRoot . 'trader/history?user_id=' . $buyer_id;
		}
		
		if (!$useFriendlyUrls)
		{
			$linkSeller = $webRoot . 'trader/history&user_id=' . $userId;
			$linkBuyer = $webRoot . 'trader/history&user_id=' . $buyer_id;
		}
		
		// get email_address
		$email_address = $user['email'];
		
		// get subject
		$subject = \XF::phrase('trader_subject');
		
		// ratingString
		if ($rating == 0)
		{
			$ratingString = \XF::phrase('trader_positive');
		}
		
		// ratingString
		if ($rating == 1)
		{
			$ratingString = \XF::phrase('trader_neutral');
		}
		
		// ratingString
		if ($rating == 2)
		{
			$ratingString = \XF::phrase('trader_negative');
		}
		
		// get message
		$message = \XF::phrase('trader_seller') . ': ' . $username . '<br />' . '
' . \XF::phrase('trader_buyer') . ': ' . $buyerName . '<br />' . '
' . \XF::phrase('trader_buyer_rating') . ': ' . $ratingString . '<br />' . '
' . \XF::phrase('trader_buyer_comment') . ': ' . $buyer_comment . '<br /><br />' . '
' . '<a href="' . $linkSeller . '">' . \XF::phrase('trader_trader_history_for') . ' ' . $username . '</a>' . '<br />' . '
' . '<a href="' . $linkBuyer . '">' . \XF::phrase('trader_trader_history_for') . ' ' . $buyerName . '</a>';					

		// send email
		$mail = \XF::app()->mailer()->newMail();

		$user = \XF::app()->find('XF:User', $userId);
		$mail->setToUser($user);

		$mail->setTemplate('andy_trader', [
			'subject' => $subject,
			'message' => $message
		]);

		$mail->queue();
		
		// return to history
		return $this->redirect($this->buildLink('trader/history', '', array('user_id' => $userId)));
	}
	
	public function actionSaveBuyer()
	{
		//########################################
		// save buyer
		//########################################	
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// make sure data comes from $_POST
		$this->assertPostOnly();	
		
		// get userId
		$userId = $this->filter('user_id', 'uint');					
		
		// get username
		$username = $this->filter('username', 'str');
		
		// verify username
		if ($username == '')
		{
			return $this->error(\XF::phrase('trader_username_missing'));
		}
		
		// get db
		$db = \XF::db();			
		
		// run query
		$user = $db->fetchRow("
		SELECT user_id, email
		FROM xf_user
		WHERE username = ?
		", $username);					
		
		// get rating 
		$rating = $this->filter('rating', 'str');
		
		// make sure a rating was selected
		if ($rating == '')
		{
			return $this->error(\XF::phrase('trader_rating_missing'));
		}					
		
		// get seller_comment 
		$seller_comment = $this->filter('seller_comment', 'str');
		
		// make sure a seller comment was made
		if ($seller_comment == '')
		{
			return $this->error(\XF::phrase('trader_seller_comment_missing'));
		}
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Multibyte
		$multibyte = $options->traderMultibyte;	
		
		if (!$multibyte)
		{
			// limit to 200 characters
			$seller_comment = substr($seller_comment, 0, 200);
		}
		
		if ($multibyte)
		{
			// limit to 200 characters
			$seller_comment = mb_substr($seller_comment, 0, 200);
		}		

		// get timestamp
		$timestamp = time();
		
		// get seller_id
		$seller_id = $visitor['user_id'];
		
		// run query
		$sellerName = $db->fetchOne("
		SELECT username
		FROM xf_user
		WHERE user_id = ?
		", $seller_id);		
		
		// define variable
		$buyer_comment = '';
		
		// get db
		$db = \XF::db();		
		
		// insert new row
		$db->query("
			INSERT INTO xf_andy_trader
				(timestamp, rating, seller_id, buyer_id, seller_comment, buyer_comment)
			VALUES
				(?, ?, ?, ?, ?, ?)
		", array($timestamp, $rating, $seller_id, $userId, $seller_comment, $buyer_comment));
		
		// get link to forum index
		$webRoot = \XF::app()->router()->buildLink('index');	
		
		// remove index.php if not using full friendly url's
		$replace_src = 'index.php';
		$replace_str = 'index.php?';
		$text = $webRoot;					
		$webRoot = str_replace($replace_src, $replace_str, $text);		
		
		// get options
		$options = \XF::options();
		
		// get options from Admin CP -> Options -> Basic board information -> Use full friendly URLs
		$useFriendlyUrls = $options->useFriendlyUrls;			
		
		if ($useFriendlyUrls)
		{
			$linkSeller = $webRoot . 'trader/history?user_id=' . $seller_id;
			$linkBuyer = $webRoot . 'trader/history?user_id=' . $userId;
		}
		
		if (!$useFriendlyUrls)
		{
			$linkSeller = $webRoot . 'trader/history&user_id=' . $seller_id;
			$linkBuyer = $webRoot . 'trader/history&user_id=' . $userId;
		}
		
		// get email_address
		$email_address = $user['email'];
		
		// ratingString
		if ($rating == 0)
		{
			$ratingString = \XF::phrase('trader_positive');
		}
		
		// ratingString
		if ($rating == 1)
		{
			$ratingString = \XF::phrase('trader_neutral');
		}
		
		// ratingString
		if ($rating == 2)
		{
			$ratingString = \XF::phrase('trader_negative');
		}
		
		// get message
		$message = \XF::phrase('trader_buyer') . ': ' . $username . '<br />' . '
' . \XF::phrase('trader_seller') . ': ' . $sellerName . '<br />' . '
' . \XF::phrase('trader_seller_rating') . ': ' . $ratingString . '<br />' . '
' . \XF::phrase('trader_seller_comment') . ': ' . $seller_comment . '<br /><br />' . '
' . '<a href="' . $linkBuyer . '">' . \XF::phrase('trader_trader_history_for') . ' ' . $username . '</a>' . '<br />' . '
' . '<a href="' . $linkSeller . '">' . \XF::phrase('trader_trader_history_for') . ' ' . $sellerName . '</a>';					

		// send email
		$mail = \XF::app()->mailer()->newMail();

		$user = \XF::app()->find('XF:User', $userId);
		$mail->setToUser($user);

		$mail->setTemplate('andy_trader', [
			'message' => $message
		]);

		$mail->queue();
		
		// return to history
		return $this->redirect($this->buildLink('trader/history', '', array('user_id' => $userId)));		
	}	
	
	public function actionUpdateSeller()
	{
		//########################################
		// update seller
		//########################################	
				
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// make sure data comes from $_POST
		$this->assertPostOnly();
				
		// get traderId 
		$traderId = $this->filter('trader_id', 'uint');
		
		// get username 
		$username = $this->filter('username', 'str');
		
		// verify username
		if ($username == '')
		{
			return $this->error(\XF::phrase('trader_username_missing'));
		}
		
		// get db
		$db = \XF::db();			
		
		// run query
		$seller_id = $db->fetchOne("
		SELECT user_id
		FROM xf_user
		WHERE username = ?
		", $username);			
		
		// get rating 
		$rating = $this->filter('rating', 'str');
		
		// get buyer_comment 
		$buyer_comment = $this->filter('buyer_comment', 'str');
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Multibyte
		$multibyte = $options->traderMultibyte;	
		
		if (!$multibyte)
		{
			// limit to 200 characters
			$buyer_comment = substr($buyer_comment, 0, 200);
		}
		
		if ($multibyte)
		{
			// limit to 200 characters
			$buyer_comment = substr($buyer_comment, 0, 200);
		}		

		$db->query("
		UPDATE xf_andy_trader SET
			rating = ?,
			buyer_comment = ?
			WHERE trader_id = ?
		", array($rating, $buyer_comment, $traderId));		

		// return to ratingseller
		return $this->redirect($this->buildLink('trader/ratingseller', '', array('user_id' => $seller_id)));
	}
	
	public function actionUpdateBuyer()
	{
		//########################################
		// update buyer
		//########################################	

		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'rate'))
		{
			return $this->noPermission();
		}
		
		// make sure data comes from $_POST
		$this->assertPostOnly();		
				
		// get traderId 
		$traderId = $this->filter('trader_id', 'uint');
	
		// get username 
		$username = $this->filter('username', 'str');				
		
		// verify name
		if ($username == '')
		{
			return $this->error(\XF::phrase('trader_username_missing'));
		}
		
		// get db
		$db = \XF::db();			
		
		// run query
		$buyer_id = $db->fetchOne("
		SELECT user_id
		FROM xf_user
		WHERE username = ?
		", $username);			
		
		// get rating 
		$rating = $this->filter('rating', 'str');
		
		// get seller_comment 
		$seller_comment = $this->filter('seller_comment', 'str');
		
		// get options
		$options = \XF::options();		
		
		// get options from Admin CP -> Options -> Trader -> Multibyte
		$multibyte = $options->traderMultibyte;	
		
		if (!$multibyte)
		{
			// limit to 200 characters
			$seller_comment = substr($seller_comment, 0, 200);
		}
		
		if ($multibyte)
		{
			// limit to 200 characters
			$seller_comment = substr($seller_comment, 0, 200);
		}

		$db->query("
		UPDATE xf_andy_trader SET
			rating = ?,
			seller_comment = ?
			WHERE trader_id = ?
		", array($rating, $seller_comment, $traderId));

		// return to ratingbuyer
		return $this->redirect($this->buildLink('trader/ratingbuyer', '', array('user_id' => $buyer_id)));	
	}
	
    public function actionImportXenTrader()
    {
		// get visitor
		$visitor = \XF::visitor();				
		
		// check for user group permission
		if (!$visitor->hasPermission('trader', 'admin'))
		{
			return $this->noPermission();
		}
				
		// get db
		$db = \XF::db();
        
        // run query
        $data = $db->fetchAll("
        SELECT *
        FROM xf_andy_trader
        "); 
		
		$count = count($data);

		if ($count > 0)
		{
			return $this->error(\XF::phrase('trader_xf_andy_trader_must_be_empty'));
		}
        
        // unset srray
        unset($data);
        
        // run query
        $data = $db->fetchAll("
        SELECT *
        FROM xentrader_feedback
        ORDER BY feedback_id ASC
        ");
        
        // foreach multidimensional array
        foreach ($data as $k => $v)
        {
            if ($v['type'] == 'buy')
            {
                $timestamp = $v['feedback_date'];
				if ($v['rating'] == 1)
				{
					$rating = 0;
				}
				if ($v['rating'] == 0)
				{
					$rating = 1;
				}
				if ($v['rating'] == -1)
				{
					$rating = 2;
				}				
                $seller_id = $v['to_user_id'];
                $buyer_id = $v['from_user_id'];
                $seller_comment = '';
                $buyer_comment = $v['feedback'];
                
                // run query
                $db->query("
                    INSERT INTO xf_andy_trader
                        (timestamp, rating, seller_id, buyer_id, seller_comment, buyer_comment)
                    VALUES
                        (?, ?, ?, ?, ?, ?)
                ", array($timestamp, $rating, $seller_id, $buyer_id, $seller_comment, $buyer_comment));
				
				// run query
				$db->query("
					UPDATE xf_user
					SET andy_trader_seller_count = andy_trader_seller_count + 1
					WHERE user_id = ?
				", $seller_id);	
            }
            
            if ($v['type'] == 'sell')
            {            
                $timestamp = $v['feedback_date'];
				if ($v['rating'] == 1)
				{
					$rating = 0;
				}
				if ($v['rating'] == 0)
				{
					$rating = 1;
				}
				if ($v['rating'] == -1)
				{
					$rating = 2;
				}
                $seller_id = $v['to_user_id'];
                $buyer_id = $v['from_user_id'];
                $seller_comment = $v['feedback'];
                $buyer_comment = '';
                
                // run query
                $db->query("
                    INSERT INTO xf_andy_trader
                        (timestamp, rating, seller_id, buyer_id, seller_comment, buyer_comment)
                    VALUES
                        (?, ?, ?, ?, ?, ?)
                ", array($timestamp, $rating, $seller_id, $buyer_id, $seller_comment, $buyer_comment));
				
				// run query
				$db->query("
					UPDATE xf_user
					SET andy_trader_buyer_count = andy_trader_buyer_count + 1
					WHERE user_id = ?
				", $seller_id);	
            }
        }
        
		// send to template
		return $this->view('Andy\Trader:ImportXenTrader', 'andy_trader_import_confirm');
	}
}		