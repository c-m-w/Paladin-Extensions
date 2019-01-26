<?php
// FROM HASH: 224451d3120b08bbe864d4238419acec
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['enableTagging'] AND ($__templater->method($__vars['xf']['visitor'], 'canEditTags', array()) OR $__vars['xf']['visitor']['useress_tags'])) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__vars['xf']['visitor']['useress_tags']) {
			$__compilerTemp1 .= '
			';
			if ($__templater->isTraversable($__vars['xf']['visitor']['useress_tags'])) {
				foreach ($__vars['xf']['visitor']['useress_tags'] AS $__vars['tag']) {
					$__compilerTemp1 .= '
				<a href="' . $__templater->fn('link', array('tags', $__vars['tag'], ), true) . '" class="tagItem" dir="auto">' . $__templater->escape($__vars['tag']['tag']) . '</a>
			';
				}
			}
			$__compilerTemp1 .= '
		';
		} else {
			$__compilerTemp1 .= '
			' . 'None' . '
		';
		}
		$__compilerTemp2 = '';
		if ($__templater->method($__vars['xf']['visitor'], 'canEditTags', array())) {
			$__compilerTemp2 .= '
			<a href="' . $__templater->fn('link', array('members/tags', $__vars['xf']['visitor'], ), true) . '" class="u-concealed" data-xf-click="overlay"
				data-xf-init="tooltip" title="' . $__templater->filter('Edit tags', array(array('for_attr', array()),), true) . '">
				<i class="fa fa-pencil" aria-hidden="true"></i>
				<span class="u-srOnly">' . 'Edit' . '</span>
			</a>
		';
		}
		$__finalCompiled .= $__templater->formRow('
		' . $__compilerTemp1 . '

		' . $__compilerTemp2 . '
	', array(
			'label' => 'Profile tags',
		)) . '
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});