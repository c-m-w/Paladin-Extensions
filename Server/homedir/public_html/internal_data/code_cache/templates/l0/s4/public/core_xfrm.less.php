<?php
// FROM HASH: dc77b7271243f7ba06ea3d5c9f8e2069
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
        ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'settings',
	), $__vars) . '
        vertical-align: -0.03em;
    }
}';
	return $__finalCompiled;
});