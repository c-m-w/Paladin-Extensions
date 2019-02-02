<?php
// FROM HASH: 16555338a89c2a6b2a0c52062e7ff653
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Sort special character categories');
	$__finalCompiled .= '

' . $__templater->callMacro('public:nestable_macros', 'setup', array(), $__vars) . '

';
	$__compilerTemp1 = '';
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['characters'])) {
		foreach ($__vars['characters'] AS $__vars['character']) {
			$__vars['i']++;
			$__compilerTemp1 .= '
						<li class="nestable-item" data-id="' . $__templater->escape($__vars['character']['character_id']) . '">
							<div class="nestable-handle" aria-label="' . 'Drag handle' . '"><i class="fa fa-bars" aria-hidden="true"></i></div>
							<div class="nestable-content">' . $__templater->filter($__vars['character']['code'], array(array('raw', array()),), true) . ' - ' . $__templater->escape($__vars['character']['title']) . '</div>
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
				' . $__templater->formHiddenVal('characters', '', array(
	)) . '
			</div>
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/special-chars/characters/sort', $__vars['group'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});