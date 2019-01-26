<?php
// FROM HASH: a2c403a7722286c869d6d370fbb9711a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = array();
	if ($__templater->method($__vars['thread'], 'canEditLockPermissions', array())) {
		$__compilerTemp1[] = array(
			'name' => 'allow_user_lock',
			'value' => '1',
			'selected' => $__vars['thread']['ThreadPermissions']['allowLockByUser'],
			'label' => 'Lock thread',
			'hint' => 'If enabled, the thread starter will be able to lock this thread even if it was unlocked by a moderator.',
			'afterhtml' => '
				' . $__templater->formHiddenVal('_xfSet[allow_user_lock]', '1', array(
		)) . '
			',
			'_type' => 'option',
		);
		$__compilerTemp1[] = array(
			'name' => 'allow_user_unlock',
			'value' => '1',
			'selected' => $__vars['thread']['ThreadPermissions']['allowUnlockByUser'],
			'label' => 'Unlock thread',
			'hint' => 'If enabled, the thread starter will be able to unlock this thread even if it was locked by a moderator.',
			'afterhtml' => '
				' . $__templater->formHiddenVal('_xfSet[allow_user_unlock]', '1', array(
		)) . '
			',
			'_type' => 'option',
		);
	}
	if ($__templater->method($__vars['thread'], 'canEditReplyBanPermissions', array())) {
		$__compilerTemp1[] = array(
			'name' => 'allow_user_reply_ban',
			'value' => '1',
			'selected' => $__vars['thread']['ThreadPermissions']['replyBanInOwnThread'],
			'label' => 'Manage reply bans',
			'hint' => 'If enabled, the thread starter will be able manage reply bans for this thread.',
			'afterhtml' => '
				' . $__templater->formHiddenVal('_xfSet[allow_user_reply_ban]', '1', array(
		)) . '
			',
			'_type' => 'option',
		);
	}
	$__finalCompiled .= $__templater->formCheckBoxRow(array(
		'hideempty' => 'true',
	), $__compilerTemp1, array(
		'rowtype' => $__vars['rowType'],
		'label' => 'Thread starter permissions',
	)) . '
';
	return $__finalCompiled;
});