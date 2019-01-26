<?php
// FROM HASH: 00cbc8a6abacb084a9bcbc6c6087b079
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('History');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['threads'])) {
		foreach ($__vars['threads'] AS $__vars['thread']) {
			$__compilerTemp1 .= '
					';
			$__compilerTemp2 = array(array(
				'_type' => 'cell',
				'html' => '
						<span class="contentRow-figure">
							' . $__templater->fn('avatar', array($__vars['thread']['Thread']['User'], 'xs', false, array(
				'defaultname' => $__vars['thread']['Thread']['username'],
			))) . '
						</span>
						',
			));
			if (($__vars['thread']['Thread']['last_post_date'] <= $__vars['thread']['thread_read_date']) OR ($__vars['thread']['Thread']['last_post_username'] == $__vars['xf']['visitor']['username'])) {
				$__compilerTemp2[] = array(
					'href' => $__templater->fn('link', array('threads/', $__vars['thread']['Thread'], ), false),
					'_type' => 'cell',
					'html' => $__templater->fn('prefix', array('thread', $__vars['thread']['Thread']['prefix_id'], 'html', '', ), true) . ' ' . $__templater->escape($__vars['thread']['Thread']['title']),
				);
			}
			if (($__vars['thread']['Thread']['last_post_date'] > $__vars['thread']['thread_read_date']) AND ($__vars['thread']['Thread']['last_post_username'] != $__vars['xf']['visitor']['username'])) {
				$__compilerTemp2[] = array(
					'href' => $__templater->fn('link', array('threads/unread', $__vars['thread']['Thread'], ), false),
					'style' => 'font-weight: 700;',
					'_type' => 'cell',
					'html' => $__templater->fn('prefix', array('thread', $__vars['thread']['Thread']['prefix_id'], 'html', '', ), true) . ' ' . $__templater->escape($__vars['thread']['Thread']['title']),
				);
			}
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => '<a href="' . $__templater->fn('link', array('forums', $__vars['thread']['Thread']['Forum'], ), true) . '">' . $__templater->escape($__vars['thread']['Thread']['Forum']['title']) . '</a>',
			);
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['thread']['Thread']['reply_count']),
			);
			$__compilerTemp2[] = array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['thread']['thread_read_date'], array(
			))),
			);
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
		'html' => 'Thread starter',
	),
	array(
		'_type' => 'cell',
		'html' => 'Title',
	),
	array(
		'_type' => 'cell',
		'html' => 'Forum',
	),
	array(
		'_type' => 'cell',
		'html' => 'Replies',
	),
	array(
		'_type' => 'cell',
		'html' => 'Thread read date',
	))) . '
				' . $__compilerTemp1 . '
			', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});