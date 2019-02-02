<?php
// FROM HASH: 4a8f9bc029b99046d5c3f5da515dfd36
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
				' . 'You need to reply to this in order to see this content.' . '
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});