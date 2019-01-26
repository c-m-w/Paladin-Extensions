<?php
// FROM HASH: e66b3af27ccb7c4bf7aa97f300941153
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.uix_headerContainer {
	.p-body-header {
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

.p-pageWrapper > .p-body-header .pageContent {
	.m-pageWidth();
	min-height: 36px;
}

.p-body-header {
	.xf-uix_titlebar();
	
	.pageContent {
		display: flex;
		align-items: center;
		// max-width: 100%;
		
		.p-title-pageAction {margin-top: 0;}
		
		@media(max-width: @xf-responsiveMedium) {
			flex-wrap: wrap;
			
			.uix_headerInner--opposite {
				width: 100%;
				flex-grow: 1;
			}
		}
	}
	
	.contentRow {flex-grow: 1;}

	.uix_headerInner {
		margin: 5px;
		margin-left: 0;
		margin-right: auto;
	}
	
	.uix_headerInner--opposite {
		display: inline-flex;
		align-items: center;
		flex-wrap: wrap;
		justify-content: center;
		margin: 5px;
		margin-left: auto;
		margin-right: 0;
		
		@media (max-width: @xf-responsive)
	}
	
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
		font-size: inherit;
		color: inherit;
	}
}

.p-title-pageAction .button + .button {margin-left: @xf-paddingMedium;}

@media (max-width: @xf-responsiveNarrow)
{
	.p-title-value
	{
		font-size: @xf-fontSizeLarger;
	}
}';
	return $__finalCompiled;
});