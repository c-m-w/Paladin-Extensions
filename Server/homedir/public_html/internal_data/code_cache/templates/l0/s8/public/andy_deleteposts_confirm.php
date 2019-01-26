<?php
// FROM HASH: 4c0fa32058961204cca377739e4ac6de
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Delete posts');
	$__finalCompiled .= '

(' . 'Confirm' . ')
<br /><br />
' . 'Username' . ': ' . $__templater->escape($__vars['postedBy']) . '
<br />
' . 'Posts' . ': ' . $__templater->escape($__vars['postsCount']) . '
<br />
' . 'Limit' . ': ' . $__templater->escape($__vars['xf']['options']['deletePostsLimit']) . '
<br /><br />
' . 'Position 0 indicates entire thread will be deleted.' . '
<br /><br />

';
	if ($__vars['xf']['options']['deletePostsLimit'] < $__vars['postsCount']) {
		$__finalCompiled .= '
<a href="' . $__templater->fn('link', array('deleteposts/delete', '', array('user_id' => $__vars['userId'], ), ), true) . '">' . 'Delete' . ' ' . $__templater->escape($__vars['limit']) . ' ' . 'deleteposts_posts' . '</a>
';
	} else {
		$__finalCompiled .= '
<a href="' . $__templater->fn('link', array('deleteposts/delete', '', array('user_id' => $__vars['userId'], ), ), true) . '">' . 'Delete' . ' ' . $__templater->escape($__vars['postsCount']) . ' ' . 'posts' . '</a>
';
	}
	$__finalCompiled .= '
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
				'html' => $__templater->escape($__vars['post']['position']),
			))) . '
			';
		}
	}
	$__finalCompiled .= $__templater->dataList('
			' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Post number',
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
		'html' => 'Position',
	))) . '
			' . $__compilerTemp1 . '
		', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
	</div>
</div>';
	return $__finalCompiled;
});