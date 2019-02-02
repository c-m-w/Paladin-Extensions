<?php
// FROM HASH: d304afa397e4cb227da2513744a692ed
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Editor templates');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['canCreateTemplates']) {
		$__compilerTemp1 .= '
			' . $__templater->button('Add template', array(
			'href' => $__templater->fn('link', array('account/editor-templates/add', ), false),
			'icon' => 'add',
			'overlay' => 'true',
		), '', array(
		)) . '
		';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__compilerTemp1 . '
		' . $__templater->button('', array(
		'href' => $__templater->fn('link', array('account/editor-templates/sort', ), false),
		'icon' => 'sort',
		'overlay' => 'true',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

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
							<a href="' . $__templater->fn('link', array('account/editor-templates/edit', $__vars['template'], ), true) . '">
								<div class="dataList-mainRow">' . $__templater->escape($__vars['template']['title']) . '</div>
							</a>
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
				'href' => $__templater->fn('link', array('account/editor-templates/delete', $__vars['template'], ), false),
				'_type' => 'delete',
				'html' => '',
			))) . '
				';
		}
	}
	$__finalCompiled .= $__templater->form('
	
	<div class="block-container">
		<div class="block-body">
			' . $__templater->dataList('
				' . $__compilerTemp2 . '
			', array(
	)) . '
		</div>
		<div class="block-footer">
			<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['templates'], ), true) . '</span>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('account/editor-templates/toggle', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});