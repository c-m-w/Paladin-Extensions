<?php
// FROM HASH: 480a786cc68f17d869e350cbad0ce551
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_message-actionColumnWidth: 40px;
@_messageSimple-userColumnWidth: 70px;

.message
{
	+ .message,
	&.message--bordered
	{
		border-top: @xf-borderSize solid @xf-borderColor;
	}
}

.message,
.block--messages .message
{
	&.is-mod-selected
	{
		background: @xf-inlineModHighlightColor;

		.message-userArrow:after
		{
			border-right-color: @xf-inlineModHighlightColor;
		}
	}
}

.message-inner
{
	display: flex;

	.has-no-flexbox &
	{
		display: table;
		table-layout: fixed;
		width: 100%;
	}
}

.message-cell
{
	display: block;
	vertical-align: top;
	padding: @xf-messagePadding;

	.has-no-flexbox &
	{
		display: table-cell;
	}

	.message--quickReply &
	{
		//padding-bottom: 35px; // for the submit row

		> .formRow:last-child
		{
			> dd
			{
				padding-bottom: 0;
			}
		}
	}

	&.message-cell--closer
	{
		padding: @xf-messagePaddingSmall;

		&.message-cell--main
		{
			padding-left: ((@xf-messagePaddingSmall) * 1.5);

		}

		&.message-cell--user
		{
			.m-fixedWidthFlex((@xf-messageUserBlockWidth) + 2 * (@xf-messagePaddingSmall));

			.message--simple &
			{
				.m-fixedWidthFlex(@_messageSimple-userColumnWidth + 2 * (@xf-messagePaddingSmall));
			}
		}

		&.message-cell--action
		{
			.m-fixedWidthFlex((@_message-actionColumnWidth) + 2 * (@xf-messagePaddingSmall));
		}
	}

	&.message-cell--user,
	&.message-cell--action
	{
		position: relative;
		.xf-messageUserBlock(no-border);
		border-right: @xf-messageUserBlock--border-width solid @xf-messageUserBlock--border-color;
		min-width: 0;
	}

	&.message-cell--user
	{
		.m-fixedWidthFlex((@xf-messageUserBlockWidth) + 2 * (@xf-messagePadding));

		.message--simple &
		{
			.m-fixedWidthFlex(@_messageSimple-userColumnWidth + 2 * @xf-messagePaddingSmall);
			// width: auto;
			// min-width: auto;
			background: none;
			border: none;
			padding-right: 0;
		}
	}

	&.message-cell--action
	{
		.m-fixedWidthFlex((@_message-actionColumnWidth) + 2 * (@xf-messagePadding));
	}

	&.message-cell--main
	{
		// padding-left: (@xf-messagePadding * 1.5);

		flex: 1 1 auto;
		width: 100%;
		display: flex;
		min-width: 0;
		.xf-uix_messageMain();

		&.is-editing
		{
			padding: 0;
		}

		.block
		{
			margin: 0;
		}

		.block-container
		{
			margin: 0;
			border: none;
		}
	}

	&.message-cell--alert
	{
		font-size: @xf-fontSizeSmall;
		flex: 1 1 auto;
		width: 100%;
		min-width: 0;
		.xf-contentAccentBase();

		a
		{
			.xf-contentAccentLink();
		}
	}
}

.message-main
{
	height: 100%;
	display: flex;
	flex-direction: column;
	width: 100%;
}

.message-content
{
	flex: 1 1 auto;

	// IE11 flex bug
	min-height: 1px;
	max-width: 100%;
}

.message-footer
{
	margin-top: auto;
}

form.message--simple .message-cell--main {
	flex-direction: column;
	padding: @xf-paddingLarge;
}

.message--quickReply .message-cell--main {
	flex-direction: column;
	padding: @xf-messagePadding;
}

