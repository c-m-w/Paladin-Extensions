<?php
// FROM HASH: 48f43120288556fd15e2cef0848d7a03
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . 'Latest topics' . ' (' . '' . ' ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . ')
</mail:subject>

';
	if ($__vars['xf']['options']['inactiveMembersImageUrl'] != '') {
		$__finalCompiled .= '
	<img src="' . $__templater->escape($__vars['xf']['options']['inactiveMembersImageUrl']) . '" alt="image" />
';
	}
	$__finalCompiled .= '

<br />

' . 'Hi ' . $__templater->escape($__vars['username']) . ',
<br /><br />
We look forward to seeing you at ' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '.
<br /><br />
Some of our latest topics include:' . '

<br />

';
	if ($__templater->isTraversable($__vars['threads'])) {
		foreach ($__vars['threads'] AS $__vars['thread']) {
			$__finalCompiled .= '
	<br />
	<div><a href="' . $__templater->fn('link', array('canonical:threads/', $__templater->filter($__vars['thread'], array(array('censor', array()),), false), ), true) . '">' . $__templater->filter($__vars['thread']['title'], array(array('censor', array()),), true) . '</a></div>
	<div style="color:#8c8c8c;font-size:80%;">' . $__templater->escape($__vars['thread']['forumTitle']) . '</div>
';
		}
	}
	$__finalCompiled .= '

<br />
<a href="' . $__templater->fn('link', array('canonical:account/preferences', ), true) . '">' . 'Click here to unsubscribe.' . '</a>';
	return $__finalCompiled;
});