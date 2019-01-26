<?php
// FROM HASH: b1100806b24550423370056d96f402d2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Activate' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['purchase'], 'getBreadcrumbs', array(true, )));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'license_name',
		'value' => $__vars['purchase']['license_name'],
		'required' => 'required',
	), array(
		'label' => 'License name',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'type' => 'url',
		'name' => 'license_url',
		'value' => $__vars['purchase']['license_url'],
		'required' => 'required',
	), array(
		'label' => 'License URL',
		'explain' => '
					' . 'You must provide a valid name and URL for this purchase and ensure it is kept up to date before downloading.' . '
				',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'vote',
		'submit' => 'Activate',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('products/purchase/activate', $__vars['purchase'], ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});