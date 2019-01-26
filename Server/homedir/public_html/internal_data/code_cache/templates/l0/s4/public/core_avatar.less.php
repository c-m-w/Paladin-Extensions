<?php
// FROM HASH: 982ab02f49724fa548a654d1c377041b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ################################### AVATARS #############################

.m-uix_avatarShape() {
	';
	if ($__templater->fn('property', array('uix_avatarShape', ), false) == 1) {
		$__finalCompiled .= '
		border-radius: 100%;
	';
	} else if ($__templater->fn('property', array('uix_avatarShape', ), false) == 2) {
		$__finalCompiled .= '
		border-radius: 0;
	';
	} else if ($__templater->fn('property', array('uix_avatarShape', ), false) == 3) {
		$__finalCompiled .= '
		-webkit-clip-path: polygon(50% 0, 100% 50%, 50% 100%, 0 50%);
		clip-path: polygon(50% 0, 100% 50%, 50% 100%, 0 50%);
	';
	} else if ($__templater->fn('property', array('uix_avatarShape', ), false) == 4) {
		$__finalCompiled .= '
		-webkit-clip-path: polygon(50% 0, 100% 38%, 80% 100%, 20% 100%, 0 38%);
		clip-path: polygon(50% 0, 100% 38%, 80% 100%, 20% 100%, 0 38%);
	';
	} else if ($__templater->fn('property', array('uix_avatarShape', ), false) == 5) {
		$__finalCompiled .= '
		-webkit-clip-path: polygon(50% 0, 95% 25%, 95% 75%, 50% 100%, 5% 75%, 5% 25%);
		clip-path: polygon(50% 0, 95% 25%, 95% 75%, 50% 100%, 5% 75%, 5% 25%);
	';
	} else if ($__templater->fn('property', array('uix_avatarShape', ), false) == 6) {
		$__finalCompiled .= '
		-webkit-clip-path: polygon(0 50%, 15% 15%, 50% 0, 85% 15%, 100% 50%, 85% 85%, 50% 100%, 15% 85%);
		clip-path: polygon(0 50%, 15% 15%, 50% 0, 85% 15%, 100% 50%, 85% 85%, 50% 100%, 15% 85%);
	';
	}
	$__finalCompiled .= '
}

.avatar
{
	// display: inline-block;
	border-radius: @xf-avatarBorderRadius;
	vertical-align: top;
	overflow: hidden;
	display: inline-flex;
	align-items: center;
	justify-content: center;
	line-height: 1;
	.m-uix_avatarShape();

	img { background-color: @xf-avatarBg; }

	&.avatar--default
	{
		&.avatar--default--dynamic,
		&.avatar--default--text
		{
			font-family: @xf-avatarDynamicFont;
			font-weight: normal;
			text-align: center;
			text-decoration: none !important;

			// converts our avatar sized LH to a font sized version which adapts based solely on font-size
			line-height: (@xf-avatarDynamicLineHeight) / ((@xf-avatarDynamicTextPercent) / 100);

			-webkit-user-select: none;
			-moz-user-select: none;
			-ms-user-select: none;
			user-select: none;
			
		}

		&.avatar--default--text
		{
			color: @xf-textColorMuted !important;
			background: mix(@xf-textColorMuted, @xf-avatarBg, 25%) !important;
			> span:before { content: ~"\'@{xf-avatarDefaultTextContent}\'"; }
		}

		&.avatar--default--image
		{
			background-color: @xf-avatarBg;
			background-image: url(@xf-avatarDefaultImage);
			background-size: cover;
			> span { display: none; }
		}
	}

	&:hover
	{
		text-decoration: none;
	}

	&.avatar--updateLink
	{
		position: relative;
	}

	&.avatar--separated
	{
		border: 1px solid @xf-avatarBg;
	}

	&.avatar--xxs
	{
		.m-avatarSize(@avatar-xxs);
	}

	&.avatar--xs
	{
		.m-avatarSize(@avatar-xs);
	}

	&.avatar--s
	{
		.m-avatarSize(@avatar-s);
	}

	&.avatar--m
	{
		.m-avatarSize(@avatar-m);
	}

	&.avatar--l
	{
		.m-avatarSize(@avatar-l);
	}

	&.avatar--o
	{
		.m-avatarSize(@avatar-o);
	}

	img:not(.cropImage)
	{
		.m-hideText;
		display: block;
		border-radius: inherit;
		width: 100%;
		height: 100%;
	}

	&:not(a)
	{
		cursor: default;
	}
}

.avatar-update
{
	width: 100%;
	height: 30px;
	bottom: -30px;
	position: absolute;

	.m-hiddenLinks();
	.m-gradient(rgba(0, 0, 0, 0), rgba(0, 0, 0, 0.3), #000);
	.m-transition();

	padding: @xf-paddingSmall;
	overflow: hidden;

	font-size: @xf-fontSizeSmaller;

	display: none;
	align-items: flex-end;
	justify-content: center;

	.avatar--updateLink &
	{
		display: flex;
	}

	.has-no-flexbox &
	{
		display: table;
		width: 100%;
	}

	.has-touchevents &,
	.avatar:hover &
	{
		bottom: 0;
	}

	a
	{
		text-shadow: 0 0 2px rgba(0, 0, 0, 0.6);
		color: #fff;

		&:hover
		{
			text-decoration: none;
		}
	}
}';
	return $__finalCompiled;
});