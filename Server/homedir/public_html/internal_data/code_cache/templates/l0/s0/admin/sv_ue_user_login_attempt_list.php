<?php
// FROM HASH: 8e7600d0404a89f39f19f46b50e6827b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login attempts logged for ' . $__templater->escape($__vars['user']['username']) . '');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['attempts'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = array(array(
			'_type' => 'cell',
			'html' => 'Login',
		)
,array(
			'_type' => 'cell',
			'html' => 'IP address',
		)
,array(
			'_type' => 'cell',
			'html' => 'Date',
		));
		if ($__templater->method($__vars['xf']['visitor'], 'hasAdminPermission', array('user', ))) {
			$__compilerTemp1[] = array(
				'class' => 'dataList-cell--min',
				'_type' => 'cell',
				'html' => 'Delete',
			);
		}
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['attempts'])) {
			foreach ($__vars['attempts'] AS $__vars['attempt']) {
				$__compilerTemp2 .= '
						';
				$__compilerTemp3 = array(array(
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('login' => $__vars['attempt']['login'], ), ), true) . '">' . $__templater->escape($__vars['attempt']['login']) . '</a>',
				)
,array(
					'class' => 'u-ltr',
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('ip_address' => $__templater->filter($__vars['attempt']['ip_address'], array(array('ip', array()),), false), ), ), true) . '">
									' . $__templater->filter($__vars['attempt']['ip_address'], array(array('ip', array()),), true) . '
								</a>
							',
				)
,array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['attempt']['attempt_date'], array(
				))),
				));
				if ($__templater->method($__vars['attempt'], 'canDelete', array())) {
					$__compilerTemp3[] = array(
						'href' => $__templater->fn('link', array('logs/login-attempt', $__vars['attempt'], ), false),
						'_type' => 'delete',
						'html' => '',
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
		</div>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No login attempts were found for the requested user.' . '</div>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});