<?php
// FROM HASH: ab7b1dffdb80252d13299c6cac283dfb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<span class="u-anchorTarget" id="' . $__templater->escape($__vars['option']['option_id']) . '"></span>
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
			<a href="' . $__templater->fn('link', array('add-ons/options', $__vars['option']['AddOn'], ), true) . '">
				' . $__templater->escape($__vars['option']['AddOn']['title']) . '
			</a>
		</span>
	';
	}
	$__vars['hintHtml'] = $__templater->preEscaped(trim('
	' . $__compilerTemp1 . '
	' . $__compilerTemp2 . '
	') . '
');
	$__finalCompiled .= '
';
	$__vars['inputName'] = $__templater->preEscaped('
		' . $__templater->callMacro('option_macros', 'input_name', array(
		'id' => $__vars['option']['option_id'],
	), $__vars) . '
	');
	$__vars['listedHtml'] = $__templater->preEscaped('
		' . $__templater->callMacro('option_macros', 'listed_html', array(
		'id' => $__vars['option']['option_id'],
	), $__vars) . '
	');
	$__compilerTemp3 = '';
	if ($__templater->isTraversable($__vars['colors'])) {
		foreach ($__vars['colors'] AS $__vars['color']) {
			$__compilerTemp3 .= '					
			<li>
				' . $__templater->callMacro('public:color_picker_macros', 'color_picker', array(
				'name' => 'color_adder[]',
				'row' => false,
				'rowClass' => 'js-ColorAdder',
				'value' => $__vars['color'],
			), $__vars) . '
			</li>
		';
		}
	}
	$__templater->inlineCss('
		.split-row li {
			display: inline-block;
			width: calc(' . (100 / $__vars['xf']['options']['klEMColorStep']) . '% - 6px);
			transition: width 100ms;
			will-change: width;
		}
		
		.split-row .inputGroup-text {
			border-radius: 4px;
		}
		
		.split-row .input {
			display: none;
		}
		
		.split-row li:last-child .colorPickerBox::before {
			content: "\\f067";
			font-family: "FontAwesome";
			color: #777;
			position: absolute;
			left: calc(50% - .5em);
			top: -1px;
		}
	');
	$__templater->inlineJs('
		$(\'.js-ColorAdder\').on(\'change\', function() {
			var values = [];
			$(\'.js-ColorAdder\').each(function() {
				$values.push($(this).val());
			});
			$values.push(\'REMOVE\');
			$(\'.js-ColorValue\').val(values.join())
		});
		
		$(\'[name="options[klEMColorStep]"]\').on(\'change\', function() {
			var cols = $(this).val();
			console.log(cols);
			$(\'.split-row li\').css(\'width\', \'calc(\'+(100/cols)+\'% - 6px)\');
		});
	');
	$__finalCompiled .= $__templater->formRow('

	' . '' . '
	' . '' . '
	<input type="hidden" name="' . $__templater->escape($__vars['inputName']) . '" value="' . $__templater->escape($__vars['option']['option_value']) . '" class="js-ColorValue" />

	<ul class="inputList split-row">
		' . $__compilerTemp3 . '
		<li data-xf-init="field-adder">
				' . $__templater->callMacro('public:color_picker_macros', 'color_picker', array(
		'row' => false,
		'name' => 'color_adder[]',
		'rowClass' => 'js-ColorAdder',
	), $__vars) . '
		</li>
	</ul>
	' . '' . '
	' . '' . '
', array(
		'label' => $__templater->escape($__vars['option']['title']),
		'explain' => $__templater->escape($__vars['option']['explain']),
		'hint' => $__templater->escape($__vars['hintHtml']),
	));
	return $__finalCompiled;
});