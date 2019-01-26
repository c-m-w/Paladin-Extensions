<?php
// FROM HASH: b6e770f905292d80e3021f8b503aa7e0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ((($__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), false) == 'textPublicControlsDesktop') OR ($__templater->fn('property', array('originalPosterHighlightPositionMobile', ), false) == 'textPublicControlsMobile')) AND ($__vars['__globals']['originalPosterActive'] AND ($__vars['__globals']['originalPosterRibbonEnabled'] AND ($__vars['__globals']['post'] AND ($__vars['__globals']['thread'] AND ($__vars['__globals']['post']['post_id'] AND (($__vars['__globals']['thread']['user_id'] == $__vars['__globals']['post']['user_id']) AND ($__vars['__globals']['thread']['first_post_id'] != $__vars['__globals']['post']['post_id'])))))))) {
		$__finalCompiled .= '
    ';
		$__templater->includeCss('public:aloph_op_ribbon_text_public_controls.less');
		$__finalCompiled .= '
    ';
		if ($__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), false) == 'textPublicControlsDesktop') {
			$__finalCompiled .= '
        <span class="' . $__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), true) . '">' . 'Thread Starter' . '</span>
    ';
		}
		$__finalCompiled .= '
    ';
		if ($__templater->fn('property', array('originalPosterHighlightPositionMobile', ), false) == 'textPublicControlsMobile') {
			$__finalCompiled .= '
        <span class="' . $__templater->fn('property', array('originalPosterHighlightPositionMobile', ), true) . '">' . 'Thread Starter' . '</span>
    ';
		}
		$__finalCompiled .= '

';
	}
	return $__finalCompiled;
});