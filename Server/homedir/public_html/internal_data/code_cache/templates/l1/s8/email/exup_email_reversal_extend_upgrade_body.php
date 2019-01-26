<?php
// FROM HASH: 7df84de287e36af1cca1dd737df0adb5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'exup_email_payment_reversal_extend_upgrade_subject' . '
</mail:subject>

' . 'exup_email_payment_reversal_extend_upgrade_body_html' . '

' . '<p class="minorText">Please do not reply to this message. You must visit the forum to reply.</p>

<p class="minorText">This message was sent to you because you opted to receive emails when your user upgrade payments are reversed ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.</p>

<p class="minorText">If you no longer wish to receive these emails, you may <a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['xf']['toUser'], array('t' => 'user_upgrade_reversed', 'id' => $__vars['xf']['toUser']['user_id'], ), ), true) . '">disable emails when youur user upgrade payments are reversed</a> or <a href="' . $__templater->fn('link', array('canonical:email-stop/all', $__vars['xf']['toUser'], ), true) . '">disable all emails</a>.</p>';
	return $__finalCompiled;
});