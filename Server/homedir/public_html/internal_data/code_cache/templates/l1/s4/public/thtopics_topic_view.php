<?php
// FROM HASH: 2de2b0eda9ccecc4f195be10fd431995
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['topic']['title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped($__templater->escape($__vars['topic']['description']));
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

';
	$__templater->setPageParam('uix_mainTabSets', 'forum');
	$__finalCompiled .= '
';
	$__templater->setPageParam('uix_mainTabActive', 'topics');
	$__finalCompiled .= '

';
	$__templater->setPageParam('$topic', '$topic');
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'canonical_url', array(
		'canonicalUrl' => $__templater->fn('link', array('canonical:topics', $__vars['topic'], array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

';
	if ($__vars['pendingApproval']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important">' . 'Your content has been submitted and will be displayed pending approval by a moderator.' . '</div>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['canInlineMod']) {
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

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('
		' . 'Post' . '
	', array(
		'href' => $__templater->fn('link', array('topics/post-thread', $__vars['topic'], ), false),
		'overlay' => ($__vars['topic']['node_id'] ? '' : 'true'),
		'class' => 'button--cta',
		'icon' => 'write',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

' . $__templater->callAdsMacro('thtopics_topic_view_above_thread_list', array(
		'topic' => $__vars['topic'],
	), $__vars) . '
' . $__templater->widgetPosition('thtopics_topic_view_above_thread_list', array()) . '

' . $__templater->callMacro('thtopics_topic_scroller', 'scroller', array(
		'route' => 'topic_view',
		'page' => $__vars['page'],
		'extra' => $__vars['topic']['topic_id'],
	), $__vars) . '

<div class="block"
	 data-xf-init="' . ($__vars['canInlineMod'] ? 'inline-mod' : '') . '"
	 data-type="thread"
	 data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">

	';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'topics',
		'data' => $__vars['topic'],
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

		';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
						';
	if ($__vars['canInlineMod']) {
		$__compilerTemp2 .= '
							' . $__templater->callMacro('inline_mod_macros', 'button', array(), $__vars) . '
						';
	}
	$__compilerTemp2 .= '
						';
	if ($__vars['xf']['visitor']['user_id']) {
		$__compilerTemp2 .= '
							' . $__templater->button('
								' . 'Mark read' . '
							', array(
			'href' => $__templater->fn('link', array('topics/mark-read', $__vars['topic'], array('date' => $__vars['xf']['time'], ), ), false),
			'class' => 'button--link',
			'overlay' => 'true',
		), '', array(
		)) . '
						';
	}
	$__compilerTemp2 .= '
						';
	if ($__templater->method($__vars['topic'], 'canWatch', array())) {
		$__compilerTemp2 .= '
							';
		$__compilerTemp3 = '';
		if ($__vars['topic']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp3 .= 'Unwatch';
		} else {
			$__compilerTemp3 .= 'Watch';
		}
		$__compilerTemp2 .= $__templater->button('
								' . $__compilerTemp3 . '
							', array(
			'href' => $__templater->fn('link', array('topics/watch', $__vars['topic'], ), false),
			'class' => 'button--link',
			'data-xf-click' => 'switch-overlay',
			'data-sk-watch' => 'Watch',
			'data-sk-unwatch' => 'Unwatch',
		), '', array(
		)) . '
						';
	}
	$__compilerTemp2 .= '
					';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
			<div class="block-outer-opposite">
				<div class="buttonGroup">
					' . $__compilerTemp2 . '
				</div>
			</div>
		';
	}
	$__compilerTemp1 .= '
		';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
	<div class="block-outer">
		' . $__compilerTemp1 . '
	</div>
	';
	}
	$__finalCompiled .= '

	';
	$__vars['dateLimits'] = array('-1' => 'Any time', '7' => '' . '7' . ' days', '14' => '' . '14' . ' days', '30' => '' . '30' . ' days', '60' => '' . '2' . ' months', '90' => '' . '3' . ' months', '182' => '' . '6' . ' months', '365' => '1 year', );
	$__finalCompiled .= '
	';
	$__vars['sortOrders'] = array('last_post_date' => 'Last message', 'post_date' => 'First message', 'title' => 'Title', 'reply_count' => 'Replies', 'view_count' => 'Views', 'first_post_likes' => 'First message likes', );
	$__finalCompiled .= '

	<div class="block-container">
		<div class="block-filterBar">
			<div class="filterBar">
				';
	$__compilerTemp4 = '';
	$__compilerTemp4 .= '
							';
	if ($__vars['filters']['prefix_id']) {
		$__compilerTemp4 .= '
								<li><a href="' . $__templater->fn('link', array('topics', $__vars['topic'], $__templater->filter($__vars['filters'], array(array('replace', array('prefix_id', null, )),), false), ), true) . '"
									   class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
									<span class="filterBar-filterToggle-label">' . 'Prefix' . $__vars['xf']['language']['label_separator'] . '</span>
									' . $__templater->fn('prefix_title', array('thread', $__vars['filters']['prefix_id'], ), true) . '</a></li>
							';
	}
	$__compilerTemp4 .= '
							';
	if ($__vars['filters']['starter_id'] AND $__vars['starterFilter']) {
		$__compilerTemp4 .= '
								<li><a href="' . $__templater->fn('link', array('topics', $__vars['topic'], $__templater->filter($__vars['filters'], array(array('replace', array('starter_id', null, )),), false), ), true) . '"
									   class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
									<span class="filterBar-filterToggle-label">' . 'Started by' . $__vars['xf']['language']['label_separator'] . '</span>
									' . $__templater->escape($__vars['starterFilter']['username']) . '</a></li>
							';
	}
	$__compilerTemp4 .= '
							';
	if ($__vars['filters']['last_days'] AND $__vars['dateLimits'][$__vars['filters']['last_days']]) {
		$__compilerTemp4 .= '
								<li><a href="' . $__templater->fn('link', array('topics', $__vars['topic'], $__templater->filter($__vars['filters'], array(array('replace', array('last_days', null, )),), false), ), true) . '"
									   class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Remove this filter', array(array('for_attr', array()),), true) . '">
									<span class="filterBar-filterToggle-label">' . 'Last updated' . $__vars['xf']['language']['label_separator'] . '</span>
									' . $__templater->escape($__vars['dateLimits'][$__vars['filters']['last_days']]) . '</a></li>
							';
	}
	$__compilerTemp4 .= '
							';
	if ($__vars['filters']['order'] AND $__vars['sortOrders'][$__vars['filters']['order']]) {
		$__compilerTemp4 .= '
								<li><a href="' . $__templater->fn('link', array('topics', $__vars['topic'], $__templater->filter($__vars['filters'], array(array('replace', array(array('order' => null, 'direction' => null, ), )),), false), ), true) . '"
									   class="filterBar-filterToggle" data-xf-init="tooltip" title="' . $__templater->filter('Return to the default order', array(array('for_attr', array()),), true) . '">
									<span class="filterBar-filterToggle-label">' . 'Sort by' . $__vars['xf']['language']['label_separator'] . '</span>
									' . $__templater->escape($__vars['sortOrders'][$__vars['filters']['order']]) . '
									<i class="fa ' . (($__vars['filters']['direction'] == 'asc') ? 'fa-angle-up' : 'fa-angle-down') . '" aria-hidden="true"></i>
									<span class="u-srOnly">';
		if ($__vars['filters']['direction'] == 'asc') {
			$__compilerTemp4 .= 'Ascending';
		} else {
			$__compilerTemp4 .= 'Descending';
		}
		$__compilerTemp4 .= '</span>
									</a></li>
							';
	}
	$__compilerTemp4 .= '

							' . $__templater->includeTemplate('thtopics_filterbar_topics', $__vars) . '
						';
	if (strlen(trim($__compilerTemp4)) > 0) {
		$__finalCompiled .= '
					<ul class="filterBar-filters">
						' . $__compilerTemp4 . '
					</ul>
				';
	}
	$__finalCompiled .= '

				<a class="filterBar-menuTrigger" data-xf-click="menu" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true">' . 'Filters' . '</a>
				<div class="menu menu--wide" data-menu="menu" aria-hidden="true"
					 data-href="' . $__templater->fn('link', array('topics/filters', $__vars['topic'], $__vars['filters'], ), true) . '"
					 data-load-target=".js-filterMenuBody">
					<div class="menu-content">
						<h4 class="menu-header">' . 'Show only' . $__vars['xf']['language']['label_separator'] . '</h4>
						<div class="js-filterMenuBody">
							<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
						</div>
					</div>
				</div>
			</div>
		</div>

		';
	$__vars['qtPos'] = $__templater->preEscaped(((($__vars['sortInfo']['order'] == 'last_post_date') AND ($__vars['sortInfo']['direction'] == 'asc')) ? 'bottom' : 'top'));
	$__finalCompiled .= '
		<div class="block-body" data-thtopic-replace="replace">
			<div class="structItemContainer">
				' . $__templater->callMacro('thread_list_macros', 'quick_thread', array(
		'forum' => $__vars['topic']['Forum'],
		'page' => $__vars['page'],
		'order' => $__vars['sortInfo']['order'],
		'direction' => $__vars['sortInfo']['direction'],
	), $__vars) . '
				';
	if (!$__templater->test($__vars['threads'], 'empty', array())) {
		$__finalCompiled .= '
					<div class="structitemContainer-group js-threadList">
						';
		if ($__templater->isTraversable($__vars['threads'])) {
			foreach ($__vars['threads'] AS $__vars['thread']) {
				$__finalCompiled .= '
							' . $__templater->callMacro('thread_list_macros', 'item', array(
					'thread' => $__vars['thread'],
					'forum' => $__vars['forum'],
				), $__vars) . '
						';
			}
		}
		$__finalCompiled .= '
					</div>
					';
	} else if ($__vars['filters']) {
		$__finalCompiled .= '
					<div class="structItem js-emptyThreadList">
						<div class="block-row">' . 'There are no threads matching your filters.' . '</div>
					</div>
					';
	} else {
		$__finalCompiled .= '
					<div class="structItem js-emptyThreadList">
						<div class="block-row">' . 'thtopics_there_no_threads_in_this_topic' . '</div>
					</div>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'forums',
		'data' => $__vars['forum'],
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>

' . $__templater->callAdsMacro('thtopics_topic_view_below_thread_list', array(
		'topic' => $__vars['topic'],
	), $__vars) . '
' . $__templater->widgetPosition('thtopics_topic_view_below_thread_list', array()) . '

';
	$__templater->modifySidebarHtml('_xfWidgetPositionSidebarThtopicsTopicViewSidebar', $__templater->widgetPosition('thtopics_topic_view_sidebar', array(
		'topic' => $__vars['topic'],
	)), 'replace');
	$__finalCompiled .= '

' . $__templater->callMacro('thtopics_topic_macros', 'assets', array(), $__vars);
	return $__finalCompiled;
});