<?php
// FROM HASH: 4d216ba17d2d94d7874366e85ff930df
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<hr class="formRowSep" />

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[currentPageLink]',
		'selected' => $__vars['options']['currentPageLink'],
		'label' => 'Enable current page referral link',
		'_type' => 'option',
	)), array(
		'explain' => 'This option allows you to display the referral link of the current page viewed.',
	)) . '

' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[invitationsSent]',
		'selected' => $__vars['options']['invitationsSent'],
		'label' => 'Enable invitations sent link',
		'_type' => 'option',
	)), array(
		'explain' => 'This option allows you to display a quick link to the invitations the user has sent.',
	));
	return $__finalCompiled;
});