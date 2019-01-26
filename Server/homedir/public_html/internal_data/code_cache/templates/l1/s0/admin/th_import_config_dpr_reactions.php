<?php
// FROM HASH: dd2afd079694f9cddd368f81c7409f3a
return array('macros' => array('reaction_type_map_selectrow' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'label' => '!',
		'name' => '!',
		'value' => '!',
		'reactionTypes' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['reactionTypes'])) {
		foreach ($__vars['reactionTypes'] AS $__vars['reactionType']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['reactionType']['reaction_type_id'],
				'label' => $__templater->escape($__vars['reactionType']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => $__vars['name'],
		'value' => $__vars['value'],
	), $__compilerTemp1, array(
		'label' => $__templater->escape($__vars['label']),
	)) . '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<h3 class="block-header">
	' . 'Map reactions' . '
</h3>
';
	if ($__templater->isTraversable($__vars['postRatings'])) {
		foreach ($__vars['postRatings'] AS $__vars['rating']) {
			$__finalCompiled .= '
	';
			$__compilerTemp1 = array(array(
				'value' => '0',
				'label' => 'Add reaction',
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['reactions'])) {
				foreach ($__vars['reactions'] AS $__vars['reaction']) {
					$__compilerTemp1[] = array(
						'value' => $__vars['reaction']['reaction_id'],
						'selected' => (($__vars['reaction']['title'] == $__vars['rating']['title']) ? 1 : 0),
						'label' => $__templater->escape($__vars['reaction']['title']),
						'_type' => 'option',
					);
				}
			}
			$__finalCompiled .= $__templater->formSelectRow(array(
				'name' => 'config[reaction_map][' . $__vars['rating']['id'] . ']',
			), $__compilerTemp1, array(
				'label' => $__templater->escape($__vars['rating']['title']),
			)) . '
';
		}
	}
	$__finalCompiled .= '

<h3 class="block-header">
	' . 'Map reaction types' . '
</h3>

' . $__templater->callMacro(null, 'reaction_type_map_selectrow', array(
		'label' => 'Positive',
		'name' => 'config[reaction_type_map][1]',
		'value' => 'positive',
		'reactionTypes' => $__vars['reactionTypes'],
	), $__vars) . '
' . $__templater->callMacro(null, 'reaction_type_map_selectrow', array(
		'label' => 'Neutral',
		'name' => 'config[reaction_type_map][0]',
		'value' => 'neutral',
		'reactionTypes' => $__vars['reactionTypes'],
	), $__vars) . '
' . $__templater->callMacro(null, 'reaction_type_map_selectrow', array(
		'label' => 'Negative',
		'name' => 'config[reaction_type_map][-1]',
		'value' => 'negative',
		'reactionTypes' => $__vars['reactionTypes'],
	), $__vars) . '

' . '
';
	return $__finalCompiled;
});