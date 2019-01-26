<?php
// FROM HASH: 5f770e5996d0bd647c4256d95e516a82
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
				<h3 class="block-header">
					<a href="' . $__templater->escape($__vars['link']) . '" rel="nofollow">' . ($__templater->escape($__vars['title']) ?: 'Latest resources') . '</a>
				</h3>
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
			if ($__vars['hasMore']) {
				$__finalCompiled .= '
					<div class="block-footer">
						<span class="block-footer-controls">
							' . $__templater->button('View more' . $__vars['xf']['language']['ellipsis'], array(
					'href' => $__vars['link'],
					'rel' => 'nofollow',
				), '', array(
				)) . '
						</span>
					</div>
				';
			}
			$__finalCompiled .= '
			';
		} else {
			$__finalCompiled .= '
				<h3 class="block-minorHeader">
					<a href="' . $__templater->escape($__vars['link']) . '" rel="nofollow">' . ($__templater->escape($__vars['title']) ?: 'Latest resources') . '</a>
				</h3>
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