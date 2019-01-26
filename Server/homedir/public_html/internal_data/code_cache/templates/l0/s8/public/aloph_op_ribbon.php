<?php
// FROM HASH: f40999d9ac0658e209db6e9f3ee19abf
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('public:aloph_op_ribbon_style.less');
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), false) != 'textPublicControlsDesktop') {
		$__finalCompiled .= '
    <div class="ribbonBox desktopRibbon ' . $__templater->fn('property', array('originalPosterHighlightPositionDesktop', ), true) . '">
        <div class="ribbon-wrapper">
            <div class="ribbon"
                    ';
		if (!$__vars['xf']['options']['aloph_disable_tooltip']) {
			$__finalCompiled .= '
                        data-xf-init="tooltip"
                        data-original-title="' . 'Thread Starter' . '"
                    ';
		}
		$__finalCompiled .= '
                >
                <span>' . 'OP' . ' </span>
            </div>
        </div>
    </div>
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('originalPosterHighlightPositionMobile', ), false) != 'textPublicControlsMobile') {
		$__finalCompiled .= '
    <div class="ribbonBox mobileRibbon ' . $__templater->fn('property', array('originalPosterHighlightPositionMobile', ), true) . '">
        <div class="ribbon-wrapper">
            <div class="ribbon">
                <span>' . 'OP' . '</span>
            </div>
        </div>
    </div>
';
	}
	return $__finalCompiled;
});