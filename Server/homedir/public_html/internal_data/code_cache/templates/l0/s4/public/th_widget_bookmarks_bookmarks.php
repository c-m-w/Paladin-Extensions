<?php
// FROM HASH: fcdc51d80bde7d22d73a99c14267e7f6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['bookmarks'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('th_bookmarks.less');
		$__finalCompiled .= '
	';
		$__templater->includeCss('bb_code.less');
		$__finalCompiled .= '

	<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
		<div class="block-container">
			<h3 class="block-minorHeader">
				<a href="' . $__templater->fn('link', array('bookmarks', ), true) . '" rel="nofollow">' . $__templater->escape($__vars['title']) . '</a>
			</h3>
			<ul class="block-body">
				';
		if ($__templater->isTraversable($__vars['bookmarks'])) {
			foreach ($__vars['bookmarks'] AS $__vars['bookmark']) {
				$__finalCompiled .= '
					<li class="block-row">
						' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'row', array(
					'editLink' => false,
					'bookmark' => $__vars['bookmark'],
					'widget' => $__vars['widget'],
					'options' => $__vars['options'],
				), $__vars) . '
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
			<div class="block-footer">
				<a href="' . $__templater->fn('link', array('bookmarks', ), true) . '">' . 'View full list' . '</a>
			</div>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});