<?php
// FROM HASH: e0ed94874a8cde6859a1f13d09de7249
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Ticket prefixes');
	$__finalCompiled .= '

' . $__templater->includeTemplate('base_prefix_list', $__vars);
	return $__finalCompiled;
});