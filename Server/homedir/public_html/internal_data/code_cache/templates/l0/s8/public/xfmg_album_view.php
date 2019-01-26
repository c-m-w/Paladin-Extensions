<?php
// FROM HASH: 21e276a38c107570be58f8bac632526d
return array('macros' => array('info_sidebar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'album' => $__vars['album'],
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'xfmg_album_information' . '</h3>
			<div class="block-body block-row">
				';
	if ($__vars['album']['Category']) {
		$__finalCompiled .= '
					<dl class="pairs pairs--justified">
						<dt>' . 'xfmg_category' . '</dt>
						<dd><a href="' . $__templater->fn('link', array('media/categories', $__vars['album']['Category'], ), true) . '">' . $__templater->escape($__vars['album']['Category']['title']) . '</a></dd>
					</dl>
				';
	}
	$__finalCompiled .= '

				<dl class="pairs pairs--justified">
					<dt>' . 'xfmg_album_owner' . '</dt>
					<dd>' . $__templater->fn('username_link', array($__vars['album']['User'], false, array(
		'defaultname' => $__vars['album']['username'],
	))) . '</dd>
				</dl>

				<dl class="pairs pairs--justified">
					<dt>' . 'xfmg_date_created' . '</dt>
					<dd>' . $__templater->fn('date_dynamic', array($__vars['album']['create_date'], array(
	))) . '</dd>
				</dl>

				<dl class="pairs pairs--justified">
					<dt>' . 'xfmg_item_count' . '</dt>
					<dd>' . $__templater->filter($__vars['album']['media_count'], array(array('number', array()),), true) . '</dd>
				</dl>

				<dl class="pairs pairs--justified">
					<dt>' . 'xfmg_view_count' . '</dt>
					<dd>' . $__templater->filter($__vars['album']['view_count'], array(array('number', array()),), true) . '</dd>
				</dl>

				<dl class="pairs pairs--justified">
					<dt>' . 'xfmg_comment_count' . '</dt>
					<dd>' . $__templater->filter($__vars['album']['comment_count'], array(array('number', array()),), true) . '</dd>
				</dl>

				';
	if ($__vars['album']['rating_count']) {
		$__finalCompiled .= '
					<dl class="pairs pairs--justified">
						<dt>' . 'xfmg_ratings' . '</dt>
						<dd>
							<a href="' . $__templater->fn('link', array('media/album-ratings/ratings', $__vars['album'], ), true) . '" data-xf-click="overlay">
								';
		if ($__vars['album']['rating_count'] > 1) {
			$__finalCompiled .= '
									' . $__templater->escape($__vars['album']['rating_count']) . ' ratings
									';
		} else {
			$__finalCompiled .= '
									' . $__templater->escape($__vars['album']['rating_count']) . ' rating
								';
		}
		$__finalCompiled .= '
							</a>
						</dd>
					</dl>
				';
	}
	$__finalCompiled .= '

				<dl class="pairs pairs--justified u-jsOnly">
					';
	if ($__templater->method($__vars['album'], 'canRate', array())) {
		$__finalCompiled .= '
						<dt>' . 'xfmg_rate_this_media' . '</dt>
						<dd>
							' . $__templater->callMacro('rating_macros', 'rating', array(
			'row' => false,
			'currentRating' => $__vars['album']['rating_avg'],
			'ratingHref' => $__templater->fn('link', array('media/album-ratings/rate', $__vars['album'], ), false),
		), $__vars) . '
						</dd>
					';
	} else {
		$__finalCompiled .= '
						<dt>' . 'xfmg_current_rating' . '</dt>
						<dd>
							' . $__templater->callMacro('rating_macros', 'rating', array(
			'row' => false,
			'readOnly' => 'true',
			'currentRating' => $__vars['album']['rating_avg'],
		), $__vars) . '
						</dd>
					';
	}
	$__finalCompiled .= '
				</dl>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'privacy_sidebar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'album' => '!',
		'addUsers' => '!',
		'viewUsers' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['album']['User']) {
		$__finalCompiled .= '
		<div class="block">
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'xfmg_album_privacy' . '</h3>
			<div class="block-body">
				<div class="block-row">
					<div class="contentRow">
						<div class="contentRow-figure">
							' . $__templater->fn('avatar', array($__vars['album']['User'], 's', false, array(
		))) . '
						</div>
						<div class="contentRow-main">
							<h3 class="contentRow-title">' . $__templater->fn('username_link', array($__vars['album']['User'], true, array(
		))) . '</h3>

							<div class="contentRow-muted">
								<dl class="pairs pairs--justified fauxBlockLink">
									<dt>' . 'xfmg_media_items' . '</dt>
									<dd>
										<a href="' . $__templater->fn('link', array('media/users', $__vars['album']['User'], ), true) . '" class="fauxBlockLink-blockLink u-concealed">
											' . $__templater->filter($__vars['album']['User']['xfmg_media_count'], array(array('number', array()),), true) . '
										</a>
									</dd>
								</dl>
								<dl class="pairs pairs--justified fauxBlockLink">
									<dt>' . 'xfmg_albums' . '</dt>
									<dd>
										<a href="' . $__templater->fn('link', array('media/albums/users', $__vars['album']['User'], ), true) . '" class="fauxBlockLink-blockLink u-concealed">
											' . $__templater->filter($__vars['album']['User']['xfmg_album_count'], array(array('number', array()),), true) . '
										</a>
									</dd>
								</dl>
							</div>
						</div>
					</div>
				</div>
				<div class="block-row">
					<dl class="pairs pairs--justified">
						<dt>' . 'xfmg_can_view_media_items' . '</dt>
						<dd>' . $__templater->escape($__templater->method($__vars['album'], 'getPrivacyPhrase', array($__vars['album']['view_privacy'], ))) . '</dd>
					</dl>
					';
		if (($__vars['album']['view_privacy'] == 'shared') AND $__vars['viewUsers']) {
			$__finalCompiled .= '
						<ul class="listHeap">
							';
			if ($__templater->isTraversable($__vars['viewUsers'])) {
				foreach ($__vars['viewUsers'] AS $__vars['user']) {
					$__finalCompiled .= '
								<li>' . $__templater->fn('avatar', array($__vars['user'], 'xs', false, array(
					))) . '</li>
							';
				}
			}
			$__finalCompiled .= '
						</ul>
					';
		}
		$__finalCompiled .= '
				</div>
				<div class="block-row">
					<dl class="pairs pairs--justified">
						<dt>' . 'xfmg_can_add_media_items' . '</dt>
						<dd>' . $__templater->escape($__templater->method($__vars['album'], 'getPrivacyPhrase', array($__vars['album']['add_privacy'], ))) . '</dd>
					</dl>
					';
		if (($__vars['album']['add_privacy'] == 'shared') AND $__vars['addUsers']) {
			$__finalCompiled .= '
						<ul class="listHeap">
							';
			if ($__templater->isTraversable($__vars['addUsers'])) {
				foreach ($__vars['addUsers'] AS $__vars['user']) {
					$__finalCompiled .= '
								<li>' . $__templater->fn('avatar', array($__vars['user'], 'xs', false, array(
					))) . '</li>
							';
				}
			}
			$__finalCompiled .= '
						</ul>
					';
		}
		$__finalCompiled .= '
				</div>
			</div>
			';
		if ($__templater->method($__vars['album'], 'canChangePrivacy', array())) {
			$__finalCompiled .= '
				<div class="block-footer">
					<span class="block-footer-controls">
						' . $__templater->button('xfmg_change_privacy', array(
				'href' => $__templater->fn('link', array('media/albums/change-privacy', $__vars['album'], ), false),
				'class' => 'button--small button--link',
				'overlay' => 'true',
			), '', array(
			)) . '
					</span>
				</div>
			';
		}
		$__finalCompiled .= '
		</div>
	</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'share_sidebar' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'album' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
								' . $__templater->callMacro('share_page_macros', 'buttons', array(
		'iconic' => true,
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
						<h3 class="block-minorHeader">' . 'xfmg_share_this_album' . '</h3>
						<div class="block-body block-row block-row--separated">
							' . $__compilerTemp2 . '
						</div>
					';
	}
	$__compilerTemp1 .= '
					';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
								';
	if ($__vars['album']['thumbnail_date']) {
		$__compilerTemp3 .= '
									' . $__templater->callMacro('share_page_macros', 'share_clipboard_input', array(
			'label' => 'xfmg_copy_url_bb_code_with_thumbnail',
			'text' => '[URL="' . $__templater->fn('link', array('canonical:media/albums', $__vars['album'], ), false) . '"][IMG]' . $__templater->method($__vars['album'], 'getThumbnailUrl', array(true, )) . '[/IMG][/URL]',
		), $__vars) . '
								';
	}
	$__compilerTemp3 .= '

								' . $__templater->callMacro('share_page_macros', 'share_clipboard_input', array(
		'label' => 'xfmg_copy_gallery_bb_code',
		'text' => '[GALLERY=album, ' . $__vars['album']['album_id'] . '][/GALLERY]',
	), $__vars) . '
							';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__compilerTemp1 .= '
						<div class="block-body block-row block-row--separated">
							' . $__compilerTemp3 . '
						</div>
					';
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
		<div class="block">
			<div class="block-container">
				' . $__compilerTemp1 . '
			</div>
		</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['album']['title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['noH1'] = true;
	$__finalCompiled .= '

';
	$__templater->includeCss('xfmg_album_view.less');
	$__finalCompiled .= '

' . $__templater->callMacro('xfmg_page_macros', 'xfmg_page_options', array(
		'album' => $__vars['album'],
		'category' => $__vars['album']['Category'],
	), $__vars) . '

