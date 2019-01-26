<?php
// FROM HASH: 4743bd4355730b292f409179c7b48c8d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ########################## GLOBAL BASE SETUP #######################

html
{
	font: @xf-fontSizeNormal / @xf-lineHeightDefault sans-serif;
	font-family: @xf-fontFamilyUi;
	font-weight: @xf-fontWeightNormal;
	color: @xf-textColor;
	margin: 0;
	padding: 0;
	word-wrap: break-word;
	background-color: @xf-pageBg;

	/* // just a reminder that we *might* want this at some point
	-ms-text-size-adjust: none;
	-webkit-text-size-adjust: none;*/
}

button, input, optgroup, select, textarea
{
	font-family: @xf-fontFamilyUi;
	line-height: @xf-lineHeightDefault;
}

img
{
	max-width: 100%;
	height: auto;
}

a
{
	.xf-link();

	&:hover
	{
		.xf-linkHover();
	}
}

' . $__templater->includeTemplate('core_setup.less', $__vars) . '
' . $__templater->includeTemplate('core_utilities.less', $__vars) . '
' . $__templater->includeTemplate('core_list.less', $__vars) . '
' . $__templater->includeTemplate('core_categorylist.less', $__vars) . '
' . $__templater->includeTemplate('core_block.less', $__vars) . '
' . $__templater->includeTemplate('core_blockmessage.less', $__vars) . '
' . $__templater->includeTemplate('core_blockstatus.less', $__vars) . '
' . $__templater->includeTemplate('core_blocklink.less', $__vars) . '
' . $__templater->includeTemplate('core_blockend.less', $__vars) . '
' . $__templater->includeTemplate('core_fixedmessage.less', $__vars) . '
' . $__templater->includeTemplate('core_button.less', $__vars) . '

// ################################# INPUTS & FORMS #####################

.m-formElementExplain()
{
	display: block;
	font-style: normal;
	.xf-formExplain();

	.m-textColoredLinks();
}

' . $__templater->includeTemplate('core_input.less', $__vars) . '
' . $__templater->includeTemplate('core_formrow.less', $__vars) . '

' . $__templater->includeTemplate('core_collapse.less', $__vars) . '
' . $__templater->includeTemplate('core_badge.less', $__vars) . '
' . $__templater->includeTemplate('core_tooltip.less', $__vars) . '
' . $__templater->includeTemplate('core_menu.less', $__vars) . '
' . $__templater->includeTemplate('core_offcanvas.less', $__vars) . '
' . $__templater->includeTemplate('core_tab.less', $__vars) . '
' . $__templater->includeTemplate('core_overlay.less', $__vars) . '
' . $__templater->includeTemplate('core_globalaction.less', $__vars) . '
' . $__templater->includeTemplate('core_avatar.less', $__vars) . '
' . $__templater->includeTemplate('core_datalist.less', $__vars) . '
' . $__templater->includeTemplate('core_filter.less', $__vars) . '
' . $__templater->includeTemplate('core_contentrow.less', $__vars) . '
' . $__templater->includeTemplate('core_pagenav.less', $__vars) . '
' . $__templater->includeTemplate('core_hscroller.less', $__vars) . '

// FLASH MESSAGES
.flashMessage
{
	display: none;
	position: fixed;
	top: 0;
	left: 0;
	right: 0;
	padding: @xf-paddingLargest;
	font-size: @xf-fontSizeLargest;
	text-align: center;
	z-index: @zIndex-9;
	background: #e2e2e2;
	color: #202020;
	.m-dropShadow(0, 5px, 5px);

	.m-transitionFadeDown(@xf-animationSpeed);
}

// AUTOCOMPLETE
.autoCompleteList
{
	.m-autoCompleteList();
	margin-top: 2px;
}

// #################################### TAGS ##############################
// note that while this is related to tags, it\'s commonly used so just include it

.tagItem
{
	display: inline-block;
	max-width: 100%;
	padding: 0 6px 1px;
	margin: 0 0 2px;
	border-radius: @xf-borderRadiusMedium;
	font-size: @xf-fontSizeSmaller;
	.xf-chip();
	.xf-uix_tag();

	&:hover
	{
		text-decoration: none;
		color: @xf-chip--color;
		.xf-chipHover();
		.xf-uix_tagHover();
	}
}

