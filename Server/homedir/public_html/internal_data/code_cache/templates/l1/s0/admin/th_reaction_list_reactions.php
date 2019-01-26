<?php
// FROM HASH: 2a528a1a99682e293afcffa17df3f998
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reactions');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['reactions']) {
		$__compilerTemp1 .= '
			' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('reactions', null, array('export' => ($__vars['exportView'] ? '' : '1'), ), ), false),
			'icon' => 'export',
		), '', array(
		)) . '
		';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add reaction', array(
		'href' => $__templater->fn('link', array('reactions/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
		' . $__templater->button('', array(
		'href' => $__templater->fn('link', array('reactions/import', ), false),
		'icon' => 'import',
	), '', array(
	)) . '
		' . $__compilerTemp1 . '
	</div>
');
	$__finalCompiled .= '

';
	$__templater->includeCss('public:th_reactions.less');
	$__finalCompiled .= '
';
	$__templater->inlineCss('
	.dataList-cell.dataList-cell--imageSmall .reaction img
	{
		padding: 3px;
	}
');
	$__finalCompiled .= '
';
	if (!$__templater->test($__vars['reactions'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['reactions'])) {
			foreach ($__vars['reactions'] AS $__vars['reactionId'] => $__vars['reaction']) {
				$__compilerTemp2 .= '
						<tbody class="dataList-rowGroup">
							';
				$__compilerTemp3 = array();
				if ($__vars['exportView']) {
					$__compilerTemp3[] = array(
						'name' => 'export[]',
						'value' => $__vars['reaction']['reaction_id'],
						'_type' => 'toggle',
						'html' => '',
					);
				}
				$__compilerTemp3[] = array(
					'href' => $__templater->fn('link', array('reactions/edit', $__vars['reaction'], ), false),
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageSmall',
					'_type' => 'cell',
					'html' => '
									' . $__templater->fn('reaction', array($__vars['reaction'], 'admin', true, ), true) . '
								',
				);
				$__compilerTemp4 = '';
				if (!$__vars['reaction']['random']) {
					$__compilerTemp4 .= '<span style="color: ' . $__templater->escape($__vars['reaction']['ReactionType']['color']) . ';">(' . $__templater->escape($__vars['reaction']['ReactionType']['title']) . ')</span>';
				} else {
					$__compilerTemp4 .= '<span>(' . 'Random reaction' . ')</span>';
				}
				$__compilerTemp3[] = array(
					'href' => $__templater->fn('link', array('reactions/edit', $__vars['reaction'], ), false),
					'_type' => 'cell',
					'html' => '
									' . $__templater->escape($__vars['reaction']['title']) . ' ' . $__compilerTemp4 . '
								',
				);
				if (!$__vars['exportView']) {
					$__compilerTemp3[] = array(
						'name' => 'enabled[' . $__vars['reactionId'] . ']',
						'selected' => $__vars['reaction']['enabled'],
						'class' => 'dataList-cell--separated',
						'submit' => 'true',
						'_type' => 'toggle',
						'html' => '',
					);
					$__compilerTemp3[] = array(
						'href' => $__templater->fn('link', array('reactions/delete', $__vars['reaction'], ), false),
						'_type' => 'delete',
						'html' => '',
					);
				}
				$__compilerTemp2 .= $__templater->dataRow(array(
				), $__compilerTemp3) . '
						</tbody>
					';
			}
		}
		$__compilerTemp5 = '';
		if ($__vars['exportView']) {
			$__compilerTemp5 .= '
					<span class="block-footer-select">' . $__templater->formCheckBox(array(
				'standalone' => 'true',
			), array(array(
				'check-all' => '.dataList',
				'label' => 'Select all',
				'_type' => 'option',
			))) . '</span>
					<span class="block-footer-controls">' . $__templater->button('', array(
				'type' => 'submit',
				'icon' => 'export',
				'accesskey' => 's',
			), '', array(
			)) . '</span>
				';
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'reactions',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>

		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp2 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['reactions'], ), true) . '</span>

				' . $__compilerTemp5 . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array(($__vars['exportView'] ? 'reactions/export' : 'reactions/toggle'), ), false),
			'ajax' => ($__vars['exportView'] ? false : true),
			'class' => 'block',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No reactions have been added yet.' . '</div>
';
	}
	return $__finalCompiled;
});