<?php
// FROM HASH: 2423cd0b64d80bdddbfdca1df3d7a779
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['reactionType'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add reaction type');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit reaction type' . ': ' . $__templater->escape($__vars['reactionType']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['reactionType'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('reaction-types/delete', $__vars['reactionType'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('public:color_picker.less');
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'xf/color_picker.js',
		'min' => '1',
	));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-body">
		' . $__templater->formTextBoxRow(array(
		'name' => 'reaction_type_id',
		'value' => $__vars['reactionType']['reaction_type_id'],
		'class' => ($__vars['reactionType']['reaction_type_id'] ? 'is-disabled' : ''),
		'readonly' => ($__vars['reactionType']['reaction_type_id'] ? 'readonly' : ''),
	), array(
		'label' => 'Reaction type ID',
		'explain' => ((!$__vars['reactionType']['reaction_type_id']) ? 'This is the reaction type that will uniquely identify it.<br>
<b>This cannot be changed once defined.</b>' : ''),
	)) . '

		<hr class="formRowSep" />

		' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['reactionType']['title'],
	), array(
		'label' => 'Title',
	)) . '

		' . $__templater->formTextBoxRow(array(
		'name' => 'display_order',
		'value' => $__vars['reactionType']['display_order'],
		'min' => '0',
		'step' => '10',
		'type' => 'number',
	), array(
		'label' => 'Display order',
	)) . '

		<hr class="formRowSep" />

		' . $__templater->formRow('
			<div class="inputGroup inputGroup--joined inputGroup--color"
				data-xf-init="color-picker"
				data-map-name="' . $__templater->escape($__vars['reactionType']['color']) . '"
			>
				' . $__templater->formTextBox(array(
		'name' => 'color',
		'value' => $__vars['reactionType']['color'],
	)) . '
				<div class="inputGroup-text"><span class="colorPickerBox js-colorPickerTrigger"></span></div>
			</div>
		', array(
		'label' => 'Color',
		'rowclass' => 'formRow--input',
	)) . '

		<hr class="formRowSep" />

		' . '
	</div>

	' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('reaction-types/save', $__vars['reactionType'], ), false),
		'ajax' => 'true',
		'class' => 'block-container',
	));
	return $__finalCompiled;
});