';
	$__vars['descSnippet'] = $__templater->fn('snippet', array($__vars['mediaItem']['description'], 250, ), false);
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'metadata', array(
		'description' => $__vars['descSnippet'],
		'shareUrl' => $__templater->fn('link', array('canonical:media/albums', $__vars['album'], ), false),
		'imageUrl' => $__templater->method($__vars['album'], 'getThumbnailUrl', array(true, )),
		'canonicalUrl' => $__templater->fn('link', array('canonical:media/albums', $__vars['album'], array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

';
	$__templater->setPageParam('ldJsonHtml', '
<script type="application/ld+json">
' . $__templater->filter($__vars['album']['structured_data'], array(array('json', array(true, )),array('raw', array()),), true) . '
</script>
');
	$__finalCompiled .= '

' . $__templater->callMacro('xfmg_media_list_macros', 'media_create_message', array(
		'transcoding' => $__vars['transcoding'],
		'pendingApproval' => $__vars['pendingApproval'],
	), $__vars) . '

';
	$__templater->breadcrumbs($__templater->method($__vars['album'], 'getBreadcrumbs', array(false, )));
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['album'], 'canAddMedia', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
		' . $__templater->button('
			' . 'xfmg_add_media' . '
		', array(
			'href' => $__templater->fn('link', array('media/albums/add', $__vars['album'], ), false),
			'class' => 'button--cta',
			'icon' => 'add',
		), '', array(
		)) . '
	');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
					';
	if ($__vars['album']['album_state'] == 'deleted') {
		$__compilerTemp1 .= '
						<dd class="blockStatus-message blockStatus-message--deleted">
							' . $__templater->callMacro('deletion_macros', 'notice', array(
			'log' => $__vars['album']['DeletionLog'],
		), $__vars) . '
						</dd>
					';
	} else if ($__vars['album']['album_state'] == 'moderated') {
		$__compilerTemp1 .= '
						<dd class="blockStatus-message blockStatus-message--moderated">
							' . 'Awaiting approval before being displayed publicly.' . '
						</dd>
					';
	}
	$__compilerTemp1 .= '
					';
	if ($__vars['album']['warning_message']) {
		$__compilerTemp1 .= '
						<dd class="blockStatus-message blockStatus-message--warning">
							' . $__templater->escape($__vars['album']['warning_message']) . '
						</dd>
					';
	}
	$__compilerTemp1 .= '
					';
	if ($__templater->method($__vars['album'], 'isIgnored', array())) {
		$__compilerTemp1 .= '
						<div class="blockStatus-message blockStatus-message--ignored">
							' . 'You are ignoring content by this member.' . '
						</div>
					';
	}
	$__compilerTemp1 .= '
				';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-outer">
			<dl class="blockStatus">
				<dt>' . 'Status' . '</dt>
				' . $__compilerTemp1 . '
			</dl>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['canInlineModMediaItems']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'xf/inline_mod.js',
			'min' => '1',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

