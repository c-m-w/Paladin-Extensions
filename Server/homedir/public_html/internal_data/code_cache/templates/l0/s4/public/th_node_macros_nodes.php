<?php
// FROM HASH: 9c65f6508a65bef2b98468a2185ef706
return array('macros' => array('node_list_item_footer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'node' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__templater->fn('property', array('th_enableNodeFooter_nodes', ), false)) {
		$__finalCompiled .= '
		<div class="block-footer has-flexbox">
			<div class="node-footer--actions">
				';
		if (($__vars['node']['node_type_id'] === 'Forum') AND $__templater->method($__templater->method($__vars['node'], 'getData', array()), 'canCreateThread', array())) {
			$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('forums/post-thread', $__vars['node'], ), true) . '"
					   data-xf-click="overlay"
					   class="node-footer--createThread"
					   data-xf-init="tooltip"
					   title="' . 'Post thread' . $__vars['xf']['language']['ellipsis'] . '"></a>
				';
		}
		$__finalCompiled .= '

				';
		if (($__vars['node']['node_type_id'] === 'Forum') AND $__templater->method($__vars['node']['Data'], 'canWatch', array())) {
			$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('forums/watch', $__vars['node']['Data'], ), true) . '"
					   data-xf-click="switch-overlay"
					   title="' . ($__vars['node']['Data']['Watch'][$__vars['xf']['visitor']['user_id']] ? 'Unwatch' : 'Watch') . '"
					   data-xf-init="tooltip"
					   data-sk-watch="addClass:fa-eye,removeClass:fa-eye-slash,"
					   data-sk-unwatch="addClass:fa-eye-slash,removeClass:fa-eye,"
					   class="fa fa-eye' . ($__vars['node']['Data']['Watch'][$__vars['xf']['visitor']['user_id']] ? '-slash' : '') . '">
					</a>
				';
		}
		$__finalCompiled .= '
			</div>
			<div class="node-footer--more">
				<a href="' . $__templater->fn('link', array($__templater->method($__vars['node'], 'getRoute', array()), $__vars['node'], ), true) . '"></a>
			</div>
		</div>
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