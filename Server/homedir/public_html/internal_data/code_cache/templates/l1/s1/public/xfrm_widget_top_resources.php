<?php
// FROM HASH: da9d1e7194b2eabd0070fa9eef8f9ee5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['resources'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
		<div class="block-container">
			';
		if ($__vars['style'] == 'full') {
			$__finalCompiled .= '
				<h3 class="block-header">' . ($__templater->escape($__vars['title']) ?: 'Top extensions') . '</h3>
				<div class="block-body">
					<div class="structItemContainer">
						';
			if ($__templater->isTraversable($__vars['resources'])) {
				foreach ($__vars['resources'] AS $__vars['resource']) {
					$__finalCompiled .= '
							' . $__templater->callMacro('xfrm_resource_list_macros', 'resource', array(
						'allowInlineMod' => false,
						'resource' => $__vars['resource'],
					), $__vars) . '
						';
				}
			}
			$__finalCompiled .= '
					</div>
				</div>
			';
		} else {
			$__finalCompiled .= '
				<h3 class="block-minorHeader">' . ($__templater->escape($__vars['title']) ?: 'Top extensions') . '</h3>
				<ul class="block-body">
					';
			if ($__templater->isTraversable($__vars['resources'])) {
				foreach ($__vars['resources'] AS $__vars['resource']) {
					$__finalCompiled .= '
						<li class="block-row">
							' . $__templater->callMacro('xfrm_resource_list_macros', 'resource_simple', array(
						'resource' => $__vars['resource'],
					), $__vars) . '
						</li>
					';
				}
			}
			$__finalCompiled .= '
				</ul>
			';
		}
		$__finalCompiled .= '
		</div>
	</div>
';
	}
	return $__finalCompiled;
});