<?php
// FROM HASH: 3bc0e49d77e8d2efd733244f2d38b3a9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['department'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add department');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit department' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['department']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['department'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/departments/delete', $__vars['department'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['availableFields'], 'empty', array())) {
		$__compilerTemp1 .= '
				<hr class="formRowSep" />

				';
		$__compilerTemp2 = $__templater->mergeChoiceOptions(array(), $__vars['availableFields']);
		$__compilerTemp1 .= $__templater->formCheckBoxRow(array(
			'name' => 'available_fields',
			'value' => $__vars['department']['field_cache'],
			'listclass' => 'field listColumns',
		), $__compilerTemp2, array(
			'label' => 'Available fields',
			'hint' => '
						' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '.field.listColumns',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '
					',
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				<hr class="formRowSep" />

				' . $__templater->formRow('
					' . $__templater->filter('None', array(array('parens', array()),), true) . ' <a href="' . $__templater->fn('link', array('mjst-support/fields', ), true) . '" target="_blank">' . 'Add field' . '</a>
				', array(
			'label' => 'Available fields',
		)) . '
			';
	}
	$__compilerTemp3 = '';
	if (!$__templater->test($__vars['availablePrefixes'], 'empty', array())) {
		$__compilerTemp3 .= '
				<hr class="formRowSep" />

				';
		$__compilerTemp4 = $__templater->mergeChoiceOptions(array(), $__vars['availablePrefixes']);
		$__compilerTemp3 .= $__templater->formCheckBoxRow(array(
			'name' => 'available_prefixes',
			'value' => $__vars['department']['prefix_cache'],
			'listclass' => 'prefix listColumns',
		), $__compilerTemp4, array(
			'label' => 'Available prefixes',
			'hint' => '
						' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '.prefix.listColumns',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '
					',
		)) . '

				' . $__templater->formCheckBoxRow(array(
			'name' => 'require_prefix',
			'value' => $__vars['department']['require_prefix'],
		), array(array(
			'value' => '1',
			'label' => 'Require users to select a prefix',
			'hint' => 'If selected, users will be required to select a prefix when creating or editing a ticket. This will not be enforced for moderators.',
			'_type' => 'option',
		)), array(
		)) . '

			';
	} else {
		$__compilerTemp3 .= '

				<hr class="formRowSep" />

				' . $__templater->formRow('
					' . $__templater->filter('None', array(array('parens', array()),), true) . ' <a href="' . $__templater->fn('link', array('mjst-support/prefixes', ), true) . '" target="_blank">' . 'Add prefix' . '</a>
				', array(
			'label' => 'Available prefixes',
		)) . '

			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['department']['title'],
	), array(
		'label' => 'Title',
	)) . '
			' . $__templater->formTextAreaRow(array(
		'name' => 'short_description',
		'value' => $__vars['department']['short_description'],
		'autosize' => 'true',
	), array(
		'label' => 'Description',
		'hint' => 'You may use HTML',
	)) . '

			' . $__templater->callMacro('display_order_macros', 'row', array(
		'value' => $__vars['department']['display_order'],
	), $__vars) . '

			' . $__compilerTemp1 . '

			' . $__compilerTemp3 . '

		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/departments/save', $__vars['department'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});