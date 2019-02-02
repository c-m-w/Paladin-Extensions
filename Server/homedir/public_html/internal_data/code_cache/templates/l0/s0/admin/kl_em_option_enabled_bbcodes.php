<?php
// FROM HASH: e21901e1b785d2160e65bdd16374621a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['debug']) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_options.less');
		$__finalCompiled .= '

	';
		$__vars['formatParams'] = $__vars['option']['formatParams'];
		$__finalCompiled .= '

	';
		$__vars['inputName'] = $__templater->preEscaped($__templater->callMacro('option_macros', 'input_name', array(
			'id' => $__vars['option']['option_id'],
		), $__vars));
		$__finalCompiled .= '
	';
		$__vars['listedHtml'] = $__templater->preEscaped('
		' . $__templater->callMacro('option_macros', 'listed_html', array(
			'id' => $__vars['option']['option_id'],
		), $__vars) . '
	');
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->method($__vars['option'], 'canEdit', array())) {
			$__compilerTemp1 .= '
			' . $__templater->callMacro('option_macros', 'option_edit_link', array(
				'group' => $__vars['group'],
				'option' => $__vars['option'],
			), $__vars) . '
		';
		}
		$__compilerTemp2 = '';
		if ($__vars['includeAddOnHint'] AND ($__vars['group'] AND ($__vars['option']['addon_id'] AND (($__vars['option']['addon_id'] != $__vars['group']['addon_id']) AND ($__vars['option']['addon_id'] != 'XF'))))) {
			$__compilerTemp2 .= '
			<span class="formRow-hint-featured">
				<a href="' . $__templater->fn('link', array('add-ons/options', $__vars['option']['AddOn'], ), true) . '">' . $__templater->escape($__vars['option']['AddOn']['title']) . '</a>
			</span>
		';
		}
		$__vars['hintHtml'] = $__templater->preEscaped(trim('
		' . $__compilerTemp1 . '
		' . $__compilerTemp2 . '
		'));
		$__finalCompiled .= '
	';
		$__vars['explainHtml'] = $__templater->preEscaped($__templater->escape($__vars['option']['explain']));
		$__finalCompiled .= '

	' . $__templater->formRow('
		<div class="blockMessage blockMessage--warning blockMessage--iconic">
			' . 'This option is visible in debug mode only.' . '
		</div>
	', array(
		)) . '
	<div class="multiRow">
		' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][bold]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['bold'],
			'label' => '
				' . 'Bold' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][italic]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['italic'],
			'label' => '
				' . 'Italic' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][underline]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['underline'],
			'label' => '
				' . 'Underline' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][strike]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['strike'],
			'label' => '
				' . 'Strike-through' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][color]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['color'],
			'label' => '
				' . 'Text color' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][bgcolor]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['bgcolor'],
			'label' => '
				' . 'Background color' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][font]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['font'],
			'label' => '
				' . 'Font family' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][size]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['size'],
			'label' => '
				' . 'Font size' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][url]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['url'],
			'label' => '
				' . 'Link' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][img]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['img'],
			'label' => '
				' . 'Image' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][media]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['media'],
			'label' => '
				' . 'Media' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][quote]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['quote'],
			'label' => '
				' . 'Quote' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][spoiler]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['spoiler'],
			'label' => '
				' . 'Spoiler' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][ispoiler]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['ispoiler'],
			'label' => '
				' . 'Inline spoiler' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][code]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['code'],
			'label' => '
				' . 'Code' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][icode]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['icode'],
			'label' => '
				' . 'Inline code' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][align]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['align'],
			'label' => '
				' . 'Alignment' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][list]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['list'],
			'label' => '
				' . 'List' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][table]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['table'],
			'label' => '
				' . 'Table' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][hide]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['hide'],
			'label' => '
				' . 'Hide' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][parsehtml]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['parsehtml'],
			'label' => '
				' . 'ParseHtml' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][sub]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['sub'],
			'label' => '
				' . 'Subscript' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][sup]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['sup'],
			'label' => '
				' . 'Superscript' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][attach]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['attach'],
			'label' => '
				' . 'Attachment' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][video]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['video'],
			'label' => '
				' . 'Video' . '
			',
			'_type' => 'option',
		),
		array(
			'name' => 'options[' . $__vars['option']['option_id'] . '][audio]',
			'value' => '1',
			'selected' => $__vars['option']['option_value']['audio'],
			'label' => '
				' . 'Audio' . '
			',
			'_type' => 'option',
		)), array(
			'label' => 'Enabled BB codes',
			'hint' => $__templater->escape($__vars['hintHtml']),
			'explain' => $__templater->escape($__vars['explainHtml']),
			'finalhtml' => $__templater->escape($__vars['listedHtml']),
		)) . '
	</div>

	<input type="hidden" name="options_listed[]" value="' . $__templater->escape($__vars['option']['option_id']) . '">
	';
	} else {
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});