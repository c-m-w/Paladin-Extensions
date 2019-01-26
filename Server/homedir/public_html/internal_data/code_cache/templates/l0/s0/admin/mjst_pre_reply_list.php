<?php
// FROM HASH: 15ddbbddef1f89e44eb26664522d959f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Predefined replies');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add predefined reply', array(
		'href' => $__templater->fn('link', array('mjst-support/predefined-replies/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
		' . $__templater->button('Add predefined reply group', array(
		'href' => $__templater->fn('link', array('mjst-support/predefined-replies/group/add', ), false),
		'icon' => 'add',
		'overlay' => 'true',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['repliesGrouped'], 'empty', array()) OR ($__templater->fn('count', array($__vars['replyGroups'], ), false) > 1)) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['replyGroups'])) {
			foreach ($__vars['replyGroups'] AS $__vars['replyGroupId'] => $__vars['replyGroup']) {
				$__compilerTemp1 .= '
						<tbody class="dataList-rowGroup" id="js-replyGroup' . $__templater->escape($__vars['replyGroupId']) . '">
						';
				if (($__templater->fn('count', array($__vars['replyGroups'], ), false) > 1)) {
					$__compilerTemp1 .= '
							';
					$__compilerTemp2 = array();
					if (($__vars['replyGroupId'] > 0)) {
						$__compilerTemp2[] = array(
							'href' => $__templater->fn('link', array('mjst-support/predefined-replies/group/edit', $__vars['replyGroup'], ), false),
							'overlay' => 'true',
							'_type' => 'cell',
							'html' => '
										' . $__templater->escape($__vars['replyGroup']['title']) . '
									',
						);
						$__compilerTemp2[] = array(
							'_type' => 'cell',
							'html' => '&nbsp;',
						);
						$__compilerTemp2[] = array(
							'href' => $__templater->fn('link', array('mjst-support/predefined-replies/group/delete', $__vars['replyGroup'], ), false),
							'_type' => 'delete',
							'html' => '',
						);
					} else if ($__templater->fn('count', array($__vars['repliesGrouped'][$__vars['replyGroupId']], ), false)) {
						$__compilerTemp2[] = array(
							'_type' => 'cell',
							'html' => $__vars['xf']['language']['parenthesis_open'] . 'Ungrouped' . $__vars['xf']['language']['parenthesis_close'],
						);
						$__compilerTemp2[] = array(
							'_type' => 'cell',
							'html' => '&nbsp;',
						);
						$__compilerTemp2[] = array(
							'_type' => 'cell',
							'html' => '&nbsp;',
						);
					}
					$__compilerTemp1 .= $__templater->dataRow(array(
						'rowtype' => 'subsection',
						'rowclass' => ((!$__vars['replyGroupId']) ? 'dataList-row--noHover' : ''),
					), $__compilerTemp2) . '
						';
				}
				$__compilerTemp1 .= '
						';
				$__compilerTemp3 = true;
				if ($__templater->isTraversable($__vars['repliesGrouped'][$__vars['replyGroupId']])) {
					foreach ($__vars['repliesGrouped'][$__vars['replyGroupId']] AS $__vars['replyId'] => $__vars['reply']) {
						$__compilerTemp3 = false;
						$__compilerTemp1 .= '
							' . $__templater->dataRow(array(
							'rowclass' => 'replyGroup' . $__vars['replyGroupId'] . ((!$__vars['reply']['is_active']) ? ' dataList-row--disabled' : ''),
						), array(array(
							'href' => $__templater->fn('link', array('mjst-support/predefined-replies/edit', $__vars['reply'], ), false),
							'class' => 'dataList-cell',
							'hash' => $__vars['reply']['reply_id'],
							'_type' => 'cell',
							'html' => '
									' . $__templater->escape($__vars['reply']['title']) . '
								',
						),
						array(
							'name' => 'is_active[' . $__vars['reply']['reply_id'] . ']',
							'selected' => $__vars['reply']['is_active'],
							'class' => 'dataList-cell--separated',
							'submit' => 'true',
							'_type' => 'toggle',
							'html' => '',
						),
						array(
							'href' => $__templater->fn('link', array('mjst-support/predefined-replies/delete', $__vars['reply'], ), false),
							'_type' => 'delete',
							'html' => '',
						))) . '
						';
					}
				}
				if ($__compilerTemp3) {
					$__compilerTemp1 .= '
							';
					if (($__templater->fn('count', array($__vars['repliesGrouped'][$__vars['replyGroupId']], ), false) OR ($__vars['replyGroupId'] > 0))) {
						$__compilerTemp1 .= '
								';
						$__compilerTemp4 = '';
						if (($__templater->fn('count', array($__vars['replyGroups'], ), false) > 1)) {
							$__compilerTemp4 .= '
											' . 'No predefined replies have been added to this group yet.' . '
										';
						} else {
							$__compilerTemp4 .= '
											' . 'No predefined replies have been added yet.' . '
										';
						}
						$__compilerTemp1 .= $__templater->dataRow(array(
							'rowclass' => 'dataList-row--noHover',
						), array(array(
							'colspan' => '4',
							'class' => 'dataList-cell--noSearch',
							'_type' => 'cell',
							'html' => '
										' . $__compilerTemp4 . '
									',
						))) . '
							';
					}
					$__compilerTemp1 .= '
						';
				}
				$__compilerTemp1 .= '
						</tbody>
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'mjst-support/predefined-replies',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['replyTotal'], ), true) . '</span>
				' . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('mjst-support/predefined-replies/toggle', ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});