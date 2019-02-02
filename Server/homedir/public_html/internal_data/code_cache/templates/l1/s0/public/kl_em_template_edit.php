<?php
// FROM HASH: 2b6b2e02566f30d7b4c78c0a7f9445a2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['template'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add template');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit template' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['template']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['template'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('account/editor-templates/delete', $__vars['template'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">

		<div class="block-body">
			
			' . $__templater->formTextBoxRow(array(
		'maxlength' => $__templater->fn('max_length', array($__vars['template'], 'title', ), false),
		'name' => 'title',
		'required' => 'required',
		'value' => ($__templater->method($__vars['template'], 'exists', array()) ? $__vars['template']['title'] : ''),
	), array(
		'label' => 'Title',
	)) . '
					
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => ($__vars['template']['template_id'] ? $__vars['template']['active'] : 1),
		'label' => '
					' . 'Active' . '
				',
		'_type' => 'option',
	)), array(
	)) . '
			
			' . $__templater->formEditorRow(array(
		'name' => 'content',
		'value' => $__vars['template']['content'],
		'data-min-height' => '100',
		'maxlength' => $__vars['xf']['options']['messageMaxLength'],
	), array(
		'rowtype' => 'fullWidth noLabel',
		'label' => 'Message',
	)) . '
			
			' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('account/editor-templates/save', $__vars['template'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});