<?php
// FROM HASH: 326e9cbb0e60f6929ecb8bc2ccb93c78
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="contentRow-title">
	' . '' . $__templater->fn('username_link', array($__vars['user'], false, array('defaultname' => $__vars['newsFeed']['username'], ), ), true) . ' created the extension ' . ((((('<a href="' . $__templater->fn('link', array('resources', $__vars['content'], ), true)) . '">') . $__templater->fn('prefix', array('resource', $__vars['content'], ), true)) . $__templater->escape($__vars['content']['title'])) . '</a>') . ' in ' . (((('<a href="' . $__templater->fn('link', array('resources/categories', $__vars['content']['Category'], ), true)) . '">') . $__templater->escape($__vars['content']['Category']['title'])) . '</a>') . '.' . '
</div>

<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['content']['Description']['message'], $__vars['xf']['options']['newsFeedMessageSnippetLength'], array('stripQuote' => true, ), ), true) . '</div>
';
	if ($__vars['content']['Description']['attach_count']) {
		$__finalCompiled .= '
	' . $__templater->callMacro('news_feed_attached_images', 'attached_images', array(
			'attachments' => $__vars['content']['Description']['Attachments'],
			'link' => $__templater->fn('link', array('resources', $__vars['content'], ), false),
		), $__vars) . '
';
	}
	$__finalCompiled .= '

<div class="contentRow-minor">' . $__templater->fn('date_dynamic', array($__vars['newsFeed']['event_date'], array(
	))) . '</div>';
	return $__finalCompiled;
});