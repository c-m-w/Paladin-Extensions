<?php
// FROM HASH: b406e1e1150ead5e344fe8061245ca70
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Install ' . $__templater->escape($__vars['product']['product_name']) . '');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('ThemeHouse Styles'), $__templater->fn('link', array('styles/themehouse', ), false), array(
	));
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['versions'])) {
		foreach ($__vars['versions'] AS $__vars['version']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['version']['id'],
				'label' => $__templater->escape($__vars['version']['version']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2 = '';
	if (!$__vars['freshInstall']) {
		$__compilerTemp2 .= '
			' . $__templater->formHiddenVal('style_id', $__vars['style']['style_id'], array(
		)) . '
		';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'By continuing we will attempt to automatically install the selected version of ' . $__templater->escape($__vars['product']['product_name']) . '. To ensure we provide the best installation possible your XenForo version, XenForo installation URL and ThemeHouse API key will be passed to our servers when the installation happens.' . '
			', array(
		'rowtype' => 'confirm',
	)) . '
		</div>

		' . $__templater->formSelectRow(array(
		'name' => 'version_id',
	), $__compilerTemp1, array(
		'label' => 'Version',
	)) . '

		' . $__compilerTemp2 . '

		' . $__templater->formHiddenVal('step', 'ftp_details', array(
	)) . '

		' . $__templater->formSubmitRow(array(
		'icon' => 'submit',
	), array(
	)) . '
	</div>
', array(
		'action' => $__vars['submitUrl'],
		'class' => 'block',
	));
	return $__finalCompiled;
});