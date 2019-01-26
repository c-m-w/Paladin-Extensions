<?php
// FROM HASH: 4ae1d7ad4ce9893d103fddc652edd367
return array('macros' => array('user_info' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
		'fallbackName' => '',
		'dateHtml' => '',
		'linkHtml' => '',
		'TS' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '

	
	<span class="message-userArrow"></span>
	<section itemscope itemtype="https://schema.org/Person" class="message-user">
		<div class="message-avatar ' . (($__vars['xf']['options']['showMessageOnlineStatus'] AND ($__vars['user'] AND $__templater->method($__vars['user'], 'isOnline', array()))) ? 'message-avatar--online' : '') . '">
			';
	if (($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tl') OR ($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tr')) {
		$__finalCompiled .= '
<div class="message-avatar-wrapper">
' . $__templater->includeTemplate('xfv_threadstarter_corner_banners', $__vars) . '
';
	} else {
		$__finalCompiled .= '                   
<div class="message-avatar-wrapper">
';
	}
	$__finalCompiled .= '	
				';
	if ($__templater->fn('property', array('uix_postBitAvatarSize', ), false) == 'small') {
		$__finalCompiled .= '
					' . $__templater->fn('avatar', array($__vars['user'], 's', false, array(
			'defaultname' => $__vars['fallbackName'],
			'itemprop' => 'image',
		))) . '
				';
	} else if ($__templater->fn('property', array('uix_postBitAvatarSize', ), false) == 'medium') {
		$__finalCompiled .= '
					' . $__templater->fn('avatar', array($__vars['user'], 'm', false, array(
			'defaultname' => $__vars['fallbackName'],
			'itemprop' => 'image',
		))) . '
				';
	} else if ($__templater->fn('property', array('uix_postBitAvatarSize', ), false) == 'large') {
		$__finalCompiled .= '
					' . $__templater->fn('avatar', array($__vars['user'], 'l', false, array(
			'defaultname' => $__vars['fallbackName'],
			'itemprop' => 'image',
		))) . '
				';
	}
	$__finalCompiled .= '
				';
	if ($__vars['xf']['options']['showMessageOnlineStatus'] AND ($__vars['user'] AND $__templater->method($__vars['user'], 'isOnline', array()))) {
		$__finalCompiled .= '
					<span class="message-avatar-online" data-xf-init="tooltip" title="' . $__templater->filter('Online now', array(array('for_attr', array()),), true) . '"></span>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
		<div class="uix_messagePostBitWrapper">
			<div class="message-userDetails">
				<h4 class="message-name">' . $__templater->fn('username_link', array($__vars['user'], true, array(
		'defaultname' => $__vars['fallbackName'],
		'itemprop' => 'name',
	))) . '</h4>
				' . $__templater->fn('user_title', array($__vars['user'], true, array(
		'tag' => 'h5',
		'class' => 'message-userTitle',
		'itemprop' => 'jobTitle',
	))) . '
				' . $__templater->fn('user_banners', array($__vars['user'], array(
		'tag' => 'div',
		'class' => 'message-userBanner',
		'itemprop' => 'jobTitle',
	))) . '
				';
	if ($__vars['dateHtml']) {
		$__finalCompiled .= '<div class="message-date">' . $__templater->escape($__vars['dateHtml']) . '</div>';
	}
	$__finalCompiled .= '
			</div>
			';
	if ($__vars['linkHtml']) {
		$__finalCompiled .= '<div class="message-permalink">' . $__templater->escape($__vars['linkHtml']) . '</div>';
	}
	$__finalCompiled .= '
			';
	if ($__vars['user']['user_id']) {
		$__finalCompiled .= '
				';
		$__vars['extras'] = $__templater->fn('property', array('messageUserElements', ), false);
		$__finalCompiled .= '
				';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
';
		if ($__templater->fn('property', array('th_showReactionsPostbit_reactions', ), false) AND ($__templater->fn('property', array('th_showReactionsPostbit_location_reactions', ), false) == 'top')) {
			$__compilerTemp1 .= '
	' . $__templater->callMacro('th_display_reactions', 'react_postbit', array(
				'reacts' => $__vars['user']['react_count'],
				'reactsCount' => $__templater->method($__vars['user'], 'getReactTotalCount', array()),
				'displayType' => $__templater->fn('property', array('th_showReactionsPostbit_displayType_reactions', ), false),
				'displayLocation' => 'top',
			), $__vars) . '
