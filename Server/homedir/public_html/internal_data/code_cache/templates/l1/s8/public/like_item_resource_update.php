<?php
// FROM HASH: 79c50592c8f9bbda7c8d0e59c4bb9a2f
return array('macros' => array('like_snippet' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'liker' => '!',
		'update' => '!',
		'date' => '!',
		'fallbackName' => 'Unknown member',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="contentRow-title">
		';
	if ($__vars['update']['Resource']['user_id'] == $__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
			';
		if ($__templater->method($__vars['update'], 'isDescription', array())) {
			$__finalCompiled .= '
				' . '' . $__templater->fn('username_link', array($__vars['liker'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' liked your extension ' . ((((('<a href="' . $__templater->fn('link', array('resources', $__vars['update']['Resource'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['update']['Resource'], ), true)) . $__templater->escape($__vars['update']['Resource']['title'])) . '</a>') . '.' . '
			';
		} else {
			$__finalCompiled .= '
				' . '' . $__templater->fn('username_link', array($__vars['liker'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' liked your update for extension ' . ((((('<a href="' . $__templater->fn('link', array('resources/update', $__vars['update'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['update']['Resource'], ), true)) . $__templater->escape($__vars['update']['Resource']['title'])) . '</a>') . '.' . '
			';
		}
		$__finalCompiled .= '
		';
	} else {
		$__finalCompiled .= '
			';
		if ($__templater->method($__vars['update'], 'isDescription', array())) {
			$__finalCompiled .= '
				' . '' . $__templater->fn('username_link', array($__vars['liker'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' liked ' . $__templater->escape($__vars['update']['Resource']['username']) . '\'s extension ' . ((((('<a href="' . $__templater->fn('link', array('resources', $__vars['update']['Resource'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['update']['Resource'], ), true)) . $__templater->escape($__vars['update']['Resource']['title'])) . '</a>') . '.' . '
			';
		} else {
			$__finalCompiled .= '
				' . '' . $__templater->fn('username_link', array($__vars['liker'], false, array('defaultname' => $__vars['fallbackName'], ), ), true) . ' liked ' . $__templater->escape($__vars['update']['Resource']['username']) . '\'s update for extension ' . ((((('<a href="' . $__templater->fn('link', array('resources/update', $__vars['update'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['update']['Resource'], ), true)) . $__templater->escape($__vars['update']['Resource']['title'])) . '</a>') . '.' . '
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '
	</div>

	<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['update']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], array('stripQuote' => true, ), ), true) . '</div>

	<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['date'], array(
	))) . '</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . $__templater->callMacro(null, 'like_snippet', array(
		'liker' => $__vars['like']['Liker'],
		'update' => $__vars['content'],
		'date' => $__vars['like']['like_date'],
	), $__vars);
	return $__finalCompiled;
});