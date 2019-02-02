<?php
// FROM HASH: bdd9426ebcc730e9cf7e7cebfa14327c
return array('macros' => array('row_output' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'title' => '!',
		'desc' => '!',
		'example' => '!',
		'anchor' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="' . $__templater->escape($__vars['anchor']) . '"></span>
		<h3 class="block-textHeader">' . $__templater->escape($__vars['title']) . '</h3>
		<div>' . $__templater->escape($__vars['desc']) . '</div>
		' . $__templater->callMacro(null, 'example_output', array(
		'bbCode' => $__vars['example'],
	), $__vars) . '
	</li>
';
	return $__finalCompiled;
},
'example_output' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'bbCode' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="bbCodeDemoBlock">
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd>' . $__templater->filter($__vars['bbCode'], array(array('nl2br', array()),), true) . '</dd>
		</dl>
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd>' . $__templater->fn('bb_code', array($__vars['bbCode'], 'help', null, ), true) . '</dd>
		</dl>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('help_bb_codes.less');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<ul class="listPlain block-body">
' . $__templater->includeTemplate('kl_em_help_page_bb_codes', $__vars) . '
</ul>
	</div>
</div>

' . '

';
	return $__finalCompiled;
});