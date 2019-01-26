<?php
// FROM HASH: 0a8e6a2b265139f8e370370a13532093
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Change resource type');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['category'], 'hasVersioningSupport', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formTextBoxRow(array(
			'name' => 'version_string',
			'value' => $__vars['category']['draft_resource']['version_string'],
		), array(
			'label' => 'Version number',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->callMacro('xfrm_resource_edit_macros', 'type', array(
		'currentType' => $__templater->method($__vars['resource'], 'getResourceTypeDetailed', array()),
		'resource' => $__vars['resource'],
		'category' => $__vars['category'],
		'versionAttachData' => $__vars['versionAttachData'],
		'allowCurrentType' => true,
	), $__vars) . '

			' . $__compilerTemp1 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/change-type', $__vars['resource'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});