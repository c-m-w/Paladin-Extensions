<?php
// FROM HASH: 58b5fc985abf9b0698d7252dd35f5a48
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('bb_code.less');
	$__finalCompiled .= '

<div class="bbCodeBlock bbCodeBlock--hide bbCodeBlock--' . ($__vars['visible'] ? 'visible' : 'hidden') . '">
	<div class="bbCodeBlock-content">
		<div class="bbCodeBlock-expandContent">
			';
	if ($__vars['visible']) {
		$__finalCompiled .= '
				' . $__templater->escape($__vars['content']) . '
			';
	} else {
		$__finalCompiled .= '
				' . 'You need to like or reply to this in order to see this content.' . '
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});