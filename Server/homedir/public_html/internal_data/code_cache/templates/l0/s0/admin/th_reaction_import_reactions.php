<?php
// FROM HASH: 2f9a992cdc14abac41ebcbcece8213af
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Import reactions');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formUploadRow(array(
		'name' => 'upload',
		'accept' => '.xml',
	), array(
		'label' => 'Import from uploaded XML file',
		'hint' => 'Choose a local XML file to import a list of reactions into your forum. Make sure any images or styling properties are uploaded as well.',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Proceed' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('reactions/import', ), false),
		'upload' => 'true',
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});