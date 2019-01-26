<?php
// FROM HASH: b85ef9ad1f38b412d6c4e2dec47ced1e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.actionBar
{
	.m-clearFix();
}

.actionBar-set.actionBar
{
	&.actionBar-set--internal
	{
		float: left;
		// margin-left: -3px;

		> .actionBar-action:first-child
		{
			margin-left: 0;
		}
	}

	&.actionBar-set--external
	{
		float: right;
		// margin-right: -3px;

		> .actionBar-action:last-child
		{
			margin-right: 0;
		}
	}
}

.actionBar .actionBar-action
{
	padding: 3px;
	border: 1px solid transparent;
	border-radius: @xf-borderRadiusMedium;
	margin-left: 5px;
	.xf-uix_messageControl();

	&:hover {
		.xf-uix_messageControlHover();
	}

	&:before
	{
		.m-faBase();
		font-size: 12px;
		padding-right: 2px;
	}

	&.actionBar-action--menuTrigger
	{
		display: none;

		&:after
		{
			.m-faBase();
			.m-faContent(" @{fa-var-caret-down}");
			' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'menu-down',
	), $__vars) . '
		}
	}

	&.actionBar-action--inlineMod input
	{
		.m-checkboxAligner();
		margin: 0;
	}

	&.actionBar-action--mq
	{
		&:before { .m-faContent("@{fa-var-plus}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'quote',
	), $__vars) . ' } // plus

		&.is-selected
		{
			background-color: @xf-contentHighlightBg;
			border-color: @xf-borderColorHighlight;

			&:before { .m-faContent("@{fa-var-minus}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'quote',
	), $__vars) . '} // minus
		}
	}

	&.actionBar-action--reply:before { .m-faContent("@{fa-var-reply}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'reply',
	), $__vars) . '} // reply
	&.actionBar-action--comment:before { .m-faContent("@{fa-var-reply}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'post',
	), $__vars) . '} // reply
	&.actionBar-action--like:before { .m-faContent("@{fa-var-thumbs-o-up}\\20"); ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'like',
	), $__vars) . '}
	&.actionBar-action--like.unlike:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'unlike',
	), $__vars) . '}// thumbs up
	&.actionBar-action--report:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'report',
	), $__vars) . '}
	&.actionBar-action--delete:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'delete',
	), $__vars) . '}
	&.actionBar-action--edit:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'edit',
	), $__vars) . '}
	&.actionBar-action--ip:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'ipaddress',
	), $__vars) . '}
	&.actionBar-action--history:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'history',
	), $__vars) . '}
	&.actionBar-action--warn:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'warn',
	), $__vars) . '}
	&.actionBar-action--spam:before { ' . $__templater->callMacro('uix_icons.less', 'content', array(
		'icon' => 'spam',
	), $__vars) . '}
}

@media (max-width: @xf-responsiveNarrow)
{
	.actionBar .actionBar-action
	{
		&.actionBar-action--menuItem
		{
			display: none !important;
		}

		&.actionBar-action--menuTrigger
		{
			display: inline;
		}
	}
}';
	return $__finalCompiled;
});