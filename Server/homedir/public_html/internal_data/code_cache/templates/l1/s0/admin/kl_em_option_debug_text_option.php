<?php
// FROM HASH: c042964ccbeffd69d7e2764e4a2e0190
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['debug']) {
		$__finalCompiled .= '
	<span class="u-anchorTarget" id="' . $__templater->escape($__vars['option']['option_id']) . '"></span>
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
		$__finalCompiled .= $__templater->formRow('
		<div class="blockMessage blockMessage--warning blockMessage--iconic">
			' . 'This option is visible in debug mode only.' . '
		</div>

		' . '' . '
		' . '' . '
		' . $__templater->formTextBox(array(
			'name' => $__vars['inputName'],
			'value' => $__vars['option']['option_value'],
			'type' => $__vars['formatParams']['type'],
			'class' => $__vars['formatParams']['class'],
		)) . '
	', array(
			'label' => $__templater->escape($__vars['option']['title']),
			'hint' => $__templater->escape($__vars['hintHtml']),
			'explain' => $__templater->escape($__vars['option']['explain']),
		)) . '
	';
	} else {
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});