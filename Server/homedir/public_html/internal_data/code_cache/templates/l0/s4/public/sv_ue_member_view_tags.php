<?php
// FROM HASH: 6a0d492bb3e53b3ec06195f622d6edb9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['enableTagging'] AND ($__templater->method($__vars['user'], 'canEditTags', array()) OR $__vars['user']['useress_tags'])) {
		$__finalCompiled .= '
	<div class="memberHeader-blurb">
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

		';
		if ($__templater->method($__vars['user'], 'canEditTags', array())) {
			$__finalCompiled .= '
			<a href="' . $__templater->fn('link', array('members/tags', $__vars['user'], ), true) . '" class="u-concealed" data-xf-click="overlay"
				data-xf-init="tooltip" title="' . $__templater->filter('Edit tags', array(array('for_attr', array()),), true) . '">
				<i class="fa fa-pencil" aria-hidden="true"></i>
				<span class="u-srOnly">' . 'Edit' . '</span>
			</a>
		';
		}
		$__finalCompiled .= '
	</div>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});