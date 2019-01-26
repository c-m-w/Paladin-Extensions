<?php
// FROM HASH: 6ce9013856888a309dbf6bba9d664c33
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Account upgrades');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'xf/payment.js',
		'min' => '1',
	));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
				';
	if (!$__templater->test($__vars['available'], 'empty', array())) {
		$__compilerTemp1 .= '
					<h2 class="block-header">' . 'Available upgrades' . '</h2>

					<ul class="block-body listPlain">
						';
		if ($__templater->isTraversable($__vars['available'])) {
			foreach ($__vars['available'] AS $__vars['upgrade']) {
				$__compilerTemp1 .= '
							<li>
								';
				$__compilerTemp2 = '';
				if (($__templater->fn('count', array($__vars['upgrade']['payment_profile_ids'], ), false) > 1)) {
					$__compilerTemp2 .= '
												';
					$__compilerTemp3 = array(array(
						'label' => $__vars['xf']['language']['parenthesis_open'] . 'Choose a payment method' . $__vars['xf']['language']['parenthesis_close'],
						'_type' => 'option',
					));
					if ($__templater->isTraversable($__vars['upgrade']['payment_profile_ids'])) {
						foreach ($__vars['upgrade']['payment_profile_ids'] AS $__vars['profileId']) {
							$__compilerTemp3[] = array(
								'value' => $__vars['profileId'],
								'label' => $__templater->escape($__vars['profiles'][$__vars['profileId']]),
								'_type' => 'option',
							);
						}
					}
					$__compilerTemp2 .= $__templater->formSelect(array(
						'name' => 'payment_profile_id',
					), $__compilerTemp3) . '

												<span class="inputGroup-splitter"></span>

												';
					$__vars['buffer'] = '1';
					$__compilerTemp2 .= '
												';
					if (!$__templater->test($__vars['purchased'], 'empty', array())) {
						$__compilerTemp2 .= '
													';
						if ($__templater->isTraversable($__vars['purchased'])) {
							foreach ($__vars['purchased'] AS $__vars['purupgrade']) {
								$__compilerTemp2 .= '
														';
								if ($__vars['purupgrade']['user_upgrade_id'] == $__vars['upgrade']['user_upgrade_id']) {
									$__compilerTemp2 .= '
															';
									$__vars['buffer'] = '0';
									$__compilerTemp2 .= '
														';
								}
								$__compilerTemp2 .= '
													';
							}
						}
						$__compilerTemp2 .= '
												';
					}
					$__compilerTemp2 .= '

												';
					if ((($__vars['upgrade']['user_upgrade_id'] == 13) OR ($__vars['upgrade']['user_upgrade_id'] == 18)) OR ($__vars['upgrade']['user_upgrade_id'] == 7)) {
						$__compilerTemp2 .= '
													';
						if ($__templater->method($__vars['xf']['visitor'], 'isMemberOf', array(9, ))) {
							$__compilerTemp2 .= '
														';
							if ($__vars['buffer']) {
								$__compilerTemp2 .= '
															';
								if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
									$__compilerTemp2 .= $__templater->button('', array(
										'type' => 'submit',
										'icon' => 'purchase',
									), '', array(
									));
								}
								$__compilerTemp2 .= '
';
								if ($__templater->method($__vars['upgrade'], 'canGift', array())) {
									$__compilerTemp2 .= '
	';
									if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
										$__compilerTemp2 .= '<span class="inputGroup-splitter"></span>';
									}
									$__compilerTemp2 .= '
	' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
										'type' => 'submit',
										'name' => 'gift',
										'value' => '1',
										'icon' => 'nfgift',
									), '', array(
									)) . '
';
								}
								$__compilerTemp2 .= '
														';
							} else {
								$__compilerTemp2 .= '
															' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
									'type' => 'submit',
									'class' => 'button button--icon button--icon--nfgift rippleButton',
									'name' => 'gift',
									'value' => '1',
								), '', array(
								)) . '
														';
							}
							$__compilerTemp2 .= '
													';
						}
						$__compilerTemp2 .= '
												';
					} else {
						$__compilerTemp2 .= '
													';
						if ($__vars['buffer']) {
							$__compilerTemp2 .= '
														';
							if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
								$__compilerTemp2 .= $__templater->button('', array(
									'type' => 'submit',
									'icon' => 'purchase',
								), '', array(
								));
							}
							$__compilerTemp2 .= '
';
							if ($__templater->method($__vars['upgrade'], 'canGift', array())) {
								$__compilerTemp2 .= '
	';
								if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
									$__compilerTemp2 .= '<span class="inputGroup-splitter"></span>';
								}
								$__compilerTemp2 .= '
	' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
									'type' => 'submit',
									'name' => 'gift',
									'value' => '1',
									'icon' => 'nfgift',
								), '', array(
								)) . '
