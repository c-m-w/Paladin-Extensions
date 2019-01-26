<?php
// FROM HASH: 8c17adb54100280a911fe9497f6dfb36
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
	if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
		$__compilerTemp1 .= '
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
	' . '
	' . $__compilerTemp1 . '
');
	$__finalCompiled .= '

' . $__templater->filter($__vars['innerContent'], array(array('raw', array()),), true) . '

' . $__templater->callAdsMacro('forum_overview_bottom', array(), $__vars) . '
' . $__templater->widgetPosition('forum_overview_bottom', array());
	return $__finalCompiled;
});