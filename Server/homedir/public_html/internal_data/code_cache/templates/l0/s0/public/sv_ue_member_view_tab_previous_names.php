<?php
// FROM HASH: 78aae89a999e254c06a2fc8b01a0ceab
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewUsernameChanges', array($__vars['user'], )) AND $__vars['user']['has_username_changes']) {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('members/username-changes', $__vars['user'], ), true) . '"
		class="tabs-tab"
		id="previous-names"
		role="tab">' . 'Previous names' . '</a>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});