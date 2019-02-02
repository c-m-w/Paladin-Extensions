<?php
// FROM HASH: 644df705094d8928464e011476ce6988
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['character'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add character');
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit character' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['character']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['groups'])) {
		foreach ($__vars['groups'] AS $__vars['group']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['group']['group_id'],
				'label' => $__templater->escape($__vars['group']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => ($__vars['character']['character_id'] ? $__vars['character']['MasterTitle']['phrase_text'] : ''),
	), array(
		'label' => 'Title',
	)) . '
			
			' . $__templater->formTextBoxRow(array(
		'name' => 'code',
		'value' => $__vars['character']['code'],
	), array(
		'label' => 'Code',
	)) . '
			
			' . $__templater->formSelectRow(array(
		'name' => 'group_id',
		'value' => $__vars['character']['group_id'],
	), $__compilerTemp1, array(
		'label' => 'Category',
	)) . '
			
			<hr class="formRowSep" />

			' . $__templater->callMacro('display_order_macros', 'row', array(
		'name' => 'display_order',
		'value' => $__vars['character']['display_order'],
		'explain' => 'The position of this item.',
	), $__vars) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => ($__vars['character']['character_id'] ? $__vars['character']['active'] : 1),
		'label' => '
					' . 'Enabled' . '
				',
		'_type' => 'option',
	)), array(
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/special-chars/characters/save', $__vars['character'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});