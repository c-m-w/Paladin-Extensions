<?php
// FROM HASH: f07a807dc01ae3fe2bf4a1a617d85821
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->form('
    <div class="block-container">
        <div class="block-body">
            ' . $__templater->formInfoRow('
                ' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '
                <strong>
                    ' . $__templater->escape($__vars['laulog']['from_username']) . ' - ' . $__templater->escape($__vars['laulog']['to_username']) . ': <br />
                    ' . ($__vars['laulog']['reason'] ? $__templater->escape($__vars['laulog']['reason']) : 'N/A') . '
                </strong>
            ', array(
		'rowtype' => 'confirm',
	)) . '
        </div>
        ' . $__templater->formSubmitRow(array(
		'icon' => 'delete',
	), array(
		'rowtype' => 'simple',
	)) . '
    </div>
', array(
		'action' => $__templater->fn('link', array('laulogs/delete', $__vars['laulog'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});