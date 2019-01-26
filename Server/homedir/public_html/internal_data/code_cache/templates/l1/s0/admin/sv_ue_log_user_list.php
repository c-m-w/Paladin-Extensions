<?php
// FROM HASH: 7480a42e590c6f20dc9b28541ba3df60
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('User log');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('
		' . 'Clear' . '
	', array(
			'href' => $__templater->fn('link', array('logs/user/clear', ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->formTextBox(array(
		'name' => 'username',
		'placeholder' => 'User name' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => ($__vars['limitUser'] ? $__vars['limitUser']['username'] : ''),
		'class' => 'input--inline',
	)) . '
			' . $__templater->button('Show changes', array(
		'type' => 'submit',
	), '', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('logs/user', ), false),
		'class' => 'block',
	)) . '

';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['entries'])) {
			foreach ($__vars['entries'] AS $__vars['entry']) {
				$__compilerTemp1 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'_type' => 'cell',
					'html' => '
								<div>
									<a href="' . $__templater->fn('link', array('logs/user', $__vars['entry'], ), true) . '" data-xf-click="overlay">' . $__templater->escape($__vars['entry']['action_text']) . '</a>
									<div class="dataList-subRow">' . $__templater->escape($__vars['entry']['content_title']) . '</div>
								</div>
							',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['entry']['User'], false, array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['entry']['User'], ), false),
				))),
				),
				array(
					'class' => 'u-ltr',
					'_type' => 'cell',
					'html' => ($__vars['entry']['ip_address'] ? $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), true) : ''),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['entry']['log_date'], array(
				))),
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'Action',
		),
		array(
			'_type' => 'cell',
			'html' => 'User',
		),
		array(
			'_type' => 'cell',
			'html' => 'IP address',
		),
		array(
			'_type' => 'cell',
			'html' => 'Date',
		))) . '

					' . $__compilerTemp1 . '
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
			'link' => 'logs/user',
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