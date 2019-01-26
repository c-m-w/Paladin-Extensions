<?php
// FROM HASH: 1f29519bb4bc5ada7df5f776f24dee21
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Transfer purchase' . ' ' . $__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']));
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm which user you would like to transfer the following purchase from ' . $__templater->escape($__vars['purchase']['username']) . ' to:' . '
				<strong><a href="' . $__templater->fn('link', array('product-manager/purchases/edit', $__vars['purchase'], ), true) . '">' . $__templater->escape($__vars['purchase']['Product']['product_title']) . ' - ' . $__templater->escape($__vars['purchase']['purchase_key']) . '</a></strong>
				<div class="blockMessage blockMessage--important blockMessage--small">' . '<b>Note:</b> Both users (where valid) will be emailed regarding the transfer.' . '</div>
			', array(
		'rowtype' => 'confirm',
	)) . '
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'ac' => 'single',
	), array(
		'label' => 'User name',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Transfer',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/purchases/transfer', $__vars['purchase'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});