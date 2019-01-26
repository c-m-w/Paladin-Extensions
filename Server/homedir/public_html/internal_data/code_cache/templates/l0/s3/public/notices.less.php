<?php
// FROM HASH: ba5ab49ab7ca03d400b442ff70f74467
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_notice-darkBg: @xf-paletteColor4;
@_notice-lightBg: #fff;
@_notice-floatingFade: 80%;
@_notice-imageSize: 48px;
@_notice-padding: @xf-paddingLarge;

.notices
{
	.m-listPlain();

	&.notices--block
	{
		.notice
		{
			margin-bottom: @xf-elementSpacer;
		}
	}

	&.notices--floating
	{
		// assumed to be within u-bottomFixer
		margin: 0 20px 0 auto;
		width: 300px;
		max-width: 100%;
		z-index: @zIndex-8;

		@media (max-width: 340px)
		{
			margin-right: 10px;
		}

		.notice
		{
			margin-bottom: 20px;
		}
	}
	
	.uix_noticeInner {
		display: flex;
	}
	
	.uix_noticeIcon {
		display: flex;
		align-items: center;
		padding: 0 8px;
		color: rgba(255,255,255,.5);
		font-size: 24px;
	}

	&.notices--scrolling
	{
		display: flex;
		align-items: stretch;
		overflow: hidden;
		.xf-blockBorder();
		margin-bottom: ((@xf-elementSpacer) / 2);

		&.notices--isMulti
		{
			margin-bottom: ((@xf-elementSpacer) / 2) + 20px;
		}

		.notice
		{
			width: 100%;
			flex-grow: 0;
			flex-shrink: 0;
			border: none;
			box-shadow: none;
		}

		.has-no-flexbox &
		{
			display: block;
			white-space: nowrap;
			word-wrap: normal;

			.notice
			{
				display: inline-block;
				vertical-align: top;
			}
		}
	}
}

.noticeScrollContainer
{
	margin-bottom: ((@xf-elementSpacer) / 2);
	
	box-shadow: @xf-uix_elevation1;
	';
	if ($__templater->fn('property', array('uix_similarScrollNotice', ), false)) {
		$__finalCompiled .= '
		border: 2px solid @xf-uix_primaryColor;
	';
	}
	$__finalCompiled .= '

	.lSSlideWrapper
	{
		.xf-blockBorder();
	}

	.notices.notices--scrolling
	{
		border: none;
		margin-bottom: 0;
	}
	
	';
	if ($__templater->fn('property', array('uix_similarScrollNotice', ), false)) {
		$__finalCompiled .= '
	.notice {
		&.notice--primary,
		&.notice--accent,
		&.notice--dark,
		&.notice--light {.xf-contentBase();}
		
		a {color: @xf-linkColor;}
	}
	';
	}
	$__finalCompiled .= '
	
	.lSPager {.xf-contentBase();}
}

.notice
{
	.m-clearFix();
	position: relative;

	.xf-blockBorder();
	.xf-contentBase();
	border: 2px solid @xf-borderColor;

	&.notice--primary
	{
		.xf-contentBase();
		border: 2px solid @xf-uix_primaryColor;
		
		.uix_noticeIcon {background: @xf-uix_primaryColor;}
	}

	&.notice--accent
	{
		border: 2px solid @xf-uix_secondaryColor;
		
		.uix_noticeIcon {background: @xf-uix_secondaryColor;}

		a
		{
			.xf-contentAccentLink();
		}
	}

	&.notice--dark
	{
		color: @xf-textColor;
		//background: @_notice-darkBg;
		background: @xf-uix_primaryColor;
		color: #fff;
		border-color: lighten(@xf-uix_primaryColor, 30%);

		a
		{
			color: @xf-linkColor;
		}
	}

	&.notice--light
	{
		color: rgb(20, 20, 20);
		background: @_notice-lightBg;
		
		.uix_noticeIcon {background: @xf-borderColor; color: @xf-textColorMuted;}

		a
		{
			color: rgb(130, 130, 130);
		}
	}

	.notices--block &
	{
		font-size: @xf-fontSizeNormal;
		border-radius: @xf-blockBorderRadius;
	}

	.notices--floating &
	{
		font-size: @xf-fontSizeSmallest;
		border-radius: @xf-borderRadiusMedium;
		box-shadow: @xf-uix_elevation1;

		&.notice--primary
		{
			background-color: fade(@xf-contentHighlightBase--background-color, @_notice-floatingFade);
		}

		&.notice--accent
		{
			background-color: fade(@xf-contentAccentBase--background-color, @_notice-floatingFade);
		}

		&.notice--dark
		{
			background-color: fade(@_notice-darkBg, @_notice-floatingFade);
		}

		&.notice--light
		{
			background-color: fade(@_notice-lightBg, @_notice-floatingFade);
		}

		.has-no-js &
		{
			display: none;
		}
	}

	&.notice--hasImage
	{
		.notice-content
		{
			min-height: ((@_notice-imageSize) + (@_notice-padding) * 2);
		}
	}

	@media (max-width: @xf-responsiveWide)
	{
		&.notice--hidewide:not(.is-vis-processed)
		{
			display: none;
		}
	}
	@media (max-width: @xf-responsiveMedium)
	{
		&.notice--hidemedium:not(.is-vis-processed)
		{
			display: none;
		}
	}
	@media (max-width: @xf-responsiveNarrow)
	{
		&.notice--hidenarrow:not(.is-vis-processed)
		{
			display: none;
		}
	}
}

.notice-image
{
	float: left;
	padding: @_notice-padding 0 @_notice-padding @_notice-padding;

	img
	{
		max-width: @_notice-imageSize;
		max-height: @_notice-imageSize;
	}
}

.notice-content
{
	padding: @_notice-padding;
	flex-grow: 1;
	color: @xf-textColorDimmed;

	a.notice-dismiss
	{
		&:before
		{
			.m-faBase();

			.m-faContent(@fa-var-remove, .79em);
		}

		float: right;

		color: inherit;
		font-size: 16px;
		line-height: 1;
		height: 1em;
		box-sizing: content-box;
		padding: 0 0 5px 5px;

		opacity: .5;
		.m-transition(opacity);

		cursor: pointer;

		&:hover
		{
			text-decoration: none;
			opacity: 1;
		}

		.notices--floating &
		{
			font-size: 14px;
		}
	}
}';
	return $__finalCompiled;
});