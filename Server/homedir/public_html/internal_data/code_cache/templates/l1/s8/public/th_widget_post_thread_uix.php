<?php
// FROM HASH: 7151f2d102e7111ec13036b28f4ee0f0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'isMemberOf', array(5, )) == 0) {
		$__finalCompiled .= '
	<div class="block" ' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
		<div class="block-container">
			<div class="block-body uix_postThreadWidget block-row">
				<i class="mdi mdi-cart"></i>
				<h3 class="uix_postThreadWidget__title">' . $__templater->escape($__vars['title']) . '</h3>
					<div class="uix_postThreadWidget__description">' . $__templater->filter($__vars['options']['description'], array(array('raw', array()),), true) . '</div>
				' . $__templater->button('
					VIEW EXTENSIONS
				', array(
			'href' => $__templater->fn('link', array('extensions', ), false),
			'class' => 'button--cta',
		), '', array(
		)) . '
			</div>
		</div>
	</div>
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('th_widget_post_thread_uix.less');
	return $__finalCompiled;
});