<?php
// FROM HASH: 431032211961dfe4d078109ac982f5ab
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__vars['contentMentionsRepo'] = $__templater->method($__vars['xf']['app']['em'], 'getRepository', array('SV\\UserEssentials:ContentMentions', ));
	$__finalCompiled .= '
';
	$__compilerTemp1 = array(array(
		'label' => 'All',
		'value' => '',
		'_type' => 'option',
	));
	$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__templater->method($__vars['contentMentionsRepo'], 'getSupportedContentTypePhrases', array(true, )));
	$__vars['svContentMentionsBody'] = $__templater->preEscaped('
	' . $__templater->formSelectRow(array(
		'name' => 'options[type]',
	), $__compilerTemp1, array(
		'label' => 'Content type',
	)) . '
');
	$__finalCompiled .= '
' . $__templater->callMacro('tools_rebuild', 'rebuild_job', array(
		'header' => 'Rebuild content mentions',
		'body' => $__vars['svContentMentionsBody'],
		'job' => 'SV\\UserEssentials:ContentMentionsAll',
	), $__vars);
	return $__finalCompiled;
});