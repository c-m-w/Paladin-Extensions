<?php
// FROM HASH: 3fc8c38ab9d3937d70c02ebe7fe7e678
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['watch']) {
		$__finalCompiled .= '
	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'label' => 'Unwatch thread',
			'name' => 'unwatch_thread',
			'value' => '1',
			'selected' => 1,
			'_type' => 'option',
		)), array(
		)) . '
';
	}
	return $__finalCompiled;
});