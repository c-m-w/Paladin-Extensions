<?php
// FROM HASH: e5c6e51b965e75f5282dc67fe7a3849f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Likes given');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

';
	if ($__vars['total'] > 0) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<ul class="block-body">
				';
		if ($__templater->isTraversable($__vars['likes'])) {
			foreach ($__vars['likes'] AS $__vars['like']) {
				$__finalCompiled .= '
					<li class="block-row block-row--separated">
						<div class="contentRow">
							<span class="contentRow-figure">
								' . $__templater->fn('avatar', array($__vars['like']['Liker'], 's', false, array(
				))) . '
							</span>

							<div class="contentRow-main">
								' . $__templater->filter($__templater->method($__vars['like'], 'render', array()), array(array('raw', array()),), true) . '
							</div>
						</div>
					</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</div>

		' . $__templater->fn('page_nav', array(array(
			'link' => 'account/likes-given',
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'You have not given any content any likes yet.' . '</div>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});