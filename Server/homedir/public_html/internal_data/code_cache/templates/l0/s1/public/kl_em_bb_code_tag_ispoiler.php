<?php
// FROM HASH: ac0580c76a8fa23821cb5bbef07cb4c7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('bb_code.less');
	$__finalCompiled .= '

<span class="klEMiSpoiler">
	<button class="klEMiSpoiler--button" data-xf-click="toggle"
		data-xf-init="tooltip" title="' . 'Click to reveal or hide spoiler' . '">
		<span>';
	if ($__vars['title']) {
		$__finalCompiled .= '<span class="klEMiSpoiler--title">' . $__templater->escape($__vars['title']) . '</span>';
	}
	$__finalCompiled .= '</span>
	</button>
	<span class="klEMiSpoiler--content">' . $__templater->escape($__vars['content']) . '</span>
</span>';
	return $__finalCompiled;
});