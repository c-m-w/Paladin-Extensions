<?php
// FROM HASH: 55ec37178cbc75130a7913db01cf49c8
return array('macros' => array('forum' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'activeTab' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<!-- first tab --> 
	<!-- new tab --> 
	';
	if ($__vars['xf']['options']['forumsDefaultPage'] == 'new_posts') {
		$__finalCompiled .= '
		<a href="' . $__templater->fn('link', array('forums', ), true) . '" class="tabs-tab ' . (($__vars['activeTab'] == 'new_posts') ? 'is-active' : '') . '">' . 'New posts' . '</a>
	';
	}
	$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('forums/-/list', ), true) . '" class="tabs-tab ' . (($__vars['activeTab'] == 'forum_list') ? 'is-active' : '') . '">' . 'Forum list' . '</a>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});