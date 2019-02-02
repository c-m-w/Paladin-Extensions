<?php
// FROM HASH: ab8fd3d03247122adfa424abf4588ae4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Import special characters');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['characters'])) {
		foreach ($__vars['characters'] AS $__vars['key'] => $__vars['character']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['key'],
				'selected' => true,
				'label' => '<span style=\'font-size:20px;\'>' . $__templater->filter($__vars['character']->{'code'}, array(array('raw', array()),), true) . '</span> - ' . $__templater->escape($__vars['character']->{'title'}),
				'_dependent' => array($__templater->formTextBox(array(
				'name' => 'names[' . $__vars['key'] . ']',
				'value' => $__vars['character']->{'title'},
			)), $__templater->formTextBox(array(
				'name' => 'codes[' . $__vars['key'] . ']',
				'value' => $__vars['character']->{'code'},
			))),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'categoryTitle',
		'value' => $__vars['categoryName'],
	), array(
		'label' => 'Title',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formCheckBoxRow(array(
		'name' => 'enabled[]',
	), $__compilerTemp1, array(
		'label' => 'Characters',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Proceed' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/special-chars/import-save', ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});