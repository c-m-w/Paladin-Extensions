<?php
// FROM HASH: 4e17419ab10a0e3e8fa9604e522ab05a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['contest'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add contest');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit contest' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['contest']['name']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['contest'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('referral-contests/delete', $__vars['contest'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	$__vars['counter'] = 0;
	if ($__templater->isTraversable($__vars['contest']['prizes'])) {
		foreach ($__vars['contest']['prizes'] AS $__vars['prize']) {
			$__vars['counter']++;
			$__compilerTemp1 .= '
						<li class="inputGroup">
							' . $__templater->formNumberBox(array(
				'name' => 'prizes[' . $__vars['counter'] . '][reward_amount]',
				'value' => $__vars['prize']['reward_amount'],
				'min' => '0',
				'required' => '',
			)) . '
							<span class="inputGroup-splitter"></span>
							';
			$__compilerTemp2 = array(array(
				'_type' => 'option',
			));
			$__compilerTemp2 = $__templater->mergeChoiceOptions($__compilerTemp2, $__vars['rewardTypes']);
			$__compilerTemp1 .= $__templater->formSelect(array(
				'name' => 'prizes[' . $__vars['counter'] . '][reward_type_id]',
				'value' => $__vars['prize']['reward_type_id'],
			), $__compilerTemp2) . '
						</li>
					';
		}
	}
	$__compilerTemp3 = array(array(
		'_type' => 'option',
	));
	$__compilerTemp3 = $__templater->mergeChoiceOptions($__compilerTemp3, $__vars['rewardTypes']);
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'name',
		'value' => $__vars['contest']['name'],
	), array(
		'label' => 'Contest name',
	)) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'description',
		'value' => $__vars['contest']['description'],
		'rows' => '3',
	), array(
		'label' => 'Contest description',
		'explain' => 'You may use XenForo template syntax here.',
	)) . '

			' . $__templater->formNumberBoxRow(array(
		'name' => 'minimum_posts',
		'value' => $__vars['contest']['minimum_posts'],
		'min' => '0',
	), array(
		'label' => 'Referral minimum posts',
		'explain' => 'The minimum posts required by referrals in order to be considered valid.',
	)) . '

			' . $__templater->formDateInputRow(array(
		'name' => 'end_date',
		'value' => ($__vars['contest']['end_date'] ? $__templater->fn('date', array($__vars['contest']['end_date'], 'picker', ), false) : ''),
	), array(
		'label' => 'Contest end date',
		'explain' => 'Set the date when the contest will end.',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formRow('
				<ul class="listPlain inputGroup-container">
					' . $__compilerTemp1 . '
					<li class="inputGroup" data-xf-init="field-adder" data-increment-format="prizes[{counter}]">
						' . $__templater->formNumberBox(array(
		'name' => 'prizes[' . $__vars['nextCounter'] . '][reward_amount]',
		'value' => '0',
		'min' => '0',
		'required' => '',
	)) . '
						<span class="inputGroup-splitter"></span>
						' . $__templater->formSelect(array(
		'name' => 'prizes[' . $__vars['nextCounter'] . '][reward_type_id]',
		'value' => '0',
	), $__compilerTemp3) . '
					</li>
				</ul>
			', array(
		'label' => 'Prizes',
		'explain' => 'This option allows you to award prizes to contest winners. Each prize added corresponds with the place of the referrer in the contest.',
	)) . '

			<hr class="formRowSep" />

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'enabled',
		'value' => '1',
		'selected' => $__vars['contest']['enabled'],
		'label' => 'Enable contest',
		'_type' => 'option',
	)), array(
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('referral-contests/save', $__vars['contest'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});