<?php
// FROM HASH: c99a8901cc39d4d302d0bf8aaf9a167d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Toolbar layout');
	$__finalCompiled .= '

';
	$__templater->includeCss('public:editor.less');
	$__finalCompiled .= '
';
	$__templater->includeCss('kl_em_layout.less');
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/vendor/jquery-ui.min.js',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/layout.js',
		'addon' => 'KL/EditorManager',
		'min' => '1',
	));
	$__finalCompiled .= '

';
	if ($__templater->fn('is_addon_active', array('Math', ), false)) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('public:Math.less');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add dropdown', array(
		'href' => $__templater->fn('link', array('em/dropdowns/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<h1 class="block-header">
			' . 'Dropdowns' . '
		</h1>
		<div class="block-body" style="padding: 0">
			';
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['dropdowns'])) {
		foreach ($__vars['dropdowns'] AS $__vars['dropdown']) {
			$__compilerTemp1 .= '
					' . $__templater->dataRow(array(
			), array(array(
				'class' => 'dataList-cell--link dataList-cell--main',
				'hash' => $__vars['dropdown']['dropdown_id'],
				'_type' => 'cell',
				'html' => '
							<a href="' . $__templater->fn('link', array('em/dropdowns/edit', $__vars['dropdown'], ), true) . '">
								<div class="dataList-mainRow">' . $__templater->escape($__vars['dropdown']['title']) . '</div>
							</a>
						',
			),
			array(
				'href' => $__templater->fn('link', array('em/dropdowns/delete', $__vars['dropdown'], ), false),
				'_type' => 'delete',
				'html' => '',
			))) . '
				';
		}
	}
	$__finalCompiled .= $__templater->dataList('
				' . $__compilerTemp1 . '
			', array(
	)) . '
		</div>
	</div>
</div>

';
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['bbCodes'])) {
		foreach ($__vars['bbCodes'] AS $__vars['field']) {
			$__compilerTemp2 .= '
					';
			if ($__vars['field']['iconType'] === 'separator') {
				$__compilerTemp2 .= '
						<span data-value="|" class="fr-sep fr-command fr-btn ui-draggable-element">
							<i class="separator" data-xf-init="tooltip" title="' . 'Separator' . '"></i>
						</span>
						';
			} else {
				$__compilerTemp2 .= '
						';
				if ($__vars['field']['iconType'] === 'fa') {
					$__compilerTemp2 .= '
							<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
								<i data-xf-init="tooltip" class="fa fa-' . $__templater->escape($__vars['field']['icon']) . '" title="' . $__templater->escape($__vars['field']['name']) . '"></i>
							</span>

							';
				} else if ($__vars['field']['iconType'] === 'text') {
					$__compilerTemp2 .= '

							<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
								<i data-xf-init="tooltip" title="' . $__templater->escape($__vars['field']['name']) . '" class="text-icon">' . $__templater->filter($__vars['field']['icon'], array(array('raw', array()),), true) . '</i>
							</span>

							';
				} else if ($__vars['field']['iconType'] === 'img') {
					$__compilerTemp2 .= '
							<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
								<img data-xf-init="tooltip"
									 title="' . $__templater->escape($__vars['field']['name']) . '"
									 class="text-icon"
									 src="' . $__templater->filter($__vars['field']['icon'], array(array('raw', array()),), true) . '" />
							</span>
						';
				}
				$__compilerTemp2 .= '
					';
			}
			$__compilerTemp2 .= '
				';
		}
	}
	$__compilerTemp3 = '';
	if ($__templater->isTraversable($__vars['layouts'])) {
		foreach ($__vars['layouts'] AS $__vars['key'] => $__vars['layout']) {
			$__compilerTemp3 .= '
				<h3>' . $__templater->escape($__vars['layout']['name']) . '</h3>
				<div class="fr-toolbar fr-' . $__templater->escape($__vars['key']) . ' ui-sortable ui-droppable" data-value="' . $__templater->escape($__vars['key']) . '">
					';
			if ($__templater->isTraversable($__vars['layout']['layout'])) {
				foreach ($__vars['layout']['layout'] AS $__vars['field']) {
					$__compilerTemp3 .= '
						';
					if ($__vars['field']['iconType'] === 'separator') {
						$__compilerTemp3 .= '
							<span data-value="|" class="fr-sep fr-command fr-btn ui-draggable-element">
								<i class="separator" data-xf-init="tooltip" title="' . 'Separator' . '"></i>
							</span>
							';
					} else {
						$__compilerTemp3 .= '
							';
						if ($__vars['field']['iconType'] === 'fa') {
							$__compilerTemp3 .= '
								<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
									<i data-xf-init="tooltip" class="fa fa-' . $__templater->escape($__vars['field']['icon']) . '" title="' . $__templater->escape($__vars['field']['name']) . '"></i>
								</span>

								';
						} else if ($__vars['field']['iconType'] === 'text') {
							$__compilerTemp3 .= '

								<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
									<i data-xf-init="tooltip" title="' . $__templater->escape($__vars['field']['name']) . '" class="text-icon">' . $__templater->filter($__vars['field']['icon'], array(array('raw', array()),), true) . '</i>
								</span>

								';
						} else if ($__vars['field']['iconType'] === 'img') {
							$__compilerTemp3 .= '
								<span data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="fr-command fr-btn ui-draggable-element">
									<img data-xf-init="tooltip"
										 title="' . $__templater->escape($__vars['field']['name']) . '"
										 class="text-icon"
										 src="' . $__templater->filter($__vars['field']['icon'], array(array('raw', array()),), true) . '" />
								</span>
							';
						}
						$__compilerTemp3 .= '
						';
					}
					$__compilerTemp3 .= '
					';
				}
			}
			$__compilerTemp3 .= '
				</div>
			';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<h1 class="block-header">
			' . 'Layout' . '
		</h1>
		<div class="block-body">	
			<h3>' . 'Available buttons' . '</h3>
			<div class="fr-toolbar ui-draggable-source">
				' . $__compilerTemp2 . '
			</div>

			<p class="contentRow-muted">' . 'This page allows you to define the order of buttons, that are shown in your editor toolbar. You may remove any button from any of the four toolbars by dragging it out of the toolbar. You can also add new buttons from the bar above, which holds a list of all available buttons, by dragging them to where you want to have them.' . '</p>
			' . $__compilerTemp3 . '
		</div>

		<input type="hidden" value=\'' . $__templater->filter($__vars['layoutValue'], array(array('json', array()),array('raw', array()),), true) . '\' name="toolbar_layout" id="layoutValue" />
		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/layout/save', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});