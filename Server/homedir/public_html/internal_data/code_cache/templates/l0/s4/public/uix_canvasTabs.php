<?php
// FROM HASH: c74dcc2cb98ccfc51e29efd9c14e6a90
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<ul class="sidePanel__tabs">
	<li>
		<a class="sidePanel__tab is-active js-visitorTab">' . $__templater->callMacro('uix_icons.less', 'icon', array(
		'icon' => 'menu',
	), $__vars) . '</a>
	</li>
	
	';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
	
	<li>
		<a class="sidePanel__tab js-visitorTab">' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'user',
		), $__vars) . '</a>
	</li>

	<li>
		<a class="sidePanel__tab js-convoTab">
			' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'inbox',
		), $__vars) . '
		</a>
	</li>

	<li>
		<a class="sidePanel__tab js-alertTab">
			' . $__templater->callMacro('uix_icons.less', 'icon', array(
			'icon' => 'alert',
		), $__vars) . '
		</a>
	</li>
		
	';
	}
	$__finalCompiled .= '
	
</ul>';
	return $__finalCompiled;
});