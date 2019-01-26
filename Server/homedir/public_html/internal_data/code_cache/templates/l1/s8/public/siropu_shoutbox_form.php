<?php
// FROM HASH: 1327fa426b8dcb4c29a701b37254e858
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
			<span>
				' . $__templater->formTextBox(array(
			'name' => 'shout',
			'placeholder' => 'Speak your mind :)',
			'maxlength' => $__vars['xf']['options']['siropuShoutboxShoutMaxLength'],
			'autocomplete' => 'off',
			'data-xf-init' => 'user-mentioner',
		)) . '
				';
		if ($__vars['xf']['options']['siropuShoutboxAllowBBCodes'] AND $__vars['xf']['options']['siropuShoutboxSmilieButton']) {
			$__finalCompiled .= '
					';
			$__templater->includeCss('editor.less');
			$__finalCompiled .= '
					<button type="button" class="button button--link" title="' . $__templater->filter('Smilies', array(array('for_attr', array()),), true) . '" data-xf-init="tooltip siropu-shoutbox-smilies" style="height:31px;"><i class="fa fa-smile-o" aria-hidden="true"></i></button>
				';
		}
		$__finalCompiled .= '
				<button type="submit" class="button button--link" title="' . $__templater->filter('Post', array(array('for_attr', array()),), true) . '" data-xf-init="tooltip" style="height:31px;"><i class="fa fa-comment" aria-hidden="true"></i></button>
			</span>
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