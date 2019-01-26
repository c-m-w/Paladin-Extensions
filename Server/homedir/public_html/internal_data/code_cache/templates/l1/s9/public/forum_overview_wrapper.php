<?php
// FROM HASH: a4248814ebeddcc09ecd3aaa282e3288
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callAdsMacro('forum_overview_top', array(), $__vars) . '
' . $__templater->widgetPosition('forum_overview_top', array()) . '

';
	if ($__templater->fn('property', array('uix_removeIndexPageTitle', ), false)) {
		$__finalCompiled .= '
	';
		$__templater->setPageParam('uix_hidePageTitle', '1');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->fn('property', array('uix_removeWhatsNewButtons', ), false)) {
		$__compilerTemp1 .= '
		';
		if ($__vars['pageSelected'] == 'new_posts') {
			$__compilerTemp1 .= '
			' . $__templater->button('
				' . 'Forum list' . '
			', array(
				'href' => $__templater->fn('link', array('forums/list', ), false),
				'icon' => 'list',
			), '', array(
			)) . '
		';
		} else {
			$__compilerTemp1 .= '
			' . $__templater->button('
				' . 'New posts' . '
			', array(
				'href' => (($__vars['xf']['options']['forumsDefaultPage'] == 'new_posts') ? $__templater->fn('link', array('forums/new-posts', ), false) : $__templater->fn('link', array('whats-new/posts', ), false)),
				'icon' => 'bolt',
			), '', array(
			)) . '
		';
		}
		$__compilerTemp1 .= '
	';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
		$__compilerTemp2 .= '
		' . $__templater->button('
			' . 'Post' . $__vars['xf']['language']['ellipsis'] . '
		', array(
			'href' => $__templater->fn('link', array('forums/create-thread', ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => 'true',
		), '', array(
		)) . '
	';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__compilerTemp1 . '
	' . $__compilerTemp2 . '
');
	$__finalCompiled .= '

' . $__templater->filter($__vars['innerContent'], array(array('raw', array()),), true) . '

' . $__templater->callAdsMacro('forum_overview_bottom', array(), $__vars) . '
' . $__templater->widgetPosition('forum_overview_bottom', array());
	return $__finalCompiled;
});