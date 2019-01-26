<?php
// FROM HASH: 3469326038028b9e7481d15b743bf648
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Warnings');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
' . $__templater->includeTemplate('sv_warningimprovements_warning_list1', $__vars) . '
');
	$__finalCompiled .= '

' . $__templater->includeTemplate('sv_warning_list', $__vars) . '
' . $__templater->includeTemplate('sv_warning_action_list', $__vars) . '
' . $__templater->includeTemplate('sv_warningimprovements_escalating_defaults', $__vars);
	return $__finalCompiled;
});