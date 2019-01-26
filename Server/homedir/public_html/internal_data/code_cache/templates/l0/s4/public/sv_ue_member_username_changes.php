<?php
// FROM HASH: ce3e2dd4cb9f5ae08f00d43241eb87b4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Previous names' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['user']['username']));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp1 = array(array(
		'_type' => 'cell',
		'html' => 'From name',
	)
,array(
		'_type' => 'cell',
		'html' => 'To name',
	)
,array(
		'_type' => 'cell',
		'html' => 'Date',
	));
	if ($__templater->method($__vars['xf']['visitor'], 'canViewUsernameChangeDetails', array($__vars['user']['user_id'], ))) {
		$__compilerTemp1[] = array(
			'_type' => 'cell',
			'html' => 'Status',
		);
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['usernameChanges'])) {
		foreach ($__vars['usernameChanges'] AS $__vars['usernameChange']) {
			$__compilerTemp2 .= '
					';
			$__compilerTemp3 = array(array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['usernameChange']['from_username']),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->escape($__vars['usernameChange']['to_username']),
			)
,array(
				'_type' => 'cell',
				'html' => $__templater->fn('date_dynamic', array($__vars['usernameChange']['date'], array(
			))),
			));
			if ($__templater->method($__vars['xf']['visitor'], 'canViewUsernameChangeDetails', array($__vars['user']['user_id'], ))) {
				$__compilerTemp4 = '';
				if ($__vars['usernameChange']['status'] == 'approved') {
					$__compilerTemp4 .= '
									' . 'Approved' . '
								';
				} else if ($__vars['usernameChange']['status'] == 'denied') {
					$__compilerTemp4 .= '
									' . 'Rejected' . '
								';
				} else {
					$__compilerTemp4 .= '
									' . 'Pending' . '
								';
				}
				$__compilerTemp3[] = array(
					'href' => $__templater->fn('link', array('members/username-change', '', array('unc_id' => $__vars['usernameChange']['unc_id'], ), ), false),
					'overlay' => 'true',
					'_type' => 'cell',
					'html' => '
								' . $__compilerTemp4 . '
							',
				);
			}
			$__compilerTemp2 .= $__templater->dataRow(array(
			), $__compilerTemp3) . '
				';
		}
	}
	$__finalCompiled .= $__templater->dataList('
				' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), $__compilerTemp1) . '

				' . $__compilerTemp2 . '
			', array(
		'data-xf-init' => 'responsive-data-list',
	)) . '
		</div>

		<div class="block-footer">
			<ul class="listInline listInline--bullet">
				<li>' . 'Total changes' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->filter($__templater->fn('count', array($__vars['usernameChanges'], ), false), array(array('number', array()),), true) . '</li>
			</ul>
		</div>
	</div>
</div>
';
	return $__finalCompiled;
});