<?php
// FROM HASH: 1dbebd5e25690adac98d2e8a7ef5dabd
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['reactionContentList']) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
				' . $__templater->filter($__vars['reactionContentList'], array(array('raw', array()),), true) . '
			';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
		<div class="reactions-left">
			' . $__compilerTemp1 . '
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '


';
	if ($__vars['reactionList']) {
		$__finalCompiled .= '
	';
		$__compilerTemp2 = '';
		$__compilerTemp2 .= '
				' . $__templater->filter($__vars['reactionList'], array(array('raw', array()),), true) . '
			';
		if (strlen(trim($__compilerTemp2)) > 0) {
			$__finalCompiled .= '
		<div class="reactions-right">
			' . $__compilerTemp2 . '
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});