// ############################# MISC #########################

.recaptcha
{
	&.input
	{
		box-sizing: content-box;
		max-width: 100%;
	}

	img
	{
		max-width: 100%;
	}
}

.likesBar
{
	.m-transitionFadeDown();
	.xf-minorBlockContent();
	border-left: @xf-borderSizeMinorFeature solid @xf-borderColorFeature;
	padding: @xf-paddingMedium;
	font-size: @xf-fontSizeSmaller;
	margin-top: @xf-paddingMedium;
	.xf-uix_messageLikes();
}

.likeIcon
{
	&:before
	{
		.m-faBase();
		.m-faContent(@fa-var-thumbs-o-up, 0.86em);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'like',
	), $__vars) . '
		color: @xf-textColorFeature;
		margin-right: .2em;
	}
}

// these are BB code rendering related, but they\'re very core and basic styles that may be used elsewhere.
.bbImage
{
	max-width: 100%;
}

.bbMediaWrapper
{
	width: 500px;
	max-width: 100%;
	margin: 0;
}

.bbMediaWrapper-inner
{
	position: relative;
	padding-bottom: 56.25%; /* 16:9 ratio */
	height: 0;

	&.bbMediaWrapper-inner--4to3
	{
		padding-bottom: 75%; /* 4:3 ratio */
	}

	&.bbMediaWrapper-inner--104px
	{
		padding-bottom: 104px;
	}
	&.bbMediaWrapper-inner--110px
	{
		padding-bottom: 110px;
	}
	&.bbMediaWrapper-inner--500px
	{
		padding-bottom: 500px;
	}

	iframe,
	object,
	embed,
	.bbMediaWrapper-fallback
	{
		position: absolute;
		top: 0;
		left: 0;
		width: 100%;
		height: 100%;
	}
}

.bbMediaWrapper-fallback
{
	display: flex;
	justify-content: center;
	align-items: center;
	max-width: 100%;
	.xf-minorBlockContent();
}

	.bbOembed
{
	margin: 0;
	max-width: 500px;
	&.bbOembed--loaded
	{
		display: block;
	}
	> :not(.embedly-card),
	.embedly-card-hug
	{
		/*width: auto !important;
		max-width: 500px !important;
		margin-left: 0 !important;
		margin-right: 0 !important;*/
	}
	.reddit-card
	{
		margin: 0;
	}
}

.colorChip
{
	display: inline-block;
	border: @xf-borderSize solid @xf-borderColor;
	border-radius: @xf-borderRadiusMedium;
	padding: 1px;
	width: 100px;
}
.colorChip-inner
{
	display: block;
	background-color: transparent;
	border-radius: @xf-borderRadiusSmall;
	height: 1em;
}
.colorChip-value
{
	display: none;
}

	pre.sf-dump
{
	// not ideal, but then again neither is the default of 99999...
	z-index: @zIndex-1 !important;
}

.grecaptcha-badge
{
	z-index: @zIndex-5;
}

' . $__templater->includeTemplate('core_action_bar.less', $__vars) . '
' . $__templater->includeTemplate('core_labels.less', $__vars) . '
' . $__templater->includeTemplate('core_pikaday.less', $__vars) . '
' . $__templater->includeTemplate('core_smilie.less', $__vars) . '
' . $__templater->includeTemplate('core_bbcode.less', $__vars) . '
' . $__templater->includeTemplate('core_fawidths.less', $__vars) . '

// RESOLUTION OUTPUT

.debugResolution
{
	font-size: @xf-fontSizeSmallest;
	.debugResolution-output:before
	{
		content: "Full @{xf-responsiveWide} - @{xf-pageWidthMax}";
		@media (min-width: @xf-pageWidthMax) { content: "Max > @{xf-pageWidthMax}"; }
		@media (max-width: @xf-responsiveWide) { content: "Wide < @{xf-responsiveWide}"; }
		@media (max-width: @xf-responsiveMedium) { content: "Medium < @{xf-responsiveMedium}"; }
		@media (max-width: @xf-responsiveNarrow) { content: "Narrow < @{xf-responsiveNarrow}"; }
	}
}' . $__templater->includeTemplate('core_xfrm.less', $__vars);
	return $__finalCompiled;
});