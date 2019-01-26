<?php
// FROM HASH: 861c98efe94b36dbb43ac8ce59f83e61
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['type'] === 'given') {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reactions given by ' . $__templater->escape($__vars['user']['username']) . '');
		$__finalCompiled .= '
	';
	} else if ($__vars['type'] === 'received') {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reactions received by ' . $__templater->escape($__vars['user']['username']) . '');
		$__finalCompiled .= '
	';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('' . $__templater->escape($__vars['user']['username']) . '\'s reactions');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['user']['username'])), $__templater->fn('link', array('members', $__vars['user'], ), false), array(
	));
	$__finalCompiled .= '

<div class="block">
	<div class="block-outer">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'members/reactions',
		'data' => $__vars['user'],
		'params' => $__vars['filters'],
		'perPage' => $__vars['perPage'],
	))) . '
	</div>

	<div class="block-container">
		<ul class="block-body">
			';
	if (!$__templater->test($__vars['reactedContent'], 'empty', array())) {
		$__finalCompiled .= '
				';
		$__compilerTemp1 = '';
		$__compilerTemp1 .= '
						';
		if ($__templater->isTraversable($__vars['reactedContent'])) {
			foreach ($__vars['reactedContent'] AS $__vars['react']) {
				$__compilerTemp1 .= '
							';
				$__compilerTemp2 = '';
				$__compilerTemp2 .= '
												' . $__templater->filter($__templater->method($__vars['react'], 'render', array()), array(array('raw', array()),), true) . '
											';
				if (strlen(trim($__compilerTemp2)) > 0) {
					$__compilerTemp1 .= '
								<li class="block-row block-row--separated">
									<div class="contentRow">
										<span class="contentRow-figure">
											' . $__templater->fn('avatar', array($__vars['react']['Reactor'], 's', false, array(
						'defaultname' => $__vars['item']['username'],
					))) . '
										</span>
										<div class="contentRow-main">
											' . $__compilerTemp2 . '
										</div>
									</div>
								</li>
							';
				}
				$__compilerTemp1 .= '
						';
			}
		}
		$__compilerTemp1 .= '
					';
		if (strlen(trim($__compilerTemp1)) > 0) {
			$__finalCompiled .= '
					' . $__compilerTemp1 . '
					';
		} else {
			$__finalCompiled .= '
					<li class="block-row">
						' . 'There are no viewable reactions on this page.' . '
					</li>
				';
		}
		$__finalCompiled .= '
				';
	} else {
		$__finalCompiled .= '
				<li class="block-row">
					' . 'There are no reactions to display' . '
				</li>
			';
	}
	$__finalCompiled .= '
		</ul>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'members/reactions',
		'data' => $__vars['user'],
		'params' => $__vars['filters'],
		'perPage' => $__vars['perPage'],
	))) . '
	</div>
</div>';
	return $__finalCompiled;
});