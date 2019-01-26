<?php
// FROM HASH: 7e0a5f0a38c1e86a14ee7b9386d3ed6c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="contentRow-title">
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => 'Anonymous', ), ), true) . ' reviewed the resource ' . ((((('<a href="' . $__templater->fn('link', array('resources/review', $__vars['content'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['content']['Resource'], ), true)) . $__templater->escape($__vars['content']['Resource']['title'])) . '</a>') . '.' . '
</div>

<div class="contentRow-snippet">
	' . $__templater->callMacro('rating_macros', 'stars', array(
		'rating' => $__vars['content']['rating'],
		'class' => 'ratingStars--smaller',
	), $__vars) . '

	' . $__templater->fn('snippet', array($__vars['content']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], ), true) . '
</div>


<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});