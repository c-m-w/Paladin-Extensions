<?php
// FROM HASH: 0af4cc38753a8253d2d62484fb829aa0
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['dropdown'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add dropdown');
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit dropdown' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['dropdown']['title']));
		$__finalCompiled .= '
';
	}
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
		'min' => '1',
		'addon' => 'KL/EditorManager',
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
	$__compilerTemp1 = '';
	if ($__templater->isTraversable($__vars['bbCodes'])) {
		foreach ($__vars['bbCodes'] AS $__vars['field']) {
			$__compilerTemp1 .= '
									<li data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="ui-draggable-element">
										<a class="fr-command">
											<i class="fa fa-' . $__templater->escape($__vars['field']['icon']) . '" aria-hidden="true"></i>
											&nbsp;&nbsp;' . $__templater->escape($__vars['field']['name']) . '
										</a>
									</li>
								';
		}
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['layout'])) {
		foreach ($__vars['layout'] AS $__vars['field']) {
			$__compilerTemp2 .= '
									<li data-value="' . $__templater->escape($__vars['field']['toolbarName']) . '" class="ui-draggable-element">
										<a class="fr-command">
											<i class="fa fa-' . $__templater->escape($__vars['field']['icon']) . '" aria-hidden="true"></i>
											&nbsp;&nbsp;' . $__templater->escape($__vars['field']['name']) . '
										</a>
									</li>
								';
		}
	}
	$__finalCompiled .= $__templater->form('

	<div class="block-container">
		' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['dropdown']['title'],
	), array(
		'label' => 'Title',
	)) . '
		' . $__templater->formTextBoxRow(array(
		'name' => 'icon',
		'value' => $__vars['dropdown']['icon'],
	), array(
		'label' => 'Icon',
	)) . '

		<dl class="formRow formRow--input">
			<dt>
				<div class="formRow-labelWrapper">
					<label class="formRow-label">' . 'Layout' . '</label></div>
			</dt>
			<dd>
				<span class="fr-command fr-btn" style="display: none"></span>
				<div class="fr-dropdown-menu visible" role="listbox">
					<h3>' . 'Available buttons' . '</h3>
					<div class="fr-dropdown-wrapper" role="presentation">
						<div class="fr-dropdown-content" role="presentation">
							<ul class="fr-dropdown-list ui-draggable-source">
								' . $__compilerTemp1 . '
							</ul>
						</div>
					</div>
				</div>
				
				<span class="fr-command fr-btn" style="display: none"></span>
				<div class="fr-dropdown-menu visible" role="listbox">
					<h3>' . 'Dropdown content' . '</h3>
					<div class="fr-dropdown-wrapper" role="presentation">
						<div class="fr-dropdown-content" role="presentation">
							<ul class="fr-dropdown-list ui-sortable ui-droppable" data-value="dropdown">
								' . $__compilerTemp2 . '
							</ul>
						</div>
					</div>
				</div>
				' . '
			</dd>
		</dl>

		<input type="hidden" value=\'' . $__templater->filter($__vars['input'], array(array('json', array()),array('raw', array()),), true) . '\' name="toolbar_layout" id="layoutValue" />
		' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('em/dropdowns/save', $__vars['dropdown'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});