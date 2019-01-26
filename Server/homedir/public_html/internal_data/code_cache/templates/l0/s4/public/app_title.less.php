<?php
// FROM HASH: 37f59ee0e836ee9a6610c2aebf1d653d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.uix_headerContainer {
	.uix_titlebar {
		';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) == 'fixed') {
		$__finalCompiled .= '
		.m-pageWidth();
		';
	}
	$__finalCompiled .= '
		
		.pageContent {
			';
	if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'fixed') {
		$__finalCompiled .= '
				.m-pageWidth();
			';
	}
	$__finalCompiled .= '
		}
	}
}

.uix_titlebar {
	.xf-uix_titlebar();
	min-height: 36px;
	
	.pageContent {
		display: flex;
		align-items: center;
		max-width: 100%;
		
		@media(max-width: @xf-responsiveNarrow) {
			flex-wrap: wrap;
			justify-content: center;
		}
	}

	.p-body-header {flex-grow: 1;}
	
	.p-title
	{
		display: flex;
		flex-wrap: wrap;
		align-items: center;
		max-width: 100%;

		&.p-title--noH1
		{
			flex-direction: row-reverse;
		}

		.has-no-flexbox &
		{
			.m-clearFix();
		}

		.p-title-pageAction {
			margin: 5px 0;
		}
	}

	.p-title-value
	{
		padding: 0;
		margin: 0 0 3px 0;
		font-size: @xf-fontSizeLargest;
		font-weight: @xf-fontWeightNormal;
		margin-right: auto;
		min-width: 0;
		.xf-uix_pageTitle();

		.has-no-flexbox &
		{
			float: left;
		}
	}

	.p-title-pageAction
	{
		margin-left: @xf-paddingLarge;
		
		@media(max-width: @xf-responsiveNarrow) {
			margin-left: 0;
			margin-top: @xf-paddingLarge;
		}
		
		.has-no-flexbox &
		{
			float: right;
		}

	}

	.p-description
	{
		margin: 0;
		padding: 0;
		font-size: @xf-fontSizeSmall;
		color: @xf-textColorMuted;
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.p-title-value
	{
		font-size: @xf-fontSizeLarger;
	}
}';
	return $__finalCompiled;
});