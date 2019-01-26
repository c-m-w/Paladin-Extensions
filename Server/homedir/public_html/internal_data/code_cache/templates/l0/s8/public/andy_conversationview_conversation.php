<?php
// FROM HASH: c43763ec6ad0391cad335b2b6995830e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Conversation view');
	$__finalCompiled .= '

' . 'Conversation ID' . ': ' . $__templater->escape($__vars['conversationId']) . '
<br />
' . 'Title' . ': ' . $__templater->escape($__vars['conversationTitle']) . '
<br />
' . 'Starter' . ': ' . $__templater->escape($__vars['starter']) . '
<br />
' . 'Recipients' . ': ' . $__templater->escape($__vars['recipients']) . '
<br /><br />

<a href="' . $__templater->fn('link', array('conversationview/delete/', '', array('conversation_id' => $__vars['conversationId'], ), ), true) . '">' . 'Delete conversation' . '</a>
<br /><br />

<div class="block-container">
	<div class="block-body">
		';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['messages'])) {
		foreach ($__vars['messages'] AS $__vars['message']) {
			$__compilerTemp1 .= '
				';
			$__compilerTemp2 = array(array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['message']['message_id']),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['message']['message_date'], array(
			))),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['message']['username']),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->filter($__vars['message']['message'], array(array('nl2br', array()),), true),
			));
			if ($__vars['message']['attach_count'] > 0) {
				$__compilerTemp2[] = array(
					'href' => $__templater->fn('link', array('conversationview/viewattachments', '', array('message_id' => $__vars['message']['message_id'], ), ), false),
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['message']['attach_count']),
				);
			}
			if ($__vars['message']['attach_count'] == 0) {
				$__compilerTemp2[] = array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['message']['attach_count']),
				);
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
				'rowclass' => 'dataList-row--noHover',
			), $__compilerTemp2) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Message ID',
	),
	array(
		'_type' => 'cell',
		'html' => 'Message date',
	),
	array(
		'_type' => 'cell',
		'html' => 'Username',
	),
	array(
		'_type' => 'cell',
		'html' => 'Message',
	),
	array(
		'_type' => 'cell',
		'html' => 'Attachments',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});