<?php
// FROM HASH: 159172e7a6ba47fb1471ad5108680c45
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['visitor']['username_change_title']) {
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