';
		}
		$__compilerTemp1 .= '

									';
		if ($__vars['extras']['register_date']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Joined' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'user',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Joined' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>

											<dd>' . $__templater->fn('date', array($__vars['user']['register_date'], ), true) . '</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['message_count']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Messages' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'messages',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Messages' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd>' . $__templater->filter($__vars['user']['message_count'], array(array('number', array()),), true) . '</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['like_count']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Likes' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'like',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
														' . 'Likes' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd>' . $__templater->filter($__vars['user']['like_count'], array(array('number', array()),), true) . '</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['trophy_points'] AND $__vars['xf']['options']['enableTrophies']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Points' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'trophy',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Points' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd>' . $__templater->filter($__vars['user']['trophy_points'], array(array('number', array()),), true) . '</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['age'] AND $__vars['user']['Profile']['age']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Age' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'birthday',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Age' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd>' . $__templater->escape($__vars['user']['Profile']['age']) . '</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['location'] AND $__vars['user']['Profile']['location']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Location' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'location',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Location' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd>
												';
			if ($__vars['xf']['options']['geoLocationUrl']) {
				$__compilerTemp1 .= '
													<a href="' . $__templater->fn('link', array('misc/location-info', '', array('location' => $__vars['user']['Profile']['location'], ), ), true) . '" rel="nofollow noreferrer" target="_blank" class="u-concealed">' . $__templater->escape($__vars['user']['Profile']['location']) . '</a>
												';
			} else {
				$__compilerTemp1 .= '
													' . $__templater->escape($__vars['user']['Profile']['location']) . '
												';
			}
			$__compilerTemp1 .= '
											</dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['website'] AND $__vars['user']['Profile']['website']) {
			$__compilerTemp1 .= '
										<dl class="pairs pairs--justified">
											<dt>
												';
			if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
				$__compilerTemp1 .= '
													<span data-xf-init="tooltip" title="' . 'Website' . '">
														' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'web',
				), $__vars) . '
													</span>
												';
			} else {
				$__compilerTemp1 .= '
													' . 'Website' . '
												';
			}
			$__compilerTemp1 .= '
											</dt>
											<dd><a href="' . $__templater->escape($__vars['user']['Profile']['website']) . '" rel="nofollow" target="_blank">' . $__templater->filter($__vars['user']['Profile']['website'], array(array('url', array('host', 'Visit site', )),), true) . '</a></dd>
										</dl>
									';
		}
		$__compilerTemp1 .= '
									';
		if ($__vars['extras']['custom_fields']) {
			$__compilerTemp1 .= '
										' . $__templater->callMacro('custom_fields_macros', 'custom_fields_values', array(
				'type' => 'users',
				'group' => 'personal',
				'set' => $__vars['user']['Profile']['custom_fields'],
				'additionalFilters' => array('message', ),
				'valueClass' => 'pairs pairs--justified',
			), $__vars) . '
										';
			if ($__templater->method($__vars['user'], 'canViewIdentities', array())) {
				$__compilerTemp1 .= '
											' . $__templater->callMacro('custom_fields_macros', 'custom_fields_view', array(
					'type' => 'users',
					'group' => 'contact',
					'set' => $__vars['user']['Profile']['custom_fields'],
					'additionalFilters' => array('message', ),
					'valueClass' => 'pairs pairs--justified',
				), $__vars) . '
										';
			}
			$__compilerTemp1 .= '
									';
		}
		$__compilerTemp1 .= '
								
