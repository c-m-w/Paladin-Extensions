<?php
// FROM HASH: 5303d538f54665ee92769af4bb2c4eab
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
	' . $__templater->form('
		<div class="block-container">
			<h3 class="block-minorHeader">' . 'Log in' . '</h3>
			<div class="block-body block-row">
				<label for="ctrl_loginWidget_login">' . 'Your name or email address' . '</label>
				<div class="u-inputSpacer">
					<input name="login" id="ctrl_loginWidget_login" class="input" />
				</div>
			</div>

			<div class="block-body block-row">
				<label for="ctrl_loginWidget_password">' . 'Password' . '</label>
				<div class="u-inputSpacer">
					<input name="password" id="ctrl_loginWidget_password" type="password" class="input" />
					<a href="' . $__templater->fn('link', array('lost-password', ), true) . '" data-xf-click="overlay">' . 'Forgot your password?' . '</a>
				</div>
			</div>

			<div class="block-body block-row">
				<label>
					<input type="checkbox" name="remember" value="1" checked="checked"> ' . 'Stay logged in' . '
				</label>
			</div>

			' . $__templater->formSubmitRow(array(
			'icon' => 'login',
		), array(
		)) . '
		</div>
	', array(
			'action' => $__templater->fn('link', array('login/login', ), false),
			'class' => 'block',
			'attributes' => $__templater->fn('widget_data', array($__vars['widget'], true, ), false),
		)) . '
';
	}
	return $__finalCompiled;
});