<?php
// FROM HASH: 75a6df96c4914346a32c9c5e4a59991c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__vars['thNodes'] = 'ThemeHouse/Nodes';
	$__finalCompiled .= '
';
	$__vars['thNodesInstalled'] = '0';
	$__finalCompiled .= '
';
	$__vars['extraNodeClasses'] = '';
	$__finalCompiled .= '
';
	if ($__vars['xf']['addOns'][$__vars['thNodes']]) {
		$__finalCompiled .= '
	';
		$__vars['thNodesInstalled'] = '1';
		$__finalCompiled .= '
	';
		$__vars['extraNodeClasses'] = $__templater->fn('th_nodeclasses_nodes', array($__vars['node'], $__vars['extras'], ), false);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
<div class="node node--forum node--id' . $__templater->escape($__vars['node']['node_id']) . ' ' . ($__vars['extras']['hasNew'] ? 'node--unread' : 'node--read') . ' ' . $__templater->escape($__vars['extraNodeClasses']) . '">
	<div class="node-icon">
		<i>
			';
	if ($__vars['thNodesInstalled']) {
		$__finalCompiled .= '
				' . $__templater->fn('th_nodeicon_nodes', array($__vars['node'], $__vars['extras'], ), true) . '
			';
	}
	$__finalCompiled .= '
		</i>
	</div>
</div>

';
	$__templater->includeCss('node_list.less');
	return $__finalCompiled;
});