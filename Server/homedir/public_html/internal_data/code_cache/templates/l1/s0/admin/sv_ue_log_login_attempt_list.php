<?php
// FROM HASH: 131daf309c21d241009ae76fe2deaac8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login attempt log');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->formTextBox(array(
		'name' => 'login',
		'placeholder' => 'Login' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => $__vars['linkFilters']['login'],
		'class' => 'input--inline',
	)) . '
			' . $__templater->formTextBox(array(
		'name' => 'ip_address',
		'placeholder' => 'IP address' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => $__vars['linkFilters']['ip_address'],
		'class' => 'input--inline',
	)) . '
			' . $__templater->button('Show', array(
		'type' => 'submit',
	), '', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('logs/login-attempt', ), false),
		'class' => 'block',
	)) . '

';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
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
		if ($__templater->isTraversable($__vars['entries'])) {
			foreach ($__vars['entries'] AS $__vars['entry']) {
				$__compilerTemp2 .= '
						';
				$__compilerTemp3 = array(array(
					'_type' => 'cell',
					'html' => '<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('login' => $__vars['entry']['login'], ), ), true) . '">' . $__templater->escape($__vars['entry']['login']) . '</a>',
				)
,array(
					'class' => 'u-ltr',
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('logs/login-attempt', '', array('ip_address' => $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), false), ), ), true) . '">
									' . $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), true) . '
								</a>
							',
				)
,array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['entry']['attempt_date'], array(
				))),
				));
				if ($__templater->method($__vars['entry'], 'canDelete', array())) {
					$__compilerTemp3[] = array(
						'href' => $__templater->fn('link', array('logs/login-attempt', $__vars['entry'], ), false),
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

			<div class="block-footer">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['entries'], $__vars['total'], ), true) . '</span>
			</div>
		</div>

		' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'logs/login-attempt',
			'params' => $__vars['linkFilters'],
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No entries have been logged.' . '</div>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});