<?php
// FROM HASH: 0d587052e77fb7c7381d59b50436478b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '
.p-body {
	-webkit-backface-visibility: hidden;
	backface-visibility: hidden;
 }

.modify_reacts {
	margin:  4px 0 4px 10px;
	display: inline-block;
}

.th_reactions__triggerSecondary {
	margin-left: 10px;
}

.th_reactions__triggerPrimary img {
	pointer-events: none;
}

.reactions-bar
{
	.m-clearFix();

	display: flex;
	align-items: center;
	justify-content: space-between;
	margin: 10px 0;
}

.reactions-bar.content
{
	margin: 0;
	.xf-th_reactions__barStyle();
	padding-top: 0;
	padding-bottom: 0;
}
.reactions-bar.bit-list
{
	float: right;
	margin: 0;

	.reactions-left {
		margin-right: -5px;
		
		.th_reactions__listItem {
			// transform: scale(.75);

			img {height: 14px; width: 14px;}
		}
	}
}

.structItem-minor {
	// clear: both;
}

.reactions-bar ul
{
	padding: 0px;
	margin: 0px;

	list-style-type: none;

	display: inline-flex;
	align-items: center;
}

.reactions-left > ul { flex-wrap: wrap; }

.structItem .reactions-bar {
	margin-top: 0;
	font-size: 12px;
	margin-left: 5px;
	
	ul {max-height: 21px;}
	
	.reactions-left .th_reactions__listItem {line-height: 16px;}
}

.reactions-bar li
{
	display: flex;
	align-items: inherit;

	img {
		vertical-align: middle;
		height: 18px;
	}

}

.th_reactions__reaction {
	flex: 0 0 auto;
}

.reactions-bar .reactions-left
{
	.m-clearFix();

	margin-right: auto;
	display: flex;
	justify-items: left;

	.th_reactions__listItem
	{
		margin-right: 5px;

		.xf-th_reactions__listItemStyle();

		span {
			padding: 2px;
			vertical-align: middle;
		}

		.reaction-count {
			.xf-th_reactions__listItemRightStyle();
		}
	}
}

.reactions-bar .reactions-right
{
	.m-clearFix();

	margin-left: auto;
	display: flex;
	justify-items: right;
	align-items: center;

	li
	{
		padding-left: 5px;
	}
}

.unreact-link {
	height: 42px;
	line-height: 42px;
}

.th_reactions__trigger {
	cursor: pointer;
	-webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
	.xf-th_reactions__triggerStyle();

	.th_reactions__trigger__image {
		.xf-th_triggerImageStyling_reactions();
	}

	svg path {
		fill: @xf-th_reactions__triggerStyle--color;
	}

	span {
		display: flex;
		align-items: center;
	}

	/*
	&:hover {
		transform: scale(1, 1);
		animation-name: th_reactions_triggerHover;
		animation-duration: 0.3s;
		animation-direction: normal;
		animation-fill-mode: both;
	}
	&--hoverOut {
		//transform: scale(1.2, 1.2);
		animation-name: th_reactions_triggerHover;
		animation-duration: 0.3s;
		animation-direction: reverse;
		animation-fill-mode: both;
	}
	*/
}

.reactions-bar .list-reactions
{

}

.reacts_total_text .reacts_total_text__reactionType:after,
.reacts_total_perc .reacts_total_perc__reactionType:after
{
	content: "|";
	padding-left: 2px;
	color: @xf-textColor;
}

.reacts_total_text .reacts_total_text__reactionType:last-child:after,
.reacts_total_perc .reacts_total_perc__reactionType:last-child:after
{
	content: "";
}

.react-modify .menu-row
{
	padding: 0;
	margin: 0;
}

.reactions-bar a
{
	text-decoration: none;
	white-space: nowrap;
}

.reaction
{
	display: flex;
	max-width: none;
	display: inline-block;
    vertical-align: middle;
}

.reaction-item
{
	display: flex;
	align-items: center;

	.reaction-title
	{
		padding-left: 5px;
	}
}

/* Handling display for specific classes */
.reaction.alert img,
.reaction.bit-list img
{
	max-width: 20px;
	vertical-align: middle;
}

.reaction.newsfeed img,
.reaction.list img,
{
	max-width: 20px;
	vertical-align: sub;
}

