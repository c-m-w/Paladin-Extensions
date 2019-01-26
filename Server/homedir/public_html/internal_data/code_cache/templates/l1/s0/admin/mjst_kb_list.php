<?php
// FROM HASH: 8fce7709f34b11b5305fd4ae1827c028
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Knowledge bases');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add knowledge base', array(
		'href' => $__templater->fn('link', array('mjst-support/kb/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
		' . $__templater->button('Add knowledge base category', array(
		'href' => $__templater->fn('link', array('mjst-support/kb/category/add', ), false),
		'icon' => 'add',
		'overlay' => 'true',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['kbsGrouped'], 'empty', array()) OR ($__templater->fn('count', array($__vars['kbCategories'], ), false) > 1)) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['kbCategories'])) {
			foreach ($__vars['kbCategories'] AS $__vars['kbCategoryId'] => $__vars['kbCategory']) {
				$__compilerTemp1 .= '
						<tbody class="dataList-rowGroup" id="js-kbCategory' . $__templater->escape($__vars['kbCategoryId']) . '">
						';
				if (($__templater->fn('count', array($__vars['kbCategories'], ), false) > 1)) {
					$__compilerTemp1 .= '
							';
					$__compilerTemp2 = array();
					if (($__vars['kbCategoryId'] > 0)) {
						$__compilerTemp2[] = array(
							'href' => $__templater->fn('link', array('mjst-support/kb/category/edit', $__vars['kbCategory'], ), false),
							'overlay' => 'true',
							'_type' => 'cell',
							'html' => '
										' . $__templater->escape($__vars['kbCategory']['title']) . '
									',
						);
						$__compilerTemp2[] = array(
							'_type' => 'cell',
							'html' => '&nbsp;',
						);
						$__compilerTemp2[] = array(
							'href' => $__templater->fn('link', array('mjst-support/kb/category/delete', $__vars['kbCategory'], ), false),
							'_type' => 'delete',
							'html' => '',
						);
					} else if ($__templater->fn('count', array($__vars['kbsGrouped'][$__vars['kbCategoryId']], ), false)) {
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
						'rowclass' => ((!$__vars['kbCategoryId']) ? 'dataList-row--noHover' : ''),
					), $__compilerTemp2) . '
						';
				}
				$__compilerTemp1 .= '
						';
				$__compilerTemp3 = true;
				if ($__templater->isTraversable($__vars['kbsGrouped'][$__vars['kbCategoryId']])) {
					foreach ($__vars['kbsGrouped'][$__vars['kbCategoryId']] AS $__vars['kbId'] => $__vars['kb']) {
						$__compilerTemp3 = false;
						$__compilerTemp1 .= '
							' . $__templater->dataRow(array(
							'rowclass' => 'kbCategory' . $__vars['kbCategoryId'] . ((!$__vars['kb']['is_active']) ? ' dataList-row--disabled' : ''),
						), array(array(
							'href' => $__templater->fn('link', array('mjst-support/kb/edit', $__vars['kb'], ), false),
							'class' => 'dataList-cell',
							'hash' => $__vars['kb']['kb_id'],
							'_type' => 'cell',
							'html' => '
									' . $__templater->escape($__vars['kb']['title']) . '
								',
						),
						array(
							'name' => 'is_active[' . $__vars['kb']['kb_id'] . ']',
							'selected' => $__vars['kb']['is_active'],
							'class' => 'dataList-cell--separated',
							'submit' => 'true',
							'_type' => 'toggle',
							'html' => '',
						),
						array(
							'href' => $__templater->fn('link', array('mjst-support/kb/delete', $__vars['kb'], ), false),
							'_type' => 'delete',
							'html' => '',
						))) . '
						';
					}
				}
				if ($__compilerTemp3) {
					$__compilerTemp1 .= '
							';
					if (($__templater->fn('count', array($__vars['kbsGrouped'][$__vars['kbCategoryId']], ), false) OR ($__vars['kbCategoryId'] > 0))) {
						$__compilerTemp1 .= '
								';
						$__compilerTemp4 = '';
						if (($__templater->fn('count', array($__vars['kbCategories'], ), false) > 1)) {
							$__compilerTemp4 .= '
											' . 'No knowledge bases have been added to this category yet.' . '
										';
						} else {
							$__compilerTemp4 .= '
											' . 'No knowledge bases have been added yet.' . '
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
			'key' => 'mjst-support/kb',
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
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['kbTotal'], ), true) . '</span>
				' . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('mjst-support/kb/toggle', ), false),
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