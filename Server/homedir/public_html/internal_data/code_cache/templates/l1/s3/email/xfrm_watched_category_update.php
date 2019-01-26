<?php
// FROM HASH: 56d1baaa160244898936c27cf651a533
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . ($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title'])) . ' updated: ' . $__templater->escape($__vars['update']['title']) . '' . '
</mail:subject>

' . '<p>' . $__templater->fn('username_link_email', array($__vars['resource']['User'], $__vars['resource']['username'], ), true) . ' updated an extension within a category you are watching at ' . (((('<a href="' . $__templater->fn('link', array('canonical:index', ), true)) . '">') . $__templater->escape($__vars['xf']['options']['boardTitle'])) . '</a>') . '.</p>' . '

<h2><a href="' . $__templater->fn('link', array('canonical:resources/update', $__vars['update'], ), true) . '">' . $__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . $__templater->escape($__vars['update']['title']) . '</a></h2>

';
	if ($__vars['xf']['options']['emailWatchedThreadIncludeMessage']) {
		$__finalCompiled .= '
	<div class="message">' . $__templater->fn('bb_code_type', array('emailHtml', $__vars['update']['message'], 'resource_update', $__vars['update'], ), true) . '</div>
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro('xfrm_resource_macros', 'go_resource_bar', array(
		'resource' => $__vars['resource'],
		'watchType' => 'category',
	), $__vars) . '

' . $__templater->callMacro('xfrm_resource_macros', 'watched_category_footer', array(
		'category' => $__vars['category'],
		'resource' => $__vars['resource'],
	), $__vars) . '
';
	return $__finalCompiled;
});