<?php
// FROM HASH: 18bf9cddfd48512ba1c85c9812d9da38
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('memberNotes', 'view', ))) {
		$__finalCompiled .= '

';
		$__templater->includeCss('andy_membernotes.less');
		$__finalCompiled .= '
	
<div class="block">
	<div class="block-container">
		<h3 class="block-minorHeader">' . 'Member notes' . '</h3>
		<div class="block-body block-row">
			';
		if ($__templater->isTraversable($__vars['results'])) {
			foreach ($__vars['results'] AS $__vars['result']) {
				$__finalCompiled .= '
				' . $__templater->filter($__vars['result']['notes'], array(array('nl2br', array()),), true) . '
			';
			}
		}
		$__finalCompiled .= '
		</div>
		<div class="block-footer">
			<span class="block-footer-counter">
				<a href="' . $__templater->fn('link', array('membernotes/edit', '', array('user_id' => $__vars['userId'], ), ), true) . '">' . 'Edit' . '</a>
			</span>
		</div>
	</div>
</div>

';
	}
	return $__finalCompiled;
});