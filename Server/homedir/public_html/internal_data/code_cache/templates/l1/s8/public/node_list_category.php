<?php
// FROM HASH: 6e7c675888f318681e7b42fbb6028389
return array('macros' => array('depth1' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'node' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block block--category block--category' . $__templater->escape($__vars['node']['node_id']) . ' ';
	if ($__templater->method($__vars['node'], 'isCollapsed_uix', array())) {
		$__finalCompiled .= 'category--collapsed';
	}
	$__finalCompiled .= '">
		<span class="u-anchorTarget" id="' . $__templater->escape($__templater->method($__vars['node']['Data'], 'getCategoryAnchor', array())) . '"></span>
		';
	if ($__templater->fn('property', array('uix_categoryStripOutsideWrapper', ), false)) {
		$__finalCompiled .= '
			<h2 class="block-header js-nodeMain' . ($__templater->fn('property', array('uix_stickyCategoryStrips', ), false) ? ' uix_stickyBodyElement' : '') . '">
				';
		if ($__templater->fn('property', array('uix_categoryStripIcons', ), false)) {
			$__finalCompiled .= '
					<div class="uix_categoryStrip__icon">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'folder',
			), $__vars) . '
					</div>
				';
		}
		$__finalCompiled .= '
				<div class="uix_categoryStrip-content">
					' . '
					' . '
					';
		$__vars['uix_categoryDescriptionDisplay'] = $__templater->fn('property', array('uix_categoryDescriptionDisplay', ), false);
		$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('categories', $__vars['node'], ), true) . '" class="uix_categoryTitle" data-xf-init="' . (($__vars['uix_categoryDescriptionDisplay'] == 'tooltip') ? 'element-tooltip' : '') . '" data-shortcut="node-description">' . $__templater->escape($__vars['node']['title']) . '</a>
					';
		if (($__vars['uix_categoryDescriptionDisplay'] != 'none') AND $__vars['node']['description']) {
			$__finalCompiled .= '
						<div class="node-description ' . (($__vars['uix_categoryDescriptionDisplay'] == 'tooltip') ? 'node-description--tooltip js-nodeDescTooltip' : '') . '">' . $__templater->filter($__vars['node']['description'], array(array('raw', array()),), true) . '</div>
					';
		}
		$__finalCompiled .= '
				</div>
				';
		if (($__templater->fn('property', array('uix_categoryCollapse', ), false) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('th_uix', 'collapseCategories', )))) {
			$__finalCompiled .= '
					<a class="u-ripple categoryCollapse--trigger">' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-up',
			), $__vars) . '</a>
				';
		}
		$__finalCompiled .= '
			</h2>
		';
	}
	$__finalCompiled .= '
		<div class="block-container">
			';
	if (!$__templater->fn('property', array('uix_categoryStripOutsideWrapper', ), false)) {
		$__finalCompiled .= '
			<h2 class="block-header js-nodeMain ' . ($__templater->fn('property', array('uix_stickyCategoryStrips', ), false) ? ' uix_stickyBodyElement' : '') . '">
				';
		if ($__templater->fn('property', array('uix_categoryStripIcons', ), false)) {
			$__finalCompiled .= '
					<div class="uix_categoryStrip__icon">
						' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'folder',
			), $__vars) . '
					</div>
				';
		}
		$__finalCompiled .= '
				<div class="uix_categoryStrip-content">
					' . '
					' . '
					';
		$__vars['uix_categoryDescriptionDisplay'] = $__templater->fn('property', array('uix_categoryDescriptionDisplay', ), false);
		$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('categories', $__vars['node'], ), true) . '" class="uix_categoryTitle" data-xf-init="' . (($__vars['uix_categoryDescriptionDisplay'] == 'tooltip') ? 'element-tooltip' : '') . '" data-shortcut="node-description">' . $__templater->escape($__vars['node']['title']) . '</a>
					';
		if (($__vars['uix_categoryDescriptionDisplay'] != 'none') AND $__vars['node']['description']) {
			$__finalCompiled .= '
						<div class="node-description ' . (($__vars['uix_categoryDescriptionDisplay'] == 'tooltip') ? 'node-description--tooltip js-nodeDescTooltip' : '') . '">' . $__templater->filter($__vars['node']['description'], array(array('raw', array()),), true) . '</div>
					';
		}
		$__finalCompiled .= '
				</div>
				';
		if (($__templater->fn('property', array('uix_categoryCollapse', ), false) AND $__templater->method($__vars['xf']['visitor'], 'hasPermission', array('th_uix', 'collapseCategories', )))) {
			$__finalCompiled .= '
					<a class="u-ripple categoryCollapse--trigger">' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'chevron-up',
			), $__vars) . '</a>
				';
		}
		$__finalCompiled .= '
			</h2>
			';
	}
	$__finalCompiled .= '
			<div class="uix_block-body--outer">
				<div class="block-body">
					' . $__templater->callMacro('forum_list', 'node_list', array(
		'children' => $__vars['children'],
		'extras' => $__vars['childExtras'],
		'depth' => ($__vars['depth'] + 1),
	), $__vars) . '
				</div>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'depth2' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'node' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="node below--xl node--id' . $__templater->escape($__vars['node']['node_id']) . ' node--depth' . $__templater->escape($__vars['depth']) . ' node--category ' . ($__vars['extras']['hasNew'] ? 'node--unread' : 'node--read') . '">
		<div class="node-body">
			<span class="node-icon" aria-hidden="true"><i></i></span>
			<div class="node-main js-nodeMain">
				';
	$__vars['descriptionDisplay'] = $__templater->fn('property', array('nodeListDescriptionDisplay', ), false);
	$__finalCompiled .= '
				<h3 class="node-title">
					<a href="' . $__templater->fn('link', array('categories', $__vars['node'], ), true) . '" data-xf-init="' . (($__vars['descriptionDisplay'] == 'tooltip') ? 'element-tooltip' : '') . '" data-shortcut="node-description">' . $__templater->escape($__vars['node']['title']) . '</a>
					';
	if ($__vars['extras']['hasNew'] AND $__templater->fn('property', array('uix_newNodeMarker', ), false)) {
		$__finalCompiled .= '<span class="uix_newIndicator">' . 'New' . '</span>';
	}
	$__finalCompiled .= '
				</h3>
				';
	if (($__vars['descriptionDisplay'] != 'none') AND $__vars['node']['description']) {
		$__finalCompiled .= '
					<div class="node-description ' . (($__vars['descriptionDisplay'] == 'tooltip') ? 'node-description--tooltip js-nodeDescTooltip' : '') . '">' . $__templater->filter($__vars['node']['description'], array(array('raw', array()),), true) . '</div>
				';
	}
	$__finalCompiled .= '

				';
	if (!$__templater->fn('property', array('uix_hideNodeStats', ), false)) {
		$__finalCompiled .= '
					<div class="node-meta">
						';
		if (!$__vars['extras']['privateInfo']) {
			$__finalCompiled .= '
							<div class="node-statsMeta">
								<dl class="pairs pairs--inline">
									';
			if ($__templater->fn('property', array('uix_nodeStatsIcons', ), false)) {
				$__finalCompiled .= '
										<dt>' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'post',
				), $__vars) . '</dt>
									';
			} else {
				$__finalCompiled .= '
										<dt>' . 'Threads' . '</dt>
									';
			}
			$__finalCompiled .= '
									<dd>' . $__templater->filter($__vars['extras']['discussion_count'], array(array('number', array()),), true) . '</dd>
								</dl>
								<dl class="pairs pairs--inline">
									';
			if ($__templater->fn('property', array('uix_nodeStatsIcons', ), false)) {
				$__finalCompiled .= '
										<dt>' . $__templater->callMacro('uix_icons.less', 'icon', array(
					'icon' => 'messages',
				), $__vars) . '</dt>
									';
			} else {
				$__finalCompiled .= '
										<dt>' . 'Messages' . '</dt>
									';
			}
			$__finalCompiled .= '
									<dd>' . $__templater->filter($__vars['extras']['message_count'], array(array('number', array()),), true) . '</dd>
								</dl>
							</div>
						';
		}
		$__finalCompiled .= '

						';
		if (($__vars['depth'] == 2) AND ($__templater->fn('property', array('nodeListSubDisplay', ), false) == 'menu')) {
			$__finalCompiled .= '
							' . $__templater->callMacro('forum_list', 'sub_nodes_menu', array(
				'children' => $__vars['children'],
				'childExtras' => $__vars['childExtras'],
				'depth' => ($__vars['depth'] + 1),
			), $__vars) . '
						';
		}
		$__finalCompiled .= '
					</div>
				';
	}
	$__finalCompiled .= '

				';
	if (($__vars['depth'] == 2) AND ($__templater->fn('property', array('nodeListSubDisplay', ), false) == 'flat')) {
		$__finalCompiled .= '
					' . $__templater->callMacro('forum_list', 'sub_nodes_flat', array(
			'children' => $__vars['children'],
			'childExtras' => $__vars['childExtras'],
			'depth' => ($__vars['depth'] + 1),
		), $__vars) . '
				';
	}
	$__finalCompiled .= '
			</div>

			';
	if ((!$__vars['extras']['privateInfo']) AND (!$__templater->fn('property', array('uix_hideNodeStats', ), false))) {
		$__finalCompiled .= '
				<div class="node-stats">
					<dl class="pairs pairs--rows">
						<dt>' . 'Threads' . '</dt>
						<dd>' . $__templater->filter($__vars['extras']['discussion_count'], array(array('number', array()),), true) . '</dd>
					</dl>
					<dl class="pairs pairs--rows">
						<dt>' . 'Messages' . '</dt>
						<dd>' . $__templater->filter($__vars['extras']['message_count'], array(array('number', array()),), true) . '</dd>
					</dl>
				</div>
			';
	}
	$__finalCompiled .= '

			';
	if (!$__templater->fn('property', array('uix_hideNodeLastPost', ), false)) {
		$__finalCompiled .= '
				<div class="node-extra">
					';
		if ($__vars['extras']['privateInfo']) {
			$__finalCompiled .= '
						<span class="node-extra-placeholder">' . 'Private' . '</span>
					';
		} else if ($__vars['extras']['last_post_date']) {
			$__finalCompiled .= '
						<div class="uix_nodeExtra__rows">
							<div class="node-extra-row"><a href="' . $__templater->fn('link', array('posts', array('post_id' => $__vars['extras']['last_post_id'], ), ), true) . '" class="node-extra-title" title="' . $__templater->escape($__vars['extras']['last_thread_title']) . '">' . $__templater->escape($__vars['extras']['last_thread_title']) . '</a></div>
							<div class="node-extra-row">
								<ul class="listInline listInline--bullet">
									<li class="node-extra-date">' . $__templater->fn('date_dynamic', array($__vars['extras']['last_post_date'], array(
			))) . '</li>
									';
			if ($__templater->method($__vars['xf']['visitor'], 'isIgnoring', array($__vars['extras']['last_post_user_id'], ))) {
				$__finalCompiled .= '
										<li class="node-extra-user">' . 'Ignored member' . '</li>
									';
			} else {
				$__finalCompiled .= '
										<li class="node-extra-user">' . $__templater->fn('username_link', array(array('user_id' => $__vars['extras']['last_post_user_id'], 'username' => $__vars['extras']['last_post_username'], ), false, array(
				))) . '</li>
									';
			}
			$__finalCompiled .= '
								</ul>
							</div>
						</div>
					';
		} else {
			$__finalCompiled .= '
						<span class="node-extra-placeholder">' . 'None' . '</span>
					';
		}
		$__finalCompiled .= '
				</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
';
	return $__finalCompiled;
},
'depthN' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'node' => '!',
		'extras' => '!',
		'children' => '!',
		'childExtras' => '!',
		'depth' => '1',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li>
		<a href="' . $__templater->fn('link', array('categories', $__vars['node'], ), true) . '" class="subNodeLink subNodeLink--category ' . ($__vars['extras']['hasNew'] ? 'subNodeLink--unread' : '') . '">' . $__templater->escape($__vars['node']['title']) . '</a>
		' . $__templater->callMacro('forum_list', 'sub_node_list', array(
		'children' => $__vars['children'],
		'childExtras' => $__vars['childExtras'],
		'depth' => ($__vars['depth'] + 1),
	), $__vars) . '
	</li>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

';
	return $__finalCompiled;
});