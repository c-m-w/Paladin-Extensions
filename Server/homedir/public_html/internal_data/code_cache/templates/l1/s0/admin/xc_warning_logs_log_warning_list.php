<?php
// FROM HASH: 96991bf7bbcd0d3b4bbef8029f1652b5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Warning log');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('Warning log'), $__templater->fn('link', array('logs/warning', ), false), array(
	));
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('
		' . 'Clear' . '
	', array(
			'href' => $__templater->fn('link', array('logs/warning/clear', ), false),
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
			' . 'Search for warnings issued by' . $__vars['xf']['language']['label_separator'] . '&nbsp;
			' . $__templater->formTextBox(array(
		'name' => 'username',
		'placeholder' => 'User name' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => ($__vars['limitUser'] ? $__vars['limitUser']['username'] : ''),
		'class' => 'input--inline',
	)) . '
			' . $__templater->button('Search', array(
		'type' => 'submit',
	), '', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('logs/warning', ), false),
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
					'html' => $__templater->fn('username_link', array($__vars['entry']['WarnedBy'], false, array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['entry']['User'], false, array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['entry']['warning_date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['entry']['points']),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['entry']['notes']),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['entry']['expiry_date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->button('View', array(
					'href' => $__templater->fn('link_type', array('public', 'warnings', $__vars['entry'], ), false),
					'data-xf-click' => 'overlay',
				), '', array(
				)),
				))) . '
				';
			}
		}
		$__finalCompiled .= $__templater->dataList('
				' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'Issued By',
		),
		array(
			'_type' => 'cell',
			'html' => 'Issued To',
		),
		array(
			'_type' => 'cell',
			'html' => 'Date',
		),
		array(
			'_type' => 'cell',
			'html' => 'Points',
		),
		array(
			'_type' => 'cell',
			'html' => 'Reason',
		),
		array(
			'_type' => 'cell',
			'html' => 'Expiry',
		),
		array(
			'_type' => 'cell',
			'html' => 'Manage',
		))) . '
				
				' . $__compilerTemp1 . '
			', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '
		</div>
	</div>
	' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'logs/warning',
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No warnings have been logged.' . '</div>
';
	}
	return $__finalCompiled;
});