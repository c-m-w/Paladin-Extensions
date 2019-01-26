<?php
// FROM HASH: 271544d424c8f929c5935f839e4f9baa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_nodeList-statsCellBreakpoint: @xf-uix_viewportCollapseStats;
@_iconWidth: ' . ($__templater->fn('property', array('uix_nodeIconWidth', ), false) + $__templater->fn('property', array('paddingLarge', ), false)) . 'px;

.block--category {
	.block-header {
		display: flex;
		align-items: center;
		.xf-uix_categoryStrip();
		';
	if ($__templater->fn('property', array('uix_categoryStripOutsideWrapper', ), false)) {
		$__finalCompiled .= '
			.m-uix_removePageSpacer();
		';
	}
	$__finalCompiled .= '

		.uix_categoryStrip__icon {
			align-self: flex-start;

			i {
				.xf-uix_categoryIconStyle();
				vertical-align: middle;
			}
		}


		.node-description {
			.xf-uix_categoryDescription();
		}

		.categoryCollapse--trigger {
			font-size: @xf-uix_iconSizeLarge;
			// padding-right: @xf-paddingMedium;
			margin-left: auto;
		}
	}
}

.uix_nodeList {
	.block-container {.xf-uix_nodeContainer();}
	.block-body {.xf-uix_nodeBlockBody();}
}

.block-body {
	.node {
		&:first-child .node-body {
			border-top-left-radius: @xf-uix_nodeBlockBody--border-radius;
			border-top-right-radius: @xf-uix_nodeBlockBody--border-radius;
		}

		&:last-child .node-body {
			border-bottom-left-radius: @xf-uix_nodeBlockBody--border-radius;
			border-bottom-right-radius: @xf-uix_nodeBlockBody--border-radius;
		}
	}
}


.node
{
	& + .node
	{
		border-top: @xf-borderSize solid @xf-borderColorFaint;
	}
}


.node-body
{
	display: table;
	table-layout: fixed;
	width: 100%;
	transition: all ease-in .15s;
	.xf-uix_nodeBody();

	&:hover {
		.xf-uix_nodeBodyHover;
		';
	if ($__templater->fn('property', array('uix_nodeClickable', ), false)) {
		$__finalCompiled .= '
			cursor: pointer;
		';
	}
	$__finalCompiled .= '
	}

	';
	if ($__templater->fn('property', array('uix_nodeStatsHover', ), false)) {
		$__finalCompiled .= '
		.node-meta,
		.node-stats {
			opacity: 0;
		    transition: ease all .2s;
			left: -6px;
			position: relative;
		}

		&:hover {
			.node-meta,
			.node-stats {
				opacity: 1;
				left: 0;
			}
		}
	';
	}
	$__finalCompiled .= '
}

.node--depth2:nth-child(even) .node-body{
	background-color: @xf-uix_nodeBodyEven;

	&:hover {
		.xf-uix_nodeBodyHover;
	}
}

.has-flexbox .node-body {
	display: flex;

	.node-icon,
	.node-main {display: inline-block;}

	.node-main {
		flex-grow: 1;
		width: calc(~"100% - ' . ($__templater->fn('property', array('uix_nodeIconWidth', ), false) + $__templater->fn('property', array('paddingLarge', ), false)) . 'px");
	}

	@media (max-width: @xf-responsiveMedium) {
		flex-wrap: wrap;
		.node-extra {
			width: 100%;
			padding-left: ' . ($__templater->fn('property', array('uix_nodeIconWidth', ), false) + $__templater->fn('property', array('paddingLarge', ), false)) . 'px;
		}
	}
}

