<?php
// FROM HASH: 60de34d437ce884d5a48967e46cc00b4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.avatar.avatar--resourceIconDefault
{
	color: @xf-textColorMuted !important;
	background: mix(@xf-textColorMuted, @xf-avatarBg, 25%) !important;
	text-align: center;
	line-height: 1.5;

	-webkit-user-select: none;
	-moz-user-select: none;
	-ms-user-select: none;
	user-select: none;

	> span:before
	{
		.m-faBase();
		.m-faContent(@fa-var-cog, .86em);
		vertical-align: -0.03em;
	}
}';
	return $__finalCompiled;
});