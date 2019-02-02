<?php
// FROM HASH: 6e61f8210a72da9eabe05bb0482057f2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['group'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add category');
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit category' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['group']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-tabHeader tabs hScroller" data-xf-init="h-scroller tabs" role="tablist">
			<span class="hScroller-scroll">
				<a class="tabs-tab is-active"
				   role="tab"
				   tabindex="0"
				   aria-controls="options">' . 'Options' . '</a>
				' . $__templater->callMacro('helper_criteria', 'user_tabs', array(
		'userTabTitle' => $__templater->filter('User criteria', array(array('for_attr', array()),), false),
	), $__vars) . '
			</span>
		</h2>

		<ul class="block-body tabPanes">
			<li class="is-active" role="tabpanel" id="options">
				' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => ($__vars['group']['group_id'] ? $__vars['group']['MasterTitle']['phrase_text'] : ''),
	), array(
		'label' => 'Title',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->callMacro('display_order_macros', 'row', array(
		'name' => 'display_order',
		'value' => $__vars['group']['display_order'],
		'explain' => 'The position of this item.',
	), $__vars) . '

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => ($__vars['group']['group_id'] ? $__vars['group']['active'] : 1),
		'label' => '
						' . 'Enabled' . '
					',
		'_type' => 'option',
	)), array(
	)) . '
			</li>

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
		'action' => $__templater->fn('link', array('em/special-chars/save', $__vars['group'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});