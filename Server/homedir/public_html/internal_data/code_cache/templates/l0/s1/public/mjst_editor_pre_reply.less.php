<?php
// FROM HASH: 113a463d8e1fd7fb6cf739e35336463e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.mjstEditorPreReplies
{
	display: none;
	border: @xf-borderSize solid @xf-borderColorHeavy;
	border-top: none;
	background: @xf-editorToolbarBg;
	overflow: hidden;
	.m-transition();
	.m-transitionProperty(all, -xf-height;);
	height: 0;

	&.is-active
	{
		display: block;
		height: auto;
	}

	&.is-transitioning
	{
		display: block;
	}

	.smilie
	{
		cursor: pointer;
	}

	.tabPanes > li
	{
		padding: @xf-blockPaddingV @xf-blockPaddingH;
	}
	.replyTitle{
		font-weight: bold;
		cursor: pointer;
	}
	.reply-full{
		display: none;
	}
}';
	return $__finalCompiled;
});