<?php
// FROM HASH: 3447914d55266f44ecfd3a120be85722
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Export special characters');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['categories'])) {
		foreach ($__vars['categories'] AS $__vars['category']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['category']['group_id'],
				'label' => $__templater->escape($__vars['category']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'category',
	), $__compilerTemp1, array(
		'label' => 'Category',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Proceed' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/special-chars/export', ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});