<?php
// FROM HASH: 4805b55a0af388899298c7093d0c55bc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['similarThreads']) {
		$__finalCompiled .= '

';
		$__templater->includeCss('andy_similarthreads.less');
		$__finalCompiled .= '

<div class="block"' . $__templater->fn('widget_data', array($__vars['widget'], ), true) . '>
	<div class="block-container">
		<h3 class="block-minorHeader">' . 'Similar threads' . '</h3>
		<div class="block-body block-row">
			<ul class="block-body">
				';
		if ($__templater->isTraversable($__vars['similarThreads'])) {
			foreach ($__vars['similarThreads'] AS $__vars['thread']) {
				$__finalCompiled .= '
					<li class="block-row">
						' . $__templater->callMacro('thread_list_macros', 'item_new_threads', array(
					'thread' => $__vars['thread'],
				), $__vars) . '
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</div>
	</div>
</div>
	
';
	}
	return $__finalCompiled;
});