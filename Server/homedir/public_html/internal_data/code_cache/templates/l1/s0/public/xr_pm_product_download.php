<?php
// FROM HASH: 15d958b7a9b674ae6056f8d6b33fcda9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']) . ' - ' . 'Download');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['purchases'])) {
		foreach ($__vars['purchases'] AS $__vars['purchase']) {
			$__vars['firstVersion'] = $__templater->filter($__vars['purchase']['downloadable_versions'], array(array('first', array()),), false);
			$__compilerTemp2 = '';
			if ($__vars['purchase']['license_name']) {
				$__compilerTemp2 .= '
								&middot; ' . $__templater->escape($__vars['purchase']['license_name']) . '
							';
			}
			$__compilerTemp1[] = array(
				'value' => $__vars['purchase']['purchase_id'] . '|' . $__vars['firstVersion']['product_version_id'],
				'label' => '
							' . $__templater->escape($__vars['firstVersion']['version_string']) . ' &middot; ' . $__templater->escape($__vars['purchase']['purchase_key']) . '
							' . $__compilerTemp2 . '
						',
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp3 = '';
	if ($__vars['product']['confirm_license']) {
		$__compilerTemp3 .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'confirmed',
			'label' => 'I agree to and accept the <a href="' . $__templater->fn('link', array('products/terms', $__vars['product'], ), true) . '" target="_blank">terms and conditions</a> for this product.',
			'_type' => 'option',
		)), array(
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'purchase_version',
	), $__compilerTemp1, array(
		'label' => 'Select purchase to download product',
		'explain' => 'You can download more versions from the <a href="' . $__templater->fn('link', array('products/purchases', ), true) . '" target="_blank">Your purchases</a> page.',
	)) . '
			' . $__compilerTemp3 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'download',
		'submit' => 'Download',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('products/download', $__vars['product'], ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});