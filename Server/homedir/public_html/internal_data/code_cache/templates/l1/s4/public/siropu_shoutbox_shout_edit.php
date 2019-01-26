<?php
// FROM HASH: e87ce84580f8a63a84371980839eb62c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit shout');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			<input type="text" name="message" class="input" value="' . $__templater->escape($__vars['shout']['shout_message']) . '" autocomplete="off">
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'class' => 'js-overlayClose',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('shoutbox/edit', $__vars['shout'], ), false),
		'class' => 'block',
		'data-xf-init' => 'siropu-shoutbox-edit-shout',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});