@media (max-width: @xf-messageSingleColumnWidth)
{
	.message:not(.message--forceColumns)
	{
		.message-inner
		{
			display: block;
		}

		.message-cell
		{
			display: block;
			.m-clearFix();

			&.message-cell--user
			{
				width: auto;
				border-right: none;
				border-bottom: @xf-messageUserBlock--border-width solid @xf-messageUserBlock--border-color;
			}

			&.message-cell--main
			{
				// padding-left: @xf-messagePadding;
			}
		}
	}

	.message--simple:not(.message--forceColumns),
	.message--quickReply:not(.message--forceColumns)
	{
		.message-cell.message-cell--user
		{
			display: none;
		}
	}
}

// ######################## USER COLUMN #########################

.message-userArrow
{
	position: absolute;
	top: (@xf-messagePadding) * 2;
	right: -1px;

	.m-triangleLeft(xf-default(@xf-messageUserBlock--border-color, transparent), @xf-messagePadding);

	';
	if ($__templater->fn('property', array('uix_removeMessageArrow', ), false)) {
		$__finalCompiled .= '
	display: none;
	';
	}
	$__finalCompiled .= '

	&:after
	{
		position: absolute;
		top: -(@xf-messagePadding - 1px);
		right: -@xf-messagePadding;
		content: "";

		.m-triangleLeft(@xf-contentBg, @xf-messagePadding - 1px);
	}
}


.message-avatar
{
	text-align: center;
	margin-bottom: 3px;

	.avatar
	{
		vertical-align: bottom;
	}
}

.message-avatar-wrapper
{
	position: relative;
	display: inline-block;
	vertical-align: bottom;

	.message-avatar-online
	{
		position: absolute;
		top: -3px;
		left: -3px;

		// border: 7px solid transparent;
		// border-left-color: rgb(127, 185, 0);
		// border-top-color: rgb(127, 185, 0);
		// border-radius: (@xf-avatarBorderRadius + 1) max(0px, @xf-avatarBorderRadius - 1px) 0 max(0px, @xf-avatarBorderRadius - 1);
		height: 10px;
		width: 10px;
		background: rgb(127, 185, 0);
		border-radius: 100%;
	}
}

.message-name
{
	font-weight: @xf-fontWeightHeavy;
	font-size: inherit;
	text-align: center;
	margin: 0;
}

.message-userTitle
{
	font-size: @xf-fontSizeSmaller;
	font-weight: normal;
	text-align: center;
	margin: 0;
}

.message-userBanner.userBanner
{
	display: block;
	margin-top: 3px;
}