';
							}
							$__compilerTemp2 .= '
													';
						} else {
							$__compilerTemp2 .= '
														' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
								'type' => 'submit',
								'class' => 'button button--icon button--icon--nfgift rippleButton',
								'name' => 'gift',
								'value' => '1',
							), '', array(
							)) . '
													';
						}
						$__compilerTemp2 .= '
												';
					}
					$__compilerTemp2 .= '
												
											';
				} else {
					$__compilerTemp2 .= '
												';
					$__vars['buffer'] = '1';
					$__compilerTemp2 .= '
												';
					if (!$__templater->test($__vars['purchased'], 'empty', array())) {
						$__compilerTemp2 .= '
													';
						if ($__templater->isTraversable($__vars['purchased'])) {
							foreach ($__vars['purchased'] AS $__vars['purupgrade']) {
								$__compilerTemp2 .= '
														';
								if ($__vars['purupgrade']['user_upgrade_id'] == $__vars['upgrade']['user_upgrade_id']) {
									$__compilerTemp2 .= '
															';
									$__vars['buffer'] = '0';
									$__compilerTemp2 .= '
														';
								}
								$__compilerTemp2 .= '
													';
							}
						}
						$__compilerTemp2 .= '
												';
					}
					$__compilerTemp2 .= '

												';
					if ((($__vars['upgrade']['user_upgrade_id'] == 13) OR ($__vars['upgrade']['user_upgrade_id'] == 18)) OR ($__vars['upgrade']['user_upgrade_id'] == 7)) {
						$__compilerTemp2 .= '
													';
						if ($__templater->method($__vars['xf']['visitor'], 'isMemberOf', array(90, ))) {
							$__compilerTemp2 .= '
														hey
													';
						}
						$__compilerTemp2 .= '
													';
						if ($__templater->method($__vars['xf']['visitor'], 'isMemberOf', array(9, ))) {
							$__compilerTemp2 .= '
														';
							if ($__vars['buffer']) {
								$__compilerTemp2 .= '
															';
								if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
									$__compilerTemp2 .= $__templater->button('', array(
										'type' => 'submit',
										'icon' => 'purchase',
									), '', array(
									));
								}
								$__compilerTemp2 .= '
';
								if ($__templater->method($__vars['upgrade'], 'canGift', array())) {
									$__compilerTemp2 .= '
	';
									if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
										$__compilerTemp2 .= '<span class="inputGroup-splitter"></span>';
									}
									$__compilerTemp2 .= '
	' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
										'type' => 'submit',
										'name' => 'gift',
										'value' => '1',
										'icon' => 'nfgift',
									), '', array(
									)) . '
';
								}
								$__compilerTemp2 .= '
														';
							} else {
								$__compilerTemp2 .= '
															' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
									'type' => 'submit',
									'class' => 'button button--icon button--icon--nfgift rippleButton',
									'name' => 'gift',
									'value' => '1',
								), '', array(
								)) . '
														';
							}
							$__compilerTemp2 .= '
													';
						}
						$__compilerTemp2 .= '
												';
					} else {
						$__compilerTemp2 .= '
													';
						if ($__vars['buffer']) {
							$__compilerTemp2 .= '
														';
							if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
								$__compilerTemp2 .= $__templater->button('', array(
									'type' => 'submit',
									'icon' => 'purchase',
								), '', array(
								));
							}
							$__compilerTemp2 .= '
';
							if ($__templater->method($__vars['upgrade'], 'canGift', array())) {
								$__compilerTemp2 .= '
	';
								if ($__templater->method($__vars['upgrade'], 'canPurchase', array())) {
									$__compilerTemp2 .= '<span class="inputGroup-splitter"></span>';
								}
								$__compilerTemp2 .= '
	' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
									'type' => 'submit',
									'name' => 'gift',
									'value' => '1',
									'icon' => 'nfgift',
								), '', array(
								)) . '
