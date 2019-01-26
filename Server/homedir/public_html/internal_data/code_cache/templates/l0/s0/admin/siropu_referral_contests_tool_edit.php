<?php
// FROM HASH: d09e5a70c3aa9b1885116b364e34d831
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['tool'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['tool'], 'isBanner', array())) {
			$__finalCompiled .= '
		';
			$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add banner');
			$__finalCompiled .= '
	';
		} else {
			$__finalCompiled .= '
		';
			$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add text link');
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit tool' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['tool']['name']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['tool'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('referral-contests/tools/delete', $__vars['tool'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['tool'], 'isBanner', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formSelectRow(array(
			'name' => 'size',
			'value' => $__vars['tool']['size'],
		), array(array(
			'value' => '468x60',
			'label' => '468 x 60',
			'_type' => 'option',
		),
		array(
			'value' => '728x90',
			'label' => '728 x 90',
			'_type' => 'option',
		),
		array(
			'value' => '250x250',
			'label' => '250 x 250',
			'_type' => 'option',
		),
		array(
			'value' => '200x200',
			'label' => '200 x 200',
			'_type' => 'option',
		),
		array(
			'value' => '300x250',
			'label' => '300 x 250',
			'_type' => 'option',
		),
		array(
			'value' => '300x600',
			'label' => '300 x 600',
			'_type' => 'option',
		),
		array(
			'value' => '320x100',
			'label' => '320 x 100',
			'_type' => 'option',
		),
		array(
			'value' => '320x50',
			'label' => '320 x 50',
			'_type' => 'option',
		),
		array(
			'value' => '336x280',
			'label' => '336 x 280',
			'_type' => 'option',
		),
		array(
			'value' => '234x60',
			'label' => '234 x 60',
			'_type' => 'option',
		),
		array(
			'value' => '120x600',
			'label' => '120 x 600',
			'_type' => 'option',
		),
		array(
			'value' => '120x240',
			'label' => '120 x 240',
			'_type' => 'option',
		),
		array(
			'value' => '160x600',
			'label' => '160 x 600',
			'_type' => 'option',
		),
		array(
			'value' => '970x250',
			'label' => '970 x 250',
			'_type' => 'option',
		),
		array(
			'value' => '125x125',
			'label' => '125 x 125',
			'_type' => 'option',
		)), array(
			'label' => 'Banner size',
		)) . '
				
				' . $__templater->formUploadRow(array(
			'name' => 'upload',
			'accept' => '.gif,.jpeg,.jpg,.jpe,.png',
		), array(
			'label' => 'Upload banner',
		)) . '
				
				';
		if ($__vars['tool']['content']) {
			$__compilerTemp1 .= '
					' . $__templater->formRow('
						<img src="' . $__templater->escape($__vars['tool']['absolute_file_path']) . '">
					', array(
				'label' => 'Current banner',
			)) . '
				';
		}
		$__compilerTemp1 .= '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'content',
			'value' => $__vars['tool']['content'],
		), array(
			'label' => 'Link text',
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['tool'], 'isInsert', array())) {
		$__compilerTemp2 .= '
		' . $__templater->formHiddenVal('type', $__vars['tool']['type'], array(
		)) . '
	';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'name',
		'value' => $__vars['tool']['name'],
	), array(
		'label' => 'Tool name',
	)) . '

			' . $__compilerTemp1 . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'target_url',
		'value' => $__vars['tool']['target_url'],
	), array(
		'label' => 'Target URL',
		'explain' => 'If not provided, the target URL will be the main board URL.',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'enabled',
		'value' => '1',
		'selected' => $__vars['tool']['enabled'],
		'label' => 'Enable tool',
		'_type' => 'option',
	)), array(
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
	' . $__compilerTemp2 . '
', array(
		'action' => $__templater->fn('link', array('referral-contests/tools/save', $__vars['tool'], ), false),
		'upload' => 'true',
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});