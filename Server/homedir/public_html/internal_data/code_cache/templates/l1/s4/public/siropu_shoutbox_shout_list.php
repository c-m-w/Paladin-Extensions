<?php
// FROM HASH: be093f8833d8e4dc645af1408fda4417
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->isTraversable($__vars['shoutbox']['shouts'])) {
		foreach ($__vars['shoutbox']['shouts'] AS $__vars['shout']) {
			$__finalCompiled .= '
	<li data-id="' . $__templater->escape($__vars['shout']['shout_id']) . '">
		';
			if ($__vars['xf']['options']['siropuShoutboxUserAvatar']) {
				$__finalCompiled .= '
			' . $__templater->fn('avatar', array($__vars['shout']['User'], 'xxs', false, array(
					'defaultname' => 'Guest',
					'itemprop' => 'image',
				))) . '
		';
			}
			$__finalCompiled .= '
		' . $__templater->fn('username_link', array($__vars['shout']['User'], true, array(
				'defaultname' => 'Guest',
			))) . ':
		<span>' . ($__vars['xf']['options']['siropuShoutboxAllowBBCodes'] ? $__templater->fn('bb_code', array($__templater->filter($__vars['shout']['shout_message'], array(array('censor', array()),), false), 'shoutbox_message', $__vars['shout']['User'], ), true) : $__templater->filter($__vars['shout']['shout_message'], array(array('censor', array()),), true)) . '</span>
		' . $__templater->fn('date_dynamic', array($__vars['shout']['shout_date'], array(
			))) . '
		';
			if ($__templater->method($__vars['shout'], 'canEdit', array())) {
				$__finalCompiled .= '
			<a href="' . $__templater->fn('link', array('shoutbox/edit', $__vars['shout'], ), true) . '" data-xf-click="overlay" title="' . 'Edit' . '"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a>
		';
			}
			$__finalCompiled .= '
		';
			if ($__templater->method($__vars['shout'], 'canDelete', array())) {
				$__finalCompiled .= '
			<a href="' . $__templater->fn('link', array('shoutbox/delete', $__vars['shout'], ), true) . '" data-xf-click="overlay" title="' . 'Delete' . '"><i class="fa fa-trash-o" aria-hidden="true"></i></a>
		';
			}
			$__finalCompiled .= '
	</li>
';
		}
	}
	return $__finalCompiled;
});