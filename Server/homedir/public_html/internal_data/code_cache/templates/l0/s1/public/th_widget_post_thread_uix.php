<?php
// FROM HASH: 8c2813b17265714177f554b74022345a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
		$__finalCompiled .= '
	<div class="block" ' . $__templater->fn('widget_data', array($__vars['widget'], true, ), true) . '>
		<div class="block-container">
			<h3 class="block-minorHeader">' . $__templater->escape($__vars['title']) . '</h3>
			<div class="block-body">
				<div class="block-row">
					' . $__templater->filter($__vars['options']['description'], array(array('raw', array()),), true) . '
				</div>
				<div class="block-row">
					' . $__templater->button('
						' . 'Post thread' . $__vars['xf']['language']['ellipsis'] . '
					', array(
			'href' => $__templater->fn('link', array('forums/create-thread', ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => 'true',
		), '', array(
		)) . '
				</div>
			</div>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});