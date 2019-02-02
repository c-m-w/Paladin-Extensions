<?php
// FROM HASH: 31ff8c09ae9fb1d82077c4ac5bfce845
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
				' . 'You need to like this in order to view this content.' . '
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});