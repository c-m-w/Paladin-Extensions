<?php
// FROM HASH: 03d5f331324f6cadd21aa06a92cc0a5d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Download' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['purchase'], 'getBreadcrumbs', array(true, )));
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['versions']);
	$__compilerTemp2 = '';
	if ($__vars['firstVersionId'] != $__vars['product']['current_version_id']) {
		$__compilerTemp2 .= '
						' . 'There are newer (but unsupported) versions available for download in the list above.' . '
					';
	}
	$__compilerTemp3 = '';
	if ($__vars['product']['confirm_license']) {
		$__compilerTemp3 .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'confirmed',
			'label' => 'I agree to and accept the <a href="' . $__templater->fn('link', array('products/terms', $__vars['product'], ), true) . '" target="_blank">terms and conditions</a> for this extension.',
			'_type' => 'option',
		)), array(
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'product_version_id',
		'value' => $__vars['product']['current_version_id'],
	), $__compilerTemp1, array(
		'label' => 'Pick a version to download',
		'explain' => '
					' . $__compilerTemp2 . '
				',
	)) . '
			' . $__compilerTemp3 . '
			' . $__templater->formSubmitRow(array(
		'icon' => 'download',
		'submit' => 'Download',
	), array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('products/purchase/download', $__vars['purchase'], ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});