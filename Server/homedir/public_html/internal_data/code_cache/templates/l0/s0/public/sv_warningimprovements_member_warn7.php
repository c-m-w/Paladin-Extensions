<?php
// FROM HASH: 9930ec4a332b3b071afb1a7fea060595
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('sv_warningimprovements_member_warn7.less');
	$__finalCompiled .= '

<h2 class="block-formSectionHeader">
	<span class="collapseTrigger collapseTrigger--block" data-xf-click="toggle" data-target="< :up :next">
		<span class="block-formSectionHeader-aligner">' . 'Previous Warnings (' . $__templater->escape($__vars['user']['warning_count']) . ')' . '</span>
	</span>
</h2>

<div class="block-body previous-warnings block-body--collapsible">
	';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['previousWarnings'])) {
		foreach ($__vars['previousWarnings'] AS $__vars['previousWarning']) {
			$__compilerTemp1 .= '
				';
			$__compilerTemp2 = '';
			if ($__vars['previousWarning']['expiry_date']) {
				$__compilerTemp2 .= '
							' . $__templater->fn('date_dynamic', array($__vars['previousWarning']['expiry_date'], array(
				))) . '
							';
			} else {
				$__compilerTemp2 .= '
							' . 'N/A' . '
						';
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
				'rowclass' => ($__vars['previousWarning']['is_expired'] ? 'dataList-row--disabled' : ''),
			), array(array(
				'href' => $__templater->fn('link', array('warnings', $__vars['previousWarning'], ), false),
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['previousWarning']['title']),
			),
			array(
				'href' => $__templater->fn('link', array('warnings', $__vars['previousWarning'], ), false),
				'overlay' => 'true',
				'class' => 'dataList-cell--min',
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['previousWarning']['warning_date'], array(
			))),
			),
			array(
				'href' => $__templater->fn('link', array('warnings', $__vars['previousWarning'], ), false),
				'overlay' => 'true',
				'class' => 'dataList-cell--min',
				'_type' => 'cell',
				'html' => $__templater->filter($__vars['previousWarning']['points'], array(array('number', array()),), true),
			),
			array(
				'href' => $__templater->fn('link', array('warnings', $__vars['previousWarning'], ), false),
				'overlay' => 'true',
				'class' => 'dataList-cell--min',
				'_type' => 'cell',
				'html' => '
						' . $__compilerTemp2 . '
					',
			))) . '
			';
		}
	}
	$__compilerTemp3 = '';
	if ($__templater->fn('count', array($__vars['previousWarnings'], ), false) < $__vars['user']['warning_count']) {
		$__compilerTemp3 .= '
				' . $__templater->dataRow(array(
			'rowclass' => ($__vars['previousWarning']['is_expired'] ? 'dataList-row--disabled' : ''),
		), array(array(
			'href' => $__templater->fn('link', array('members', $__vars['user'], ), false) . '#warnings',
			'colspan' => '4',
			'_type' => 'cell',
			'html' => 'All Warnings (' . ($__vars['user']['warning_count'] - $__templater->fn('count', array($__vars['previousWarnings'], ), false)) . ' more)',
		))) . '
			';
	}
	$__finalCompiled .= $__templater->formRow('
		' . $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Warning',
	),
	array(
		'_type' => 'cell',
		'html' => 'Date',
	),
	array(
		'_type' => 'cell',
		'html' => 'Points',
	),
	array(
		'_type' => 'cell',
		'html' => 'Expiry',
	))) . '
			' . $__compilerTemp1 . '
			' . $__compilerTemp3 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	', array(
	)) . '
</div>';
	return $__finalCompiled;
});