<?php
// FROM HASH: ecefc1ba5dad046de278fa33b129250b
return array('macros' => array('quick_filter' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'key' => '',
		'ajax' => '',
		'class' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__templater->includeJs(array(
		'src' => 'xf/filter.js',
		'min' => '1',
	));
	$__finalCompiled .= '
	<div class="' . $__templater->escape($__vars['class']) . ' quickFilter u-jsOnly" data-xf-init="filter" data-key="' . $__templater->escape($__vars['key']) . '" data-ajax="' . $__templater->escape($__vars['ajax']) . '">
		<div class="inputGroup inputGroup--inline inputGroup--joined">
			<input type="text" class="input js-filterInput" placeholder="' . $__templater->filter('Filter' . $__vars['xf']['language']['ellipsis'], array(array('for_attr', array()),), true) . '" data-xf-key="' . $__templater->filter('f', array(array('for_attr', array()),), true) . '" />
			' . $__templater->formCheckBox(array(
		'standalone' => 'true',
	), array(array(
		'labelclass' => 'inputGroup-text',
		'class' => 'js-filterPrefix',
		'label' => 'Prefix',
		'_type' => 'option',
	))) . '
			<i class="inputGroup-text js-filterClear is-disabled" aria-hidden="true"></i>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '
';
	return $__finalCompiled;
});