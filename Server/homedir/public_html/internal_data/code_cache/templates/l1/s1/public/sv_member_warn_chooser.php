<?php
// FROM HASH: 079dd527d567d3f83ba839fd016788f7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('sv_member_warn_chooser.less');
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'addon' => 'SV/WarningImprovements',
		'src' => 'sv/warningimprovements/warnings.js',
		'min' => '1',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'prod' => 'vendor/select2/select2.full.js',
		'dev' => 'vendor/select2/select2.full.min.js',
	));
	$__finalCompiled .= '

';
	$__templater->inlineJs('
jQuery.extend(XF.config, {
	sv_warningimprovements_copy_title: ' . $__vars['xf']['options']['sv_warningimprovements_copy_title'] . '
});
');
	$__finalCompiled .= '

<div id="warning-view-select" style="display: none; opacity: 0;">
	';
	$__compilerTemp1 = array();
	$__compilerTemp2 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp2)) {
		foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
			$__vars['category'] = $__vars['treeEntry']['record'];
			$__compilerTemp1[] = array(
				'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), false) . ' ' . $__vars['category']['title'],
				'_type' => 'optgroup',
				'options' => array(),
			);
			end($__compilerTemp1); $__compilerTemp3 = key($__compilerTemp1);
			if ($__templater->isTraversable($__vars['warnings'][$__vars['category']['warning_category_id']])) {
				foreach ($__vars['warnings'][$__vars['category']['warning_category_id']] AS $__vars['warning']) {
					$__compilerTemp1[$__compilerTemp3]['options'][] = array(
						'value' => $__vars['warning']['warning_definition_id'],
						'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['warning']['title']),
						'_type' => 'option',
					);
				}
			}
		}
	}
	$__finalCompiled .= $__templater->formSelectRow(array(
		'name' => 'warning_definition_id',
		'class' => 'js-FormFiller',
		'value' => '0',
		'data-no-results-text' => 'No results match',
		'data-place-holder-text' => 'Choose a warning...',
		'data-xf-init' => 'warning-view-select warning-title-watcher',
		'data-warning-select' => 'true',
	), $__compilerTemp1, array(
		'label' => 'Warning type',
	)) . '

	';
	$__compilerTemp4 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp4)) {
		foreach ($__compilerTemp4 AS $__vars['treeEntry']) {
			$__finalCompiled .= '
		';
			$__vars['category'] = $__vars['treeEntry']['record'];
			$__finalCompiled .= '
		';
			if ($__templater->isTraversable($__vars['warnings'][$__vars['category']['warning_category_id']])) {
				foreach ($__vars['warnings'][$__vars['category']['warning_category_id']] AS $__vars['warningDefinition']) {
					$__finalCompiled .= '
				';
					$__compilerTemp5 = '';
					if ($__vars['warningDefinition']['sv_custom_title'] OR ($__vars['warningDefinition']['warning_definition_id'] == 0)) {
						$__compilerTemp5 .= '
						' . $__templater->formTextBox(array(
							'name' => 'custom_title',
							'maxlength' => $__templater->fn('max_length', array($__vars['warningDefinition'], 'title', ), false),
							'value' => '',
							'data-xf-init' => 'warning-title-watcher',
							'data-warning-title-input' => '1',
							'data-for-warning' => $__vars['warningDefinition']['warning_definition_id'],
							'disabled' => 'disabled',
							'placeholder' => 'Custom title',
						)) . '
					';
					} else {
						$__compilerTemp5 .= '
						' . $__templater->formHiddenVal('custom_title', '', array(
							'data-warning-title-input' => '1',
							'data-for-warning' => $__vars['warningDefinition']['warning_definition_id'],
						)) . '
					';
					}
					$__finalCompiled .= $__templater->formRow('
					' . $__compilerTemp5 . '
				', array(
						'label' => '',
						'data-custom-title-container' => '1',
						'data-warning-view-type' => 'select',
						'data-warning-label' => $__vars['warningDefinition']['custom_title_placeholder'],
						'data-for-warning' => $__vars['warningDefinition']['warning_definition_id'],
					)) . '
		';
				}
			}
			$__finalCompiled .= '
	';
		}
	}
	$__finalCompiled .= '
</div>

