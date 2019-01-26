<?php
// FROM HASH: 9f8f960ce6757b8594fdf68d421bdd45
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Referrals');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add referral', array(
		'href' => $__templater->fn('link', array('referral-contests/referrals/add', ), false),
		'icon' => 'add',
		'data-xf-click' => 'overlay',
	), '', array(
	)) . '
');
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
			' . $__templater->button('Find referrals', array(
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
	if (!$__templater->test($__vars['referrals'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['referrals'])) {
			foreach ($__vars['referrals'] AS $__vars['referral']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['referral'], true, array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['referral']['register_date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->filter($__vars['referral']['message_count'], array(array('number', array()),), true),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['referral']['SRC_Referrer'], true, array(
				))),
				),
				array(
					'href' => $__templater->fn('link', array('referral-contests/referrals/delete', $__vars['referral'], ), false),
					'_type' => 'delete',
					'html' => '',
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
			'html' => 'User',
		),
		array(
			'_type' => 'cell',
			'html' => 'Joined',
		),
		array(
			'_type' => 'cell',
			'html' => 'Messages',
		),
		array(
			'_type' => 'cell',
			'html' => 'Referrer',
		),
		array(
			'_type' => 'cell',
			'html' => '&nbsp;',
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
		</div>
	</div>

	' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'params' => $__vars['linkParams'],
			'link' => 'referral-contests/referrals',
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No entries have been logged.' . '</div>
';
	}
	return $__finalCompiled;
});