<?php
// FROM HASH: 61f80834227775cc968d4953f0936973
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Referrer log');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->formTextBox(array(
		'name' => 'username',
		'placeholder' => 'Referrer' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => '',
		'data-xf-init' => 'auto-complete',
		'data-single' => 'true',
		'class' => 'input--inline',
	)) . '
			' . $__templater->button('Find', array(
		'type' => 'submit',
	), '', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('referral-contests/referrals', ), false),
		'class' => 'block',
	)) . '

';
	if ($__vars['referrerLogs']) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['referrerLogs'])) {
			foreach ($__vars['referrerLogs'] AS $__vars['log']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['log']['date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['log']['User'], true, array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['log']['url']),
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					<thead>
						' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'Date',
		),
		array(
			'_type' => 'cell',
			'html' => 'Referrer username',
		),
		array(
			'_type' => 'cell',
			'html' => 'siropu_referral_contests_referrer_url',
		))) . '
					</thead>
					' . $__compilerTemp1 . '
				', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '
			</div>
			<div class="block-footer">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['referrals'], $__vars['total'], ), true) . '</span>
			</div>
			' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'referral-contests/referrals',
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No entries have been logged.' . '</div>
';
	}
	return $__finalCompiled;
});