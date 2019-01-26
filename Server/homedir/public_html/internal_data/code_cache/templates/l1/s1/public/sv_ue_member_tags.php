<?php
// FROM HASH: 19a4c3cbd1a2d74591f6553b9a3aa62c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit tags');
	$__finalCompiled .= '

' . $__templater->callMacro('tag_macros', 'edit_form', array(
		'action' => $__templater->fn('link', array('members/tags', $__vars['user'], ), false),
		'uneditableTags' => $__vars['uneditableTags'],
		'editableTags' => $__vars['editableTags'],
	), $__vars) . '
';
	return $__finalCompiled;
});