<div class="block" data-xf-init="' . ($__vars['canInlineModMediaItems'] ? 'inline-mod' : '') . '" data-type="xfmg_media" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">
	<div class="block-outer">';
	$__compilerTemp2 = '';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
					';
	$__compilerTemp4 = '';
	$__compilerTemp4 .= '
								';
	if ($__templater->method($__vars['album'], 'canRate', array())) {
		$__compilerTemp4 .= '
									' . $__templater->button('
										' . 'Leave a rating' . '
									', array(
			'href' => $__templater->fn('link', array('media/album-ratings/rate', $__vars['album'], ), false),
			'overlay' => 'true',
		), '', array(
		)) . '
								';
	}
	$__compilerTemp4 .= '
							';
	if (strlen(trim($__compilerTemp4)) > 0) {
		$__compilerTemp3 .= '
						<div class="buttonGroup">
							' . $__compilerTemp4 . '
						</div>
					';
	}
	$__compilerTemp3 .= '

					';
	$__compilerTemp5 = '';
	$__compilerTemp5 .= '
								';
	if ($__vars['canInlineModMediaItems']) {
		$__compilerTemp5 .= '
									' . $__templater->callMacro('inline_mod_macros', 'button', array(), $__vars) . '
								';
	}
	$__compilerTemp5 .= '
								';
	if ($__templater->method($__vars['album'], 'canUndelete', array()) AND ($__vars['album']['album_state'] == 'deleted')) {
		$__compilerTemp5 .= '
									' . $__templater->button('
										' . 'Undelete' . '
									', array(
			'href' => $__templater->fn('link', array('media/albums/undelete', $__vars['album'], ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
								';
	}
	$__compilerTemp5 .= '
								';
	if ($__templater->method($__vars['album'], 'canApproveUnapprove', array()) AND ($__vars['album']['album_state'] == 'moderated')) {
		$__compilerTemp5 .= '
									' . $__templater->button('
										' . 'Approve' . '
									', array(
			'href' => $__templater->fn('link', array('media/albums/approve', $__vars['album'], ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
								';
	}
	$__compilerTemp5 .= '
								';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp5 .= '
									' . $__templater->button('

										' . 'xfmg_mark_viewed' . '
									', array(
			'href' => $__templater->fn('link', array('media/albums/mark-viewed', $__vars['album'], array('date' => $__vars['xf']['time'], ), ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
								';
	}
	$__compilerTemp5 .= '

								';
	if ($__templater->method($__vars['album'], 'canWatch', array())) {
		$__compilerTemp5 .= '
									';
		$__compilerTemp6 = '';
		if ($__vars['album']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp6 .= '
											' . 'Unwatch' . '
											';
		} else {
			$__compilerTemp6 .= '
											' . 'Watch' . '
										';
		}
		$__compilerTemp5 .= $__templater->button('

										' . $__compilerTemp6 . '
									', array(
			'href' => $__templater->fn('link', array('media/albums/watch', $__vars['album'], ), false),
			'class' => 'button--link',
			'data-xf-click' => 'switch-overlay',
			'data-sk-watch' => 'Watch',
			'data-sk-unwatch' => 'Unwatch',
		), '', array(
		)) . '
								';
	}
	$__compilerTemp5 .= '

								';
	$__compilerTemp7 = '';
	$__compilerTemp7 .= '
													' . '
													';
	if ($__templater->method($__vars['album'], 'canEdit', array())) {
		$__compilerTemp7 .= '
														<a href="' . $__templater->fn('link', array('media/albums/edit', $__vars['album'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'xfmg_edit_album' . '</a>
													';
	}
	$__compilerTemp7 .= '
													';
	if ($__templater->method($__vars['album'], 'canMove', array())) {
		$__compilerTemp7 .= '
														<a href="' . $__templater->fn('link', array('media/albums/move', $__vars['album'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'xfmg_move_album' . '</a>
													';
	}
	$__compilerTemp7 .= '
													';
	if ($__templater->method($__vars['album'], 'canDelete', array('soft', ))) {
		$__compilerTemp7 .= '
														<a href="' . $__templater->fn('link', array('media/albums/delete', $__vars['album'], ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'xfmg_delete_album' . '</a>
													';
	}
	$__compilerTemp7 .= '
													' . '
													';
	if ($__templater->method($__vars['album'], 'canUseInlineModeration', array())) {
		$__compilerTemp7 .= '
														<div class="menu-footer"
															 data-xf-init="inline-mod"
															 data-type="xfmg_album"
															 data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '"
															 data-toggle=".js-albumInlineModToggle">
															' . $__templater->formCheckBox(array(
		), array(array(
			'class' => 'js-albumInlineModToggle',
			'value' => $__vars['album']['album_id'],
			'label' => 'Select for moderation',
			'_type' => 'option',
		))) . '
														</div>
													';
	}
	$__compilerTemp7 .= '
													' . '
												';
	if (strlen(trim($__compilerTemp7)) > 0) {
		$__compilerTemp5 .= '
									<div class="buttonGroup-buttonWrapper">
										' . $__templater->button('&#8226;&#8226;&#8226;', array(
			'class' => 'button--link menuTrigger',
			'data-xf-click' => 'menu',
			'aria-expanded' => 'false',
			'aria-haspopup' => 'true',
			'title' => 'More options',
		), '', array(
		)) . '
										<div class="menu" data-menu="menu" aria-hidden="true">
											<div class="menu-content">
												<h4 class="menu-header">' . 'More options' . '</h4>
												' . $__compilerTemp7 . '
											</div>
										</div>
									</div>
								';
	}
	$__compilerTemp5 .= '
							';
	if (strlen(trim($__compilerTemp5)) > 0) {
		$__compilerTemp3 .= '
						<div class="buttonGroup">
							' . $__compilerTemp5 . '
						</div>
					';
	}
	$__compilerTemp3 .= '
				';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__compilerTemp2 .= '
			<div class="block-outer-opposite">
				' . $__compilerTemp3 . '
			</div>
		';
	}
	$__finalCompiled .= trim('

		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['totalItems'],
		'link' => 'media/albums',
		'data' => $__vars['album'],
		'params' => (array('comment_page' => ($__vars['commentPage'] ?: null), ) + $__vars['filters']),
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

		' . $__compilerTemp2 . '

	') . '</div>
	<div class="block-container">
		' . $__templater->callMacro('xfmg_album_list_macros', 'list_filter_bar', array(
		'filters' => (array('comment_page' => ($__vars['commentPage'] ?: null), ) + $__vars['filters']),
		'baseLinkPath' => 'media/albums',
		'linkData' => $__vars['album'],
		'ownerFilter' => $__vars['ownerFilter'],
	), $__vars) . '

		<div class="block-body">
			';
	if (!$__templater->test($__vars['mediaItems'], 'empty', array())) {
		$__finalCompiled .= '
				' . $__templater->callMacro('xfmg_media_list_macros', 'media_list', array(
			'mediaItems' => $__vars['mediaItems'],
		), $__vars) . '
			';
	} else if ($__vars['filters']) {
		$__finalCompiled .= '
				<div class="block-row">' . 'xfmg_no_media_has_been_added_to_this_album_which_matches_your_filters' . '</div>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'xfmg_no_media_has_been_added_to_this_album_yet' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['totalItems'],
		'link' => 'media/albums',
		'data' => $__vars['album'],
		'params' => (array('comment_page' => ($__vars['commentPage'] ?: null), ) + $__vars['filters']),
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>

<div class="block">
	<div class="block-container">
		<div class="block-body block-row xfmgInfoBlock">
			<div class="xfmgInfoBlock-title">
				<div class="contentRow">
						<span class="contentRow-figure">
							' . $__templater->fn('avatar', array($__vars['album']['User'], 's', false, array(
		'defaultname' => $__vars['album']['username'],
	))) . '
						</span>
					<div class="contentRow-main">
						<h1 class="contentRow-title p-title-value">
							' . $__templater->fn('page_h1', array('')) . '
						</h1>
						<div class="contentRow-lesser p-description">
							<ul class="listInline listInline--bullet">
								<li><i class="fa fa-th" title="' . $__templater->filter('xfmg_items', array(array('for_attr', array()),), true) . '" aria-hidden="true"></i> ' . $__templater->filter($__vars['album']['media_count'], array(array('number_short', array()),), true) . '</li>
								<li><i class="fa fa-user" title="' . $__templater->filter('xfmg_album_owner', array(array('for_attr', array()),), true) . '" aria-hidden="true"></i> ' . $__templater->fn('username_link', array($__vars['album']['User'], false, array(
		'defaultname' => $__vars['album']['username'],
		'class' => 'u-concealed',
	))) . '</li>
								<li><i class="fa fa-clock-o" title="' . $__templater->filter('xfmg_date_created', array(array('for_attr', array()),), true) . '" aria-hidden="true"></i> ' . $__templater->fn('date_dynamic', array($__vars['album']['create_date'], array(
	))) . '</li>
							</ul>
						</div>
					</div>
				</div>
			</div>

			';
	if ($__vars['album']['description']) {
		$__finalCompiled .= '
				<div class="xfmgInfoBlock-description">
					<div class="bbCodeBlock bbCodeBlock--expandable">
						<div class="bbCodeBlock-content">
							<div class="bbCodeBlock-expandContent">
								' . $__templater->fn('structured_text', array($__vars['album']['description'], ), true) . '
							</div>
							<div class="bbCodeBlock-expandLink"><a>' . 'Click to expand...' . '</a></div>
						</div>
					</div>
				</div>
			';
	}
	$__finalCompiled .= '
			
			';
	if (!$__templater->fn('react_handler_status', array('xfmg_album', ), false)) {
		$__finalCompiled .= '
	<div class="likesBar js-likeList' . ($__vars['album']['likes'] ? ' is-active' : '') . '">
				' . $__templater->fn('likes_content', array($__vars['album'], $__templater->fn('link', array('media/albums/likes', $__vars['album'], ), false), array(
			'url' => $__templater->fn('link', array('media/albums/likes', $__vars['album'], ), false),
		))) . '
			</div>
