<?php
// FROM HASH: 79c2e0127a8744f0de0f3c23371285ee
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->formNumberBoxRow(array(
		'name' => 'exup_days',
		'value' => $__vars['upgrade']['exup_days'],
		'step' => '1',
		'min' => '0',
		'max' => '30',
	), array(
		'label' => 'Expiration Notification (Days)',
		'explain' => 'Notify users this many days before the upgrade expires (max 30).<br />To disable notifications, set this value to Zero (0).<br /><br />An <a href="admin.php?options/groups/exup/">Alert and/or Email</a> will be sent to all users who own this upgrade notifying them that it will expire in X days.<br />If the upgrade is a recurring one, the notification will be sent out X days prior to the subscription renewal date. While this may help users ensure that they have sufficient funds in their PayPal account prior to renewal, it may also cause them to cancel the subscription.',
	));
	return $__finalCompiled;
});