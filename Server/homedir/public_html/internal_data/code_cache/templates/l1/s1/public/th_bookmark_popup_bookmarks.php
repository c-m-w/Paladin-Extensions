<?php
// FROM HASH: c3453535d329b0c6f09315f41b35bee5
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['bookmarks'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('th_bookmarks.less');
		$__finalCompiled .= '
	';
		$__templater->includeCss('bb_code.less');
		$__finalCompiled .= '
	<div class="menu-scroller">
		<ol class="listPlain">
			';
		if ($__templater->isTraversable($__vars['bookmarks'])) {
			foreach ($__vars['bookmarks'] AS $__vars['bookmark']) {
				$__finalCompiled .= '
				<li class="menu-row menu-row--separated menu-row--clickable ' . ($__vars['bookmark']['sticky'] ? 'menu-row--highlighted' : 'menu-row--alt') . '">
					<div class="menu-fauxLinkRow">
						' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'row', array(
					'fauxBlockList' => '1',
					'editLink' => false,
					'bookmark' => $__vars['bookmark'],
				), $__vars) . '
					</div>
				</li>
			';
			}
		}
		$__finalCompiled .= '
		</ol>
	</div>
	';
	} else {
		$__finalCompiled .= '
	<div class="menu-row">' . 'There are currently no bookmarks to display.' . '</div>
';
	}
	return $__finalCompiled;
});