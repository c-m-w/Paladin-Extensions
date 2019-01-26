<?php
// FROM HASH: 0fa0244f7b701249e2a9be23a70f54f8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	$__compilerTemp2 = $__templater->fn('react_handlers', array(), false);
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['contentType'] => $__vars['reactHandler']) {
			$__compilerTemp1 .= '
			';
			if ($__templater->method($__vars['reactHandler']['object'], 'getReactionBarPositions', array())) {
				$__compilerTemp1 .= '
				';
				$__compilerTemp3 = array();
				$__compilerTemp4 = $__templater->method($__vars['reactHandler']['object'], 'getReactionBarPositions', array());
				if ($__templater->isTraversable($__compilerTemp4)) {
					foreach ($__compilerTemp4 AS $__vars['positionId'] => $__vars['positionPhrase']) {
						$__compilerTemp3[] = array(
							'value' => $__vars['positionId'],
							'label' => $__templater->escape($__vars['positionPhrase']),
							'selected' => $__vars['property']['property_value'][$__vars['contentType']] == $__vars['positionId'],
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp1 .= $__templater->formRadioRow(array(
					'name' => $__vars['formBaseKey'] . '[' . $__vars['contentType'] . ']',
				), $__compilerTemp3, array(
					'label' => $__templater->escape($__templater->method($__vars['reactHandler']['object'], 'getTitle', array())),
				)) . '
			';
			}
			$__compilerTemp1 .= '
		';
		}
	}
	$__finalCompiled .= $__templater->formRow('
	<div class="inputGroup">
		' . $__compilerTemp1 . '
	</div>
', array(
		'label' => $__templater->escape($__vars['titleHtml']),
		'hint' => $__templater->escape($__vars['hintHtml']),
		'rowclass' => $__vars['rowClass'],
		'explain' => $__templater->escape($__vars['property']['description']),
		'rowtype' => 'input',
	));
	return $__finalCompiled;
});