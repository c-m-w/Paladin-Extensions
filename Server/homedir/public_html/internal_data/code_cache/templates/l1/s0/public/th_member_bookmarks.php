<?php
// FROM HASH: 88b0861e6d8ecf673eea5f5736e4ba0e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('' . $__templater->escape($__vars['user']['username']) . '\'s bookmarks');
	$__finalCompiled .= '
';
	$__templater->includeCss('th_bookmarks.less');
	$__finalCompiled .= '
';
	$__templater->includeCss('bb_code.less');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['user']['username'])), $__templater->fn('link', array('members', $__vars['user'], ), false), array(
	));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['bookmarks'], 'empty', array())) {
		$__finalCompiled .= '
				<ol class="listPlain">
					';
		if ($__templater->isTraversable($__vars['bookmarks'])) {
			foreach ($__vars['bookmarks'] AS $__vars['bookmark']) {
				$__finalCompiled .= '
						<li class="block-row block-row--separated ' . ($__vars['bookmark']['sticky'] ? 'block-row--highlighted' : 'block-row--alt') . '">
							' . $__templater->callMacro('th_bookmark_macros_bookmarks', 'row', array(
					'bookmark' => $__vars['bookmark'],
				), $__vars) . '
						</li>
					';
			}
		}
		$__finalCompiled .= '
				</ol>
				';
	} else if ($__vars['page'] <= 1) {
		$__finalCompiled .= '
				<div class="block-row">' . 'There are currently no bookmarks to display.' . '</div>
				';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No bookmarks can be shown.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
		';
	if ($__vars['hidePagination'] AND !$__templater->test($__vars['bookmarks'], 'empty', array())) {
		$__finalCompiled .= '
			<div class="block-footer">
				<span class="block-footer-controls">' . $__templater->button('
					' . 'See more' . '
				', array(
			'href' => $__templater->fn('link', array('members/bookmarks', $__vars['user'], ), false),
			'rel' => 'nofollow',
		), '', array(
		)) . '</span>
			</div>
		';
	}
	$__finalCompiled .= '
	</div>

	';
	if (!$__vars['hidePagination']) {
		$__finalCompiled .= '
		' . $__templater->fn('page_nav', array(array(
			'link' => 'members/bookmarks',
			'data' => $__vars['user'],
			'page' => $__vars['page'],
			'total' => $__vars['totalBookmarks'],
			'params' => $__vars['pageNavParams'],
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	';
	}
	$__finalCompiled .= '
</div>';
	return $__finalCompiled;
});