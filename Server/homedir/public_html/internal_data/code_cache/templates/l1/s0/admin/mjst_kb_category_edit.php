<?php
// FROM HASH: 2b175538d035f597fd96d9e7c7ce546e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['kbCategory'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add knowledge base category');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit knowledge base category' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['kbCategory']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['kbCategory'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('mjst-support/kb/category/delete', $__vars['kbCategory'], ), false),
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
		'name' => 'title',
		'value' => ($__vars['kbCategory']['kb_category_id'] ? $__vars['kbCategory']['title'] : ''),
	), array(
		'label' => 'Title',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'description',
		'value' => $__vars['kbCategory']['description'],
	), array(
		'label' => 'Description',
	)) . '

			' . $__templater->callMacro('display_order_macros', 'row', array(
		'value' => $__vars['kbCategory']['display_order'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('mjst-support/kb/category/save', $__vars['kbCategory'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});