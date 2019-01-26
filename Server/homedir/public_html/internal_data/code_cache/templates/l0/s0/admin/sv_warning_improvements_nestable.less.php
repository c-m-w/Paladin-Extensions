<?php
// FROM HASH: 9d0b556605d275b717b603db396af688
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.category-container
{
	position: relative;

	&:first-child
	{
		padding: 0 @xf-paddingMedium;
	}

	.m-clearFix();
}

.category-list
{
	.m-listPlain();

	width: 100%;
	position: relative;

	.category-list
	{
		padding-left: 30px;
	}
	
	.nestable-list
	{
		padding-left: 30px;
	}

	.category-collapsed
	{
		.category-list
		{
			display: none;
		}
		
		.nestable-list
		{
			display: none;
		}
	}
}

.category-item
{
	.category-handle,
	.category-content,
	.category-button
	{
		border: 1px solid @xf-borderColor;
		border-radius: @xf-borderRadiusSmall;
		padding: @xf-paddingMedium;

		background-color: @xf-contentAltBg;
	}

	.category-button
	{
		float: left;

		color: @xf-textColorMuted;
		margin-left: 30px;

		border-radius: 0;
		border-left: none;
		border-right: none;
		outline: none;
	}

	.category-handle
	{
		position: absolute;
		margin: 0;
		left: 0;
		top: 0;
		width: 30px;

		text-align: center;
		color: @xf-textColorMuted;
		cursor: move;

		border-right: @xf-borderSize solid @xf-borderColor;
		border-top-right-radius: 0;
		border-bottom-right-radius: 0;

		&.category-handle--full
		{
			bottom: 0;
		}
	}

	.category-content
	{
		text-overflow: ellipsis;
		overflow: hidden;
		white-space: nowrap;

		margin: @xf-paddingMedium 0;

		border-top-left-radius: 0;
		border-bottom-left-radius: 0;
	}
}

.category-item,
.category-empty,
.category-placeholder
{
	position: relative;
	vertical-align: middle;
}

.category-placeholder,
.category-empty
{
	opacity: .6;
	border: 1px solid @xf-borderColor;
	background: @xf-contentAltBg;
	border-radius: @xf-borderRadiusSmall;
	margin: @xf-paddingMedium 0;
}

.category-empty
{
	min-height: floor((@xf-fontSizeNormal) * 1.475 + 2 * (@xf-paddingMedium) + 2 * (@xf-borderSize));
}

.category-dragel
{
	position: absolute;
	pointer-events: none;
	z-index: 9999;
}';
	return $__finalCompiled;
});