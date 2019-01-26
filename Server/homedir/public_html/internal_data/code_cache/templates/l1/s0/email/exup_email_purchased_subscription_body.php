<?php
// FROM HASH: fb37ae1dafbe241727698727afb17479
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . $__templater->escape($__vars['boardTitle']) . ' Account Upgrade Subscription Purchase' . '
</mail:subject>

' . '' . $__templater->escape($__vars['username']) . ', thank you for purchasing the account subscription named <i><b>' . $__templater->escape($__vars['upgrade_title']) . '</b></i> at ' . $__templater->escape($__vars['boardTitle']) . '.<br />We hope you will take advantage of and enjoy all the benefits it has to offer.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" style="color: #176093; text-decoration: none">here</a>.<p>Sincerely,<br />
' . $__templater->escape($__vars['boardTitle']) . '</p>' . '

' . '<p class="minorText">Please do not reply to this message. You must visit the forum to reply.</p>

<p class="minorText">This message was sent to you because you opted to receive emails when you purchase user upgrades at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'user_upgrade_purchased', 'id' => $__vars['xf']['toUser']['user_id'], ), ), true) . '">disable emails when you purchase user upgrades</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>';
	return $__finalCompiled;
});