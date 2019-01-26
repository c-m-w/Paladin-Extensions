<?php
// FROM HASH: bf277b915ac41835fe2a45ee2f7da64c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['upgrade'], 'canExtend', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if (($__templater->fn('count', array($__vars['upgrade']['payment_profile_ids'], ), false) > 1)) {
			$__compilerTemp1 .= '
				';
			$__compilerTemp2 = array(array(
				'label' => $__vars['xf']['language']['parenthesis_open'] . 'Choose a payment method' . $__vars['xf']['language']['parenthesis_close'],
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['upgrade']['payment_profile_ids'])) {
				foreach ($__vars['upgrade']['payment_profile_ids'] AS $__vars['profileId']) {
					$__compilerTemp2[] = array(
						'value' => $__vars['profileId'],
						'label' => $__templater->escape($__vars['profiles'][$__vars['profileId']]),
						'_type' => 'option',
					);
				}
			}
			$__compilerTemp1 .= $__templater->formSelect(array(
				'name' => 'payment_profile_id',
			), $__compilerTemp2) . '

				<span class="inputGroup-splitter"></span>
				' . $__templater->button('exup_extend', array(
				'type' => 'submit',
				'icon' => 'purchase',
			), '', array(
			)) . '
			';
		} else {
			$__compilerTemp1 .= '
				' . $__templater->button('exup_extend', array(
				'type' => 'submit',
				'icon' => 'purchase',
			), '', array(
			)) . '
				' . $__templater->formHiddenVal('payment_profile_id', $__templater->filter($__vars['upgrade']['payment_profile_ids'], array(array('first', array()),), false), array(
			)) . '
			';
		}
		$__finalCompiled .= $__templater->form('
		<div class="inputGroup" style="margin-bottom: 10px">
			' . $__compilerTemp1 . '
		</div>
	', array(
			'action' => $__templater->fn('link', array('purchase', $__vars['upgrade'], array('user_upgrade_id' => $__vars['upgrade']['user_upgrade_id'], ), ), false),
			'ajax' => 'true',
			'data-xf-init' => 'payment-provider-container',
		)) . '
';
	}
	return $__finalCompiled;
});