.message-userExtras
{
	// margin-top: 3px;
	font-size: @xf-fontSizeSmaller;

	';
	if ($__templater->fn('property', array('uix_postBitIcons', ), false)) {
		$__finalCompiled .= '
		dl.pairs dt:after {content:\'\';}

	.pairs {

		display: flex;
		align-items: center;

		i {font-size: 18px;}

		dd {
			min-width: 0;
			max-width: 100%;
			white-space: nowrap;
			overflow: hidden;
			text-overflow: ellipsis;
			text-align: left;
		}
	}


	';
	}
	$__finalCompiled .= '
}

.message--deleted
{
	.message-userDetails
	{
		display: none;
	}

	.message-avatar .avatar
	{
		.m-avatarSize(@avatar-s);
	}
}

.message-cell--user
{
	.message-date,
	.message-permalink
	{
		display: none;
	}
}

@media (max-width: @xf-messageSingleColumnWidth)
{

	.uix_messagePostBitWrapper {
		display: flex;
		flex-grow: 1;
		flex-direction: column;
		min-width: 0;
		max-width: 100%;
	}

	.message:not(.message--forceColumns)
	{
		.message-userArrow
		{
			top: auto;
			right: auto;
			bottom: -1px;
			left: ((@avatar-s) / 2);

			border: none;
			.m-triangleUp(xf-default(@xf-messageUserBlock--border-color, transparent), @xf-messagePadding);

			&:after
			{
				top: auto;
				right: auto;
				left: -(@xf-messagePadding - 1px);
				bottom: -@xf-messagePadding;

				border: none;
				.m-triangleUp(@xf-contentBg, @xf-messagePadding - 1px);
			}
		}

		&.is-mod-selected
		{
			.message-userArrow:after
			{
				border-color: transparent;
				border-bottom-color: @xf-inlineModHighlightColor;
			}
		}

		.message-user
		{
			display: flex;
			.has-no-flexbox &
			{
				display: table;
				width: 100%;
			}
		}

		.message-avatar
		{
			margin-bottom: 0;
			.has-no-flexbox &
			{
				display: table-cell;
				width: 1%;
			}

			.avatar
			{
				.m-avatarSize(@avatar-s);
			}
		}

		.message-userDetails
		{
			flex: 1;
			min-width: 0;
			padding-left: @xf-messagePadding;
			width: 100%;

			.has-no-flexbox &
			{
				display: table-cell;
			}
		}

		.message-userExtras {
			display: flex;
			flex-wrap: wrap;
			align-items: center;
			padding-left: @xf-messagePadding;
			padding-top: @xf-paddingSmall;

			.pairs {
				margin-right: @xf-paddingMedium;
				line-height: 1.3;
			}
		}

		.message-name
		{
			text-align: left;
		}

		.message-userTitle,
		.message-userBanner.userBanner
		{
			display: inline-block;
			text-align: left;
			margin: 0;
		}

		.message--deleted
		{
			.message-userDetails
			{
				display: block;
			}
		}
	}
}

// ####################### MAIN COLUMN ####################

.message-content
{
	position: relative;

	.js-selectToQuoteEnd
	{
		height: 0;
		font-size: 0;
		overflow: hidden;
	}

	.message--multiQuoteList &
	{
		min-height: 80px;
		max-height: 120px;
		overflow: hidden;

		.message-body
		{
			pointer-events: none;
		}
	}
}

.message-attribution
{
	color: @xf-textColorMuted;
	font-size: @xf-fontSizeSmaller;
	border-bottom: @xf-borderSize solid @xf-borderColorFaint;
	padding-bottom: 3px;
	// .m-clearFix();
	.xf-uix_messageMeta;

	&.message-attribution--plain
	{
		border-bottom: none;
		font-size: inherit;
		padding-bottom: 0;
	}
}

.message-attribution-main { float: left; }
.message-attribution-opposite { float: right; }

.message-attribution-source
{
	font-size: @xf-fontSizeSmaller;
	margin-bottom: @xf-paddingSmall;
}

.message-attribution-user
{
	font-weight: @xf-fontWeightHeavy;

	.avatar
	{
		display: none;
	}

	.attribution
	{
		display: inline;
		font-size: inherit;
		font-weight: inherit;
		margin: 0;
	}
}

.message-newIndicator
{
	.xf-messageNewIndicator();
}

.message-minorHighlight
{
	font-size: @xf-fontSizeSmall;
	color: @xf-textColorFeature;
}

.message-fields
{
	margin: @xf-messagePadding 0;
}

.message-body
{
	margin: @xf-messagePadding 0;
	font-family: @xf-fontFamilyBody;
	.xf-uix_messageBody();

	.message--simple &
	{
		margin-top: @xf-messagePaddingSmall;
		margin-bottom: @xf-messagePaddingSmall;
	}

	&:last-child
	{
		margin-bottom: 0;
	}
}

.message-attachments
{
	margin: .5em 0;
	.xf-uix_messageAttachments();
}

	.message-attachments-list
	{
		.m-listPlain();
	}

.message-lastEdit
{
	margin-top: .5em;
	color: @xf-textColorMuted;
	font-size: @xf-fontSizeSmallest;
	text-align: right;
	padding: 0 @xf-messagePadding @xf-messagePadding;
}

.message-signature
{
	margin-top: @xf-messagePadding;
	.xf-messageSignature();
}

.message-actionBar .actionBar-set
{
	// margin-top: @xf-messagePadding;
	font-size: @xf-fontSizeSmall;
	padding: calc( @xf-messagePadding / 2 );
	.message--simple &
	{
		margin-top: @xf-messagePaddingSmall;
	}
}

.message .likesBar
{
	// .xf-minorBlockContent();
	// font-size: @xf-fontSizeSmaller;
	margin-top: @xf-messagePadding;
	padding: @xf-messagePaddingSmall;
}

.message-historyTarget
{
	margin-top: @xf-messagePadding;
	.xf-uix_messageLikes();
}

.message-gradient
{
	position: absolute;
	bottom: 0;
	left: 0;
	right: 0;
	height: 60px;

	.m-gradient(fade(@xf-contentBg, 0%), @xf-contentBg, @xf-contentBg, 0%, 90%);
}

.message-responses
{
	// margin-top: @xf-messagePaddingSmall;
	margin-right: @xf-messagePadding;
	margin-left: @xf-messagePadding;
	font-size: @xf-fontSizeSmall;
}

.message-responseRow
{
	margin-top: -@xf-minorBlockContent--border-width;
	.xf-minorBlockContent();
	padding: @xf-messagePadding;
	margin-bottom: @xf-messagePadding;

	// note that border radiuses are very difficult to do here due to a lot of dynamic showing/hiding

	&.message-responseRow--likes
	{
		.m-transitionFadeDown();
	}
}



@media (max-width: @xf-messageSingleColumnWidth)
{
	.message:not(.message--forceColumns)
	{
		.message-attribution-user .avatar
		{
			display: inline-block;
			.m-avatarSize((@xf-fontSizeNormal) * (@xf-lineHeightDefault));
		}

		.message-content
		{
			// this is 1px to workaround an IE11 issue - see #139187
			min-height: 1px;
		}
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.message-signature
	{
		display: none;
	}
}

// MESSAGE MENU

.message-menuGroup
{
	display: inline-block;
}

.message-menuTrigger
{
	display: inline-block;

	&:after
	{
		.m-faBase();
		.m-faContent(@fa-var-caret-down, 1em);
		//font-size: 120%;
		text-align: right;
	}

	&:hover:after
	{
		color: black;
	}
}

.message-menu-section
{
	&--editDelete
	{
		.menu-linkRow
		{
			font-weight: @xf-fontWeightHeavy;
			font-size: @xf-fontSizeNormal;
		}
	}
}

.message-menu-link
{
	&--delete i:after
	{
		.m-faContent(@fa-var-trash-o);
	}
	&--edit i:after
	{
		.m-faContent(@fa-var-edit);
	}
	&--report i:after
	{
		.m-faContent(@fa-var-frown-o);
	}
	&--warn i:after
	{
		.m-faContent(@fa-var-warning);
	}
	&--spam i:after
	{
		.m-faContent(@fa-var-ban);
	}
	&--ip i:after
	{
		.m-faContent(@fa-var-sitemap);
	}
	&--history i:after
	{
		.m-faContent(@fa-var-history);
	}
	&--follow i:after
	{
		.m-faContent(@fa-var-user-plus);
	}
	&--ignore i:after
	{
		.m-faContent(@fa-var-user-times);
	}
	&--share i:after
	{
		.m-faContent(@fa-var-share-alt);
	}
}

// ############################# COMMENTS ###############

.comment
{
}

.comment-inner
{
	display: table;
	table-layout: fixed;
	width: 100%;
}

.comment-avatar
{
	display: table-cell;
	width: 24px;
	vertical-align: top;

	.avatar,
	img
	{
		vertical-align: bottom;
	}
}

.comment-main
{
	display: table-cell;
	padding-left: @xf-messagePadding;
	vertical-align: top;
}

.comment-contentWrapper
{
	margin-bottom: @xf-messagePaddingSmall;
}

.message-responses .comment-actionBar.actionBar {padding: 0;}

.message-responses .comment-actionBar .actionBar-set.actionBar-set--internal {padding: 0;}

.comment-user
{
	font-weight: @xf-fontWeightHeavy;
}

.comment-body
{
	display: inline;
}

.comment-input
{
	display: block;
	height: 2.34em;
	margin-bottom: @xf-messagePaddingSmall;
}

.comment-actionBar .actionBar-set
{
	// margin-top: @xf-messagePaddingSmall;
	color: @xf-textColorMuted;
}

.comment-likes
{
	.m-transitionFadeDown();

	margin-top: @xf-messagePaddingSmall;
	font-size: @xf-fontSizeSmaller;
}

// ######################### ACTION BAR #######################

.actionBar
{
	.m-clearFix();
	.xf-uix_messageActionBar();
}

.actionBar-set
{
	&.actionBar-set--internal
	{
		float: left;
		margin-left: -3px;

		> .actionBar-action:first-child
		{
			margin-left: 0;
		}
	}

	&.actionBar-set--external
	{
		float: right;
		margin-right: -3px;

		> .actionBar-action:last-child
		{
			margin-right: 0;
		}
	}
}

.actionBar-action
{
	padding: 3px;
	border: 1px solid transparent;
	border-radius: @xf-borderRadiusMedium;
	margin-left: 5px;
	.xf-uix_messageControl();

	&:hover {
		.xf-uix_messageControlHover();
	}

	&:before
	{
		.m-faBase();
		font-size: 12px;
		padding-right: 2px;
	}

	&.actionBar-action--menuTrigger
	{
		display: none;

		&:after
		{
			.m-faBase();
			.m-faContent(" @{fa-var-caret-down}");
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'menu-down',
	), $__vars) . '
		}
	}

	&.actionBar-action--inlineMod input
	{
		.m-checkboxAligner();
		margin: 0;
	}

	&.actionBar-action--mq
	{
		&:before { .m-faContent("@{fa-var-plus}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'quote',
	), $__vars) . ' } // plus

		&.is-selected
		{
			background-color: @xf-contentHighlightBg;
			border-color: @xf-borderColorHighlight;

			&:before { .m-faContent("@{fa-var-minus}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'quote',
	), $__vars) . '} // minus
		}
	}

	&.actionBar-action--reply:before { .m-faContent("@{fa-var-reply}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'reply',
	), $__vars) . '} // reply
	&.actionBar-action--like:before { .m-faContent("@{fa-var-thumbs-o-up}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'like',
	), $__vars) . '}
	&.actionBar-action--like.unlike:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'unlike',
	), $__vars) . '}// thumbs up
	&.actionBar-action--report:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'report',
	), $__vars) . '}
	&.actionBar-action--delete:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . '}
	&.actionBar-action--edit:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'edit',
	), $__vars) . '}
	&.actionBar-action--ip:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'ipaddress',
	), $__vars) . '}
	&.actionBar-action--history:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'history',
	), $__vars) . '}
	&.actionBar-action--warn:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'warn',
	), $__vars) . '}
	&.actionBar-action--spam:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'spam',
	), $__vars) . '}
}

