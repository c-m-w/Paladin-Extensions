<?php
// FROM HASH: e8e80eb3e74f5df210ca77ea0b4d0c87
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// #################################### OVERLAYS ################################

.overlay-container
{
	display: none;
	position: fixed;
	top: 0;
	bottom: 0;
	left: 0;
	right: 0;
	z-index: @zIndex-6;
	background: @xf-overlayMaskColor;
	-webkit-overflow-scrolling: touch;
	opacity: 0;
	.m-transition(opacity);
	
	@media (max-width: @xf-responsiveNarrow) {
		transition: transform ease-in .25s;
		transform: translatey(100%);
		display: block;
		opacity: 1;
		
		.overlay-title {
			position: sticky;
			top: 0;
		}
	}

	&.is-transitioning
	{
		display: block;
	}

	&.is-active
	{
		display: block;
		opacity: 1;
		@media (max-width: @xf-responsiveNarrow) {
			transform: translatey(0);
		}
	}
}

.overlay
{
	position: relative;
	margin: 40px auto 10px;
	margin-top: @xf-overlayTopMargin;
	width: 100%;
	max-width: 800px;
	background: @xf-contentBg;
	color: @xf-textColor;
	.xf-blockBorder();
	border-radius: @xf-blockBorderRadius;
	.m-dropShadow(0, 5px, 15px, 0, .5);
	outline: none;

	> .overlay-title:first-child,
	.overlay-firstChild
	{
		border-top-left-radius: @xf-blockBorderRadius;
		border-top-right-radius: @xf-blockBorderRadius;
	}

	> .overlay-content > *:last-child,
	.overlay-lastChild
	{
		border-bottom-left-radius: @xf-blockBorderRadius;
		border-bottom-right-radius: @xf-blockBorderRadius;
	}
	
	.block-container {box-shadow: none;}
}

@media (max-width: @xf-responsiveWide)
{
	.overlay
	{
		max-width: ~"calc(100% - 20px)";
		max-width: ~"calc(100% - env(safe-area-inset-left) - env(safe-area-inset-right))";
	}
}

@media (max-width: @xf-responsiveNarrow) {
	.overlay {
		max-width: 100%;
		margin: 0;
		height: 100vh;
		border-radius: 0;
	}
}

.overlay-title
{
	.m-clearFix();

	display: none;
	margin: 0;
	font-weight: @xf-fontWeightNormal;
	.xf-overlayHeader();

	.overlay &
	{
		display: block;
	}
}

.overlay-titleCloser
{
	float: right;
	cursor: pointer;
	margin-left: 5px;
	text-decoration: none;
	// opacity: .5;
	.m-transition();

	&:after
	{
		.m-faBase();
		.m-faContent(@fa-var-close, 0.79em);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'close',
	), $__vars) . '
	}

	&:hover
	{
		text-decoration: none;
		opacity: 1;
	}
}

.overlay-content
{
	.m-clearFix();
}

// when displaying a modal, prevent scrolling on the main content but allow it on the overlay
body.is-modalOpen
{
	overflow: hidden !important;

	.overlay-container,
	.offCanvasMenu
	{
		overflow-y: scroll !important;
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.overlay-title
	{
		font-size: @xf-fontSizeLarger;
	}
}

// ############################### OVERLAY/BLOCK NESTING ##############################

.block-container > .tabPanes > li,
.block-container > .block-body,
.block-container > .block-body > .block-row,
.overlay-content
{
	> .blocks > .block > .block-container,
	> .block > .block-container,
	> .blockMessage
	{
		margin-left: 0;
		margin-right: 0;
		border-left: none;
		border-right: none;
	}

	> .blocks > .block:first-child,
	> .block:first-child,
	> .blockMessage:first-child
	{
		margin-top: 0;

		.block-outer:not(.block-outer--after)
		{
			border-bottom: @xf-borderSize solid @xf-borderColorLight;
			padding: @xf-blockPaddingV;
		}
	}

	> .blocks > .block:last-child,
	> .block:last-child,
	> .blockMessage:last-child
	{
		margin-bottom: 0;

		.block-outer.block-outer--after
		{
			border-top: @xf-borderSize solid @xf-borderColorLight;
			padding: @xf-blockPaddingV;
		}
	}

	> .blocks > .block:first-child > .block-container,
	> .block:first-child > .block-container,
	> .blockMessage:first-child
	{
		border-top: none;
	}

	> .blocks > .block:last-child > .block-container,
	> .block:last-child > .block-container,
	> .blockMessage:last-child
	{
		border-bottom: none;
	}

	> .block:not(:first-child) > .block-container,
	> .blockMessage:not(:first-child)
	{
		.m-borderTopRadius(0);
	}

	> .blocks > .block:not(:last-child) > .block-container,
	> .block:not(:last-child) > .block-container,
	> .blockMessage:not(:last-child)
	{
		.m-borderBottomRadius(0);
	}
}';
	return $__finalCompiled;
});