';
		if ($__templater->fn('property', array('th_showReactionsPostbit_reactions', ), false) AND ($__templater->fn('property', array('th_showReactionsPostbit_location_reactions', ), false) == 'bottom')) {
			$__compilerTemp1 .= '
	' . $__templater->callMacro('th_display_reactions', 'react_postbit', array(
				'reacts' => $__vars['user']['react_count'],
				'reactsCount' => $__templater->method($__vars['user'], 'getReactTotalCount', array()),
				'displayType' => $__templater->fn('property', array('th_showReactionsPostbit_displayType_reactions', ), false),
				'displayLocation' => 'bottom',
			), $__vars) . '
';
		}
		$__compilerTemp1 .= '
';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
					';
			if ($__templater->fn('property', array('uix_collapseExtraInfo', ), false)) {
				$__finalCompiled .= '
						<div class="thThreads__message-userExtras">
					';
			}
			$__finalCompiled .= '
							<div class="message-userExtras">
								' . $__compilerTemp1 . '
							</div>
						';
			if ($__templater->fn('property', array('uix_collapseExtraInfo', ), false)) {
				$__finalCompiled .= '
							</div>
							<div class="thThreads__userExtra--toggle">
								<span class="thThreads__userExtra--trigger"></span>
							</div>
						';
			}
			$__finalCompiled .= '
				';
		}
		$__finalCompiled .= '
			';
	}
	$__finalCompiled .= '
		</div>
		<span class="message-userArrow"></span>
	</section>
';
	return $__finalCompiled;
},
'user_info_simple' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
		'fallbackName' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<header itemscope itemtype="https://schema.org/Person" class="message-user">
		<meta itemprop="name" content="' . ($__templater->escape($__vars['user']['username']) ?: $__templater->escape($__vars['fallbackName'])) . '">
		<div class="message-avatar">
			';
	if (($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tl') OR ($__templater->fn('property', array('xfv_threadstarter_locale', ), false) == 'avatar_banner_tr')) {
		$__finalCompiled .= '
<div class="message-avatar-wrapper">
' . $__templater->includeTemplate('xfv_threadstarter_corner_banners', $__vars) . '
';
	} else {
		$__finalCompiled .= '                   
<div class="message-avatar-wrapper">
';
	}
	$__finalCompiled .= '	
				' . $__templater->fn('avatar', array($__vars['user'], 's', false, array(
		'defaultname' => $__vars['fallbackName'],
		'itemprop' => 'image',
	))) . '
			</div>
		</div>
		<span class="message-userArrow"></span>
	</header>
';
	return $__finalCompiled;
},
'attachments' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'attachments' => '!',
		'message' => '!',
		'canView' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	if ($__templater->isTraversable($__vars['attachments'])) {
		foreach ($__vars['attachments'] AS $__vars['attachment']) {
			if (!$__templater->method($__vars['message'], 'isAttachmentEmbedded', array($__vars['attachment'], ))) {
				$__compilerTemp1 .= '
						' . $__templater->callMacro('attachment_macros', 'attachment_list_item', array(
					'attachment' => $__vars['attachment'],
					'canView' => $__vars['canView'],
				), $__vars) . '
					';
			}
		}
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		';
		$__templater->includeCss('attachments.less');
		$__finalCompiled .= '
		<section class="message-attachments">
			<h4 class="block-textHeader">' . 'Attachments' . '</h4>
			<ul class="attachmentList">
				' . $__compilerTemp1 . '
			</ul>
		</section>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'signature' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['xf']['visitor']['Option']['content_show_signature'] AND $__vars['user']['Profile']['signature']) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
				' . $__templater->fn('bb_code', array($__vars['user']['Profile']['signature'], 'user:signature', $__vars['user'], ), true) . '
			';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
			<aside class="message-signature">
			' . $__compilerTemp1 . '
			</aside>
		';
		}
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

' . '

';
	return $__finalCompiled;
});