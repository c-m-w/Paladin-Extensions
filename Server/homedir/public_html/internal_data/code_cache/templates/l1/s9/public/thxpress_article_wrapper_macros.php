<?php
// FROM HASH: 0d09fb59ac6156a17043fc7115be64c8
return array('macros' => array('header' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'article' => '!',
		'thread' => '!',
		'titleHtml' => null,
		'showMeta' => true,
		'metaHtml' => null,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	
	';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['thread'], 'canReply', array())) {
		$__compilerTemp1 .= '
			' . $__templater->button('
				' . 'thxpress_go_to_article' . '
			', array(
			'href' => $__vars['article']['link'],
			'class' => 'button--cta',
			'icon' => 'article',
		), '', array(
		)) . '
		';
	}
	$__compilerTemp2 = '';
	if ($__templater->method($__vars['thread'], 'canReply', array())) {
		$__compilerTemp2 .= '
            ' . $__templater->button('
                ' . 'Reply' . '
            ', array(
			'href' => $__templater->fn('link', array('threads/reply', $__vars['thread'], ), false),
			'class' => 'button--cta uix_quickReply--button',
			'icon' => 'write',
		), '', array(
		)) . '
        ';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
		' . $__compilerTemp1 . '
        ' . $__compilerTemp2 . '
	');
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<!--dont believe we need this anymore (IH) -->
';
	return $__finalCompiled;
});