<?php
// FROM HASH: f5abe6c0203c9baefdee72b2ecdfb491
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Public templates');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add template', array(
		'href' => $__templater->fn('link', array('em/templates/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
		' . $__templater->button('', array(
		'href' => $__templater->fn('link', array('em/templates/sort', ), false),
		'icon' => 'sort',
		'overlay' => 'true',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['templates'], 'empty', array())) {
		$__compilerTemp1 .= '
				';
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['templates'])) {
			foreach ($__vars['templates'] AS $__vars['template']) {
				$__compilerTemp2 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['template']['template_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('em/templates/edit', $__vars['template'], ), true) . '">
									<div class="dataList-mainRow">' . $__templater->escape($__vars['template']['title']) . '</div>
								</a>
							',
				),
				array(
					'class' => ((!$__templater->fn('empty', array($__vars['template']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
					'href' => $__templater->fn('link', array('em/templates/edit', $__vars['template'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'User criteria' . '
							',
				),
				array(
					'name' => 'active[' . $__vars['template']['template_id'] . ']',
					'selected' => $__vars['template']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['template']['title'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('em/templates/delete', $__vars['template'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__compilerTemp1 .= $__templater->dataList('
					' . $__compilerTemp2 . '
				', array(
		)) . '
				';
	} else {
		$__compilerTemp1 .= '
				<div class="block-row">
					' . 'There are no public editor templates yet.' . '
				</div>
			';
	}
	$__finalCompiled .= $__templater->form('
	<xen:comment>
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
		'key' => 'nodes',
		'class' => 'block-outer-opposite',
	), $__vars) . '
		</div>
	</xen:comment>

	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
		</div>
		<div class="block-footer">
			<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['templates'], ), true) . '</span>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/templates/toggle', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});