<?php

return function($__templater, $__selectedNav, array $__vars)
{
	$__tree = [];
	$__flat = [];


	$__navTemp = [
		'title' => \XF::phrase('nav._default'),
		'href' => '',
		'attributes' => [],
	];
	if ($__navTemp) {
		$__tree['_default'] = $__navTemp;
		$__flat['_default'] =& $__tree['_default'];
		if (empty($__tree['_default']['children'])) { $__tree['_default']['children'] = []; }

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.defaultYourProfile'),
		'href' => $__templater->fn('link', array('members', $__vars['xf']['visitor'], ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['_default']['children']['defaultYourProfile'] = $__navTemp;
				$__flat['defaultYourProfile'] =& $__tree['_default']['children']['defaultYourProfile'];
			}
		}

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.defaultYourAccount'),
		'href' => $__templater->fn('link', array('account', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['_default']['children']['defaultYourAccount'] = $__navTemp;
				$__flat['defaultYourAccount'] =& $__tree['_default']['children']['defaultYourAccount'];
			}
		}

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.defaultLogOut'),
		'href' => $__templater->fn('link', array('logout', null, array('t' => $__templater->fn('csrf_token', array(), false), ), ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['_default']['children']['defaultLogOut'] = $__navTemp;
				$__flat['defaultLogOut'] =& $__tree['_default']['children']['defaultLogOut'];
			}
		}

		if ((!$__vars['xf']['visitor']['user_id'])) {
			$__navTemp = [
		'title' => \XF::phrase('nav.defaultRegister'),
		'href' => $__templater->fn('link', array('register', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['_default']['children']['defaultRegister'] = $__navTemp;
				$__flat['defaultRegister'] =& $__tree['_default']['children']['defaultRegister'];
			}
		}

	}

	$__navTemp = [
		'title' => \XF::phrase('nav.forums'),
		'href' => $__templater->fn('link', array('forums', ), false),
		'attributes' => [],
	];
	if ($__navTemp) {
		$__tree['forums'] = $__navTemp;
		$__flat['forums'] =& $__tree['forums'];
		if (empty($__tree['forums']['children'])) { $__tree['forums']['children'] = []; }

		if (($__vars['xf']['options']['forumsDefaultPage'] != 'new_posts')) {
			$__navTemp = [
		'title' => \XF::phrase('nav.newPosts'),
		'href' => $__templater->fn('link', array('whats-new/posts', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['newPosts'] = $__navTemp;
				$__flat['newPosts'] =& $__tree['forums']['children']['newPosts'];
			}
		}

		if (($__vars['xf']['options']['forumsDefaultPage'] != 'forums')) {
			$__navTemp = [
		'title' => \XF::phrase('nav.forumList'),
		'href' => $__templater->fn('link', array('forums/list', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['forumList'] = $__navTemp;
				$__flat['forumList'] =& $__tree['forums']['children']['forumList'];
			}
		}

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.findThreads'),
		'href' => $__templater->fn('link', array('find-threads/started', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['findThreads'] = $__navTemp;
				$__flat['findThreads'] =& $__tree['forums']['children']['findThreads'];
				if (empty($__tree['forums']['children']['findThreads']['children'])) { $__tree['forums']['children']['findThreads']['children'] = []; }

				if ($__vars['xf']['visitor']['user_id']) {
					$__navTemp = [
		'title' => \XF::phrase('nav.yourThreads'),
		'href' => $__templater->fn('link', array('find-threads/started', ), false),
		'attributes' => [],
	];
					if ($__navTemp) {
						$__tree['forums']['children']['findThreads']['children']['yourThreads'] = $__navTemp;
						$__flat['yourThreads'] =& $__tree['forums']['children']['findThreads']['children']['yourThreads'];
					}
				}

				if ($__vars['xf']['visitor']['user_id']) {
					$__navTemp = [
		'title' => \XF::phrase('nav.contributedThreads'),
		'href' => $__templater->fn('link', array('find-threads/contributed', ), false),
		'attributes' => [],
	];
					if ($__navTemp) {
						$__tree['forums']['children']['findThreads']['children']['contributedThreads'] = $__navTemp;
						$__flat['contributedThreads'] =& $__tree['forums']['children']['findThreads']['children']['contributedThreads'];
					}
				}

				$__navTemp = [
		'title' => \XF::phrase('nav.unansweredThreads'),
		'href' => $__templater->fn('link', array('find-threads/unanswered', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['forums']['children']['findThreads']['children']['unansweredThreads'] = $__navTemp;
					$__flat['unansweredThreads'] =& $__tree['forums']['children']['findThreads']['children']['unansweredThreads'];
				}

			}
		}

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.watched'),
		'href' => $__templater->fn('link', array('watched/threads', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['watched'] = $__navTemp;
				$__flat['watched'] =& $__tree['forums']['children']['watched'];
				if (empty($__tree['forums']['children']['watched']['children'])) { $__tree['forums']['children']['watched']['children'] = []; }

				if ($__vars['xf']['visitor']['user_id']) {
					$__navTemp = [
		'title' => \XF::phrase('nav.watchedThreads'),
		'href' => $__templater->fn('link', array('watched/threads', ), false),
		'attributes' => [],
	];
					if ($__navTemp) {
						$__tree['forums']['children']['watched']['children']['watchedThreads'] = $__navTemp;
						$__flat['watchedThreads'] =& $__tree['forums']['children']['watched']['children']['watchedThreads'];
					}
				}

				if ($__vars['xf']['visitor']['user_id']) {
					$__navTemp = [
		'title' => \XF::phrase('nav.watchedForums'),
		'href' => $__templater->fn('link', array('watched/forums', ), false),
		'attributes' => [],
	];
					if ($__navTemp) {
						$__tree['forums']['children']['watched']['children']['watchedForums'] = $__navTemp;
						$__flat['watchedForums'] =& $__tree['forums']['children']['watched']['children']['watchedForums'];
					}
				}

			}
		}

		if ($__templater->method($__vars['xf']['visitor'], 'canSearch', array())) {
			$__navTemp = [
		'title' => \XF::phrase('nav.searchForums'),
		'href' => $__templater->fn('link', array('search', null, array('type' => 'post', ), ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['searchForums'] = $__navTemp;
				$__flat['searchForums'] =& $__tree['forums']['children']['searchForums'];
			}
		}

		if ($__vars['xf']['visitor']['user_id']) {
			$__navTemp = [
		'title' => \XF::phrase('nav.markForumsRead'),
		'href' => $__templater->fn('link', array('forums/mark-read', '-', array('date' => $__vars['xf']['time'], ), ), false),
		'attributes' => [
			'data-xf-click' => 'overlay',
		],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['markForumsRead'] = $__navTemp;
				$__flat['markForumsRead'] =& $__tree['forums']['children']['markForumsRead'];
			}
		}

		if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('history', 'view', ))) {
			$__navTemp = [
		'title' => \XF::phrase('nav.history'),
		'href' => $__templater->fn('link', array('history', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['forums']['children']['history'] = $__navTemp;
				$__flat['history'] =& $__tree['forums']['children']['history'];
			}
		}

	}

	if (($__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array()) AND $__vars['xf']['options']['mjstDisplayOption']['nav_tabs'])) {
		$__navTemp = [
		'title' => \XF::phrase('nav.mjstSupportTicket'),
		'href' => $__templater->fn('link', array('support-tickets', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['mjstSupportTicket'] = $__navTemp;
			$__flat['mjstSupportTicket'] =& $__tree['mjstSupportTicket'];
			if (empty($__tree['mjstSupportTicket']['children'])) { $__tree['mjstSupportTicket']['children'] = []; }

			if (($__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array()) AND $__vars['xf']['visitor']['user_id'])) {
				$__navTemp = [
		'title' => \XF::phrase('nav.mjstYourTickets'),
		'href' => $__templater->fn('link', array('support-tickets/yours', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['mjstSupportTicket']['children']['mjstYourTickets'] = $__navTemp;
					$__flat['mjstYourTickets'] =& $__tree['mjstSupportTicket']['children']['mjstYourTickets'];
				}
			}

			if (($__templater->method($__vars['xf']['visitor'], 'canViewSupportTickets', array()) AND ($__vars['xf']['visitor']['user_id'] AND ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('mjstSupport', 'viewAnyTicket', )) OR $__vars['xf']['visitor']['mjst_department_ids'])))) {
				$__navTemp = [
		'title' => \XF::phrase('nav.mjstYourAssigned'),
		'href' => $__templater->fn('link', array('support-tickets/assigned', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['mjstSupportTicket']['children']['mjstYourAssigned'] = $__navTemp;
					$__flat['mjstYourAssigned'] =& $__tree['mjstSupportTicket']['children']['mjstYourAssigned'];
				}
			}

			if ($__templater->method($__vars['xf']['visitor'], 'canViewKb', array())) {
				$__navTemp = [
		'title' => \XF::phrase('nav.mjstKb'),
		'href' => $__templater->fn('link', array('support-tickets/knowledge-base', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['mjstSupportTicket']['children']['mjstKb'] = $__navTemp;
					$__flat['mjstKb'] =& $__tree['mjstSupportTicket']['children']['mjstKb'];
				}
			}

			if ($__vars['xf']['visitor']['user_id']) {
				$__navTemp = [
		'title' => \XF::phrase('nav.mjstWatched'),
		'href' => $__templater->fn('link', array('watched/tickets', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['mjstSupportTicket']['children']['mjstWatched'] = $__navTemp;
					$__flat['mjstWatched'] =& $__tree['mjstSupportTicket']['children']['mjstWatched'];
					if (empty($__tree['mjstSupportTicket']['children']['mjstWatched']['children'])) { $__tree['mjstSupportTicket']['children']['mjstWatched']['children'] = []; }

					if ($__vars['xf']['visitor']['user_id']) {
						$__navTemp = [
		'title' => \XF::phrase('nav.mjstWatchedTickets'),
		'href' => $__templater->fn('link', array('watched/tickets', ), false),
		'attributes' => [],
	];
						if ($__navTemp) {
							$__tree['mjstSupportTicket']['children']['mjstWatched']['children']['mjstWatchedTickets'] = $__navTemp;
							$__flat['mjstWatchedTickets'] =& $__tree['mjstSupportTicket']['children']['mjstWatched']['children']['mjstWatchedTickets'];
						}
					}

					if ($__vars['xf']['visitor']['user_id']) {
						$__navTemp = [
		'title' => \XF::phrase('nav.mjstWatchedDepartments'),
		'href' => $__templater->fn('link', array('watched/ticket-departments', ), false),
		'attributes' => [],
	];
						if ($__navTemp) {
							$__tree['mjstSupportTicket']['children']['mjstWatched']['children']['mjstWatchedDepartments'] = $__navTemp;
							$__flat['mjstWatchedDepartments'] =& $__tree['mjstSupportTicket']['children']['mjstWatched']['children']['mjstWatchedDepartments'];
						}
					}

				}
			}

		}
	}

	if ($__templater->method($__vars['xf']['visitor'], 'canViewMemberList', array())) {
		$__navTemp = [
		'title' => \XF::phrase('nav.members'),
		'href' => $__templater->fn('link', array('members', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['members'] = $__navTemp;
			$__flat['members'] =& $__tree['members'];
			if (empty($__tree['members']['children'])) { $__tree['members']['children'] = []; }

			if ($__vars['xf']['options']['enableMemberList']) {
				$__navTemp = [
		'title' => \XF::phrase('nav.registeredMembers'),
		'href' => $__templater->fn('link', array('members/list', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['members']['children']['registeredMembers'] = $__navTemp;
					$__flat['registeredMembers'] =& $__tree['members']['children']['registeredMembers'];
				}
			}

			$__navTemp = [
		'title' => \XF::phrase('nav.currentVisitors'),
		'href' => $__templater->fn('link', array('online', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['members']['children']['currentVisitors'] = $__navTemp;
				$__flat['currentVisitors'] =& $__tree['members']['children']['currentVisitors'];
			}

			if ($__templater->method($__vars['xf']['visitor'], 'canViewProfilePosts', array())) {
				$__navTemp = [
		'title' => \XF::phrase('nav.newProfilePosts'),
		'href' => $__templater->fn('link', array('whats-new/profile-posts', ), false),
		'attributes' => [
			'rel' => 'nofollow',
		],
	];
				if ($__navTemp) {
					$__tree['members']['children']['newProfilePosts'] = $__navTemp;
					$__flat['newProfilePosts'] =& $__tree['members']['children']['newProfilePosts'];
				}
			}

			if ($__vars['xf']['visitor']['user_id']) {
				$__navTemp = [
		'title' => \XF::phrase('nav.membersActivePlayers'),
		'href' => $__templater->fn('link', array('steam/active-players', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['members']['children']['membersActivePlayers'] = $__navTemp;
					$__flat['membersActivePlayers'] =& $__tree['members']['children']['membersActivePlayers'];
				}
			}

		}
	}

	if ($__templater->method($__vars['xf']['visitor'], 'canViewProducts', array())) {
		$__navTemp = [
		'title' => \XF::phrase('nav.xr_pm_products'),
		'href' => $__templater->fn('link', array('products', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['xr_pm_products'] = $__navTemp;
			$__flat['xr_pm_products'] =& $__tree['xr_pm_products'];
			if (empty($__tree['xr_pm_products']['children'])) { $__tree['xr_pm_products']['children'] = []; }

			if ($__vars['xf']['visitor']['user_id']) {
				$__navTemp = [
		'title' => \XF::phrase('nav.xr_pm_your_purchases'),
		'href' => $__templater->fn('link', array('products/purchases', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['xr_pm_products']['children']['xr_pm_your_purchases'] = $__navTemp;
					$__flat['xr_pm_your_purchases'] =& $__tree['xr_pm_products']['children']['xr_pm_your_purchases'];
				}
			}

			if ($__templater->method($__vars['xf']['visitor'], 'canSearch', array())) {
				$__navTemp = [
		'title' => \XF::phrase('nav.xr_pm_products_search'),
		'href' => $__templater->fn('link', array('search', null, array('type' => 'xr_pm_product', ), ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['xr_pm_products']['children']['xr_pm_products_search'] = $__navTemp;
					$__flat['xr_pm_products_search'] =& $__tree['xr_pm_products']['children']['xr_pm_products_search'];
				}
			}

		}
	}



	return [
		'tree' => $__tree,
		'flat' => $__flat
	];
};