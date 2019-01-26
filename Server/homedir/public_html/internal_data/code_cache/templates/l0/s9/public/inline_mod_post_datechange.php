<?php
// FROM HASH: 688f3a8398de224346c559a4478c7837
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__vars['number'] = ($__vars['post']['position'] + 1);
	$__finalCompiled .= '
';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Change Date for Post #' . $__templater->escape($__vars['number']) . '');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['posts'])) {
		foreach ($__vars['posts'] AS $__vars['post']) {
			$__compilerTemp1 .= '
        ' . $__templater->formHiddenVal('ids[]', $__vars['post']['post_id'], array(
			)) . '
    ';
		}
	}
	$__finalCompiled .= $__templater->form('
    <div class="block-container">
        <div class="block-body">
            ' . $__templater->formTextBoxRow(array(
		'name' => 'datechange',
		'value' => $__vars['formatted_date'],
	), array(
		'label' => 'New Date',
	)) . '
            ' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
        </div>
    </div>

    ' . $__compilerTemp1 . '

    ' . $__templater->formHiddenVal('type', 'post', array(
	)) . '
    ' . $__templater->formHiddenVal('action', 'datechange', array(
	)) . '
    ' . $__templater->formHiddenVal('confirmed', '1', array(
	)) . '

    ' . $__templater->fn('redirect_input', array($__vars['redirect'], null, true)) . '
', array(
		'action' => $__templater->fn('link', array('inline-mod', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});