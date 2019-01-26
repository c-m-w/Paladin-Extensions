<?php
// FROM HASH: 671be6d2cec8c7c50ec7e4360d708d96
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->method($__vars['xf']['visitor'], 'canUseSiropuShoutbox', array())) {
		$__finalCompiled .= '
';
		if ($__templater->method($__vars['xf']['visitor'], 'canCreateThread', array())) {
			$__finalCompiled .= '
	<div class="block" ' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
		<div class="block-container">
			<div class="block-body uix_postThreadWidget block-row">
				<i class="mdi mdi-forum"></i>
				<h3 class="uix_postThreadWidget__title">' . $__templater->escape($__vars['title']) . '</h3>
				<div class="uix_postThreadWidget__description">' . $__templater->filter($__vars['options']['description'], array(array('raw', array()),), true) . '</div>
				' . $__templater->button('
					' . 'Post' . '
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
';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('th_widget_post_thread_uix.less');
	return $__finalCompiled;
});