';
							}
							$__compilerTemp2 .= '
													';
						} else {
							$__compilerTemp2 .= '
														' . $__templater->button('<font size="4"><i class="fa fa-gift" style="padding-right:7px;"></i></font>Gift', array(
								'type' => 'submit',
								'class' => 'button button--icon button--icon--nfgift rippleButton',
								'name' => 'gift',
								'value' => '1',
							), '', array(
							)) . '
													';
						}
						$__compilerTemp2 .= '
												';
					}
					$__compilerTemp2 .= '
												
												' . $__templater->formHiddenVal('payment_profile_id', $__templater->filter($__vars['upgrade']['payment_profile_ids'], array(array('first', array()),), false), array(
					)) . '
											';
				}
				$__compilerTemp1 .= $__templater->form('

									' . $__templater->formRow('

										<div class="inputGroup">
' . $__templater->includeTemplate('sv_ue_account_upgrades_cost_input', $__vars) . '

											' . $__compilerTemp2 . '
										</div>
									', array(
					'rowtype' => 'button',
					'label' => $__templater->escape($__vars['upgrade']['title']),
					'hint' => (($__vars['upgrade']['cost_amount'] != '0.00') ? $__templater->escape($__vars['upgrade']['cost_phrase']) : false),
					'explain' => $__templater->filter($__vars['upgrade']['description'], array(array('raw', array()),), true),
				)) . '
								', array(
					'action' => $__templater->fn('link', array('purchase', $__vars['upgrade'], array('user_upgrade_id' => $__vars['upgrade']['user_upgrade_id'], ), ), false),
					'ajax' => 'true',
					'data-xf-init' => 'payment-provider-container',
				)) . '
								<div class="js-paymentProviderReply-user_upgrade' . $__templater->escape($__vars['upgrade']['user_upgrade_id']) . '"></div>
							</li>
						';
			}
		}
		$__compilerTemp1 .= '
					</ul>
				';
	}
	$__compilerTemp1 .= '

				';
	if (!$__templater->test($__vars['purchased'], 'empty', array())) {
		$__compilerTemp1 .= '
					<h2 class="block-header">' . 'Purchased upgrades' . '</h2>

					<ul class="block-body listPlain">
						';
		if ($__templater->isTraversable($__vars['purchased'])) {
			foreach ($__vars['purchased'] AS $__vars['upgrade']) {
				$__compilerTemp1 .= '
							<li>
								<div>
									';
				$__vars['active'] = $__vars['upgrade']['Active'][$__vars['xf']['visitor']['user_id']];
				$__compilerTemp1 .= '
									';
				$__compilerTemp4 = '';
				if ($__vars['active']['end_date']) {
					$__compilerTemp4 .= '
											' . 'Expires' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('date_dynamic', array($__vars['active']['end_date'], array(
					))) . '
										';
				} else {
					$__compilerTemp4 .= '
											' . 'Expires: Never' . '
										';
				}
				$__compilerTemp5 = '';
				if ($__vars['upgrade']['length_unit'] AND ($__vars['upgrade']['recurring'] AND $__vars['active']['PurchaseRequest'])) {
					$__compilerTemp5 .= '
											';
					$__vars['provider'] = $__vars['active']['PurchaseRequest']['PaymentProfile']['Provider'];
					$__compilerTemp5 .= '
											' . $__templater->filter($__templater->method($__vars['provider'], 'renderCancellation', array($__vars['active'], )), array(array('raw', array()),), true) . '
										';
				}
				$__compilerTemp1 .= $__templater->formRow('

										' . $__templater->includeTemplate('expiringUserUpgrades_account_upgrades_extend_button', $__vars) . '
' . $__compilerTemp4 . '

										' . $__compilerTemp5 . '
									', array(
					'rowclass' => 'formRow--noColon',
					'label' => $__templater->escape($__vars['upgrade']['title']),
					'hint' => (($__vars['upgrade']['cost_amount'] != '0.00') ? $__templater->escape($__vars['upgrade']['cost_phrase']) : false),
					'explain' => $__templater->filter($__vars['upgrade']['description'], array(array('raw', array()),), true),
				)) . '
								</div>
							</li>
						';
			}
		}
		$__compilerTemp1 .= '
					</ul>
				';
	}
	$__compilerTemp1 .= '
			';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
			' . $__compilerTemp1 . '
		';
	} else {
		$__finalCompiled .= '
			<div class="block-row">' . 'There are currently no purchasable user upgrades.' . '</div>
		';
	}
	$__finalCompiled .= '
	</div>
</div>';
	return $__finalCompiled;
});