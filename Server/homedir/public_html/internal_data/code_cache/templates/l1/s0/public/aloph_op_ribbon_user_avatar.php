<?php
// FROM HASH: 70b601dc656d9f579774fe372bce1493
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ((($__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), false) != 'textPublicControlsDesktop') OR ($__templater->fn('property', array('originalPosterHighlightPositionMobile', ), false) != 'textPublicControlsMobile')) AND ($__vars['__globals']['originalPosterActive'] AND ($__vars['__globals']['originalPosterRibbonEnabled'] AND ($__vars['__globals']['post'] AND ($__vars['__globals']['thread'] AND ($__vars['__globals']['post']['post_id'] AND (($__vars['__globals']['thread']['user_id'] == $__vars['__globals']['post']['user_id']) AND ($__vars['__globals']['thread']['first_post_id'] != $__vars['__globals']['post']['post_id'])))))))) {
		$__finalCompiled .= '
    ' . $__templater->includeTemplate('aloph_op_ribbon', $__vars) . '
';
	}
	return $__finalCompiled;
});