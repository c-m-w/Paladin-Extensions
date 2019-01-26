<?php
// FROM HASH: ec0f4bf935100d409ddb82b8321a92d8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['previousUsernameChanges'], 'empty', array()) AND $__vars['user']['username_change_title']) {
		$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'user[custom_title_revert]',
			'label' => 'Revert user name change title',
			'_type' => 'option',
		)), array(
		)) . '
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});