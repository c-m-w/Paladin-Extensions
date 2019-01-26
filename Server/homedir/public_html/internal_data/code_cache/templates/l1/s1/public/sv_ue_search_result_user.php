<?php
// FROM HASH: a46e5c2a8c6943a083a1d4cbfd3bb368
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li class="block-row block-row--separated ' . ($__templater->method($__vars['xf']['visitor'], 'isIgnoring', array($__vars['user']['user_id'], )) ? 'is-ignored' : '') . '" data-author="' . $__templater->escape($__vars['user']['username']) . '">
	<div class="contentRow">
		<span class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['user'], 's', false, array(
	))) . '
		</span>

		<div class="contentRow-main">
			<h3 class="contentRow-title">
				<a href="' . $__templater->fn('link', array('members', $__vars['user'], ), true) . '">' . $__templater->fn('highlight', array($__vars['user']['username'], $__vars['options']['term'], ), true) . '</a>
			</h3>

			<div class="contentRow-snippet">
				<ul class="listInline listInline--bullet">
					';
	if ($__vars['xf']['options']['enableTagging'] AND $__vars['user']['useress_tags']) {
		$__finalCompiled .= '
						<li>
							<i class="fa fa-tags" aria-hidden="true" title="' . $__templater->filter('Tags', array(array('for_attr', array()),), true) . '"></i>
							<span class="u-srOnly">' . 'Tags' . '</span>

							';
		if ($__vars['user']['useress_tags']) {
			$__finalCompiled .= '
								';
			if ($__templater->isTraversable($__vars['user']['useress_tags'])) {
				foreach ($__vars['user']['useress_tags'] AS $__vars['tag']) {
					$__finalCompiled .= '
									<a href="' . $__templater->fn('link', array('tags', $__vars['tag'], ), true) . '" class="tagItem" dir="auto">' . $__templater->escape($__vars['tag']['tag']) . '</a>
								';
				}
			}
			$__finalCompiled .= '
							';
		} else {
			$__finalCompiled .= '
								' . 'None' . '
							';
		}
		$__finalCompiled .= '
						</li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>

			<div class="contentRow-minor contentRow-minor--hideLinks">
				<ul class="listInline listInline--bullet">
					<li>' . 'User' . '</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['user']['register_date'], array(
	))) . '</li>
				</ul>
			</div>
		</div>
	</div>
</li>
';
	return $__finalCompiled;
});