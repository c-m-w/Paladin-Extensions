<?php
// FROM HASH: 8ffc297545e7e64caa9de6ecb88ce691
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// This contains rules that apply to various block and block-related systems. This file should be included
// after all of the primary definitions to ensure the rules override.

.blockMessage,
.blockStatus,
.block-row
{
	p:first-child
	{
		margin-top: 0;
	}

	p:last-child
	{
		margin-bottom: 0;
	}
}

@media (max-width: @xf-responsiveEdgeSpacerRemoval)
{
	.block-container,
	.blockMessage
	{
		margin-left: -@xf-pageEdgeSpacer * .5;
		margin-right: -@xf-pageEdgeSpacer * .5;
		border-radius: 0;
		border-left: none;
		border-right: none;
	}

	.blockStatus
	{
		margin-left: -@xf-pageEdgeSpacer;
		margin-right: -@xf-pageEdgeSpacer;
		border-radius: 0;
		border-right: none;
	}

	.blockMessage.blockMessage--none
	{
		margin-left: 0;
		margin-right: 0;
	}
}';
	return $__finalCompiled;
});