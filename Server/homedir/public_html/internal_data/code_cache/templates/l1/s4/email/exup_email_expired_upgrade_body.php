<?php
// FROM HASH: a30545b1b96911f55986d73520766761
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . $__templater->escape($__vars['boardTitle']) . ' Account Upgrade Expired' . '
</mail:subject>

' . '' . $__templater->escape($__vars['username']) . ', your subscription to <i><b>' . $__templater->escape($__vars['upgrade_title']) . '</b></i> has now expired.<br />Thank you for having purchased premium and we hope you have enjoyed the extensions it offered.<br />You may renew your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" style="color: #176093; text-decoration: none">here</a>.<p>Sincerely,<br />
' . $__templater->escape($__vars['boardTitle']) . '</p>' . '

' . '<p class="minorText">Please do not reply to this message. You must visit the forum to reply.</p>

<p class="minorText">This message was sent to you because you opted to receive emails when your user upgrades are about to expire or have expired at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'sv_up_expired_expirying', 'id' => $__vars['xf']['toUser']['user_id'], ), ), true) . '">disable emails when your user upgrades are about to expire or have expired</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>';
	return $__finalCompiled;
});