@media (max-width: @xf-responsiveNarrow)
{
	.actionBar-action
	{
		&.actionBar-action--menuItem
		{
			display: none !important;
		}

		&.actionBar-action--menuTrigger
		{
			display: inline;
		}
	}
}

// ################################## MESSAGE QUICK REPLY ADDITIONS #############

.formSubmitRow.formSubmitRow--messageQr
{
	.formSubmitRow-controls
	{
		text-align: center;
		padding-left: 0;
		padding-right: 0;
		margin-left: @xf-messagePadding;
		margin-right: @xf-messagePadding;

		@media (max-width: @xf-formResponsive)
		{
			text-align: right;
		}

		.menu & {text-align: right;}
	}
}

// ################################## MESSAGE NOTICES #############################

.messageNotice
{
	margin: @xf-messagePaddingSmall 0;
	padding: @xf-messagePaddingSmall @xf-messagePadding;
	.xf-contentAccentBase();
	font-size: @xf-fontSizeSmaller;
	border-left: @xf-borderSizeMinorFeature solid @xf-borderColorAttention;
	.xf-uix_messageNotice();

	a,
	a:hover
	{
		.xf-contentAccentLink();
	}

	&:first-child
	{
		margin-top: 0;
	}

	&:before
	{
		display: inline-block;
		.m-faBase();
		padding-right: .2em;
		font-size: 125%;
		color: @xf-textColorAttention;
		vertical-align: middle;
	}

	&.messageNotice--deleted:before { .m-faContent(@fa-var-trash, .79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . '}
	&.messageNotice--moderated:before { .m-faContent(@fa-var-shield, .72em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'moderate',
	), $__vars) . '}
	&.messageNotice--warning:before { .m-faContent(@fa-var-warning, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'warning',
	), $__vars) . '}
	&.messageNotice--ignored:before { .m-faContent(@fa-var-microphone-slash, .79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'ignored',
	), $__vars) . '}
}

// ##################### MESSAGE VARIANTS/RESPONSIVE ##################

@media (min-width: @xf-responsiveEdgeSpacerRemoval)
{
	.block:not(.block--messages)
	{
		@{block-noStripSel} > .block-body:first-child > .message:first-child,
		.block-topRadiusContent.message,
		.block-topRadiusContent > .message:first-child
		{
			.message-cell:first-child { border-top-left-radius: @block-borderRadius-inner; }
			.message-cell:last-child { border-top-right-radius: @block-borderRadius-inner; }
		}

		@{block-noStripSel} > .block-body:last-child > .message:last-child,
		.block-bottomRadiusContent.message,
		.block-bottomRadiusContent > .message:last-child
		{
			.message-cell:first-child { border-bottom-left-radius: @block-borderRadius-inner; }
			.message-cell:last-child { border-bottom-right-radius: @block-borderRadius-inner; }
		}
	}
}

.block--messages
{
	.block-container
	{
		background: none;
		border: none;
		box-shadow: none;
		border-radius: 0;
		overflow: visible;
	}

	.message,
	.block-row
	{
		.xf-contentBase();
		.xf-blockBorder();
		border-radius: @xf-blockBorderRadius;

		.xf-uix_message();

		+ .message,
		+ .block-row
		{
			margin-top: @xf-blockPaddingV;
		}
	}

	.message-cell
	{
		&:first-child
		{
			border-radius: 0;
			border-top-left-radius: @block-borderRadius-inner;
			border-bottom-left-radius: @block-borderRadius-inner;
		}

		&:last-child
		{
			border-radius: 0;
			border-top-right-radius: @block-borderRadius-inner;
			border-bottom-right-radius: @block-borderRadius-inner;
		}

		&:first-child:last-child
		{
			border-radius: @block-borderRadius-inner;
		}
	}

	@media (max-width: @xf-messageSingleColumnWidth)
	{
		.message:not(.message--forceColumns)
		{
			.message-cell
			{
				&:first-child
				{
					border-radius: 0;
					border-top-left-radius: @block-borderRadius-inner;
					border-top-right-radius: @block-borderRadius-inner;
				}

				&:last-child
				{
					border-radius: 0;
					border-bottom-left-radius: @block-borderRadius-inner;
					border-bottom-right-radius: @block-borderRadius-inner;
				}

				&:first-child:last-child
				{
					border-radius: @block-borderRadius-inner;
				}
			}
		}

		.message--simple:not(.message--forceColumns) .message-cell--user + .message-cell
		{
			border-radius: 0;
			border-top-left-radius: @block-borderRadius-inner;
			border-top-right-radius: @block-borderRadius-inner;
		}
	}

	@media (max-width: @xf-responsiveEdgeSpacerRemoval)
	{
		.message,
		.block-row
		{
			border-left: none;
			border-right: none;
			border-radius: 0;
		}

		.message-cell
		{
			border-radius: 0;

			&:first-child,
			&:last-child
			{
				border-radius: 0;
			}
		}

		.message--simple .message-cell--user + .message-cell
		{
			border-radius: 0;
		}
	}
}';
	return $__finalCompiled;
});