<?php
// FROM HASH: a0d9616e43090ca8bf6b58052bcdb059
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_structItem-avatarSize: 36px;
@_structItem-avatarSizeExpanded: 48px;
@_structItem-cellPaddingH: @xf-paddingMedium; 
@_structItem-cellPaddingV: @xf-paddingMedium;

.structItemContainer
{
	display: table;
	table-layout: fixed;
	border-collapse: collapse;
	list-style: none;
	margin: 0;
	padding: 0;
	width: 100%;
}

.structItemContainer-group
{
	display: table-row-group;
}

' . '

.structItemContainer-group--sticky {
	.structItem--thread {
		.xf-uix_discussionListItemSticky();
	}
}

.structItem--thread.is-moderated {.xf-uix_discussionListItemModerated();}
.structItem--thread.is-deleted {.xf-uix_discussionListItemDeleted();}

.structItem.is-mod-selected .structItem-cell--meta,
.structItem--thread.is-deleted .structItem-cell--meta{background: none;}

.structItem
{
	display: table;
	border-top: @xf-borderSize solid @xf-borderColorFaint;
	list-style: none;
	margin: 0;
	padding: 0;
	width: 100%;
	.xf-uix_discussionListItem();

	&:nth-child(even) {
		background-color: @xf-uix_discussionListItemEven;
	}

	&:hover {
		background-color: @xf-uix_discussionListItemHover;

		';
	if ($__templater->fn('property', array('uix_discussionListItemHover', ), false)) {
		$__finalCompiled .= '
			.structItem-cell--meta {
				background-color: transparent
			}
		';
	}
	$__finalCompiled .= '
	}

	&.is-highlighted,
	&.is-moderated
	{
		// background: @xf-contentHighlightBg;
		.xf-uix_discussionListItemModerated();
	}


	&.is-deleted
	{
		opacity: .7;

		.structItem-title
		{
			text-decoration: line-through;
		}
	}

	&.is-mod-selected
	{
		background: @xf-inlineModHighlightColor;
		opacity: 1;
	}
}

.threadListSeparator {
	.xf-uix_threadListSeparator();
}

.structItem-cell
{
	display: table-cell;
	vertical-align: top;
	padding: @_structItem-cellPaddingV @_structItem-cellPaddingH;
	
	&.structItem-cell--main {padding-left: 0;}

	.structItem--middle &
	{
		vertical-align: middle;
	}

	&.structItem-cell--icon
	{
		width: ((@_structItem-avatarSize) + (@_structItem-cellPaddingH) * 2);
		position: relative;
		
		&.structItem-cell--iconExpanded
		{
			width: ((@_structItem-avatarSizeExpanded) + (@_structItem-cellPaddingH) * 2);
		}

		&.structItem-cell--iconFixedSmall
		{
			width: (60px + (@_structItem-cellPaddingH) * 2);
		}
	}

	&.structItem-cell--meta
	{
		width: 150px;
		.xf-uix_metaCell();

		@media (max-width: @xf-responsiveMedium) {
			background: none;
			// padding: 0;
			border: none;
			
			.pairs {line-height: inherit;}
		}
	}

	&.structItem-cell--latest
	{
		width: 220px;
		text-align: right;
	}
}

.structItem-iconContainer
{
	position: relative;

	img
	{
		display: block;
		width: 100%;
	}

	.avatar
	{
		.m-avatarSize(@_structItem-avatarSize);
	}

	.structItem-secondaryIcon
	{
		position: absolute;
		right: -5px;
		bottom: -5px;

		.m-avatarSize(@_structItem-avatarSize / 2  + 2px);
	}
	
	.structItem-cell--iconExpanded &
	{
		.avatar
		{
			.m-avatarSize(@_structItem-avatarSizeExpanded);
		}
		.structItem-secondaryIcon
		{
			.m-avatarSize(@_structItem-avatarSizeExpanded / 2 - 2px);
		}
	}
}

.structItem-title
{
	font-size: @xf-fontSizeLarge;
	font-weight: @xf-fontWeightNormal;
	margin: 0;
	padding: 0;

	.label
	{
		font-weight: @xf-fontWeightNormal;
	}

	.is-unread &
	{
		font-weight: @xf-fontWeightHeavy;
	}
}

.structItem-minor
{
	font-size: @xf-fontSizeSmaller;
	color: @xf-textColorMuted;

	.m-hiddenLinks();
}

