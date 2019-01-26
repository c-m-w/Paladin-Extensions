<?php
// FROM HASH: 8bbfd49d63de26f9cfdd6cb1320c86ed
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Watched categories');
	$__finalCompiled .= '

';
	$__templater->includeCss('node_list.less');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['watchedCategories'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array());
		if ($__templater->isTraversable($__compilerTemp2)) {
			foreach ($__compilerTemp2 AS $__vars['id'] => $__vars['treeEntry']) {
				$__compilerTemp1 .= '
					';
				$__vars['category'] = $__vars['treeEntry']['record'];
				$__compilerTemp1 .= '
					';
				$__vars['categoryWatch'] = $__vars['watchedCategories'][$__vars['category']['resource_category_id']];
				$__compilerTemp1 .= '
					';
				if ($__vars['categoryWatch']) {
					$__compilerTemp1 .= '
						';
					$__compilerTemp3 = '';
					if ($__vars['categoryWatch']['notify_on'] == 'resource') {
						$__compilerTemp3 .= '
									<li>' . 'New resources' . '</li>
								';
					} else if ($__vars['categoryWatch']['notify_on'] == 'update') {
						$__compilerTemp3 .= '
									<li>' . 'New resources and updates' . '</li>
								';
					}
					$__compilerTemp4 = '';
					if ($__vars['categoryWatch']['send_email']) {
						$__compilerTemp4 .= '<li>' . 'Emails' . '</li>';
					}
					$__compilerTemp5 = '';
					if ($__vars['categoryWatch']['send_alert']) {
						$__compilerTemp5 .= '<li>' . 'Alerts' . '</li>';
					}
					$__compilerTemp6 = '';
					if ($__vars['categoryWatch']['include_children']) {
						$__compilerTemp6 .= '<li>' . 'Sub-categories' . '</li>';
					}
					$__vars['bonusInfo'] = $__templater->preEscaped('
							<ul class="listInline listInline--bullet">
								' . $__compilerTemp3 . '
								' . $__compilerTemp4 . '
								' . $__compilerTemp5 . '
								' . $__compilerTemp6 . '
							</ul>
						');
					$__compilerTemp1 .= '
						' . $__templater->callMacro('xfrm_category_list_macros', 'category', array(
						'category' => $__vars['category'],
						'extras' => $__vars['categoryExtras'][$__vars['category']['resource_category_id']],
						'children' => $__vars['categoryTree'][$__vars['id']]['children'],
						'childExtras' => $__vars['categoryExtras'],
						'chooseName' => 'ids',
						'bonusInfo' => $__vars['bonusInfo'],
					), $__vars) . '
					';
				}
				$__compilerTemp1 .= '
				';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-container">
			<div class="block-body">
				' . $__compilerTemp1 . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter"></span>
				<span class="block-footer-select">' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '< .block-container',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '</span>
				<span class="block-footer-controls">
					' . $__templater->formSelect(array(
			'name' => 'watch_action',
			'class' => 'input--inline',
		), array(array(
			'label' => 'With selected' . $__vars['xf']['language']['ellipsis'],
			'_type' => 'option',
		),
		array(
			'value' => 'send_email:on',
			'label' => 'Enable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'send_email:off',
			'label' => 'Disable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'send_alert:on',
			'label' => 'Enable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'send_alert:off',
			'label' => 'Disable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'include_children:on',
			'label' => 'Enable sub-category notifications',
			'_type' => 'option',
		),
		array(
			'value' => 'include_children:off',
			'label' => 'Disable sub-category notifications',
			'_type' => 'option',
		),
		array(
			'value' => 'delete',
			'label' => 'Stop watching',
			'_type' => 'option',
		))) . '
					' . $__templater->button('Go', array(
			'type' => 'submit',
		), '', array(
		)) . '
				</span>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('watched/resource-categories/update', ), false),
			'ajax' => 'true',
			'class' => 'block',
			'autocomplete' => 'off',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'You are not watching any categories.' . '</div>
';
	}
	return $__finalCompiled;
});