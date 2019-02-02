<?php
// FROM HASH: 402658d9e24e2a2b06ac911b1ad64150
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('BB codes');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add BB code', array(
		'href' => $__templater->fn('link', array('bb-codes/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['permissions']['bold']['aliases'])) {
		foreach ($__vars['permissions']['bold']['aliases'] AS $__vars['alias']) {
			$__compilerTemp1 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['permissions']['indent']['aliases'])) {
		foreach ($__vars['permissions']['indent']['aliases'] AS $__vars['alias']) {
			$__compilerTemp2 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp3 = '';
	if ($__templater->isTraversable($__vars['permissions']['underline']['aliases'])) {
		foreach ($__vars['permissions']['underline']['aliases'] AS $__vars['alias']) {
			$__compilerTemp3 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp4 = '';
	if ($__templater->isTraversable($__vars['permissions']['strike']['aliases'])) {
		foreach ($__vars['permissions']['strike']['aliases'] AS $__vars['alias']) {
			$__compilerTemp4 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp5 = '';
	if ($__templater->isTraversable($__vars['permissions']['color']['aliases'])) {
		foreach ($__vars['permissions']['color']['aliases'] AS $__vars['alias']) {
			$__compilerTemp5 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp6 = '';
	if ($__templater->isTraversable($__vars['permissions']['font']['aliases'])) {
		foreach ($__vars['permissions']['font']['aliases'] AS $__vars['alias']) {
			$__compilerTemp6 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp7 = '';
	if ($__templater->isTraversable($__vars['permissions']['size']['aliases'])) {
		foreach ($__vars['permissions']['size']['aliases'] AS $__vars['alias']) {
			$__compilerTemp7 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp8 = '';
	if ($__templater->isTraversable($__vars['permissions']['url']['aliases'])) {
		foreach ($__vars['permissions']['url']['aliases'] AS $__vars['alias']) {
			$__compilerTemp8 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp9 = '';
	if ($__templater->isTraversable($__vars['permissions']['image']['aliases'])) {
		foreach ($__vars['permissions']['image']['aliases'] AS $__vars['alias']) {
			$__compilerTemp9 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp10 = '';
	if ($__templater->isTraversable($__vars['permissions']['media']['aliases'])) {
		foreach ($__vars['permissions']['media']['aliases'] AS $__vars['alias']) {
			$__compilerTemp10 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp11 = '';
	if ($__templater->isTraversable($__vars['permissions']['quote']['aliases'])) {
		foreach ($__vars['permissions']['quote']['aliases'] AS $__vars['alias']) {
			$__compilerTemp11 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp12 = '';
	if ($__templater->isTraversable($__vars['permissions']['spoiler']['aliases'])) {
		foreach ($__vars['permissions']['spoiler']['aliases'] AS $__vars['alias']) {
			$__compilerTemp12 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp13 = '';
	if ($__templater->isTraversable($__vars['permissions']['code']['aliases'])) {
		foreach ($__vars['permissions']['code']['aliases'] AS $__vars['alias']) {
			$__compilerTemp13 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp14 = '';
	if ($__templater->isTraversable($__vars['permissions']['icode']['aliases'])) {
		foreach ($__vars['permissions']['icode']['aliases'] AS $__vars['alias']) {
			$__compilerTemp14 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp15 = '';
	if ($__templater->isTraversable($__vars['permissions']['attach']['aliases'])) {
		foreach ($__vars['permissions']['attach']['aliases'] AS $__vars['alias']) {
			$__compilerTemp15 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-outer">
		' . $__templater->callMacro('filter_macros', 'quick_filter', array(
		'key' => 'bb-codes',
		'class' => 'block-outer-opposite',
	), $__vars) . '
	</div>
	<div class="block-container">
		<h2 class="block-header">
			' . 'Stock BB codes' . '
		</h2>
		' . $__templater->formHiddenVal('list', 'stock', array(
	)) . '
		<div class="block-body">
			' . $__templater->dataList('
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'bold', ), ), false),
		'id' => 'bold',
		'label' => 'Bold',
		'hint' => '[b]' . $__compilerTemp1,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['bold']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'bold', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[bold]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['bold'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Bold') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'italic', ), ), false),
		'id' => 'italic',
		'label' => 'Italic',
		'hint' => '[i]' . $__compilerTemp2,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['italic']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'italic', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[italic]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['italic'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Italic') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'underline', ), ), false),
		'id' => 'underline',
		'label' => 'Underline',
		'hint' => '[u]' . $__compilerTemp3,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['underline']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'underline', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[underline]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['underline'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Underline') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'strike', ), ), false),
		'id' => 'strike',
		'label' => 'Struck-through',
		'hint' => '[s]' . $__compilerTemp4,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['strike']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'strike', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[strike]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['strike'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Struck-through') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'color', ), ), false),
		'id' => 'color',
		'label' => 'Color',
		'hint' => '[color]' . $__compilerTemp5,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['color']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'color', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[color]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['color'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Color') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'font', ), ), false),
		'id' => 'font',
		'label' => 'Font family',
		'hint' => '[font]' . $__compilerTemp6,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['font']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'font', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[font]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['font'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Font family') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'size', ), ), false),
		'id' => 'size',
		'label' => 'Size',
		'hint' => '[size]' . $__compilerTemp7,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['size']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'size', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[size]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['size'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Size') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'url', ), ), false),
		'id' => 'url',
		'label' => 'URL',
		'hint' => '[url]' . $__compilerTemp8,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['url']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'url', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[url]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['url'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'URL') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'image', ), ), false),
		'id' => 'image',
		'label' => 'Image',
		'hint' => '[img]' . $__compilerTemp9,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['img']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'img', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[img]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['img'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Image') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'media', ), ), false),
		'id' => 'media',
		'label' => 'Media',
		'hint' => '[media]' . $__compilerTemp10,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['media']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'media', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[media]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['media'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Media') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'quote', ), ), false),
		'id' => 'quote',
		'label' => 'Quote',
		'hint' => '[quote]' . $__compilerTemp11,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['quote']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'quote', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[quote]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['quote'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Quote') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'spoiler', ), ), false),
		'id' => 'spoiler',
		'label' => 'Spoiler',
		'hint' => '[spoiler]' . $__compilerTemp12,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['spoiler']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'spoiler', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[spoiler]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['spoiler'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Spoiler') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'code', ), ), false),
		'id' => 'code',
		'label' => 'Code',
		'hint' => '[code]' . $__compilerTemp13,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['code']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'code', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[code]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['code'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Code') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'icode', ), ), false),
		'id' => 'icode',
		'label' => 'Inline code',
		'hint' => '[icode]' . $__compilerTemp14,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['icode']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'icode', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[icode]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['icode'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Inline code') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'align', ), ), false),
		'id' => 'align',
		'label' => 'Text align',
		'hint' => '[left], [right], [center], [justify]',
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['align']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'align', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[align]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['align'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'text_align') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'list', ), ), false),
		'id' => 'list',
		'label' => 'List',
		'hint' => '[list], [indent]',
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['list']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'list', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[list]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['list'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'List') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'attach', ), ), false),
		'id' => 'icode',
		'label' => 'Attachment',
		'hint' => '[attach]' . $__compilerTemp15,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['attach']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'attach', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[attach]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['attach'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Attachment') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
			', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/bb-codes/toggle', ), false),
		'ajax' => true,
		'class' => 'block',
	)) . '

';
	$__compilerTemp16 = '';
	if ($__templater->isTraversable($__vars['permissions']['bgcolor']['aliases'])) {
		foreach ($__vars['permissions']['bgcolor']['aliases'] AS $__vars['alias']) {
			$__compilerTemp16 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp17 = '';
	if ($__templater->isTraversable($__vars['permissions']['ispoiler']['aliases'])) {
		foreach ($__vars['permissions']['ispoiler']['aliases'] AS $__vars['alias']) {
			$__compilerTemp17 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp18 = '';
	if ($__templater->isTraversable($__vars['permissions']['parsehtml']['aliases'])) {
		foreach ($__vars['permissions']['parsehtml']['aliases'] AS $__vars['alias']) {
			$__compilerTemp18 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp19 = '';
	if ($__templater->isTraversable($__vars['permissions']['sub']['aliases'])) {
		foreach ($__vars['permissions']['sub']['aliases'] AS $__vars['alias']) {
			$__compilerTemp19 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp20 = '';
	if ($__templater->isTraversable($__vars['permissions']['sup']['aliases'])) {
		foreach ($__vars['permissions']['sup']['aliases'] AS $__vars['alias']) {
			$__compilerTemp20 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp21 = '';
	if ($__templater->isTraversable($__vars['permissions']['sup']['aliases'])) {
		foreach ($__vars['permissions']['sup']['aliases'] AS $__vars['alias']) {
			$__compilerTemp21 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__compilerTemp22 = '';
	if ($__templater->isTraversable($__vars['permissions']['audio']['aliases'])) {
		foreach ($__vars['permissions']['audio']['aliases'] AS $__vars['alias']) {
			$__compilerTemp22 .= ', [' . $__templater->escape($__vars['alias']) . ']';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-outer">
		' . $__templater->callMacro('filter_macros', 'quick_filter', array(
		'key' => 'bb-codes',
		'class' => 'block-outer-opposite',
	), $__vars) . '
	</div>
	<div class="block-container">
		<h2 class="block-header">
			' . 'Editor Manager BB codes' . '
		</h2>
		' . $__templater->formHiddenVal('list', 'klem', array(
	)) . '
		<div class="block-body">
			' . $__templater->dataList('
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'bgcolor', ), ), false),
		'id' => 'bgcolor',
		'label' => 'Background color',
		'hint' => '[bgcolor]' . $__compilerTemp16,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['bgcolor']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'bgcolor', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[bgcolor]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['bgcolor'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Background color') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'ispoiler', ), ), false),
		'id' => 'ispoiler',
		'label' => 'Inline spoiler',
		'hint' => '[ispoiler]' . $__compilerTemp17,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['ispoiler']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'ispoiler', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[ispoiler]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['ispoiler'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Inline spoiler') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'table', ), ), false),
		'id' => 'table',
		'label' => 'Table',
		'hint' => '[table], [tr], [th], [td]',
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['table']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'table', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[table]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['table'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Table') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'hide', ), ), false),
		'id' => 'hide',
		'label' => 'Hide',
		'hint' => '[hide], [hidereply], [hidethanks], [hidereplythanks], [hideposts]',
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['hide']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'hide', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[hide]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['hide'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Hide') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'parsehtml', ), ), false),
		'id' => 'parsehtml',
		'label' => 'ParseHtml',
		'hint' => '[parsehtml]' . $__compilerTemp18,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['parsehtml']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'parsehtml', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[parsehtml]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['parsehtml'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'ParseHtml') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'sub', ), ), false),
		'id' => 'sub',
		'label' => 'Subscript',
		'hint' => '[sub]' . $__compilerTemp19,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['sub']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'sub', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[sub]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['sub'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Subscript') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'sup', ), ), false),
		'id' => 'sup',
		'label' => 'Superscript',
		'hint' => '[sup]' . $__compilerTemp20,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['sup']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'sup', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[sup]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['sup'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Superscript') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'video', ), ), false),
		'id' => 'sup',
		'label' => 'Video',
		'hint' => '[video]' . $__compilerTemp21,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['video']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'video', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[video]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['video'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Video') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'audio', ), ), false),
		'id' => 'sup',
		'label' => 'Audio',
		'hint' => '[audio]' . $__compilerTemp22,
		'_type' => 'main',
		'html' => '',
	),
	array(
		'class' => ((!$__templater->fn('empty', array($__vars['permissions']['audio']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
		'href' => $__templater->fn('link', array('em/bb-codes', array('bb_code_id' => 'audio', ), ), false),
		'_type' => 'action',
		'html' => '
						' . 'User criteria' . '
					',
	),
	array(
		'name' => 'kl_active[audio]',
		'selected' => $__vars['xf']['options']['klEMEnabledBBCodes']['audio'],
		'class' => 'dataList-cell--separated',
		'submit' => 'true',
		'tooltip' => 'Enable / disable \'' . (('[' . 'Audio') . ']') . '\'',
		'_type' => 'toggle',
		'html' => '',
	))) . '
			', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/bb-codes/toggle', ), false),
		'ajax' => true,
		'class' => 'block',
	)) . '
';
	if (!$__templater->test($__vars['customBbCodes'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp23 = '';
		if ($__templater->isTraversable($__vars['customBbCodes'])) {
			foreach ($__vars['customBbCodes'] AS $__vars['bbCode']) {
				$__compilerTemp23 .= '
						';
				$__compilerTemp24 = '';
				if ($__templater->isTraversable($__vars['permissions'][$__vars['bbCode']['bb_code_id']]['aliases'])) {
					foreach ($__vars['permissions'][$__vars['bbCode']['bb_code_id']]['aliases'] AS $__vars['alias']) {
						$__compilerTemp24 .= ', [' . $__templater->escape($__vars['alias']) . ']';
					}
				}
				$__compilerTemp23 .= $__templater->dataRow(array(
				), array(array(
					'href' => $__templater->fn('link', array('em/bb-codes', $__vars['bbCode'], ), false),
					'label' => $__templater->escape($__vars['bbCode']['title']),
					'hint' => '[' . $__templater->escape($__vars['bbCode']['bb_code_id']) . ']' . $__compilerTemp24,
					'explain' => $__templater->escape($__vars['bbCode']['description']),
					'_type' => 'main',
					'html' => '',
				),
				array(
					'class' => ((!$__templater->fn('empty', array($__vars['permissions'][$__vars['bbCode']['bb_code_id']]))) ? 'dataList-cell--highlighted' : ''),
					'href' => $__templater->fn('link', array('em/bb-codes', $__vars['bbCode'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'User criteria' . '
							',
				),
				array(
					'name' => 'active[' . $__vars['bbCode']['bb_code_id'] . ']',
					'selected' => $__vars['bbCode']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . (('[' . $__vars['bbCode']['bb_code_id']) . ']') . '\'',
					'_type' => 'toggle',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'bb-codes',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<h2 class="block-header">
				' . 'Custom BB codes' . '
			</h2>
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp23 . '
				', array(
		)) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('bb-codes/toggle', ), false),
			'ajax' => true,
			'class' => 'block',
		)) . '
	';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});