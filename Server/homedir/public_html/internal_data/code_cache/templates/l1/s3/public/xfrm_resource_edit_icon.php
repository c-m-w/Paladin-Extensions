<?php
// FROM HASH: fb4b72198d4c4f135cefec82a076c184
return array('macros' => array('custom_dependent' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(), $__arguments, $__vars);
	$__finalCompiled .= '
	' . $__templater->formUpload(array(
		'name' => 'upload',
		'accept' => '.gif,.jpeg,.jpg,.jpe,.png',
	)) . '
	<dfn class="inputChoices-explain">
		' . 'It is recommended that you use an image that is at least ' . 100 . 'x' . 100 . ' pixels.' . '
	</dfn>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Extension icon');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['resource']['icon_date']) {
		$__compilerTemp1 .= '
						';
		$__compilerTemp2 = array(array(
			'value' => 'custom',
			'label' => 'Upload a custom icon' . $__vars['xf']['language']['label_separator'],
			'_dependent' => array($__templater->callMacro(null, 'custom_dependent', array(), $__vars)),
			'_type' => 'option',
		));
		if ($__vars['resource']['icon_date']) {
			$__compilerTemp2[] = array(
				'value' => 'delete',
				'label' => 'Delete the current icon',
				'_type' => 'option',
			);
		}
		$__compilerTemp1 .= $__templater->formRadio(array(
			'name' => 'icon_action',
			'value' => 'custom',
		), $__compilerTemp2) . '
					';
	} else {
		$__compilerTemp1 .= '
						<span>' . 'Upload a new icon' . $__vars['xf']['language']['label_separator'] . '</span>
						' . $__templater->callMacro(null, 'custom_dependent', array(), $__vars) . '
						' . $__templater->formHiddenVal('icon_action', 'custom', array(
		)) . '
					';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			<div class="contentRow">
				<div class="contentRow-figure">
					<span class="contentRow-figureIcon">' . $__templater->fn('resource_icon', array($__vars['resource'], 'm', ), true) . '</span>
				</div>
				<div class="contentRow-main">
					' . $__compilerTemp1 . '
				</div>
			</div>
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/edit-icon', $__vars['resource'], ), false),
		'upload' => 'true',
		'ajax' => 'true',
		'class' => 'block',
	)) . '

';
	return $__finalCompiled;
});