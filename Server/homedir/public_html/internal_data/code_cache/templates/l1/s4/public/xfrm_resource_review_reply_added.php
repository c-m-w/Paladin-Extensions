<?php
// FROM HASH: eb54248fb55c4a25843e9349e5fb0906
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('xfrm_resource_review_macros', 'author_reply_row', array(
		'review' => $__vars['review'],
		'resource' => $__vars['resource'],
	), $__vars) . '
';
	return $__finalCompiled;
});