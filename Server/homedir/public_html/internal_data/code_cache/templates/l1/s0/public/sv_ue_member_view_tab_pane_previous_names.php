<?php
// FROM HASH: 2bade8e45991b278b387027eafd8082f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canViewUsernameChanges', array($__vars['user'], )) AND $__vars['user']['has_username_changes']) {
		$__finalCompiled .= '
	<li data-href="' . $__templater->fn('link', array('members/username-changes', $__vars['user'], ), true) . '"
		aria-labelledby="previous-names"
		role="tabpanel">

		<div class="blockMessage">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
	</li>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});