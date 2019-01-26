<?php
// FROM HASH: c88918dd07a77a954de3fa37b9ebac21
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ######################################### STAFF BAR #################################

.p-staffBar
{
	.xf-publicStaffBar();
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fixed') {
		$__finalCompiled .= '
			.m-pageWidth();
		';
	}
	$__finalCompiled .= '

	.hScroller-action
	{
		.m-hScrollerActionColorVariation(
			xf-default(@xf-publicStaffBar--background-color, transparent),
			@xf-publicStaffBar--color,
			xf-intensify(@xf-publicStaffBar--color, 10%)
		);
	}

	.pageContent {
		display: flex;
		align-items: center;
		justify-content: space-between;
		position: relative;
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
		$__finalCompiled .= '
			.m-pageWidth();
		';
	}
	$__finalCompiled .= '
		
		';
	if ($__templater->fn('property', array('uix_stickyStaffBar', ), false)) {
		$__finalCompiled .= '
			min-height: @xf-uix_stickyStaffBarHeight;
		';
	}
	$__finalCompiled .= '
		
		a {
			color: @xf-uix_staffBarTab--color;
			
			&:hover {color: @xf-uix_staffBarTabHover--color;}
		}
	}


}

.p-staffBar-inner
{
	.m-clearFix();
	// padding-top: @xf-paddingMedium;
	//padding-bottom: @xf-paddingMedium;
}

.p-staffBar-link
{
	display: inline-block;
	vertical-align: top;
	color: inherit;
	padding: 4px @xf-paddingMedium;
	margin-right: .35em;
	.xf-uix_staffBarTab();

	&:last-child
	{
		margin-right: 0;
	}

	&:hover
	{
		text-decoration: none;
		background: xf-diminish(@xf-publicStaffBar--background-color, 6%);
		border-radius: @xf-borderRadiusSmall;
		.xf-uix_staffBarTabHover();
	}
}';
	return $__finalCompiled;
});