.node-icon
{
	display: table-cell;
	vertical-align: top;
	text-align: center;
	width: 46px;
	width: @xf-uix_nodeIconWidth;
	padding: @xf-uix_nodePadding 0 @xf-uix_nodePadding @xf-uix_nodePadding;
	flex-shrink: 0;

	i
	{
		display: block;
		line-height: 1;
		font-size: 32px;
		.xf-uix_nodeIconStyle();

		&:before
		{
			.m-faBase();
			.xf-uix_iconFont();

			color: @xf-nodeIconReadColor;
			// text-shadow: 1px 1px .5px fade(xf-intensify(@xf-nodeIconReadColor, 50%), 50%);

			.node--unread &
			{
				opacity: 1;
				color: @xf-nodeIconUnreadColor;
				// text-shadow: 1px 1px .5px fade(xf-intensify(@xf-nodeIconUnreadColor, 50%), 50%);
			}
		}

		.node--category &:before,
		.node--forum &:before {
			content: \'@xf-uix_glyphForumIcon\';
		}

		.node--page &:before
		{
			.m-faContent(@fa-var-file-text, .86em);
			content: \'@xf-uix_glyphPageIcon\';
		}

		.node--link &:before
		{
			.m-faContent(@fa-var-link, .93em);
			content: \'@xf-uix_glyphLinkIcon\';
		}

	';
	if ($__templater->fn('property', array('uix_nodeIconImages', ), false)) {
		$__finalCompiled .= '
		.xf-uix_imageIcon();

		&:before {display: none !important;}
	';
	}
	$__finalCompiled .= '
	}
}

';
	if ($__templater->fn('property', array('uix_nodeIconImages', ), false)) {
		$__finalCompiled .= '
.node--category .node-icon i,
.node--forum .node-icon i {.xf-uix_imageForumIcon();}

.node--forum.node--unread .node-icon i {.xf-uix_imageForumUnreadIcon();}

.node--link .node-icon i {.xf-uix_imageLinkIcon();}

.node--page .node-icon i {.xf-uix_imagePageIcon();}
';
	}
	$__finalCompiled .= '

/*
.node--forum &:before
{
	.m-faContent(@fa-var-comments, 1em);
	content: \'@xf-uix_glyphForumIcon\';
}

.node--page &:before
{
	.m-faContent(@fa-var-file-text, .86em);
	content: \'@xf-uix_glyphPageIcon\';
}

.node--link &:before
{
	.m-faContent(@fa-var-link, .93em);
	content: \'@xf-uix_glyphLinkIcon\';
}
*/

.node-main
{
	display: table-cell;
	vertical-align: middle;
	padding: @xf-uix_nodePadding;
}

.node-stats
{
	// display: table-cell;
	display: flex;
	align-items: center;
	width: 170px;
	min-width: 170px;
	vertical-align: middle;
	text-align: center;
	padding: @xf-uix_nodePadding 0;

	.pairs {line-height: 1.5;}

	> dl.pairs.pairs--rows
	{
		width: 50%;
		float: left;
		margin: 0;
		padding: 0 @xf-paddingMedium/2;
		border-right: 1px solid @xf-borderColor;

		&:first-child
		{
			padding-left: 0;
		}

		&:last-child
		{
			padding-right: 0;
			border-right: 0;
		}
	}

	&.node-stats--single
	{
		width: 100px;
		> dl.pairs.pairs--rows
		{
			width: 100%;
			float: none;
		}
	}
	&.node-stats--triple
	{
		width: 240px;
		> dl.pairs.pairs--rows
		{
			width: 33.333%;
		}
	}

	@media (max-width: @_nodeList-statsCellBreakpoint)
	{
		display: none;
	}
}

.node-extra
{
	// display: table-cell;
	display: flex;
	vertical-align: middle;
	width: 230px;
	min-width: 230px;
	padding: @xf-uix_nodePadding;
	display: inline-flex;
	//flex-direction: column;
	//justify-content: center;
	align-items: center;
	font-size: @xf-fontSizeSmall;
	
	a:not(:hover) {color: @xf-textColorDimmed;}

	.uix_nodeExtra__rows {
		display: flex;
		flex-wrap: wrap;
		min-width: 0;
		max-width: 100%;
		flex-direction: column;
		width: 100%;
	}
}

.node-extra-row
{
	.m-overflowEllipsis();
	color: @xf-textColorMuted;
	max-width: 100%;
	
	.listInline {.m-overflowEllipsis();}
}

.node-extra-title {padding-right: .5em;}

.node-extra-placeholder
{
	font-style: italic;
}

.node-title
{
	/* -- Changed to Style Property -- Ian --
	margin: 0;
	padding: 0;
	font-size: @xf-fontSizeLarge;
	font-weight: @xf-fontWeightNormal;
	*/
	.xf-uix_nodeTitle();

	a {color: inherit;}

	.node--unread &
	{
		font-weight: @xf-fontWeightHeavy;
		.xf-uix_nodeTitle__unread();
	}
}

