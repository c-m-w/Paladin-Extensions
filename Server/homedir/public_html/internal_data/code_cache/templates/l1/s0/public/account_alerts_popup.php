<?php
// FROM HASH: 0d39ddc68fae38a323ebd284f8c17c19
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['alerts'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="menu-scroller">
		<ol class="listPlain">
			';
		if ($__templater->isTraversable($__vars['alerts'])) {
			foreach ($__vars['alerts'] AS $__vars['alert']) {
				$__finalCompiled .= '
				';
				if ($__templater->method($__vars['alert'], 'getHandler', array())) {
					$__finalCompiled .= '
					<li class="menu-row menu-row--separated menu-row--clickable ' . ($__templater->method($__vars['alert'], 'isUnviewed', array()) ? 'menu-row--highlighted' : ($__templater->method($__vars['alert'], 'isRecentlyViewed', array()) ? '' : 'menu-row--alt')) . '">
						<div class="fauxBlockLink">
							' . $__templater->callMacro('alert_macros', 'row', array(
						'alert' => $__vars['alert'],
					), $__vars) . '
						</div>
					</li>
				';
				}
				$__finalCompiled .= '
			';
			}
		}
		$__finalCompiled .= '
		</ol>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="menu-row">' . 'You have no new alerts.' . '</div>
';
	}
	return $__finalCompiled;
});