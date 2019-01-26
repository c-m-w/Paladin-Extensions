<?php
// FROM HASH: 65a9db0155c79c49ac501285c2702a2b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['escalatingDefaults'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<h2 class="block-header">' . 'Warning Escalating Defaults' . '</h2>
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['escalatingDefaults'])) {
			foreach ($__vars['escalatingDefaults'] AS $__vars['escalatingDefault']) {
				$__compilerTemp1 .= '
						';
				$__vars['expiry_extension_phrase'] = $__templater->preEscaped('' . $__templater->escape($__vars['escalatingDefault']['expiry_extension']) . ' days');
				$__compilerTemp1 .= '
						';
				if ($__vars['escalatingDefault']['expiry_type'] == 'weeks') {
					$__compilerTemp1 .= '
							';
					$__vars['expiry_extension_phrase'] = $__templater->preEscaped('' . $__templater->escape($__vars['escalatingDefault']['expiry_extension']) . ' Weeks');
					$__compilerTemp1 .= '
						';
				}
				$__compilerTemp1 .= '
						';
				if ($__vars['escalatingDefault']['expiry_type'] == 'months') {
					$__compilerTemp1 .= '
							';
					$__vars['expiry_extension_phrase'] = $__templater->preEscaped('' . $__templater->escape($__vars['escalatingDefault']['expiry_extension']) . ' months');
					$__compilerTemp1 .= '
						';
				}
				$__compilerTemp1 .= '
						';
				if ($__vars['escalatingDefault']['expiry_type'] == 'years') {
					$__compilerTemp1 .= '
							';
					$__vars['expiry_extension_phrase'] = $__templater->preEscaped('sv_x_years');
					$__compilerTemp1 .= '
						';
				}
				$__compilerTemp1 .= '
						
						' . $__templater->dataRow(array(
				), array(array(
					'href' => $__templater->fn('link', array('warnings/default/edit', null, array('warning_default_id' => $__vars['escalatingDefault']['warning_default_id'], ), ), false),
					'label' => 'Points' . ': ' . $__templater->escape($__vars['escalatingDefault']['threshold_points']),
					'hint' => ' increase default expiry by ' . $__templater->escape($__vars['expiry_extension_phrase']) . '',
					'_type' => 'main',
					'html' => '',
				),
				array(
					'name' => 'active[' . $__vars['escalatingDefault']['warning_default_id'] . ']',
					'selected' => $__vars['escalatingDefault']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable this warning default',
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('warnings/default/delete', null, array('warning_default_id' => $__vars['escalatingDefault']['warning_default_id'], ), ), false),
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
			<div class="block-footer">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['actions'], ), true) . '</span>
			</div>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});