.node-description
{
	/* UI.X Style property -- Ian
	font-size: @xf-fontSizeSmall;
	color: @xf-textColorDimmed;
	*/
	.xf-uix_nodeDescription();

	&.node-description--tooltip
	{
		.has-js.has-no-touchevents &
		{
			display: none;
		}
	}
}

.node-meta
{
	font-size: @xf-fontSizeSmall;
	display: inline;
}

.node-statsMeta
{
	display: none;

	.pairs {padding-right: .4em;}

	';
	if ($__templater->fn('property', array('uix_nodeStatsIcons', ), false)) {
		$__finalCompiled .= '
		dt,
		dt:after {display: none;}
	';
	}
	$__finalCompiled .= '

	@media (max-width: @_nodeList-statsCellBreakpoint)
	{
		display: inline;
	}
}

.node-bonus
{
	font-size: @xf-fontSizeSmall;
	color: @xf-textColorMuted;
	text-align: right;
}

.node-subNodesFlat
{
	font-size: @xf-fontSizeSmall;
	margin-top: .3em;

	.node-subNodesLabel
	{
		display: none;
	}
}

.node-subNodeMenu
{
	display: inline;

	i {display: none;}

	@media (max-width: @xf-uix_viewportCollapseStats) {
		i {display: inline-block;}
		span {display: none;}
	}

	.menuTrigger
	{
		color: @xf-textColorMuted;
	}
}

@media (max-width: @xf-responsiveMedium)
{
	.node-main
	{
		display: block;
		width: auto;
	}

	.node-extra
	{
		display: flex;
		// align-items: center;
		width: auto;
		// this gives an equivalent of medium padding between main and extra, with main still having large
		margin-top: (@xf-paddingMedium - @xf-paddingLarge);
		padding-top: 0;
	}

	.node-extra-row
	{
		display: inline-block;
		vertical-align: top;
		max-width: 100%;
	}

	.node-description,
	.node-subNodesFlat
	{
		display: none;
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.node-subNodeMenu
	{
		// display: none;
	}
}

.subNodeLink
{
	&:before
	{
		display: inline-block;
		.m-faBase();
		width: 1em;
		padding-right: .3em;
		text-decoration: none;

		color: @xf-textColorMuted;
		// text-shadow: 1px 1px 0 fade(xf-intensify(@xf-nodeIconReadColor, 50%), 50%);
	}

	&:hover:before
	{
		text-decoration: none;
	}

	&.subNodeLink--unread
	{
		font-weight: @xf-fontWeightHeavy;

		&:before
		{
			color: @xf-nodeIconUnreadColor;
			// text-shadow: 1px 1px 0 fade(xf-intensify(@xf-nodeIconUnreadColor, 50%), 50%);
		}
	}

	&.subNodeLink--forum:before,
	&.subNodeLink--category:before
	{
		.m-faContent(@fa-var-comments);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'forum',
	), $__vars) . '
	}

	&.subNodeLink--page:before
	{
		.m-faContent(@fa-var-file-text);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'page',
	), $__vars) . '
	}

	&.subNodeLink--link:before
	{
		.m-faContent(@fa-var-link);
		' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'link',
	), $__vars) . '
	}
}

.node-subNodeFlatList
{
	.m-listPlain();
	.m-clearFix();

	> li
	{
		display: inline-block;
		margin-right: 1em;


		&:last-child
		{
			margin-right: 0;
		}

		a {
			.xf-uix_subForumTitle();
		}
	}

	ol,
	ul,
	.node-subNodes
	{
		display: none;
	}
}

.subNodeMenu
{
	.m-listPlain();

	ol,
	ul
	{
		.m-listPlain();
	}

	.subNodeLink
	{
		display: block;
		padding: (@xf-blockPaddingV / 2) @xf-blockPaddingH;
		text-decoration: none;
		cursor: pointer;

		&:hover
		{
			text-decoration: none;
			background: @xf-contentHighlightBg;
		}
	}

	li li .subNodeLink { padding-left: 1.5em; }
	li li li .subNodeLink { padding-left: 3em; }
	li li li li .subNodeLink { padding-left: 4.5em; }
	li li li li li .subNodeLink { padding-left: 6em; }
	li li li li li li .subNodeLink { padding-left: 7.5em; }
}';
	return $__finalCompiled;
});