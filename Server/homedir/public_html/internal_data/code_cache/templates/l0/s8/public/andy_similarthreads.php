<?php
// FROM HASH: e4262f94c5b59925419b68be98de5b96
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['similarThreads']) {
		$__finalCompiled .= '

';
		$__templater->includeCss('andy_similarthreads.less');
		$__finalCompiled .= '

<div class="block similarthreads-wide">
	<div class="block-container">
		<div class="block-body">
			';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['similarThreads'])) {
			foreach ($__vars['similarThreads'] AS $__vars['thread']) {
				$__compilerTemp1 .= '
					' . $__templater->dataRow(array(
					'rowclass' => 'dataList-row--noHover',
				), array(array(
					'_type' => 'cell',
					'html' => '		
						<span class="contentRow-figure">
							' . $__templater->fn('avatar', array($__vars['thread']['User'], 'xs', false, array(
					'defaultname' => $__vars['thread']['username'],
				))) . '
						</span>
						',
				),
				array(
					'href' => $__templater->fn('link', array('threads/', $__vars['thread'], ), false),
					'_type' => 'cell',
					'html' => $__templater->fn('prefix', array('thread', $__vars['thread']['prefix_id'], 'html', '', ), true) . ' ' . $__templater->escape($__vars['thread']['title']),
				),
				array(
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->fn('link', array('forums', $__vars['thread']['Forum'], ), true) . '">' . $__templater->escape($__vars['thread']['Forum']['title']) . '</a>',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['thread']['reply_count']),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['thread']['post_date'], array(
				))),
				))) . '
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
			'html' => 'Similar threads',
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
			'html' => 'Date',
		))) . '
				' . $__compilerTemp1 . '
			', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '
		</div>
	</div>
</div>
	
<div class="block similarthreads-narrow">
	<div class="block-container">
		<h3 class="block-minorHeader">' . 'Similar threads' . '</h3>
		<div class="block-body block-row">
			<ul class="block-body">
				';
		if ($__templater->isTraversable($__vars['similarThreads'])) {
			foreach ($__vars['similarThreads'] AS $__vars['thread']) {
				$__finalCompiled .= '
					<li class="block-row">
						' . $__templater->callMacro('thread_list_macros', 'item_new_threads', array(
					'thread' => $__vars['thread'],
				), $__vars) . '
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</div>
	</div>
</div>
	
<br />
	
';
	}
	return $__finalCompiled;
});