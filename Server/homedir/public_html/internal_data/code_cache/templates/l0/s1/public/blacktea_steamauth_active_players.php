<?php
// FROM HASH: b5ee013dfb26672a8d29f4eed2256ddf
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Most active players');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

';
	$__templater->includeJs(array(
		'src' => 'xf/inline_mod.js',
		'min' => '1',
	));
	$__finalCompiled .= '

<div class="block" data-xf-init="inline-mod" data-type="active_users" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">
	<div class="block-outer">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'steam/active-players',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	</div>

	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['userPlaytimes'], 'empty', array())) {
		$__finalCompiled .= '
				<div class="structItemContainer">
					';
		if ($__templater->isTraversable($__vars['userPlaytimes'])) {
			foreach ($__vars['userPlaytimes'] AS $__vars['userPlaytime']) {
				$__finalCompiled .= '
						';
				$__templater->includeCss('structured_list.less');
				$__finalCompiled .= '
						<div class="structItem js-inlineModContainer">
							<div class="structItem-cell structItem-cell--icon">
								<div class="structItem-iconContainer">
									' . $__templater->fn('avatar', array($__vars['users'][$__vars['userPlaytime']['user_id']], 's', false, array(
				))) . '
								</div>
							</div>
							<div class="structItem-cell structItem-cell--main" data-xf-init="touch-proxy">
								<a href="' . $__templater->fn('link', array('members', $__vars['users'][$__vars['userPlaytime']['user_id']], ), true) . '" class="structItem-title">' . $__templater->escape($__vars['users'][$__vars['userPlaytime']['user_id']]['username']) . '</a>
								<div class="structItem-minor">
									<ul class="structItem-parts">
										<li>
											<ul class="listInline listInline--comma listInline--selfInline">
												<li>
													<a href="https://steamcommunity.com/profiles/' . $__templater->escape($__vars['userPlaytime']['provider_key']) . '" target="_blank">
														' . $__templater->escape($__vars['userPlaytime']['provider_key']) . '
													</a>
												</li>
											</ul>
										</li>
									</ul>
								</div>
							</div>
							<div class="structItem-cell structItem-cell--latest structItem-cell--meta">
								<dl class="pairs pairs--justified">
									<dt>' . 'Recent hours' . '</dt>
									<dd>
										<a href="https://steamcommunity.com/profiles/' . $__templater->escape($__vars['userPlaytime']['provider_key']) . '/games/?tab=recent" target="_blank">
										' . $__templater->escape($__vars['userPlaytime']['recent_hours_formatted']) . ' ' . 'h' . '
										</a>
									</dd>
								</dl>
								<dl class="pairs pairs--justified structItem-minor">
									<dt>' . 'Updated' . '</dt>
									<dd>' . $__templater->fn('date_dynamic', array($__vars['userPlaytime']['last_updated'], array(
				))) . '</dd>
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
				<div class="block-row">' . 'There are no active players to display.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'steam/active-players',
		'wrapperclass' => 'block-outer block-outer--after',
		'perPage' => $__vars['perPage'],
	))) . '
</div>';
	return $__finalCompiled;
});