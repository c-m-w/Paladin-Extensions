<?php
// FROM HASH: 715414d239dd2190a6f775705731aff0
return array('macros' => array('resource' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'resource' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['xf']['options']['xfrmAllowIcons']) {
		$__finalCompiled .= '
		' . $__templater->fn('resource_icon', array($__vars['resource'], 's', $__templater->fn('link', array('resources', $__vars['resource'], ), false), ), true) . '
		';
	} else {
		$__finalCompiled .= '
		' . $__templater->fn('avatar', array($__vars['resource']['User'], 's', false, array(
			'defaultname' => $__vars['resource']['username'],
		))) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'xfmg_media' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'media' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('media', $__vars['media'], ), true) . '" class="avatar avatar--s">
		<img src="' . $__templater->escape($__templater->method($__vars['media'], 'getThumbnailUrl', array())) . '" alt="' . $__templater->escape($__vars['media']['title']) . '">
	</a>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});