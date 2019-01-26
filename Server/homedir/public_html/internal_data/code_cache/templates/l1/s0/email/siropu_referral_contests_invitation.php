<?php
// FROM HASH: adbfe7f5f6a77881da08fc2ad828103f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>' . $__templater->escape($__vars['subject']) . '</mail:subject>

<p>' . $__templater->filter($__vars['message'], array(array('siropu_message_placeholders', array($__vars['invitation'], )),array('nl2br', array()),), true) . '</p>

<p>' . 'Your invitation link' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->escape($__vars['invitation']['invitation_url']) . '">' . $__templater->escape($__vars['invitation']['invitation_url']) . '</a></p>

';
	if ($__vars['xf']['options']['siropuReferralContestsInvitationOnly']) {
		$__finalCompiled .= '
	<p>' . 'Your invitation code' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['invitation']['invitation_code']) . '</p>
';
	} else if ($__vars['xf']['options']['siropuReferralContestsReferrerUserField']) {
		$__finalCompiled .= '
	<p>' . 'Referrer username' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['invitation']['User']['username']) . '</p>
';
	}
	return $__finalCompiled;
});