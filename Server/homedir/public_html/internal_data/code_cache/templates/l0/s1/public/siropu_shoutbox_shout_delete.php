<?php
// FROM HASH: bbd96d773b5a929acb76b45333065180
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
			<p>' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '</p>
			<strong>' . $__templater->escape($__vars['shout']['shout_message']) . '</strong>
			', array(
		'rowtype' => 'confirm',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
		'class' => 'js-overlayClose',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('shoutbox/delete', $__vars['shout'], ), false),
		'class' => 'block',
		'ajax' => 'true',
		'data-xf-init' => 'siropu-shoutbox-delete-shout',
	));
	return $__finalCompiled;
});