<?php
// FROM HASH: 681824ac04f808531dc484d68b857263
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Most owned games');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'xf/inline_mod.js',
		'min' => '1',
	));
	$__finalCompiled .= '
';
	$__templater->includeCss('public:blacktea_steamauth_list.less');
	$__finalCompiled .= '

<div class="block" data-xf-init="inline-mod" data-type="owned_games" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">
	<div class="block-outer">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'steam/owned-games',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	</div>

	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['games'], 'empty', array())) {
		$__finalCompiled .= '
				<div class="structItemContainer">
					';
		if ($__templater->isTraversable($__vars['games'])) {
			foreach ($__vars['games'] AS $__vars['game']) {
				$__finalCompiled .= '
						';
				$__templater->includeCss('structured_list.less');
				$__finalCompiled .= '
						<div class="structItem js-inlineModContainer">
							<div class="structItem-cell structItem-cell--icon game-image-container">
								<div class="structItem-iconContainer">
									<a href="' . $__templater->escape($__vars['game']['url']) . '" target="_blank">
										<img class="game-image" src="' . $__templater->escape($__vars['game']['image']) . '" />
									</a>
								</div>
							</div>
							<div class="structItem-cell structItem-cell--main" data-xf-init="touch-proxy">
								<a href="' . $__templater->escape($__vars['game']['url']) . '" target="_blank" class="structItem-title">' . $__templater->escape($__vars['game']['label']) . '</a>
								<div class="structItem-minor">
									<ul class="structItem-parts">
										<li>
											<ul class="listInline listInline--comma listInline--selfInline">
												<li>
													<a href="' . $__templater->escape($__vars['game']['url']) . '" target="_blank">
														' . $__templater->escape($__vars['game']['url']) . '
													</a>
												</li>
											</ul>
										</li>
									</ul>
								</div>
							</div>
							<div class="structItem-cell structItem-cell--latest structItem-cell--meta">
								<dl class="pairs pairs--justified">
									<dt>' . 'Total' . '</dt>
									<dd>
										<a href="' . $__templater->escape($__vars['game']['url']) . '" target="_blank">
											' . $__templater->escape($__vars['game']['user_count']) . ' ' . 'users' . '
										</a>
									</dd>
								</dl>
							</div>
						</div>
					';
			}
		}
		$__finalCompiled .= '
				</div>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'Total' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'steam/owned-games',
		'wrapperclass' => 'block-outer block-outer--after',
		'perPage' => $__vars['perPage'],
	))) . '
</div>';
	return $__finalCompiled;
});