<?php
// FROM HASH: c236250dd4138394ff9bad0ef52cee3a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<a href="' . $__templater->fn('link', array('media', $__vars['media'], ), true) . '" class="fauxBlockLink-blockLink">' . $__templater->escape($__vars['media']['title']) . '</a>

';
	if (!$__vars['options']['hide_container']) {
		$__finalCompiled .= '
	<div class="bookmarkRow-forum">
		';
		if ($__vars['media']['Category']) {
			$__finalCompiled .= '
			<span class="u-muted">' . 'Category' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('media/categories', $__vars['media']['Category'], ), true) . '">' . $__templater->escape($__vars['media']['Category']['title']) . '</a></span>
		';
		}
		$__finalCompiled .= '
		';
		if ($__vars['media']['Album']) {
			$__finalCompiled .= '
			<span class="u-muted">' . 'xfmg_album:' . ' <a href="' . $__templater->fn('link', array('media/albums', $__vars['media']['Album'], ), true) . '">' . $__templater->escape($__vars['media']['Album']['title']) . '</a></span>
		';
		}
		$__finalCompiled .= '
	</div>
';
	}
	return $__finalCompiled;
});