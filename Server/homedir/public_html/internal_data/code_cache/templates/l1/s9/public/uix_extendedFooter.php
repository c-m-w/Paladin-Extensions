<?php
// FROM HASH: a62806849c898ad3258b597499689e30
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= '
				' . $__templater->filter($__vars['uix_footerWidgets'], array(array('raw', array()),), true) . '
			';
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
<div class="uix_extendedFooter">
	<div class="pageContent">
		<div class="uix_extendedFooterRow">
			' . $__compilerTemp1 . '
		</div>
	</div>
</div>
';
	}
	return $__finalCompiled;
});