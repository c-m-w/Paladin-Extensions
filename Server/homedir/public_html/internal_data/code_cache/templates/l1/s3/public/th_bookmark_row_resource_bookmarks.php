<?php
// FROM HASH: 94cb9210464aa0639f2f47ec39febc09
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<a href="' . $__templater->fn('link', array('resources', $__vars['resource'], ), true) . '" class="fauxBlockLink-blockLink">' . $__templater->escape($__vars['resource']['title']) . '</a>

';
	if (!$__vars['options']['hide_container']) {
		$__finalCompiled .= '
	<div class="bookmarkRow-forum">
		<span class="u-muted">' . 'Category' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('resources/categories', $__vars['category'], ), true) . '">' . $__templater->escape($__vars['category']['title']) . '</a></span>
	</div>
';
	}
	return $__finalCompiled;
});