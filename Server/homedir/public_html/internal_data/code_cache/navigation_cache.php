<?php

return function($__templater, $__selectedNav, array $__vars)
{
	$__tree = [];
	$__flat = [];

	\XF\Navigation\NodeType::configureDisplay(20, [
		'title' => \XF::phrase('nav.navSupportArea'),
		'with_children' => false,
	]);

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

	$__navTemp = \XF\Navigation\NodeType::displayNode(20);
	if ($__navTemp) {
		$__tree['navSupportArea'] = $__navTemp;
		$__flat['navSupportArea'] =& $__tree['navSupportArea'];
		if (empty($__tree['navSupportArea']['children'])) { $__tree['navSupportArea']['children'] = []; }

		$__navTemp = [
		'title' => \XF::phrase('nav.navSupportCreate'),
		'href' => $__templater->fn('link', array('support/post-thread', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['navSupportArea']['children']['navSupportCreate'] = $__navTemp;
			$__flat['navSupportCreate'] =& $__tree['navSupportArea']['children']['navSupportCreate'];
		}

		$__navTemp = [
		'title' => \XF::phrase('nav.navSupportTickets'),
		'href' => $__templater->fn('link', array('support/', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['navSupportArea']['children']['navSupportTickets'] = $__navTemp;
			$__flat['navSupportTickets'] =& $__tree['navSupportArea']['children']['navSupportTickets'];
		}

	}

	if ($__templater->method($__vars['xf']['visitor'], 'canViewResources', array())) {
		$__navTemp = [
		'title' => \XF::phrase('nav.xfrm'),
		'href' => $__templater->fn('link', array('resources', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['xfrm'] = $__navTemp;
			$__flat['xfrm'] =& $__tree['xfrm'];
			if (empty($__tree['xfrm']['children'])) { $__tree['xfrm']['children'] = []; }

			$__navTemp = [
		'title' => \XF::phrase('nav.extensionsFreeExtensions'),
		'href' => $__templater->fn('link', array('extensions/categories/2', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['xfrm']['children']['extensionsFreeExtensions'] = $__navTemp;
				$__flat['extensionsFreeExtensions'] =& $__tree['xfrm']['children']['extensionsFreeExtensions'];
			}

			$__navTemp = [
		'title' => \XF::phrase('nav.extensionsPremiumExtensions'),
		'href' => $__templater->fn('link', array('extensions/categories/1', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['xfrm']['children']['extensionsPremiumExtensions'] = $__navTemp;
				$__flat['extensionsPremiumExtensions'] =& $__tree['xfrm']['children']['extensionsPremiumExtensions'];
			}

			if ($__vars['xf']['visitor']['user_id']) {
				$__navTemp = [
		'title' => \XF::phrase('nav.xfrmWatched'),
		'href' => '',
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['xfrm']['children']['xfrmWatched'] = $__navTemp;
					$__flat['xfrmWatched'] =& $__tree['xfrm']['children']['xfrmWatched'];
					if (empty($__tree['xfrm']['children']['xfrmWatched']['children'])) { $__tree['xfrm']['children']['xfrmWatched']['children'] = []; }

					if ($__vars['xf']['visitor']['user_id']) {
						$__navTemp = [
		'title' => \XF::phrase('nav.xfrmWatchedResources'),
		'href' => $__templater->fn('link', array('watched/resources', ), false),
		'attributes' => [],
	];
						if ($__navTemp) {
							$__tree['xfrm']['children']['xfrmWatched']['children']['xfrmWatchedResources'] = $__navTemp;
							$__flat['xfrmWatchedResources'] =& $__tree['xfrm']['children']['xfrmWatched']['children']['xfrmWatchedResources'];
						}
					}

					if ($__vars['xf']['visitor']['user_id']) {
						$__navTemp = [
		'title' => \XF::phrase('nav.xfrmWatchedCategories'),
		'href' => $__templater->fn('link', array('watched/resource-categories', ), false),
		'attributes' => [],
	];
						if ($__navTemp) {
							$__tree['xfrm']['children']['xfrmWatched']['children']['xfrmWatchedCategories'] = $__navTemp;
							$__flat['xfrmWatchedCategories'] =& $__tree['xfrm']['children']['xfrmWatched']['children']['xfrmWatchedCategories'];
						}
					}

				}
			}

			if ($__templater->method($__vars['xf']['visitor'], 'canSearch', array())) {
				$__navTemp = [
		'title' => \XF::phrase('nav.xfrmSearchResources'),
		'href' => $__templater->fn('link', array('search', null, array('type' => 'resource', ), ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['xfrm']['children']['xfrmSearchResources'] = $__navTemp;
					$__flat['xfrmSearchResources'] =& $__tree['xfrm']['children']['xfrmSearchResources'];
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

		}
	}

	if ($__vars['xf']['visitor']['user_id']) {
		$__navTemp = [
		'title' => \XF::phrase('nav.navPremium'),
		'href' => $__templater->fn('link', array('account', ), false) . 'upgrades',
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['navPremium'] = $__navTemp;
			$__flat['navPremium'] =& $__tree['navPremium'];
			if (empty($__tree['navPremium']['children'])) { $__tree['navPremium']['children'] = []; }

			$__navTemp = [
		'title' => \XF::phrase('nav.navPremiumSupport'),
		'href' => $__templater->fn('link', array('support/post-thread?prefix_id=4', ), false),
		'attributes' => [],
	];
			if ($__navTemp) {
				$__tree['navPremium']['children']['navPremiumSupport'] = $__navTemp;
				$__flat['navPremiumSupport'] =& $__tree['navPremium']['children']['navPremiumSupport'];
			}

			if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'createInvitations', ))) {
				$__navTemp = [
		'title' => \XF::phrase('nav.navPremiumInvitations'),
		'href' => $__templater->fn('link', array('account/invitations/create', ), false),
		'attributes' => [],
	];
				if ($__navTemp) {
					$__tree['navPremium']['children']['navPremiumInvitations'] = $__navTemp;
					$__flat['navPremiumInvitations'] =& $__tree['navPremium']['children']['navPremiumInvitations'];
				}
			}

		}
	}

	if (($__vars['xf']['options']['EWRdiscord_navtab'] AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('EWRdiscord', 'viewDiscord', )))) {
		$__navTemp = [
		'title' => \XF::phrase('nav.EWRdiscord'),
		'href' => $__templater->fn('link', array('ewr-discord', ), false),
		'attributes' => [],
	];
		if ($__navTemp) {
			$__tree['EWRdiscord'] = $__navTemp;
			$__flat['EWRdiscord'] =& $__tree['EWRdiscord'];
			if (empty($__tree['EWRdiscord']['children'])) { $__tree['EWRdiscord']['children'] = []; }

			if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('EWRdiscord', 'botPost', ))) {
				$__navTemp = [
		'title' => \XF::phrase('nav.EWRdiscord_botpost'),
		'href' => $__templater->fn('link', array('ewr-discord/botpost', ), false),
		'attributes' => [
			'data-xf-click' => 'overlay',
			'data-cache' => 'false',
		],
	];
				if ($__navTemp) {
					$__tree['EWRdiscord']['children']['EWRdiscord_botpost'] = $__navTemp;
					$__flat['EWRdiscord_botpost'] =& $__tree['EWRdiscord']['children']['EWRdiscord_botpost'];
				}
			}

		}
	}



	return [
		'tree' => $__tree,
		'flat' => $__flat
	];
};