.react_total_bar
{
	padding: 0;
	margin: 0;

	width: 100%;
	display: flex;
	height: 16px;

	border-radius: @xf-borderRadiusSmall;
	overflow: hidden;

	display: flex;

	.react_bar_segment
	{
		display: inline-block;
		height: inherit;
		min-width: 3px;
	}

	&--top {
		margin-top: @xf-paddingSmall;
	}
}

.overlay-content .react_total_bar {border-radius: 0 !important;}

.reactOverviewBlocks
{
	.m-listPlain();

	display: flex;
	flex-wrap: wrap;
	align-items: stretch;

	> li
	{
		.has-no-flexbox &
		{
			display: inline-block;
			vertical-align: top;
		}

		width: 33.3%;
		max-width: 100%;
		padding: @xf-blockPaddingV @xf-blockPaddingH;

		@media (max-width: 1150px)
		{
			width: 50%;
		}

		@media (max-width: 580px)
		{
			width: 100%;
		}
	}
}

.reactOverviewBlock
{
	display: flex;
	flex-direction: column;
}
.has-no-touchevents .reactOverviewBlock .reactOverviewBlock-list li
{
	.contentRow-extra
	{
		opacity: 0;
	}

	&:hover .contentRow-extra
	{
		opacity: 1;
	}
}

.reactOverviewBlock-list
{
	.m-listPlain();

	> li
	{
		margin: @xf-paddingMedium 0;
	}
}

