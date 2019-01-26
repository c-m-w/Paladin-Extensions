<?php
// FROM HASH: a065b5dec1cfb6bdbb35928c9ef20da0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Invitation link' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['invitation']['invitation_code']));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
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