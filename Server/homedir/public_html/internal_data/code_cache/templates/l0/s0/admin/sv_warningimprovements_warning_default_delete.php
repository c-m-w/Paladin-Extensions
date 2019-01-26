<?php
// FROM HASH: 034b63dd49c0657150aa263c48ecdcb9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm Deletion of Warning Default.');
	$__finalCompiled .= '

';
	$__templater->includeCss('public:delete_confirmation.css');
	$__finalCompiled .= '

' . $__templater->form('

    <div class="block-container">
        <div class="block-body">
            ' . $__templater->formInfoRow('
                ' . 'Please confirm that you want to delete the following' . $__vars['xf']['language']['label_separator'] . '
                <strong><a href="' . $__templater->fn('link', array('warnings/default/edit', null, array('warning_default_id' => $__vars['default']['warning_default_id'], ), ), true) . '">' . 'Points' . ': ' . $__templater->escape($__vars['default']['threshold_points']) . '</a></strong>
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
    ' . $__templater->fn('redirect_input', array(null, null, true)) . '
', array(
		'action' => $__templater->fn('link', array('warnings/default/delete', null, array('warning_default_id' => $__vars['default']['warning_default_id'], ), ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});