';
	if ($__vars['reactions']) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = $__vars['reactions'];
		if ($__templater->isTraversable($__compilerTemp1)) {
			foreach ($__compilerTemp1 AS $__vars['reactionId'] => $__vars['reaction']) {
				$__finalCompiled .= '
		';
				if ($__vars['reaction']['styling_type'] == 'image') {
					$__finalCompiled .= '
			';
					if (($__vars['reaction']['image_type'] == 'sprite') AND $__vars['reaction']['image_sprite_css']) {
						$__finalCompiled .= '
				.reaction--sprite.reaction--sprite' . $__templater->escape($__vars['reactionId']) . '
				{
					' . $__templater->filter($__vars['reaction']['image_sprite_css'], array(array('raw', array()),), true) . '
				}
			';
					} else if (($__vars['reaction']['image_type'] == 'normal') AND $__vars['reaction']['image_url']) {
						$__finalCompiled .= '
				.reaction--normal.reaction--normal' . $__templater->escape($__vars['reactionId']) . '
				{
					';
						if ($__vars['reaction']['styling']['image_normal']['style_dimensions']) {
							$__finalCompiled .= '
						width: @{thReactionsImageDimensions[width]}@{thReactionsImageDimensions[unit]};
						height: @{thReactionsImageDimensions[height]}@{thReactionsImageDimensions[unit]};
					';
						} else {
							$__finalCompiled .= '
						width: ' . $__templater->escape($__vars['reaction']['styling']['image_normal']['w']) . $__templater->escape($__vars['reaction']['styling']['image_normal']['u']) . ';
						height: ' . $__templater->escape($__vars['reaction']['styling']['image_normal']['h']) . $__templater->escape($__vars['reaction']['styling']['image_normal']['u']) . ';
					';
						}
						$__finalCompiled .= '
				}
			';
					}
					$__finalCompiled .= '
		';
				}
				$__finalCompiled .= '

		';
				if ($__vars['reaction']['styling_type'] == 'html_css') {
					$__finalCompiled .= '
			' . $__templater->filter($__vars['reaction']['styling']['html_css']['css'], array(array('raw', array()),), true) . '
		';
				}
				$__finalCompiled .= '
	';
			}
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '


//linear
.linear(@start, @end, @ratio) {
	@linear: @start + ((@end - @start) * @ratio)
}

//ease
.ease(@start, @end, @ratio) {
	@ease: @start + ((@end - @start) * (pow(@ratio, 2) / (pow(@ratio, 2) + pow((1 - @ratio), 2))))
}

// wobbly
.tween(@start, @end, @ratio) {
	@tween: @start + (-0.5 * pow(2.71828, (-6 * @ratio)) * (-2 * pow(2.71828, (6 * @ratio)) + sin(12 * @ratio) + 2 * cos(12 * @ratio))) * (@end - @start);
}
.tween2(@start, @end, @ratio) {
	@tween2: @start + (-0.5 * pow(2.71828, (-6 * @ratio)) * (-2 * pow(2.71828, (6 * @ratio)) + sin(12 * @ratio) + 2 * cos(12 * @ratio))) * (@end - @start);
}
.tween3(@start, @end, @ratio) {
	@tween3: @start + (-0.5 * pow(2.71828, (-6 * @ratio)) * (-2 * pow(2.71828, (6 * @ratio)) + sin(12 * @ratio) + 2 * cos(12 * @ratio))) * (@end - @start);
}

// gentle wobble
.tweenGentle(@start, @end, @ratio) {
	@tweenGentle: @start + (((7 * pow(2.71828, (-7 * @ratio)) * sin(sqrt(71) * @ratio)) / sqrt(71)) - (pow(2.71828, (-7 * @ratio)) * cos(sqrt(71) * @ratio)) + 1) * (@end - @start);
}
.tweenGentle2(@start, @end, @ratio) {
	@tweenGentle2: @start + (((7 * pow(2.71828, (-7 * @ratio)) * sin(sqrt(71) * @ratio)) / sqrt(71)) - (pow(2.71828, (-7 * @ratio)) * cos(sqrt(71) * @ratio)) + 1) * (@end - @start);
}
.tweenGentle3(@start, @end, @ratio) {
	@tweenGentle3: @start + (((7 * pow(2.71828, (-7 * @ratio)) * sin(sqrt(71) * @ratio)) / sqrt(71)) - (pow(2.71828, (-7 * @ratio)) * cos(sqrt(71) * @ratio)) + 1) * (@end - @start);
}

// no wobble
.tweenStiff(@start, @end, @ratio) {
	@tweenStiff: @start + (pow(2.71828, (-13 * @ratio)) * (pow(2.71828, (13 * @ratio)) - 13 * sin(@ratio) - cos(@ratio))) * (@end - @start);
}
.tweenStiff2(@start, @end, @ratio) {
	@tweenStiff2: @start + (pow(2.71828, (-13 * @ratio)) * (pow(2.71828, (13 * @ratio)) - 13 * sin(@ratio) - cos(@ratio))) * (@end - @start);
}
.tweenStiff3(@start, @end, @ratio) {
	@tweenStiff3: @start + (pow(2.71828, (-13 * @ratio)) * (pow(2.71828, (13 * @ratio)) - 13 * sin(@ratio) - cos(@ratio))) * (@end - @start);
}

.th_reactions_triggerHover(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'@{i}%\');
    @{selector}{
		.tween(1, 1.2, (@i / @n));
		transform: scale(@tween, @tween);
	}
	.th_reactions_triggerHover(@n, (@i + 1));
}

@keyframes th_reactions_triggerHover {
	.th_reactions_triggerHover(100);
}

.th_reactions_triggerHoverLarge(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'@{i}%\');
    @{selector}{
		.tween(1, 1.5, (@i / @n));
		transform: scale(@tween, @tween)

	}
	.th_reactions_triggerHoverLarge(@n, (@i + 1));
}

@keyframes th_reactions_triggerHoverLarge {
	.th_reactions_triggerHoverLarge(100);
}



.reactions-bar .reactions-right__list {
	margin: 0 10px;
	align-items: center;
	justify-content: space-between;
}

.reactions-bar--modal .reactions-right__list {
	justify-content: center;
	flex-wrap: wrap;
	margin: 10px;
	width: 250px;
}

.reactions-bar--modal .th_reactions__scrollContainer {
	border-radius: 6px;
}

.reactions-bar--out .reactions-right__list {
	transform: none;
	opacity: 0;
	transform-origin: 100% 50%;
	transform-style: flat;
	display: inline-flex;
	pointer-events: none;
}

.th_reactions_expandShow(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'@{i}%\');
    @{selector}{
		.tweenGentle(0, 1, (@i / @n));
		.tweenGentle2(0.5, 1, (@i / @n));
		transform: scale(@tweenGentle, @tweenGentle2);
		opacity: (0.1 + ((@i / @n) * 1.5));
		& when (@i = 0) {
			pointer-events: none;
			overflow-x: hidden !important;
			will-change: unset;
		}
		& when (@i = 1) {
			will-change: transform;
		}
		& when (@i = 99) {
			overflow-x: hidden !important;
			will-change: transform;
		}
		& when (@i = 100) {
			transform: scale(1, 1);
			overflow-x: auto !important;
			pointer-events: all;
			will-change: unset;
		}
	}
	.th_reactions_expandShow(@n, (@i + 1));
}

@keyframes th_reactions_expandShow {
	.th_reactions_expandShow(100);
}

.reactions-bar--out .reactions-bar--show {
	animation-name: th_reactions_expandShow;
	animation-duration: 0.5s;
	animation-direction: normal;
	animation-fill-mode: both;
	opacity: 1;
	display: inline-flex;
}

.reactions-bar--out .reactions-bar--hide {
	opacity: 0;
	display: inline-flex;
	animation-name: th_reactions_expandShow;
	animation-duration: 0.5s;
	animation-direction: reverse;
	animation-fill-mode: both;
}



.reactions-bar--up .reactions-right__list {
	li {
		transform: translateY(20px);
		transform-origin: center;
		transform-style: flat;
		visibility: hidden;
	}

	a {
		transform: scale(0.4, 0.4);
	}
}

.th_reactions_slideUpShow(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'@{i}%\');
	.tweenGentle(20, 0, (@i / @n));
	@translateY: e(\'@{tweenGentle}px\');
    @{selector}{
		transform: translateY(@translateY);
		opacity: (0.4 + ((@i / @n)));
		& when (@i = 0) {
			display: none;
			visibility: hidden;
			width: 0;
			height: 0;
		}
		& when (@i = 1) {
			display: inline-flex;
			visibility: visible;
			width: auto;
			height: auto;
		}
		& when (@i = 100) {
			display: inline-flex;
			visibility: visible;
		}
	}
	.th_reactions_slideUpShow(@n, (@i + 1));
}

@keyframes th_reactions_slideUpShow {
	.th_reactions_slideUpShow(100);
}

.th_reactions_slideExpandShow(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'@{i}%\');
	.tween(0.4, 1, (@i / @n));
    @{selector}{
		transform: scale(@tween, @tween);
	}
	.th_reactions_slideExpandShow(@n, (@i + 1));
}

@keyframes th_reactions_slideExpandShow {
	.th_reactions_slideExpandShow(100);
}


.th_reactions_delay(@n, @i: 0) when (@i =< @n) {
	@selector: e(\'.reactions-bar--up .reactions-right:not(.th_reactions__reactionsBar--overflowing) .reactions-bar--show li:nth-last-of-type(@{i}), .reactions-bar--up .reactions-right:not(.th_reactions__reactionsBar--overflowing) .reactions-bar--show a:nth-last-of-type(@{i})\');
    @{selector}{
		animation-delay: (0.025s * @i);
	}
	.th_reactions_delay(@n, (@i + 1));
}

// .th_reactions_delay(50);



.reactions-bar--up .reactions-bar--show {
	li {
		animation-name: th_reactions_slideUpShow;
		animation-duration: 0.5s;
		animation-direction: normal;
		animation-fill-mode: both;
		display: inline-flex;
		visibility: visible;;
	}

	a {
		animation-name: th_reactions_slideExpandShow;
		animation-duration: 0.5s;
		animation-direction: normal;
		animation-fill-mode: both;


		@media(max-width: @xf-responsiveMedium) {
			padding: @xf-paddingSmall;
		}
	}
}

.reactions-bar--up .reactions-bar--hide {
	li {
		animation-name: th_reactions_slideUpShow;
		animation-duration: 0.5s;
		animation-direction: reverse;
		animation-fill-mode: both;
		display: inline-flex;
		visibility: visible;
	}

	a {
		animation-name: th_reactions_slideExpandShow;
		animation-duration: 0.5s;
		animation-direction: reverse;
		animation-fill-mode: both;

	}
}

.reactions-bar--out .reactions-right__list,
.reactions-bar--up .reactions-right__list,
.reactions-bar--none .reactions-right__list {
	@media(max-width: @xf-responsiveWide) {
		margin-top: 3px;
		margin-bottom: 3px;
		flex-wrap: nowrap;
		a {
			padding: @xf-paddingSmall;
		}
		overflow: hidden;
	}
}

.reactions-bar--none .reactions-right__list {
	overflow-x: auto;
}

.reactions-right {
	position: relative;
	max-width: 100%;
}

.th_reactions__scroll {
	display: none;
}

.th_reactions__scroll__iconWrap {
	transition: opacity 0.3s, color 0.3s;
	opacity: 0;
	color: @xf-linkColor;
}

@keyframes th_reactions__modalBackground {
	0% {
		opacity: 0;
	}
	100% {
		opacity: 1;
	}
}


.reactions-right__list {
	li.th_reactions__reaction {
		padding: 5px;
		z-index: 2;
	}

	@media(max-width: @xf-responsiveMedium) {
		li.th_reactions__reaction {
			padding: 0 9px;
		}

		a {
			padding: @xf-paddingSmall;
		}
	}

	li.th_reactions__reaction:first-of-type {
		padding-left: 5px;
	}

	li.th_reactions__reaction:last-of-type {
		padding-right: 5px;
	}
}

.reactions-bar:not(.reactions-bar--none) .th_reactions__scrollContainer {
	opacity: 0;
	pointer-events: none;

	&.reactions-barChildren--show {
		opacity: 1;
		pointer-events: all;
	}
}

:not(.reactions-bar--none) .th_reactions__scrollContainer,
.reactions-bar--modal .th_reactions__scrollContainer {
	position: absolute;
	transition: opacity 0.2s;
	.xf-th_reactions__modalStyle();
}

.th_reactions__scrollContainer {
	justify-content: space-between;
	display: flex;

	min-height: 50px;
	overflow: hidden;
	border-radius: 1000px;
	.xf-th_reactions__modalWrapperStyle();
}

.th_reactions__reactionsBar--overflowing {
	.th_reactions__scrollContainer {
		width: calc(~"100vw - 30px");
	}

	.th_reactions__scroll {
		display: flex;
		padding: 10px 14px;
		font-size: 16px;
		align-items: center;
		justify-content: center;
	}

	.reactions-right__list {
		margin: 0;
	}

	& .reactions-barChildren--show .th_reactions__scroll__iconWrap,
	.reactions-bar--none & .th_reactions__scroll__iconWrap {
		opacity: 1;
	}

	&.th_reactions__rightScroll--inactive .reactions-barChildren--show .th_reactions__rightScrollRight__iconWrap,
	.reactions-bar--none &.th_reactions__rightScroll--inactive .th_reactions__rightScrollRight__iconWrap,
	&.th_reactions__leftScroll--inactive .reactions-barChildren--show .th_reactions__leftScrollLeft__iconWrap,
	.reactions-bar--none &.th_reactions__leftScroll--inactive .th_reactions__leftScrollLeft__iconWrap {
		color: @xf-textColorMuted;
		opacity: 0.4;
	}
}


@keyframes th_reactions__label {
	0% {
		opacity: 0;
	}
	100% {
		opacity: 1;
	}
}

.th_reactions__reactionLabel {
	text-align: center;
	opacity: 0;
	animation-name: th_reactions__label;
	animation-duration: 0.2s;
	animation-fill-mode: both;
	animation-direction: normal;
	pointer-events: none;
	position: absolute;
	transform: translate(-50%, 0);
	padding: 3px 8px;
	font-size: 12px;
	border-radius: 1000px;
	background: rgba(0, 0, 0, 0.6);
	color: #FFF;
	margin-top: -@xf-paddingMedium;
	z-index: 10;
}

.th_reactions__reactionLabel--out {
	opacity: 1;
	animation-name: th_reactions__label;
	animation-duration: 0.1s;
	animation-fill-mode: both;
	animation-direction: reverse;
}

/*
.th_reactions__reaction--hovered {
	img {
		transform: scale(1, 1);
		animation-name: th_reactions_triggerHoverLarge;
		animation-duration: 0.3s;
		animation-direction: normal;
		animation-fill-mode: both;
	}
}

.th_reactions__reaction--hoveredOut {
	img {
		transform: scale(1.5, 1.5);
		animation-name: th_reactions_triggerHoverLarge;
		animation-duration: 0.3s;
		animation-direction: reverse;
		animation-fill-mode: forwards;
	}
}
*/

.reactions-bar--modal {
	.reactions-bar--show {
		li.th_reactions__reaction {
			animation-name: th_reactions_slideUpShow;
			animation-duration: 0.5s;
			animation-direction: normal;
			animation-fill-mode: both;
			display: inline-flex;
			visibility: visible;;
		}

		a {
			animation-name: th_reactions_slideExpandShow;
			animation-duration: 0.5s;
			animation-direction: normal;
			animation-fill-mode: both;
		}
	}
}

.reactionCount {
	display: table;
	width: 100%;
}

.reactionCount-row {
	display: table-row;
}

.reactionCount-row-cell {
	display: table-cell;
	padding: 0 @xf-paddingSmall;

	&--primary {
		color: @xf-textColorMuted;
	}

	&--secondary {
		text-align: right;
	}
}';
	return $__finalCompiled;
});