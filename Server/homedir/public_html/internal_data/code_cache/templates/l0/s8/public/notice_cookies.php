<?php
// FROM HASH: 1ba7ebff45368854fd8a329737bd7426
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="">
	' . 'This site uses cookies. By continuing to use this site, you are agreeing to our use of cookies.' . '
</div>

<div class="u-inputSpacer uix_cookieButtonRow">
	' . $__templater->button('accept', array(
		'icon' => 'confirm',
		'href' => $__templater->fn('link', array('account/dismiss-notice', null, array('notice_id' => $__vars['notice']['notice_id'], ), ), false),
		'class' => 'js-noticeDismiss button--notice',
		'data-xf-init' => 'tooltip',
		'title' => 'Dismiss notice',
	), '', array(
	)) . '
	' . $__templater->button('Learn more.' . $__vars['xf']['language']['ellipsis'], array(
		'href' => $__templater->fn('link', array('help/cookies', ), false),
		'class' => 'button--notice',
	), '', array(
	)) . '
</div>';
	return $__finalCompiled;
});