<?php
// FROM HASH: 725ee38742d1690ed07324f802354b7f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Import special characters');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['libraries'])) {
		foreach ($__vars['libraries'] AS $__vars['library']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['library']['file'],
				'label' => $__templater->escape($__vars['library']['name']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRadioRow(array(
		'name' => 'mode',
		'value' => 'upload',
	), array(array(
		'value' => 'upload',
		'label' => 'Import from uploaded XML file',
		'hint' => 'Use this option to import an XML file containing special character definitions.',
		'_dependent' => array($__templater->formUpload(array(
		'name' => 'upload',
		'accept' => '.xml',
	))),
		'_type' => 'option',
	),
	array(
		'value' => 'library',
		'label' => 'Import from library',
		'hint' => 'Use this option to import from one of the pre-defined libraries.',
		'_dependent' => array($__templater->formSelect(array(
		'name' => 'library',
	), $__compilerTemp1)),
		'_type' => 'option',
	)), array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Proceed' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/special-chars/import-form', ), false),
		'upload' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});