<div id="warning-view-radio" style="display: none; opacity: 0;">
	';
	$__compilerTemp6 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
	if ($__templater->isTraversable($__compilerTemp6)) {
		foreach ($__compilerTemp6 AS $__vars['treeEntry']) {
			$__finalCompiled .= '
		';
			$__vars['category'] = $__vars['treeEntry']['record'];
			$__finalCompiled .= '

		';
			if ($__vars['warnings'][$__vars['category']['warning_category_id']]) {
				$__finalCompiled .= '
			';
				if ($__vars['treeEntry']['depth'] === 0) {
					$__finalCompiled .= '
				';
					$__vars['categoryTitleForFormRow'] = $__templater->preEscaped($__templater->escape($__vars['category']['title']));
					$__finalCompiled .= '
			';
				} else {
					$__finalCompiled .= '
				';
					if (((!$__vars['warnings'][$__vars['category']['Parent']['warning_category_id']]) AND ($__vars['category']['Parent']['depth'] === 0)) OR ((!$__vars['warnings'][$__vars['category']['Parent']['warning_category_id']]) AND ($__vars['category']['Parent']['depth'] !== 0))) {
						$__finalCompiled .= '
					';
						$__vars['categoryTitleForFormRow'] = $__templater->preEscaped($__templater->escape($__vars['category']['title']));
						$__finalCompiled .= '
				';
					} else {
						$__finalCompiled .= '
					';
						$__vars['categoryTitleForFormRow'] = $__templater->preEscaped('');
						$__finalCompiled .= '
				';
					}
					$__finalCompiled .= '
			';
				}
				$__finalCompiled .= '

			';
				if ($__vars['treeEntry']['depth'] !== 0) {
					$__finalCompiled .= '
				';
					if (((!$__vars['warnings'][$__vars['category']['Parent']['warning_category_id']]) AND ($__vars['category']['Parent']['depth'] === 0)) OR ((!$__vars['warnings'][$__vars['category']['Parent']['warning_category_id']]) AND ($__vars['category']['Parent']['depth'] !== 0))) {
						$__finalCompiled .= '
					';
						$__vars['categoryTitleForRadio'] = $__templater->preEscaped('');
						$__finalCompiled .= '
				';
					} else {
						$__finalCompiled .= '
					';
						$__vars['categoryTitleForRadio'] = $__templater->preEscaped($__templater->escape($__vars['category']['title']) . ':');
						$__finalCompiled .= '
				';
					}
					$__finalCompiled .= '
			';
				} else {
					$__finalCompiled .= '
				';
					$__vars['categoryTitleForRadio'] = $__templater->preEscaped('');
					$__finalCompiled .= '
			';
				}
				$__finalCompiled .= '

			';
				$__compilerTemp7 = '';
				if (!$__templater->fn('empty', array($__vars['categoryTitleForRadio']))) {
					$__compilerTemp7 .= '
					<label class="u-depth' . $__templater->escape($__vars['treeEntry']['depth']) . '">' . $__templater->escape($__vars['categoryTitleForRadio']) . '</label>
				';
				}
				$__compilerTemp8 = '';
				if ($__templater->isTraversable($__vars['warnings'][$__vars['category']['warning_category_id']])) {
					foreach ($__vars['warnings'][$__vars['category']['warning_category_id']] AS $__vars['warningDefinition']) {
						$__compilerTemp8 .= '
					<div class="u-depth' . $__templater->escape($__vars['treeEntry']['depth']) . '">
						';
						$__compilerTemp9 = '';
						if ($__vars['warningDefinition']['sv_custom_title'] OR ($__vars['warningDefinition']['warning_definition_id'] == 0)) {
							$__compilerTemp9 .= '
										' . $__templater->formRow('
											' . $__templater->formTextBox(array(
								'name' => 'custom_title',
								'maxlength' => $__templater->fn('max_length', array($__vars['warningDefinition'], 'title', ), false),
								'value' => $__vars['warningDefinition']['custom_title_placeholder'],
								'data-xf-init' => 'warning-title-watcher',
								'data-warning-title-input' => '1',
								'data-for-warning' => $__vars['warningDefinition']['warning_definition_id'],
							)) . '
										', array(
								'label' => '',
								'data-custom-title-container' => '1',
								'data-warning-view-type' => 'radio',
							)) . '
									';
						}
						$__compilerTemp8 .= $__templater->formRadio(array(
							'name' => 'warning_definition_id',
							'value' => '0',
						), array(array(
							'value' => $__vars['warningDefinition']['warning_definition_id'],
							'class' => 'js-FormFiller',
							'label' => $__templater->escape($__vars['warningDefinition']['title']),
							'data-warning-radio' => 'true',
							'data-warning-label' => $__vars['warningDefinition']['custom_title_placeholder'],
							'data-xf-init' => 'warning-title-watcher',
							'_dependent' => array('
									' . $__compilerTemp9 . '
								'),
							'_type' => 'option',
						))) . '
					</div>
				';
					}
				}
				$__finalCompiled .= $__templater->formRow('
				' . $__compilerTemp7 . '

				' . $__compilerTemp8 . '
			', array(
					'label' => $__templater->escape($__vars['categoryTitleForFormRow']),
					'class' => 'u-depth' . $__vars['treeEntry']['depth'],
				)) . '
		';
			}
			$__finalCompiled .= '
	';
		}
	}
	$__finalCompiled .= '
</div>

' . $__templater->formRow('
	<a class="u-jsOnly" data-xf-init="warning-view-toggle" href="#"
	data-select-view="#warning-view-select"
	data-radio-view="#warning-view-radio"
	data-toggle-select-phrase="' . $__templater->filter('Use select view', array(array('for_attr', array()),), true) . '"
	data-toggle-radio-phrase="' . $__templater->filter('Use radio view', array(array('for_attr', array()),), true) . '"></a>
', array(
	));
	return $__finalCompiled;
});