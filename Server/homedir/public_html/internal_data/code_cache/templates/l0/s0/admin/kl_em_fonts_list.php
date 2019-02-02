<?php
// FROM HASH: 6f4c5d1124095f9cbd565deaaa9a5ac7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Fonts');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add font', array(
		'href' => $__templater->fn('link', array('em/fonts/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
		' . $__templater->button('', array(
		'href' => $__templater->fn('link', array('em/fonts/sort', ), false),
		'icon' => 'sort',
		'overlay' => 'true',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	if ($__vars['externalFontCount'] > 4) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--warning blockMessage--iconic">
		' . 'You are using a lot of fonts, that are either hosted from your server or external services. This will slow down your page and will have a negative impact on your user experience. You should consider to reduce the number of fonts you host from external sources.' . '
	</div>
';
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['fonts'])) {
		foreach ($__vars['fonts'] AS $__vars['font']) {
			$__compilerTemp1 .= '
					' . $__templater->dataRow(array(
			), array(array(
				'class' => 'dataList-cell--link dataList-cell--main',
				'hash' => $__vars['font']['font_id'],
				'_type' => 'cell',
				'html' => '
							<a href="' . $__templater->fn('link', array('em/fonts/edit', $__vars['font'], ), true) . '">
								<div class="dataList-mainRow">' . $__templater->escape($__vars['font']['title']) . ' <span class="dataList-hint" dir="auto">' . $__templater->escape($__vars['font']['family']) . '</span></div>
							</a>
						',
			),
			array(
				'name' => 'active[' . $__vars['font']['font_id'] . ']',
				'selected' => $__vars['font']['active'],
				'class' => 'dataList-cell--separated',
				'submit' => 'true',
				'tooltip' => 'Enable / disable \'' . $__vars['font']['font_id'] . '\'',
				'_type' => 'toggle',
				'html' => '',
			),
			array(
				'href' => $__templater->fn('link', array('em/fonts/delete', $__vars['font'], ), false),
				'_type' => 'delete',
				'html' => '',
			))) . '
				';
		}
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
			' . $__templater->dataList('
				' . $__compilerTemp1 . '
			', array(
	)) . '
		</div>
		<div class="block-footer">
			<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['fonts'], ), true) . '</span>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/fonts/toggle', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});