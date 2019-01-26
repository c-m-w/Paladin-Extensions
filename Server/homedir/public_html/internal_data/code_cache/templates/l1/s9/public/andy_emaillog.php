<?php
// FROM HASH: 40c83574b32f60f766396e84a0ee42d3
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Email log');
	$__finalCompiled .= '

' . 'Limit' . ': ' . $__templater->escape($__vars['limit']) . '
<br /><br />

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
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['result']['email_date'], array(
			))),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['email_username']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['email_address']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['result']['email_subject']),
			))) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Date',
	),
	array(
		'_type' => 'cell',
		'html' => 'Username',
	),
	array(
		'_type' => 'cell',
		'html' => 'Email to',
	),
	array(
		'_type' => 'cell',
		'html' => 'Subject',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});