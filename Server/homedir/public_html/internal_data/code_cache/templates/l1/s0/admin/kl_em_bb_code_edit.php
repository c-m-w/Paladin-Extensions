<?php
// FROM HASH: d129a2c49a34836d61d98f656735676c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit BB code' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['bbCode']['bb_code_id']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->fn('in_array', array($__vars['bbCode']['bb_code_id'], array('table', 'align', 'list', ), ), false)) {
		$__compilerTemp1 .= '
					<a class="tabs-tab is-active"
					   role="tab"
					   tabindex="0"
					   aria-controls="bb-code-options">' . 'Options' . '</a>
				';
	}
	$__compilerTemp2 = '';
	if (!$__templater->fn('in_array', array($__vars['bbCode']['bb_code_id'], array('table', 'align', 'list', ), ), false)) {
		$__compilerTemp2 .= '
				<li class="is-active" role="tabpanel" id="bb-code-options">
					';
		$__compilerTemp3 = '';
		$__compilerTemp3 .= '
							';
		if ($__templater->isTraversable($__vars['options'])) {
			foreach ($__vars['options'] AS $__vars['option']) {
				$__compilerTemp3 .= '
								' . $__templater->callMacro('option_macros', 'option_row', array(
					'option' => $__vars['option'],
				), $__vars) . '
							';
			}
		}
		$__compilerTemp3 .= '
							<hr class="formRowSep" />
						';
		if (strlen(trim($__compilerTemp3)) > 0) {
			$__compilerTemp2 .= '
						' . $__compilerTemp3 . '
					';
		}
		$__compilerTemp2 .= '

					';
		if ($__vars['bbCode']['bb_code_id'] != 'hide') {
			$__compilerTemp2 .= '
						';
			$__compilerTemp4 = '';
			if ($__templater->isTraversable($__vars['bbCode']['aliases'])) {
				foreach ($__vars['bbCode']['aliases'] AS $__vars['alias']) {
					$__compilerTemp4 .= '					
									<li>
										' . $__templater->formTextBox(array(
						'name' => 'aliases[]',
						'value' => $__vars['alias'],
					)) . '
									</li>
								';
				}
			}
			$__compilerTemp2 .= $__templater->formRow('
							<ul class="inputList">
								' . $__compilerTemp4 . '
								<li data-xf-init="field-adder">
									' . $__templater->formTextBox(array(
				'name' => 'aliases[]',
			)) . '
								</li>
							</ul>
						', array(
				'label' => 'Aliases',
			)) . '
					';
		}
		$__compilerTemp2 .= '
				</li>
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<h2 class="block-tabHeader tabs hScroller" data-xf-init="h-scroller tabs" role="tablist">
			<span class="hScroller-scroll">
				' . $__compilerTemp1 . '
				' . $__templater->callMacro('helper_criteria', 'user_tabs', array(
		'userTabTitle' => $__templater->filter('User criteria', array(array('for_attr', array()),), false),
	), $__vars) . '
			</span>
		</h2>

		<ul class="block-body tabPanes">
			' . $__compilerTemp2 . '

			' . $__templater->callMacro('helper_criteria', 'user_panes', array(
		'criteria' => $__templater->method($__vars['userCriteria'], 'getCriteriaForTemplate', array()),
		'data' => $__templater->method($__vars['userCriteria'], 'getExtraTemplateData', array()),
	), $__vars) . '
		</ul>

		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/bb-codes/save', $__vars['bbCode'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});