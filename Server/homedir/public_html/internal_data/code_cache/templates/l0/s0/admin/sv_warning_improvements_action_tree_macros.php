<?php
// FROM HASH: c9c92563b338c00706c8795d90fa0683
return array('macros' => array('action_list' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'globalActions' => '!',
		'actions' => '!',
		'categoryTree' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (!$__templater->test($__vars['actions'], 'empty', array()) OR !$__templater->test($__vars['globalActions'], 'empty', array())) {
		$__finalCompiled .= '
		<div class="block">
			<div class="block-container">
				<h2 class="block-header">' . 'Warning actions' . '</h2>
				<div class="block-body">
					';
		$__templater->includeCss('sv_warning_improvements_category_list.less');
		$__finalCompiled .= '
					';
		$__compilerTemp1 = '';
		if ($__vars['globalActions']) {
			$__compilerTemp1 .= '
							' . $__templater->dataRow(array(
			), array(array(
				'class' => 'dataList-cell--link dataList-cell--main',
				'hash' => $__vars['category']['warning_category_id'],
				'_type' => 'cell',
				'html' => '
									<a>
										<div class="dataList-mainRow">
											<spam class="u-depth0"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Category"></i> ' . 'Global Warning Actions' . '</spam>
										</div>
									</a>
								',
			))) . '
							
							';
			if ($__templater->isTraversable($__vars['globalActions'])) {
				foreach ($__vars['globalActions'] AS $__vars['action']) {
					$__compilerTemp1 .= '
								';
					$__compilerTemp2 = '';
					if ($__vars['action']['action'] == 'ban') {
						$__compilerTemp2 .= '
														<li>' . 'Ban' . '</li>
														';
					} else if ($__vars['action']['action'] == 'discourage') {
						$__compilerTemp2 .= '
														<li>' . 'Discourage' . '</li>
														';
					} else if ($__vars['action']['action'] == 'groups') {
						$__compilerTemp2 .= '
														<li>' . 'Add to selected groups' . '</li>
														';
					} else {
						$__compilerTemp2 .= '
														<li>' . 'Unknown action' . '</li>
													';
					}
					$__compilerTemp3 = '';
					if ($__vars['action']['action_length_type'] == 'permanent') {
						$__compilerTemp3 .= '
														<li>' . 'Permanent' . '</li>
														';
					} else if ($__vars['action']['action_length_type'] == 'points') {
						$__compilerTemp3 .= '
														<li>' . 'While at or above points threshold' . '</li>
														';
					} else {
						$__compilerTemp3 .= '
														<li>' . 'Temporary' . '</li>
													';
					}
					$__compilerTemp1 .= $__templater->dataRow(array(
					), array(array(
						'href' => $__templater->fn('link', array('warnings/actions/edit', $__vars['action'], ), false),
						'class' => 'u-depth0',
						'_type' => 'cell',
						'html' => '
										<div class="dataList-mainRow">
											<spam class="u-depth1"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Action"></i> ' . 'Points' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['action']['points']) . '</spam>
											
											<div class="dataList-hint" dir="auto">
												<ul class="listInline listInline--bullet listInline--selfInline">
													' . $__compilerTemp2 . '

													' . $__compilerTemp3 . '
												</ul>
											</div>
										</div>
									',
					),
					array(
						'href' => $__templater->fn('link', array('warnings/actions/delete', $__vars['action'], ), false),
						'_type' => 'delete',
						'html' => '',
					))) . '
							';
				}
			}
			$__compilerTemp1 .= '
						';
		}
		$__compilerTemp4 = '';
		$__compilerTemp5 = $__templater->method($__vars['categoryTree'], 'getFlattened', array(0, ));
		if ($__templater->isTraversable($__compilerTemp5)) {
			foreach ($__compilerTemp5 AS $__vars['treeEntry']) {
				$__compilerTemp4 .= '
							';
				$__vars['category'] = $__vars['treeEntry']['record'];
				$__compilerTemp4 .= '
							';
				if (!$__templater->test($__vars['actions'][$__vars['category']['warning_category_id']], 'empty', array())) {
					$__compilerTemp4 .= '
								' . $__templater->dataRow(array(
					), array(array(
						'class' => 'dataList-cell--link dataList-cell--main',
						'hash' => $__vars['category']['warning_category_id'],
						'_type' => 'cell',
						'html' => '
										<a href="' . $__templater->fn('link', array('warnings/category-edit', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), true) . '">
											<div class="u-depth' . $__templater->escape($__vars['treeEntry']['depth']) . '">
												<div class="dataList-mainRow"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Category"></i> ' . $__templater->escape($__vars['category']['title']) . '</div>
											</div>
										</a>
									',
					),
					array(
						'href' => $__templater->fn('link', array('warnings/category-delete', null, array('warning_category_id' => $__vars['category']['warning_category_id'], ), ), false),
						'_type' => 'delete',
						'html' => '',
					))) . '
								';
					if ($__templater->isTraversable($__vars['actions'][$__vars['category']['warning_category_id']])) {
						foreach ($__vars['actions'][$__vars['category']['warning_category_id']] AS $__vars['action']) {
							$__compilerTemp4 .= '
									';
							$__compilerTemp6 = '';
							if ($__vars['action']['action'] == 'ban') {
								$__compilerTemp6 .= '
															<li>' . 'Ban' . '</li>
															';
							} else if ($__vars['action']['action'] == 'discourage') {
								$__compilerTemp6 .= '
															<li>' . 'Discourage' . '</li>
															';
							} else if ($__vars['action']['action'] == 'groups') {
								$__compilerTemp6 .= '
															<li>' . 'Add to selected groups' . '</li>
															';
							} else {
								$__compilerTemp6 .= '
															<li>' . 'Unknown action' . '</li>
														';
							}
							$__compilerTemp7 = '';
							if ($__vars['action']['action_length_type'] == 'permanent') {
								$__compilerTemp7 .= '
															<li>' . 'Permanent' . '</li>
															';
							} else if ($__vars['action']['action_length_type'] == 'points') {
								$__compilerTemp7 .= '
															<li>' . 'While at or above points threshold' . '</li>
															';
							} else {
								$__compilerTemp7 .= '
															<li>' . 'Temporary' . '</li>
														';
							}
							$__compilerTemp4 .= $__templater->dataRow(array(
							), array(array(
								'href' => $__templater->fn('link', array('warnings/actions/edit', $__vars['action'], ), false),
								'_type' => 'cell',
								'html' => '
											<div class="dataList-mainRow">
												<spam class="u-depth' . ($__vars['treeEntry']['depth'] + 1) . '"><i class="warningImprovementsListingIcons warningImprovementsListingIcons--Action"></i> ' . 'Points' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['action']['points']) . '</spam>
												<div class="dataList-hint" dir="auto">
													<ul class="listInline listInline--bullet listInline--selfInline">
														' . $__compilerTemp6 . '

														' . $__compilerTemp7 . '
													</ul>
												</div>
											</div>
										',
							),
							array(
								'href' => $__templater->fn('link', array('warnings/actions/delete', $__vars['action'], ), false),
								'_type' => 'delete',
								'html' => '',
							))) . '
								';
						}
					}
					$__compilerTemp4 .= '
							';
				}
				$__compilerTemp4 .= '
						';
			}
		}
		$__finalCompiled .= $__templater->dataList('
						' . $__compilerTemp1 . '
						' . $__compilerTemp4 . '
					', array(
		)) . '
				</div>
			</div>
		</div>
	';
	} else {
		$__finalCompiled .= '
		<div class="blockMessage">' . 'No items have been created yet.' . '</div>
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});