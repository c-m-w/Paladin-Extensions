<?php
// FROM HASH: 3551e58257e728c12ecb9c0378a4327d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . $__templater->escape($__vars['boardTitle']) . ' Account Upgrade Subscription Reversal' . '
</mail:subject>

' . '' . $__templater->escape($__vars['username']) . ', your payment for extending the account subscription named <i><b>' . $__templater->escape($__vars['upgrade_title']) . '</b></i> at ' . $__templater->escape($__vars['boardTitle']) . ' has been reversed.<br />Therefore the upgrade expiry date has been adjusted accordingly.<br />You may view your account upgrades <a href="' . $__templater->escape($__vars['upgradeUrl']) . '" style="color: #176093; text-decoration: none">here</a>.<p>Sincerely,<br />
' . $__templater->escape($__vars['boardTitle']) . '</p>' . '

' . '<p class="minorText">Please do not reply to this message. You must visit the forum to reply.</p>

<p class="minorText">This message was sent to you because you opted to receive emails when your user upgrade payments are reversed ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'user_upgrade_reversed', 'id' => $__vars['xf']['toUser']['user_id'], ), ), true) . '">disable emails when youur user upgrade payments are reversed</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>';
	return $__finalCompiled;
});