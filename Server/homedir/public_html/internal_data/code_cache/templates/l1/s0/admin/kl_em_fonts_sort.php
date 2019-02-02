<?php
// FROM HASH: ce42bad19edbcf4f9e621f0fa2536b98
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort fonts');
	$__finalCompiled .= '

' . $__templater->callMacro('public:nestable_macros', 'setup', array(), $__vars) . '

';
	$__compilerTemp1 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['fonts'])) {
		foreach ($__vars['fonts'] AS $__vars['font']) {
			$__vars['i']++;
			$__compilerTemp1 .= '
						<li class="nestable-item" data-id="' . $__templater->escape($__vars['font']['font_id']) . '">
							<div class="nestable-handle" aria-label="' . 'Drag handle' . '"><i class="fa fa-bars" aria-hidden="true"></i></div>
							<div class="nestable-content">' . $__templater->escape($__vars['font']['font_id']) . '</div>
						</li>
					';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			<div class="nestable-container" data-xf-init="nestable" data-parent-id="">
				<ol class="nestable-list">
					' . $__compilerTemp1 . '
					' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'rowtype' => 'simple',
	)) . '
				</ol>
				' . $__templater->formHiddenVal('fonts', '', array(
	)) . '
			</div>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/fonts/sort', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});