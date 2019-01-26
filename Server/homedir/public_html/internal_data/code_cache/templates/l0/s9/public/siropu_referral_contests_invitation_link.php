<?php
// FROM HASH: 80ec20c1fa0da48085c22da6d0238768
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Invitation link' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['invitation']['invitation_code']));
	$__finalCompiled .= '

';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

';
	$__templater->inlineJs('
	$(function()
	{
		setTimeout(function()
		{
			$(\'textarea[readonly]\').select();
		}, 500);
	});
');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Copy this link and send it to one of your friends to invite him or her to join our community.' . '
			', array(
	)) . '
			' . $__templater->formTextAreaRow(array(
		'value' => $__vars['invitation']['invitation_url'],
		'readonly' => 'readonly',
	), array(
		'label' => 'URL',
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});