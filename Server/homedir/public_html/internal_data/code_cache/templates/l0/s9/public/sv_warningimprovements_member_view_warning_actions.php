<?php
// FROM HASH: 1a80e767c3282ce1227b5cfd28e91421
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['user']['warning_actions_count']) {
		$__finalCompiled .= '
	<li data-href="' . $__templater->fn('link', array('members/warning-actions', $__vars['user'], ), true) . '" role="tabpanel" aria-labelledby="warningActions">
		<div class="blockMessage">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
	</li>
';
	}
	return $__finalCompiled;
});