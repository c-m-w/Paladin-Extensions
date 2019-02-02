<?php
// FROM HASH: 0fa8efb16abf26c9dcd9bb04fb047879
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort templates');
	$__finalCompiled .= '

' . $__templater->callMacro('public:nestable_macros', 'setup', array(), $__vars) . '

';
	$__compilerTemp1 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['templates'])) {
		foreach ($__vars['templates'] AS $__vars['template']) {
			$__vars['i']++;
			$__compilerTemp1 .= '
						<li class="nestable-item" data-id="' . $__templater->escape($__vars['template']['template_id']) . '">
							<div class="nestable-handle" aria-label="' . 'Drag handle' . '"><i class="fa fa-bars" aria-hidden="true"></i></div>
							<div class="nestable-content">' . $__templater->escape($__vars['template']['title']) . '</div>
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
				' . $__templater->formHiddenVal('templates', '', array(
	)) . '
			</div>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/templates/sort', ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});