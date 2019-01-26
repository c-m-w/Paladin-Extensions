<?php
// FROM HASH: 55d48a0c22e1c48cb352af2c247a0161
return array('macros' => array('bookmark_content' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'bookmarkTooltip' => false,
		'unbookmarkTooltip' => false,
		'currentBookmark' => false,
		'contentType' => '!',
		'isButton' => false,
		'aClass' => false,
		'contentId' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['currentBookmark']) {
		$__finalCompiled .= '
		';
		$__vars['iconClass'] = $__templater->preEscaped($__templater->fn('property', array('th_bookmarkIconClass_bookmarked_bookmarks', ), true));
		$__finalCompiled .= '
		';
		if ($__vars['unbookmarkTooltip']) {
			$__finalCompiled .= '
			';
			$__vars['tooltip'] = $__templater->preEscaped($__templater->escape($__vars['unbookmarkTooltip']));
			$__finalCompiled .= '
			';
		} else {
			$__finalCompiled .= '
			';
			$__vars['tooltip'] = $__templater->preEscaped('Unbookmark content');
			$__finalCompiled .= '
		';
		}
		$__finalCompiled .= '
		';
		$__vars['bookmarkUrl'] = $__templater->fn('link', array('bookmarks/edit', $__vars['currentBookmark'], ), false);
		$__finalCompiled .= '
		';
	} else {
		$__finalCompiled .= '
		';
		$__vars['iconClass'] = $__templater->preEscaped($__templater->fn('property', array('th_bookmarkIconClass_bookmarks', ), true));
		$__finalCompiled .= '
		';
		if ($__vars['bookmarkTooltip']) {
			$__finalCompiled .= '
			';
			$__vars['tooltip'] = $__templater->preEscaped($__templater->escape($__vars['bookmarkTooltip']));
			$__finalCompiled .= '
			';
		} else {
			$__finalCompiled .= '
			';
			$__vars['tooltip'] = $__templater->preEscaped('Bookmark content');
			$__finalCompiled .= '
		';
		}
		$__finalCompiled .= '
		';
		$__vars['bookmarkUrl'] = $__templater->fn('link', array('bookmarks/confirm', null, array('content_type' => $__vars['contentType'], 'content_id' => $__vars['contentId'], ), ), false);
		$__finalCompiled .= '
	';
	}
	$__finalCompiled .= '

	';
	if ($__vars['isButton']) {
		$__finalCompiled .= '
		' . $__templater->button('<i class="' . $__templater->escape($__vars['iconClass']) . '"></i>', array(
			'href' => $__vars['bookmarkUrl'],
			'class' => $__vars['aClass'],
			'data-xf-init' => 'tooltip',
			'title' => $__vars['tooltip'],
			'data-xf-click' => 'overlay',
		), '', array(
		)) . '
		';
	} else {
		$__finalCompiled .= '
		<a href="' . $__templater->escape($__vars['bookmarkUrl']) . '" class="' . $__templater->escape($__vars['aClass']) . '" data-xf-init="tooltip" title="' . $__templater->escape($__vars['tooltip']) . '" data-xf-click="overlay"><i class="' . $__templater->escape($__vars['iconClass']) . '"></i></a>
	';
	}
	$__finalCompiled .= '

';
	return $__finalCompiled;
},
'watch_thread' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'thread' => '!',
		'watch' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['thread'], 'canWatch', array())) {
		$__finalCompiled .= '
		' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'watch_thread',
			'value' => '1',
			'label' => 'Watch this thread' . $__vars['xf']['language']['ellipsis'],
			'selected' => $__vars['watch'],
			'_dependent' => array($__templater->formRadio(array(
			'name' => 'email_subscribe',
		), array(array(
			'value' => '1',
			'label' => 'and receive email notifications',
			'selected' => ($__vars['watch']['email_subscribe'] ? true : false),
			'_type' => 'option',
		),
		array(
			'value' => '0',
			'label' => 'without receiving email notifications',
			'selected' => ($__vars['watch']['email_subscribe'] ? false : true),
			'_type' => 'option',
		)))),
			'_type' => 'option',
		)), array(
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'row' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'bookmark' => '!',
		'type' => 'popup',
		'editLink' => true,
		'fauxBlockList' => false,
		'widget' => false,
		'options' => false,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['fauxBlockList']) {
		$__finalCompiled .= '<div class="fauxBlockLink">';
	}
	$__finalCompiled .= '
	<div class="contentRow bookmarkRow ' . ($__vars['bookmark']['public'] ? 'bookmarkRow--public' : '') . ' ' . ($__vars['bookmark']['sticky'] ? 'bookmarkRow--sticky' : '') . '">
		<div class="contentRow-figure">
			' . $__templater->filter($__templater->method($__vars['bookmark'], 'renderIcon', array()), array(array('raw', array()),), true) . '
		</div>
		<div class="contentRow-main contentRow-main--close">
			<div class="bookmarkRow-content">
				<div class="bookmarkRow-meta u-muted">
					';
	if ($__vars['bookmark']['public']) {
		$__finalCompiled .= '
						<i class="' . $__templater->fn('property', array('th_publicIconClass_bookmarks', ), true) . '" aria-hidden="true" title="' . 'Public' . '"></i>
					';
	}
	$__finalCompiled .= '
					';
	if ($__vars['bookmark']['sticky']) {
		$__finalCompiled .= '
						<i class="' . $__templater->fn('property', array('th_stickyIconClass_bookmarks', ), true) . '" aria-hidden="true" title="' . 'Sticky' . '"></i>
					';
	}
	$__finalCompiled .= '
				</div>
				' . $__templater->filter($__templater->method($__vars['bookmark'], 'render', array('list', $__vars['options'], )), array(array('raw', array()),), true) . '
			</div>

			';
	if ($__vars['bookmark']['note'] AND (!$__vars['options']['hide_note'])) {
		$__finalCompiled .= '
				<div class="bookmarkRow-note">
					<div class="bbCodeBlock bbCodeBlock--quote">
						<div class="bbCodeBlock-content">
							' . $__templater->escape($__vars['bookmark']['note']) . '
						</div>
					</div>
				</div>
			';
	}
	$__finalCompiled .= '

			<div class="contentRow-minor contentRow-minor--smaller">
				';
	if (!$__vars['options']['hide_date']) {
		$__finalCompiled .= '
					' . $__templater->fn('date_dynamic', array($__vars['bookmark']['bookmark_date'], array(
		))) . '
				';
	}
	$__finalCompiled .= '
				<div class="bookmarkRow-meta">
					';
	if ($__vars['editLink']) {
		$__finalCompiled .= '
						<a href="' . $__templater->fn('link', array('bookmarks/edit', $__vars['bookmark'], array('redirect' => $__templater->fn('link', array('bookmarks', ), false), ), ), true) . '" data-xf-click="overlay">' . 'Edit' . '</a>
					';
	}
	$__finalCompiled .= '
				</div>
			</div>
		</div>
	</div>
	';
	if ($__vars['fauxBlockList']) {
		$__finalCompiled .= '</div>';
	}
	$__finalCompiled .= '
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