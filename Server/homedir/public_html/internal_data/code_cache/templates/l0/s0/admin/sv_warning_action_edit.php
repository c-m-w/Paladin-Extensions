<?php
// FROM HASH: 6e72b53751acfc6dd72b536fa886f9ff
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />' . '

';
	$__compilerTemp1 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['treeEntry']['record']['warning_category_id'],
				'selected' => $__vars['action']['sv_warning_category_id'] === $__vars['treeEntry']['record']['warning_category_id'],
				'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => 'sv_warning_category_id',
		'value' => $__vars['action']['sv_warning_category_id'],
	), $__compilerTemp1, array(
		'label' => 'Warning Category' . $__vars['xf']['language']['label_separator'],
	)) . '

<hr class="formRowSep" />' . '

';
	$__compilerTemp3 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	$__compilerTemp4 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp4)) {
		foreach ($__compilerTemp4 AS $__vars['treeEntry']) {
			$__compilerTemp3[] = array(
				'value' => $__vars['treeEntry']['record']['node_id'],
				'selected' => $__vars['action']['sv_post_node_id'] === $__vars['treeEntry']['record']['node_id'],
				'disabled' => (($__vars['treeEntry']['record']['node_type_id'] != 'Forum') ? 'disabled' : ''),
				'label' => '
			' . $__templater->fn('repeat_raw', array('&nbsp; ', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']) . '
		',
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => 'sv_post_node_id',
		'value' => $__vars['action']['sv_post_node_id'],
		'class' => 'js-nodeList',
	), $__compilerTemp3, array(
		'label' => 'Post to Forum',
		'explain' => 'Post message to a new thread in the given forum when this warning action is triggered. Zero to disable.<br/>
<br/>
New Thread trumps replying to a thread. Only the last warning action is applied when posting.<br/>
<br/>
Edit the phases:
<ul class="inputChoices">
<li><strong>Warning_Thread_Message</strong></li>
<li><strong>Warning_Thread_Title</strong></li>
</ul>
',
	)) . '

' . $__templater->formNumberBoxRow(array(
		'name' => 'sv_post_thread_id',
		'value' => $__vars['action']['sv_post_thread_id'],
	), array(
		'label' => 'Reply to thread' . ':',
		'explain' => 'Post message to an existing thread when this warning action is triggered. Zero to disable.<br/>
<br/>
Edit the phases:
<ul class="inputChoices">
<li><strong>Warning_Thread_Message</strong></li>
</ul>
',
	)) . '
' . $__templater->formNumberBoxRow(array(
		'name' => 'sv_post_as_user_id',
		'value' => $__vars['action']['sv_post_as_user_id'],
	), array(
		'label' => 'User Id To Post As' . ':',
		'explain' => 'The User Id to post as. 0 to user the user triggering the warning.',
	));
	return $__finalCompiled;
});