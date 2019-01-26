<?php
// FROM HASH: b85a098f86628fb165e35c27628fbbd1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['rewardType'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add reward type' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['rewardType']['type_phrase']));
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit reward type' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['rewardType']['name']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['rewardType'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('referral-contests/reward-types/delete', $__vars['rewardType'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['currencies'], 'empty', array())) {
		$__compilerTemp1 .= '
				';
		$__compilerTemp2 = $__templater->mergeChoiceOptions(array(), $__vars['currencies']);
		$__compilerTemp1 .= $__templater->formSelectRow(array(
			'name' => 'currency',
			'value' => $__vars['rewardType']['currency'],
		), $__compilerTemp2, array(
			'label' => 'Currency',
		)) . '
			';
	}
	$__compilerTemp3 = '';
	if ($__templater->method($__vars['rewardType'], 'isInsert', array())) {
		$__compilerTemp3 .= '
		' . $__templater->formHiddenVal('type', $__vars['rewardType']['type'], array(
		)) . '
	';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'name',
		'value' => $__vars['rewardType']['name'],
	), array(
		'label' => 'Reward type name',
		'explain' => 'Set a short name for this reward type. The name will be made public to the users.',
	)) . '

			' . $__compilerTemp1 . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
	)) . '
	</div>
	' . $__compilerTemp3 . '
', array(
		'action' => $__templater->fn('link', array('referral-contests/reward-types/save', $__vars['rewardType'], ), false),
		'upload' => 'true',
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});