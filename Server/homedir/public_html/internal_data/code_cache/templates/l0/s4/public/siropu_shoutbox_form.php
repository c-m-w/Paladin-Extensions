<?php
// FROM HASH: 59d42b76943e9269d8d7ce2a2e73a0b6
return array('macros' => array('submit' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'class' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->method($__vars['xf']['visitor'], 'canUseSiropuShoutbox', array())) {
		$__finalCompiled .= '
		<form action="' . $__templater->fn('link', array('shoutbox/submit', ), true) . '"' . ($__vars['class'] ? ((' class="' . $__templater->escape($__vars['class'])) . '"') : '') . ' data-xf-init="siropu-shoutbox-submit">
			<input type="text" name="shout" class="input" maxlength="' . $__templater->escape($__vars['xf']['options']['siropuShoutboxShoutMaxLength']) . '" placeholder="' . 'What\'s on your mind?' . '" autocomplete="off" data-xf-init="user-mentioner">
			<!--<button type="submit" class="button">' . 'Shout!' . '</button>-->
		</form>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});