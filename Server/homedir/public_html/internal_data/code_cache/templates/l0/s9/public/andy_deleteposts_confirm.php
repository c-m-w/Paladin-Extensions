<?php
// FROM HASH: f15b0ddaa80a2c084dc68b15b2e50aec
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Delete posts');
	$__finalCompiled .= '

(' . 'Confirm' . ')
<br /><br />

' . 'Username' . ': ' . $__templater->escape($__vars['postedBy']) . '
<br />

' . 'Limit' . ': ' . $__templater->escape($__vars['xf']['options']['deletePostsLimit']) . '
<br /><br />

' . 'Post number 1 indicates entire thread will be deleted.' . '
<br /><br />

<a href="' . $__templater->fn('link', array('deleteposts/delete', '', array('user_id' => $__vars['userId'], ), ), true) . '">' . 'Delete' . ' ' . $__templater->escape($__vars['postsCount']) . ' ' . 'posts' . '</a>
<br /><br />

<div class="block-container">
	<div class="block-body">
		';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['posts'])) {
		foreach ($__vars['posts'] AS $__vars['post']) {
			$__compilerTemp1 .= '
				' . $__templater->dataRow(array(
				'rowclass' => 'dataList-row--noHover',
			), array(array(
				'href' => $__templater->fn('link', array('posts/', $__vars['post'], ), false),
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['post']['post_id']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['post']['Thread']['title']),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['post']['Thread']['Forum']['title']),
			),
			array(
				'_type' => 'cell',
				'html' => ($__vars['post']['position'] + 1),
			))) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Post ID',
	),
	array(
		'_type' => 'cell',
		'html' => 'Thread title',
	),
	array(
		'_type' => 'cell',
		'html' => 'Forum',
	),
	array(
		'_type' => 'cell',
		'html' => 'Post number',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});