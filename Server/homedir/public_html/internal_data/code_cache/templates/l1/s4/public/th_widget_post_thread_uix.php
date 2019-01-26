<?php
// FROM HASH: ef89ce7bf8c2cb455941f4ab35fd32ce
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->method($__vars['xf']['visitor'], 'canUseSiropuShoutbox', array())) {
		$__finalCompiled .= '
	';
		if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
			$__finalCompiled .= '
		<div class="block" ' . $__templater->fn('widget_data', array($__vars['widget'], true, ), true) . '>
			<div class="block-container">
				<div class="block-body uix_postThreadWidget">
					' . $__templater->callMacro('uix_icons.less', 'icon', array(
				'icon' => 'forum',
			), $__vars) . '
					<h3 class="uix_postThreadWidget__title">' . $__templater->escape($__vars['title']) . '</h3>
					<div class="uix_postThreadWidget__description">' . $__templater->filter($__vars['options']['description'], array(array('raw', array()),), true) . '</div>
					' . $__templater->button('
						' . 'Post' . $__vars['xf']['language']['ellipsis'] . '
					', array(
				'href' => $__templater->fn('link', array('https://www.paladin.rip/forums/9/', ), false),
				'class' => 'button--cta',
				'icon' => 'write',
				'overlay' => 'true',
			), '', array(
			)) . '
				</div>
			</div>
		</div>
	';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});