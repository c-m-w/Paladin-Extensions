<?php
// FROM HASH: 20cdd8b07a24e321462b21e2eabe2f32
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ############################ BUTTONS #################

.button,
a.button // needed for specificity over a:link
{
	.m-buttonBase();

	a
	{
		color: inherit;
		text-decoration: none;
	}

	&:hover,
	&:focus {
		.xf-uix_buttonHover();
	}

	&:active {
		.xf-uix_buttonActive();
	}

	.xf-buttonDefault();
	.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonDefault--background-color, transparent));

	&.button--primary
	{
		.xf-buttonPrimary();
		.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonPrimary--background-color, transparent));

		&:hover,
		&:focus {.xf-uix_buttonPrimaryHover();}

		&:active {.xf-uix_buttonPrimaryActive();}
	}

	&.button--cta
	{
		.xf-buttonCta();
		.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonCta--background-color, transparent));

		&:hover,
		&:focus {.xf-uix_buttonCtaHover();}

		&:active {.xf-uix_buttonCtaActive();}
	}

	&.button--link
	{
		// block colors
		// background: @xf-contentBg;
		// color: @xf-linkColor;
		// .m-buttonBorderColorVariation(@xf-borderColor);

		&:hover,
		&:focus
		{
			text-decoration: none;
			// background: @xf-contentHighlightBg;
			.xf-uix_buttonHover();
		}

		&:active {
			.xf-uix_buttonActive();
		}
	}
	
	&.button--longText
	{
		white-space: normal;
		text-align: left;
	}

	&.is-disabled
	{
		.xf-buttonDisabled();
		// .m-buttonBorderColorVariation(xf-default(@xf-buttonDisabled--background-color, transparent));

		&:hover,
		&:active,
		&:focus
		{
			.xf-buttonDisabled();
			// background: xf-default(@xf-buttonDisabled--background-color, transparent) !important;
		}
	}
	
	&.button--scroll
	{
		background: fade(xf-default(@xf-buttonDefault--background-color, transparent), 75%);
		padding: 5px 8px;
		.m-dropShadow();
	}

	&.button--small
	{
		font-size: @xf-fontSizeSmaller;
		padding: 3px 6px;
		.xf-uix_buttonSmall();
	}
	
	&.button--fullWidth
	{
		display: block;
	}


	&.button--icon
	{
		> .button-text:before
		{
			.m-faBase();
			// font-size: 120%;
			font-size: @xf-uix_iconSize;
			vertical-align: middle;
			display: inline-block;
			// margin: -.255em 6px -.255em 0;
			margin-right: .5em;
		}
		
		&.button--iconOnly > .button-text
		{
			&:before
			{
				margin: 0;
			}
		}		

		/*
		&--add          { .m-buttonIcon(@fa-var-plus-square, .79em) }
		&--confirm      { .m-buttonIcon(@fa-var-check, 1em); }
		&--write	    { .m-buttonIcon(@fa-var-pencil-square-o, 1em); }
		&--import  	    { .m-buttonIcon(@fa-var-upload, .93em); }
		&--export  	    { .m-buttonIcon(@fa-var-download, .93em); }
		&--download	    { .m-buttonIcon(@fa-var-download, .93em); }
		&--disable      { .m-buttonIcon(@fa-var-power-off); }
		&--edit         { .m-buttonIcon(@fa-var-pencil, .86em); }
		&--save         { .m-buttonIcon(@fa-var-save, .86em); }
		&--reply	    { .m-buttonIcon(@fa-var-mail-reply, 1em); }
		&--quote	    { .m-buttonIcon(@fa-var-quote-left, .93em); }
		&--purchase	    { .m-buttonIcon(@fa-var-credit-card, 1.11em); }
		&--payment	    { .m-buttonIcon(@fa-var-credit-card, 1.08em); }
		&--convert	    { .m-buttonIcon(@fa-var-flash, .5em); }
		&--search	    { .m-buttonIcon(@fa-var-search, .93em); }
		&--sort         { .m-buttonIcon(@fa-var-sort, .58em); }
		&--upload	    { .m-buttonIcon(@fa-var-upload, .93em); }
		&--attach	    { .m-buttonIcon(@fa-var-paperclip, .79em); }
		&--login        { .m-buttonIcon(@fa-var-lock, .65em); }
		&--rate         { .m-buttonIcon(@fa-var-star-half-empty, .93em); }
		&--config       { .m-buttonIcon(@fa-var-cog, .86em); }
		&--refresh      { .m-buttonIcon(@fa-var-refresh, .86em); }
		&--translate    { .m-buttonIcon(@fa-var-globe, .86em); }
		&--vote         { .m-buttonIcon(@fa-var-check-circle-o, .86em); }
		&--result       { .m-buttonIcon(@fa-var-bar-chart-o, 1.15em); }
		&--history	    { .m-buttonIcon(@fa-var-history, .86em); }
		&--cancel       { .m-buttonIcon(@fa-var-remove, .86em); }
		&--preview      { .m-buttonIcon(@fa-var-eye, 1em); }
		&--conversation { .m-buttonIcon(@fa-var-comments-o, 1em); }
		&--bolt         { .m-buttonIcon(@fa-var-bolt, .5em); }
		&--list         { .m-buttonIcon(@fa-var-list, .86em); }
		&--markRead     { .m-buttonIcon(@fa-var-check-square-o, .93em); }

		&--notificationsOn  { .m-buttonIcon(@fa-var-bell-o, 1em); }
		&--notificationsOff { .m-buttonIcon(@fa-var-bell-slash-o, 1.15em); }

		// for inline mod confirmations
		&--merge { .m-buttonIcon(@fa-var-compress, .86em); }
		&--move { .m-buttonIcon(@fa-var-share, 1em); }
		&--copy { .m-buttonIcon(@fa-var-clone, 1em); }
		&--approve, &--unapprove { .m-buttonIcon(@fa-var-shield, .72em); }
		&--delete, &--undelete { .m-buttonIcon(@fa-var-trash-o, .79em); }
		&--stick, &--unstick { .m-buttonIcon(@fa-var-thumb-tack, .65em); }
		&--lock { .m-buttonIcon(@fa-var-lock, .65em); }
		&--unlock { .m-buttonIcon(@fa-var-unlock, .93em); }
		*/

		&--add .button-text:before			{ .m-buttonIcon(@fa-var-plus-square, 0.79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'plus',
	), $__vars) . '} // fa-plus-square
		&--import .button-text:before		{ .m-buttonIcon(@fa-var-upload, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'import',
	), $__vars) . ' } // fa-upload
		&--export .button-text:before		{ .m-buttonIcon(@fa-var-download); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'export',
	), $__vars) . ' } // fa-download
		&--edit	.button-text:before			{ .m-buttonIcon(@fa-var-pencil, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'edit',
	), $__vars) . '} // fa-pencil
		&--save	.button-text:before			{ .m-buttonIcon(@fa-var-save, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'save',
	), $__vars) . ' } // fa-floppy-o
		&--delete .button-text:before		{ .m-buttonIcon(@fa-var-trash-o, 0.79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . ' } // fa-trash-o
		&--reply .button-text:before		{ .m-buttonIcon(@fa-var-mail-reply, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'reply',
	), $__vars) . '} // fa-reply
		&--quote .button-text:before		{ .m-buttonIcon(@fa-var-quote-left, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'quote',
	), $__vars) . '} // fa-quote-left
		&--purchase	.button-text:before		{ .m-buttonIcon(@fa-var-shopping-basket, 1.15em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'shopping-cart',
	), $__vars) . '} // fa-shopping-cart
		&--payment .button-text:before		{ .m-buttonIcon(@fa-var-credit-card, 1.08em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'payment',
	), $__vars) . '} // fa-credit-card
		&--convert .button-text:before		{ .m-buttonIcon(@fa-var-flash, 0.5em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'convert',
	), $__vars) . '} // fa-bolt
		&--search .button-text:before		{ .m-buttonIcon(@fa-var-search, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'search',
	), $__vars) . '} // fa-search
		&--sort .button-text:before			{ .m-buttonIcon(@fa-var-sort, 0.58em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'sort',
	), $__vars) . ' } // fa-sort
		&--upload .button-text:before		{ .m-buttonIcon(@fa-var-upload, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'upload',
	), $__vars) . '} // fa-upload
		&--attach .button-text:before		{ .m-buttonIcon(@fa-var-paperclip, 0.79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'attachment',
	), $__vars) . '} // fa-attachment
		&--login .button-text:before		{ .m-buttonIcon(@fa-var-lock, 0.65em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'login',
	), $__vars) . '} // fa-lock
		&--rate .button-text:before			{ .m-buttonIcon(@fa-var-star-half-empty, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'rate',
	), $__vars) . '} // fa-star-half-o
		&--config.button-text:before		{ .m-buttonIcon(@fa-var-cog, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'settings',
	), $__vars) . '} // fa-cog
		&--refresh .button-text:before		{ .m-buttonIcon(@fa-var-refresh, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'refresh',
	), $__vars) . '}
		&--translate .button-text:before   	{ .m-buttonIcon(@fa-var-globe, .86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'translate',
	), $__vars) . ' }
		&--vote .button-text:before        	{ .m-buttonIcon(@fa-var-check-circle-o, .86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'poll',
	), $__vars) . '}
		&--result .button-text:before      	{ .m-buttonIcon(@fa-var-bar-chart-o, 1.15em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'graph',
	), $__vars) . '}
		&--history.button-text:before	    { .m-buttonIcon(@fa-var-history, .86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'history',
	), $__vars) . '}
		&--cancel .button-text:before       { .m-buttonIcon(@fa-var-ban, .86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'close',
	), $__vars) . ' }
		&--preview .button-text:before     	{ .m-buttonIcon(@fa-var-eye, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'watched',
	), $__vars) . '}
		&--conversation .button-text:before	{ .m-buttonIcon(@fa-var-comments-o, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'message',
	), $__vars) . '}
		&--write .button-text:before	    { .m-buttonIcon(@fa-var-pencil-square-o, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'edit',
	), $__vars) . ' }
		&--download	.button-text:before    	{ .m-buttonIcon(@fa-var-download, .93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'download',
	), $__vars) . '}
		&--bolt .button-text:before	    	{ .m-buttonIcon(@fa-var-bolt, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'comment-alert',
	), $__vars) . ' }
		&--list	.button-text:before    		{ .m-buttonIcon(@fa-var-list, .93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'list',
	), $__vars) . '}
		&--confirm .button-text:before     { .m-buttonIcon(@fa-var-check, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'check',
	), $__vars) . '}
		&--disable .button-text:before     { .m-buttonIcon(@fa-var-power-off); }
		&--markRead .button-text:before    { .m-buttonIcon(@fa-var-check-square-o, .93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'check',
	), $__vars) . '}
		&--notificationsOn .button-text:before { .m-buttonIcon(@fa-var-bell-o, 1em); }
		&--notificationsOff .button-text:before { .m-buttonIcon(@fa-var-bell-slash-o, 1.15em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'alert-off',
	), $__vars) . '}
		&--merge .button-text:before { .m-buttonIcon(@fa-var-compress, .86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'merge',
	), $__vars) . '}
		&--move .button-text:before { .m-buttonIcon(@fa-var-share, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'move',
	), $__vars) . '}
		&--copy .button-text:before { .m-buttonIcon(@fa-var-clone, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'clone',
	), $__vars) . '}
		&--approve, &--unapprove .button-text:before { .m-buttonIcon(@fa-var-shield, .72em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'moderate',
	), $__vars) . '}
		&--delete .button-text:before, &--undelete .button-text:before { .m-buttonIcon(@fa-var-trash-o, .79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . '}
		&--stick .button-text:before, &--unstick .button-text:before { .m-buttonIcon(@fa-var-thumb-tack, .65em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'sticky',
	), $__vars) . '}
		&--lock .button-text:before { .m-buttonIcon(@fa-var-lock, .65em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'lock',
	), $__vars) . '}
		&--unlock .button-text:before { .m-buttonIcon(@fa-var-unlock, .93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'unlock',
	), $__vars) . '}
		

		/*
		&--login:hover::before,
		&--login:active::before
		{
			.m-faContent(@fa-var-unlock-alt, 0.65em);
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'unlock',
	), $__vars) . '
		}
		*/
	}

	&.button--provider
	{
		> .button-text:before
		{
			.m-faBase();
			font-size: 120%;
			vertical-align: middle;
			display: inline-block;
			margin: -4px 6px -4px 0;
		}

		&--facebook
		{
			.m-buttonColorVariation(#3B5998, white);
			> .button-text:before { .m-faContent(@fa-var-facebook, 0.58em);  ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'facebook',
	), $__vars) . '}
		}

		&--twitter
		{
			.m-buttonColorVariation(#1DA1F3, white);
			> .button-text:before { .m-faContent(@fa-var-twitter, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'twitter',
	), $__vars) . '}
		}

		&--google
		{
			.m-buttonColorVariation(#4285F4, white);
			> .button-text:before { .m-faContent(@fa-var-google, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'google-plus',
	), $__vars) . '}
		}

		&--github
		{
			.m-buttonColorVariation(#666666, white);
			> .button-text:before { .m-faContent(@fa-var-github, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'github',
	), $__vars) . '}
		}

		&--linkedin
		{
			.m-buttonColorVariation(#0077b5, white);
			> .button-text:before { .m-faContent(@fa-var-linkedin, 0.86em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'linkedin',
	), $__vars) . '}
		}

		&--microsoft
		{
			.m-buttonColorVariation(#00bcf2, white);
			> .button-text:before { .m-faContent(@fa-var-windows, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'microsoft',
	), $__vars) . '}
		}

		&--yahoo
		{
			.m-buttonColorVariation(#410093, white);
			> .button-text:before { .m-faContent(@fa-var-yahoo, 0.86em); }
		}
	}

	// button-text and button-menu are always children of button--splitTrigger
	// but are defined here for reasons of specificity, as these border colors
	// are overwritten by .m-buttonBorderColorVariation()

	> .button-text { border-right: @xf-borderSize solid transparent; }
	> .button-menu { border-left: @xf-borderSize solid transparent; }

	&.button--splitTrigger
	{
		.m-clearFix();
		padding: 0;
		font-size: 0;

		button.button-text
		{
			background: transparent;
			border: none;
			border-right: @xf-borderSize solid transparent;
			color: inherit;
		}

		> .button-text,
		> .button-menu
		{
			.xf-buttonBase();
			display: inline-block;

			&:hover
			{
				&:after
				{
					opacity: 1;
				}
			}
		}

		> .button-text
		{
			.m-borderRightRadius(0);
		}

		> .button-menu
		{
			.m-borderLeftRadius(0);
			padding-right: xf-default(@xf-buttonBase--padding-right, 0);// * (2/3);
			padding-left: xf-default(@xf-buttonBase--padding-left, 0);// * (2/3);

			&:after
			{
				.m-faBase();
				.m-faContent(@fa-var-caret-down, .58em);
				' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'menu-down',
	), $__vars) . '
				unicode-bidi: isolate;
				opacity: .5;
			}
		}
	}
}

.buttonGroup
{
	display: inline-block;
	vertical-align: top;
	.m-clearFix();

	&.buttonGroup--aligned
	{
		vertical-align: middle;
	}

	.button
	{
		float: left;

		&:not(:first-child)
		{
			border-left: none;
		}

		&:not(:first-child):not(:last-child)
		{
			border-radius: 0;
		}

		&:first-child:not(:last-child)
		{
			.m-borderRightRadius(0);
		}

		&:last-child:not(:first-child)
		{
			.m-borderLeftRadius(0);
		}
	}

	> .buttonGroup-buttonWrapper
	{
		float: left;

		&:not(:first-child) > .button
		{
			border-left: none;
		}

		&:not(:first-child):not(:last-child) > .button
		{
			border-radius: 0;
		}

		&:first-child:not(:last-child) > .button
		{
			.m-borderRightRadius(0);
		}

		&:last-child:not(:first-child) > .button
		{
			.m-borderLeftRadius(0);
		}
	}
}

.toggleButton
{
	> input
	{
		display: none;
	}

	> span
	{
		.xf-buttonDisabled();
		.m-buttonBorderColorVariation(xf-default(@xf-buttonDisabled--background-color, transparent));
	}

	&.toggleButton--small > span
	{
		font-size: @xf-fontSizeSmaller;
		padding: @xf-paddingSmall;
	}

	> input:checked + span
	{
		.xf-buttonDefault();
		.m-buttonBlockColorVariationSimple(xf-default(@xf-buttonDefault--background-color, transparent));
	}
}

.u-scrollButtons
{
	position: fixed;
	bottom: 30px;
	';
	if ($__templater->fn('property', array('uix_fab', ), false) == 'always') {
		$__finalCompiled .= '
		bottom: 100px;
	';
	} else if ($__templater->fn('property', array('uix_fab', ), false) == 'mobile') {
		$__finalCompiled .= '
		@media(max-width: ' . ($__templater->fn('property', array('uix_fabVw', ), false) - 1) . 'px ) {
			bottom: 100px;
		}
	';
	}
	$__finalCompiled .= '
	right: (@xf-pageEdgeSpacer) / 2;
	.has-hiddenscroll &
	{
		right: 20px;
	}
	z-index: @zIndex-9;
	.m-transition(opacity, @xf-animationSpeed);
	opacity: 0;
	display: none;
	&.is-transitioning
	{
		display: block;
	}
	&.is-active
	{
		display: block;
		opacity: 1;
	}
	.button
	{
		font-size: @xf-uix_iconSize;
		display: block;
		+ .button
		{
			margin-top: (@xf-pageEdgeSpacer) / 2;
		}
	}
}

.block-outer-opposite .button {
	.xf-uix_buttonSmall();
}';
	return $__finalCompiled;
});