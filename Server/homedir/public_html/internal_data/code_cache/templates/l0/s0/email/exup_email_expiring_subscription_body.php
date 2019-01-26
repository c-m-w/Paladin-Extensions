<?php
// FROM HASH: 7a4ac2962b40cb774d272a6135ec4acd
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . $__templater->escape($__vars['boardTitle']) . ' Account Upgrade Subscription Renewal' . '
</mail:subject>

' . '' . $__templater->escape($__vars['username']) . ', your account upgrade subscription named <i><b>' . $__templater->escape($__vars['upgrade_title']) . '</b></i> at ' . $__templater->escape($__vars['boardTitle']) . ' will automatically renew in ' . $__templater->escape($__vars['num_days']) . ' days.<br />We hope you have been enjoying the benefits this upgrade offers and thank you in advance for renewing your subscription.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" style="color: #176093; text-decoration: none">here</a>.<p>Sincerely,<br />
' . $__templater->escape($__vars['boardTitle']) . '</p>' . '

' . '<p class="minorText">Please do not reply to this message. You must visit the forum to reply.</p>

<p class="minorText">This message was sent to you because you opted to receive emails when your subscriptions are about to expire at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'sv_ups_expired_expirying', 'id' => $__vars['xf']['toUser']['user_id'], ), ), true) . '">disable emails when your subscriptions are about to expire</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>';
	return $__finalCompiled;
});