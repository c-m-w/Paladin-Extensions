<?php
// FROM HASH: aeadd77cf4d19c10b741c39a1ca93126
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Choose file' . $__vars['xf']['language']['ellipsis']);
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<ul class="block-body">
			';
	if ($__templater->isTraversable($__vars['files'])) {
		foreach ($__vars['files'] AS $__vars['file']) {
			$__finalCompiled .= '
				<li class="block-row block-row--separated">
					<div class="contentRow">
						<div class="contentRow-main">
							<span class="contentRow-extra">
								' . $__templater->button('Download', array(
				'href' => $__templater->fn('link', array('resources/version/download', $__vars['version'], array('file' => $__vars['file']['attachment_id'], ), ), false),
				'icon' => 'download',
			), '', array(
			)) . '
							</span>
							<h3 class="contentRow-title">' . $__templater->escape($__vars['file']['filename']) . '</h3>
							<div class="contentRow-minor">
								' . $__templater->filter($__vars['file']['file_size'], array(array('file_size', array()),), true) . '
							</div>
						</div>
					</div>
				</li>
			';
		}
	}
	$__finalCompiled .= '
		</ul>
	</div>
</div>';
	return $__finalCompiled;
});