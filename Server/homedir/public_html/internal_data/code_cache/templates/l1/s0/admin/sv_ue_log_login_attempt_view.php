<?php
// FROM HASH: a08b142954090420c9fb39784e851997
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login attempt');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formRow('
				<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('login' => $__vars['entry']['login'], ), ), true) . '">' . $__templater->escape($__vars['entry']['login']) . '</a>
			', array(
		'label' => 'Login',
	)) . '

			' . $__templater->formRow('
				<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('ip_address' => $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), false), ), ), true) . '">' . $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), true) . '</a>
			', array(
		'label' => 'IP address',
	)) . '

			' . $__templater->formRow('
				' . $__templater->fn('date_dynamic', array($__vars['entry']['attempt_date'], array(
	))) . '
			', array(
		'label' => 'Date',
	)) . '
		</div>

		';
	if ($__templater->method($__vars['entry'], 'canDelete', array())) {
		$__finalCompiled .= '
			' . $__templater->form('
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'delete_login',
			'value' => '1',
			'label' => 'Clear all login attempts for this login',
			'_type' => 'option',
		),
		array(
			'name' => 'delete_ip',
			'value' => '1',
			'label' => 'Clear all login attempts for this IP address',
			'_type' => 'option',
		)), array(
		)) . '
				' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
				' . $__templater->formSubmitRow(array(
			'icon' => 'delete',
		), array(
		)) . '
			', array(
			'action' => $__templater->fn('link', array('logs/login-attempt', $__vars['entry'], ), false),
		)) . '
		';
	}
	$__finalCompiled .= '
	</div>
</div>
';
	return $__finalCompiled;
});