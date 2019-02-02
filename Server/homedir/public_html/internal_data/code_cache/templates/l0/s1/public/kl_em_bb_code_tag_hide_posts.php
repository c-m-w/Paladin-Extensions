<?php
// FROM HASH: 2386a74df0a8ad228e2714ffc7f32dd5
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
				';
		if ($__vars['message_threshold'] === -1) {
			$__finalCompiled .= '
					' . 'You are not allowed to view this content.' . '
				';
		} else {
			$__finalCompiled .= '
					' . 'You need ' . ($__vars['message_threshold'] - $__vars['message_count']) . ' more posts to view this content.' . '
				';
		}
		$__finalCompiled .= '
			';
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});