<?php
// FROM HASH: c028b24c65185ad2da417876be39b7b5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />

' . $__templater->formNumberBoxRow(array(
		'name' => 'options[limit]',
		'value' => $__vars['options']['limit'],
		'min' => '1',
	), array(
		'label' => 'Bookmarks limit',
	)) . '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['contentTypes'])) {
		foreach ($__vars['contentTypes'] AS $__vars['contentType'] => $__vars['contentTypePhrase']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['contentType'],
				'label' => $__templater->escape($__vars['contentTypePhrase']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[limit_content_types]',
		'selected' => $__vars['options']['limit_content_types'],
		'label' => 'Limit ot specific content types',
		'_dependent' => array($__templater->formCheckBox(array(
		'name' => 'options[content_types]',
		'value' => $__vars['options']['content_types'],
		'listclass' => 'listColumns',
	), $__compilerTemp1)),
		'_type' => 'option',
	)), array(
		'label' => 'Content types',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[sticky_only]',
		'selected' => $__vars['options']['sticky_only'],
		'label' => 'Only show sticky bookmarks',
		'_type' => 'option',
	),
	array(
		'name' => 'options[hide_container]',
		'selected' => $__vars['options']['hide_container'],
		'label' => 'Hide container',
		'_type' => 'option',
	),
	array(
		'name' => 'options[hide_note]',
		'selected' => $__vars['options']['hide_note'],
		'label' => 'Hide note',
		'_type' => 'option',
	),
	array(
		'name' => 'options[hide_date]',
		'selected' => $__vars['options']['hide_date'],
		'label' => 'Hide bookmark date',
		'_type' => 'option',
	)), array(
	));
	return $__finalCompiled;
});