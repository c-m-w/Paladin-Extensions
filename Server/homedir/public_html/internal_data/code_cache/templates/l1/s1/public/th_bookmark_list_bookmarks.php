<?php
// FROM HASH: 189dfd1eb97e46f0866c1c304cf4975a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Bookmarks');
	$__finalCompiled .= '
';
	$__templater->includeCss('th_bookmarks.less');
	$__finalCompiled .= '
';
	$__templater->includeCss('bb_code.less');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__templater->mergeChoiceOptions(array(), $__vars['contentTypes']);
	$__templater->modifySideNavHtml(null, '
	' . $__templater->form('
		<div class="block-container">
			<h3 class="block-header">' . 'Content type' . '</h3>
			<div class="block-body">
				<div class="block-row">
					' . $__templater->formCheckBox(array(
		'name' => 'content_type[]',
		'value' => $__vars['contentType'],
	), $__compilerTemp1) . '
				</div>
			</div>
			<div class="block-footer">
				' . $__templater->button('Filter', array(
		'type' => 'submit',
	), '', array(
	)) . '
			</div>
		</div>
	', array(
		'method' => 'post',
		'class' => 'block',
	)) . '
', 'replace');
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
	</div>

	' . $__templater->fn('page_nav', array(array(
		'link' => 'bookmarks',
		'page' => $__vars['page'],
		'total' => $__vars['totalBookmarks'],
		'params' => $__vars['pageNavParams'],
		'wrapperclass' => 'block-outer block-outer--after',
		'perPage' => $__vars['perPage'],
	))) . '
</div>';
	return $__finalCompiled;
});