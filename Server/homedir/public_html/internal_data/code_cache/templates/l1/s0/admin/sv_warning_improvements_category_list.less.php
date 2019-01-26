<?php
// FROM HASH: 32668293682cb25a3cc9f4b4402c969c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.warningImprovementsListingIcons
{
	.m-faBase();
	color: @xf-textColorDimmed;
	margin-right: 0.75em;

	&--Warning:before
	{
		.m-faContent(@fa-var-exclamation-triangle, 1em);
	}

	&--Category:before
	{
		.m-faContent(@fa-var-bars, .86em);
	}

	&--Action:before
	{
		.m-faContent(@fa-var-keyboard-o, .86em);
	}
}';
	return $__finalCompiled;
});