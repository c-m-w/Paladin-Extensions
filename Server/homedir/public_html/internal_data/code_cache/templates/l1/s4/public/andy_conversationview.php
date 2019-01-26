<?php
// FROM HASH: 3eeb0a5fb8c8054a59e8da8392422bf8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Conversation view');
	$__finalCompiled .= '

';
	if ($__vars['username']) {
		$__finalCompiled .= '
	' . 'Conversations started by' . ': ' . $__templater->escape($__vars['username']) . '
	<br />
	' . 'Limit' . ': ' . $__templater->escape($__vars['limit']) . '
	<br />
	<br />
	<a href="' . $__templater->fn('link', array('conversationview', ), true) . '">' . 'Show all' . '</a>
';
	}
	$__finalCompiled .= '
	
';
	if (!$__vars['username']) {
		$__finalCompiled .= '
	' . 'Conversations started by' . ': ' . 'All' . '
	<br />
	' . 'Limit' . ': ' . $__templater->escape($__vars['limit']) . '
	<br />
	<br />
	<a href="' . $__templater->fn('link', array('conversationview/filter', ), true) . '">' . 'Filter' . '</a>
';
	}
	$__finalCompiled .= '

<br />
<br />

<div class="block-container">
	<div class="block-body">
		';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['results'])) {
		foreach ($__vars['results'] AS $__vars['result']) {
			$__compilerTemp1 .= '
				' . $__templater->dataRow(array(
				'rowclass' => 'dataList-row--noHover',
			), array(array(
				'href' => $__templater->fn('link', array('conversationview/conversation', '', array('conversation_id' => $__vars['result']['conversation_id'], ), ), false),
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['title']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->fn('username_link', array($__vars['result']['user'], false, array(
			))),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['recipients']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['result']['last_message_date'], array(
			))),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['reply_count']),
			))) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Title',
	),
	array(
		'_type' => 'cell',
		'html' => 'Conversation starter',
	),
	array(
		'_type' => 'cell',
		'html' => 'Recipients',
	),
	array(
		'_type' => 'cell',
		'html' => 'Last message date',
	),
	array(
		'_type' => 'cell',
		'html' => 'Reply count',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});