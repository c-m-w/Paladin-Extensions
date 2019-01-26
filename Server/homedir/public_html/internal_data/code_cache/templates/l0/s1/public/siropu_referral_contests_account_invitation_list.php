<?php
// FROM HASH: f0a8a1e116855e3d219b15dc22305048
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Your invitations');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		' . $__templater->callMacro('siropu_referral_contests_macros', 'invitation_tabs', array(
		'activeTab' => 'sent',
	), $__vars) . '

		<div class="block-body">
			';
	$__compilerTemp1 = '';
	$__compilerTemp2 = true;
	if ($__templater->isTraversable($__vars['invitations'])) {
		foreach ($__vars['invitations'] AS $__vars['invitation']) {
			$__compilerTemp2 = false;
			$__compilerTemp1 .= '
					';
			$__compilerTemp3 = '';
			if ($__vars['invitation']['Registered']) {
				$__compilerTemp3 .= '
								' . $__templater->fn('username_link', array($__vars['invitation']['Registered'], true, array(
				))) . '
							';
			} else {
				$__compilerTemp3 .= '
								--
							';
			}
			$__compilerTemp1 .= $__templater->dataRow(array(
			), array(array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['invitation']['invitation_date'], array(
			))),
			),
			array(
				'_type' => 'cell',
				'html' => ($__templater->escape($__vars['invitation']['recipient']) ?: '--'),
			),
			array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['invitation']['invitation_code']),
			),
			array(
				'_type' => 'cell',
				'html' => '
							' . $__compilerTemp3 . '
						',
			),
			array(
				'href' => ($__templater->method($__vars['invitation'], 'isValid', array()) ? $__templater->fn('link', array('account/invitations/link', $__vars['invitation'], ), false) : null),
				'class' => 'dataList-cell--separated',
				'style' => 'text-align: center;',
				'overlay' => 'true',
				'_type' => 'cell',
				'html' => '
							<i class="fa fa-link" aria-hidden="true"></i>
						',
			))) . '
					';
		}
	}
	if ($__compilerTemp2) {
		$__compilerTemp1 .= '
					';
		$__compilerTemp4 = '';
		if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('siropuReferralContests', 'createInvitations', ))) {
			$__compilerTemp4 .= '
								' . 'You do not have invitations.' . '
							';
		} else {
			$__compilerTemp4 .= '
								' . 'No invitations have been sent.' . '
							';
		}
		$__compilerTemp1 .= $__templater->dataRow(array(
			'rowclass' => 'dataList-row--noHover dataList-row--note',
			'colspan' => '4',
		), array(array(
			'class' => 'dataList-cell--noSearch',
			'_type' => 'cell',
			'html' => '
							' . $__compilerTemp4 . '
						',
		))) . '
				';
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
		'html' => 'Recipient',
	),
	array(
		'_type' => 'cell',
		'html' => 'Invitation code',
	),
	array(
		'_type' => 'cell',
		'html' => 'Registered user',
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
	</div>

	' . $__templater->fn('page_nav', array(array(
		'link' => 'account/invitations/list',
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'wrapperclass' => 'block-outer block-outer--after',
		'perPage' => $__vars['perPage'],
	))) . '
</div>';
	return $__finalCompiled;
});