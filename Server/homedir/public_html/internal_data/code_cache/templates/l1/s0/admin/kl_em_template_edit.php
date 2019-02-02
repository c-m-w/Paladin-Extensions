<?php
// FROM HASH: d4a63fdfc080527d06825b7346a30148
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['template'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add template');
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit template' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['template']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['template'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('em/templates/delete', $__vars['template'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
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
		'required' => 'required',
		'value' => ($__templater->method($__vars['template'], 'exists', array()) ? $__vars['template']['title'] : ''),
	), array(
		'label' => 'Title',
	)) . '

				' . $__templater->callMacro('display_order_macros', 'row', array(
		'name' => 'display_order',
		'value' => $__vars['template']['display_order'],
		'explain' => 'The position of this item.',
	), $__vars) . '

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => ($__vars['template']['template_id'] ? $__vars['template']['active'] : 1),
		'label' => '
						' . 'Enabled' . '
					',
		'_type' => 'option',
	)), array(
	)) . '

				' . $__templater->formEditorRow(array(
		'name' => 'content',
		'value' => $__vars['template']['content'],
		'data-min-height' => '100',
		'maxlength' => $__vars['xf']['options']['messageMaxLength'],
	), array(
		'rowtype' => 'fullWidth noLabel',
		'label' => 'Message',
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
	</div>
', array(
		'action' => $__templater->fn('link', array('em/templates/save', $__vars['template'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});