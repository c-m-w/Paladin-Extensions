<?php
// FROM HASH: 5d9a599209989f8d3da75435f0fe8de2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('like_item_resource_update', 'like_snippet', array(
		'liker' => $__vars['user'],
		'update' => $__vars['content'],
		'date' => $__vars['newsFeed']['event_date'],
	), $__vars);
	return $__finalCompiled;
});