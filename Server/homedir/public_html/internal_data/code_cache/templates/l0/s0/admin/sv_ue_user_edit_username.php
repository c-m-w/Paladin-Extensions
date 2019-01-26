<?php
// FROM HASH: f42d764683f035d5f6d425b556068f9a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['user'], 'isUpdate', array())) {
		$__finalCompiled .= '
	';
		if (!$__templater->test($__vars['previousUsernameChanges'], 'empty', array())) {
			$__finalCompiled .= '
		';
			$__compilerTemp1 = '';
			if ($__templater->isTraversable($__vars['previousUsernameChanges'])) {
				foreach ($__vars['previousUsernameChanges'] AS $__vars['uncId'] => $__vars['previousUsernameChange']) {
					$__compilerTemp1 .= trim('
					<li><a href="' . $__templater->fn('link_type', array('public', 'members/username-change', '', array('unc_id' => $__vars['uncId'], ), ), true) . '" data-xf-click="overlay">' . $__templater->escape($__vars['previousUsernameChange']['to_username']) . '</a></li>
				');
				}
			}
			$__compilerTemp2 = '';
			if ($__vars['unseenUsernameChanges']) {
				$__compilerTemp2 .= '
					<li><a href="' . $__templater->fn('link_type', array('public', 'members/username-changes', $__vars['user'], ), true) . '" data-xf-click="overlay">' . 'and ' . $__templater->escape($__vars['unseenUsernameChanges']) . ' more.' . '</a></li>
				';
			}
			$__finalCompiled .= $__templater->formRow('
			<ul class="listInline listInline--comma">
				' . $__compilerTemp1 . '

				' . $__compilerTemp2 . '
			</ul>
		', array(
				'label' => 'Previous names',
			)) . '
	';
		}
		$__finalCompiled .= '

	' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'sv_ue_notify',
			'selected' => $__vars['xf']['options']['useress_acp_unc_notices_default'],
			'label' => 'Send user name change notifications',
			'_type' => 'option',
		),
		array(
			'name' => 'sv_ue_private',
			'selected' => $__vars['xf']['options']['useress_acp_unc_private_default'],
			'label' => 'Private user name change',
			'_type' => 'option',
		)), array(
		)) . '
';
	}
	return $__finalCompiled;
});