.structItem-parts
{
	.m-listPlain();
	display: inline;

	> li
	{
		display: inline;
		margin: 0;
		padding: 0;

		&:nth-child(even)
		{
			color: @xf-textColorDimmed;
		}

		&:before
		{
			content: "\\00B7\\20";
		}

		&:first-child:before
		{
			content: "";
			display: none;
		}
	}
}

.structItem-pageJump
{
	margin-left: 8px;
	font-size: @xf-fontSizeSmallest;

	a
	{
		.xf-chip();
		text-decoration: none;
		border-radius: @xf-borderRadiusSmall;
		padding: 0 3px;
		opacity: .5;
		.m-transition();

		.structItem:hover &,
		.has-touchevents &
		{
			opacity: 1;
		}

		&:hover
		{
			text-decoration: none;
			.xf-chipHover();
		}
	}
}

.structItem-statuses,
.structItem-extraInfo
{
	.m-listPlain();
	float: right;

	> li
	{
		float: left;
		margin-left: 8px;
	}

	input[type=checkbox]
	{
		.m-checkboxAligner();
	}
}

.structItem-status
{
	.m-faBase();
	display: inline-block;
	// font-size: 90%;
	color: @xf-textColorMuted;

	&--deleted::before { .m-faContent(@fa-var-trash-o, .79em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . ' }
	&--locked::before { color: #d28b00; .m-faContent(@fa-var-lock, .65em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'lock',
	), $__vars) . ' }
	&--moderated::before { color: #00a500; .m-faContent(@fa-var-shield, .72em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'moderate',
	), $__vars) . ' }
	&--redirect::before { color: #0026bd; .m-faContent(@fa-var-external-link, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'redirect',
	), $__vars) . ' }
	&--starred::before { .m-faContent(@fa-var-star, 0.93em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'star',
	), $__vars) . ' color: #fae587; }
	&--sticky::before {  color: #ca0000; .m-faContent(@fa-var-thumb-tack, .65em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'sticky',
	), $__vars) . ' }
	&--watched::before { color: #910098; .m-faContent(@fa-var-eye, 1em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'watched',
	), $__vars) . ' }
	&--poll::before { color: #e200ec; .m-faContent(@fa-var-bar-chart, 1.15em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'poll',
	), $__vars) . '}
	&--attention::before { .m-faContent(@fa-var-bullhorn, 1.04em); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'attention',
	), $__vars) . '}
}

.structItem.structItem--note
{
	.xf-contentHighlightBase();
	color: @xf-textColorFeature;

	.structItem-cell
	{
		padding-top: @_structItem-cellPaddingV / 2;
		padding-bottom: @_structItem-cellPaddingV / 2;
		font-size: @xf-fontSizeSmaller;
		text-align: center;
	}
}

@media (max-width: @xf-responsiveWide)
{
	.structItem-cell
	{
		vertical-align: top;
		
		&.structItem-cell--meta
		{
			width: 120px;
			font-size: @xf-fontSizeSmaller;
		}

		&.structItem-cell--latest
		{
			width: 140px;
			font-size: @xf-fontSizeSmaller;
		}
	}
}

@media (max-width: @xf-responsiveMedium)
{
	.structItem-cell
	{

		//padding: (@_structItem-cellPaddingV) / 2 @_structItem-cellPaddingH;
		
		&.structItem-cell--main
		{
			display: block;
			padding-bottom: .2em;
			padding-left: 0;
		}

		&.structItem-cell--meta
		{
			display: block;
			width: auto;
			float: left;
			padding-top: 0;
			padding-left: 0;
			padding-right: 0;
			color: @xf-textColorMuted;

			.structItem-minor
			{
				display: none;
			}

			.pairs
			{
				> dt,
				> dd
				{
					display: inline;
					float: none;
					margin: 0;
				}
			}
		}

		&.structItem-cell--latest
		{
			display: block;
			width: auto;
			float: left;
			padding-top: 0;
			padding-left: 0;

			&:before
			{
				content: "\\00A0\\00B7\\20";
				color: @xf-textColorMuted;
			}

			a
			{
				color: @xf-textColorMuted;
			}

			.structItem-minor
			{
				display: none;
			}
		}
	}

	.structItem-pageJump,
	.structItem-extraInfoMinor
	{
		display: none;
	}

	.is-unread .structItem-latestDate
	{
		font-weight: @xf-fontWeightNormal;
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.structItem-parts
	{
		.structItem-startDate
		{
			display: none;
		}
	}
}';
	return $__finalCompiled;
});