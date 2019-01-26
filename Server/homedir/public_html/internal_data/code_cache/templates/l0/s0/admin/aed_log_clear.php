<?php
// FROM HASH: 529487a1878e7484f999393325b24401
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->form('
    <div class="block-container">
        <div class="block-body">
            ' . $__templater->formInfoRow('
                ' . 'Are you sure you want to clear the Alter Ego Detector log?' . '
            ', array(
		'rowtype' => 'confirm',
	)) . '
        </div>
        ' . $__templater->formSubmitRow(array(
		'submit' => 'Clear',
		'icon' => 'delete',
	), array(
		'rowtype' => 'simple',
	)) . '
    </div>
', array(
		'action' => $__templater->fn('link', array('logs/aed-logs/clear', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});