<?php
// FROM HASH: 483f42017391d1c12d3b822659ae4006
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Create invitations');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_tabs', array(
		'activeTab' => 'create',
	), $__vars) . '

		<div class="block-body">
			' . $__templater->form('
				' . $__templater->formInfoRow('This option allows you to create invitations that you can send out using a method other than email.', array(
	)) . '
				' . $__templater->formNumberBoxRow(array(
		'name' => 'count',
		'value' => '1',
		'min' => '1',
		'max' => '10',
	), array(
		'label' => 'Number of invitations',
	)) . '
				' . $__templater->formSubmitRow(array(
		'icon' => 'add',
		'submit' => 'Create invitations',
	), array(
	)) . '
			', array(
		'action' => $__templater->fn('link', array('account/invitations/create', ), false),
		'ajax' => 'true',
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});