';
	}
	$__finalCompiled .= '

			';
	$__compilerTemp8 = '';
	$__compilerTemp8 .= '
						' . $__templater->callMacro('th_display_reactions', 'reactions_bar', array(
		'type' => 'xfmg_album',
		'id' => 'album_id',
		'content' => $__vars['album'],
	), $__vars) . '

';
	$__compilerTemp9 = '';
	$__compilerTemp9 .= '
									';
	if (!$__templater->fn('react_handler_status', array('xfmg_album', ), false)) {
		$__compilerTemp9 .= '
	';
		if ($__templater->method($__vars['album'], 'canLike', array())) {
			$__compilerTemp9 .= '
										<a href="' . $__templater->fn('link', array('media/albums/like', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--like"
											data-xf-click="like"
											data-like-list="< .block | .js-likeList">
											';
			if ($__templater->method($__vars['album'], 'isLiked', array())) {
				$__compilerTemp9 .= 'Unlike';
			} else {
				$__compilerTemp9 .= 'Like';
			}
			$__compilerTemp9 .= '
										</a>
									';
		}
		$__compilerTemp9 .= '
';
	}
	$__compilerTemp9 .= '
								';
	if (strlen(trim($__compilerTemp9)) > 0) {
		$__compilerTemp8 .= '
							<div class="actionBar-set actionBar-set--external">
								' . $__compilerTemp9 . '
							</div>
						';
	}
	$__compilerTemp8 .= '

						';
	$__compilerTemp10 = '';
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['album'], 'canReport', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('media/albums/report', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--report"
											data-xf-click="overlay">' . 'Report' . '</a>
									';
	}
	$__compilerTemp10 .= '

									';
	$__vars['hasActionBarMenu'] = false;
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['album'], 'canEdit', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('media/albums/edit', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--edit actionBar-action--menuItem"
											data-xf-click="overlay">' . 'Edit' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	}
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['album'], 'canDelete', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('media/albums/delete', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--delete actionBar-action--menuItem"
											data-xf-click="overlay">' . 'Delete' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	}
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['album'], 'canCleanSpam', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('spam-cleaner', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--spam actionBar-action--menuItem"
											data-xf-click="overlay">' . 'Spam' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	}
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewIps', array()) AND $__vars['album']['ip_id']) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('media/albums/ip', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--ip actionBar-action--menuItem"
											data-xf-click="overlay">' . 'IP' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	}
	$__compilerTemp10 .= '
									';
	if ($__templater->method($__vars['album'], 'canWarn', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('media/albums/warn', $__vars['album'], ), true) . '"
											class="actionBar-action actionBar-action--warn actionBar-action--menuItem">' . 'Warn' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	} else if ($__vars['album']['warning_id'] AND $__templater->method($__vars['xf']['visitor'], 'canViewWarnings', array())) {
		$__compilerTemp10 .= '
										<a href="' . $__templater->fn('link', array('warnings', array('warning_id' => $__vars['album']['warning_id'], ), ), true) . '"
											class="actionBar-action actionBar-action--warn actionBar-action--menuItem"
											data-xf-click="overlay">' . 'View warning' . '</a>
										';
		$__vars['hasActionBarMenu'] = true;
		$__compilerTemp10 .= '
									';
	}
	$__compilerTemp10 .= '

									';
	if ($__vars['hasActionBarMenu']) {
		$__compilerTemp10 .= '
										<a class="actionBar-action actionBar-action--menuTrigger"
											data-xf-click="menu"
											title="' . $__templater->filter('More options', array(array('for_attr', array()),), true) . '"
											role="button"
											tabindex="0"
											aria-expanded="false"
											aria-haspopup="true">&#8226;&#8226;&#8226;</a>

										<div class="menu" data-menu="menu" aria-hidden="true" data-menu-builder="actionBar">
											<div class="menu-content">
												<h4 class="menu-header">' . 'More options' . '</h4>
												<div class="js-menuBuilderTarget"></div>
											</div>
										</div>
									';
	}
	$__compilerTemp10 .= '
								';
	if (strlen(trim($__compilerTemp10)) > 0) {
		$__compilerTemp8 .= '
							<div class="actionBar-set actionBar-set--internal">
								' . $__compilerTemp10 . '
							</div>
						';
	}
	$__compilerTemp8 .= '
					';
	if (strlen(trim($__compilerTemp8)) > 0) {
		$__finalCompiled .= '
				<div class="actionBar">
					' . $__compilerTemp8 . '
				</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>

';
	if ($__templater->method($__vars['album'], 'canViewComments', array())) {
		$__finalCompiled .= '
	<div class="columnContainer">
		<div class="columnContainer-comments">
			' . $__templater->callMacro('xfmg_comment_macros', 'comment_list', array(
			'comments' => $__vars['comments'],
			'content' => $__vars['album'],
			'linkPrefix' => 'media/album-comments',
			'link' => 'media/albums',
			'linkParams' => (array('page' => $__vars['page'], ) + $__vars['filters']),
			'page' => $__vars['commentPage'],
			'perPage' => $__vars['commentsPerPage'],
			'totalItems' => $__vars['totalComments'],
			'pageParam' => 'comment_page',
			'canInlineMod' => $__vars['canInlineModComments'],
		), $__vars) . '
		</div>

		<div class="columnContainer-sidebar">
			' . $__templater->callMacro(null, 'info_sidebar', array(
			'album' => $__vars['album'],
		), $__vars) . '
			' . $__templater->callMacro(null, 'privacy_sidebar', array(
			'album' => $__vars['album'],
			'addUsers' => $__vars['addUsers'],
			'viewUsers' => $__vars['viewUsers'],
		), $__vars) . '
			' . $__templater->callMacro(null, 'share_sidebar', array(
			'album' => $__vars['album'],
		), $__vars) . '
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->modifySidebarHtml('infoSidebar', '
		' . $__templater->callMacro(null, 'info_sidebar', array(
			'album' => $__vars['album'],
		), $__vars) . '
	', 'replace');
		$__finalCompiled .= '
	';
		$__templater->modifySidebarHtml('privacySidebar', '
		' . $__templater->callMacro(null, 'privacy_sidebar', array(
			'album' => $__vars['album'],
			'addUsers' => $__vars['addUsers'],
			'viewUsers' => $__vars['viewUsers'],
		), $__vars) . '
	', 'replace');
		$__finalCompiled .= '
	';
		$__templater->modifySidebarHtml('shareSidebar', '
		' . $__templater->callMacro(null, 'share_sidebar', array(
			'album' => $__vars['album'],
		), $__vars) . '
	', 'replace');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

' . '

';
	return $__finalCompiled;
});