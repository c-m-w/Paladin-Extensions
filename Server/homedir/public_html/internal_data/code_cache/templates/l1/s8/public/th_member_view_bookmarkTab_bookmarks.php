<?php
// FROM HASH: 725fc6f475c46e4ef9dae80e62931fb7
return array('macros' => array('tab' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'user' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('members/bookmarks', $__vars['user'], ), true) . '"
	   class="tabs-tab"
	   id="bookmarks"
	   role="tab">' . 'Bookmarks' . '</a>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

<li data-href="' . $__templater->fn('link', array('members/bookmarks', $__vars['user'], array('hide_pagination' => 1, ), ), true) . '" role="tabpanel" aria-labelledby="bookmarks">
	<div class="blockMessage">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
</li>';
	return $__finalCompiled;
});