<?php
// FROM HASH: 5fb548cb7ab1c3c9c32862ecc6e0200b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Special characters');
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if (!$__templater->test($__vars['specialChars'], 'empty', array())) {
		$__compilerTemp1 .= '
						<a href="' . $__templater->fn('link', array('em/special-chars/sort', ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Sort' . '</a>
					';
	}
	$__compilerTemp2 = '';
	if (!$__templater->test($__vars['specialChars'], 'empty', array())) {
		$__compilerTemp2 .= '
						<a href="' . $__templater->fn('link', array('em/special-chars/export', ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Export' . '</a>
					';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add category', array(
		'href' => $__templater->fn('link', array('em/special-chars/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '

		<div class="buttonGroup-buttonWrapper">
			' . $__templater->button('&#8226;&#8226;&#8226;', array(
		'class' => 'menuTrigger',
		'data-xf-click' => 'menu',
		'aria-expanded' => 'false',
		'aria-haspopup' => 'true',
		'title' => $__templater->filter('More options', array(array('for_attr', array()),), false),
	), '', array(
	)) . '
			<div class="menu" data-menu="menu" aria-hidden="true">
				<div class="menu-content">
					<h4 class="menu-header">' . 'More options' . '</h4>
					' . $__compilerTemp1 . '
					<a href="' . $__templater->fn('link', array('em/special-chars/import', ), true) . '" class="menu-linkRow">' . 'Import' . '</a>
					' . $__compilerTemp2 . '
				</div>
			</div>
		</div>
	</div>
');
	$__finalCompiled .= '

';
	if (!$__vars['enabled']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--error blockMessage--iconic">
		<a href="' . $__templater->fn('link', array('options/groups/klEM/', ), true) . '"> ' . 'The special characters button is not enabled in the general editor options. Any changes you make here won\'t be visible for your users until you activate it.' . '</a>
	</div>
';
	}
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['specialChars'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp3 = '';
		if ($__templater->isTraversable($__vars['specialChars'])) {
			foreach ($__vars['specialChars'] AS $__vars['category']) {
				$__compilerTemp3 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'href' => $__templater->fn('link', array('em/special-chars/edit', $__vars['category'], ), false),
					'label' => $__templater->escape($__vars['category']['title']),
					'_type' => 'main',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('em/special-chars/characters', $__vars['category'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'Characters' . '
							',
				),
				array(
					'class' => ((!$__templater->fn('empty', array($__vars['category']['user_criteria']))) ? 'dataList-cell--highlighted' : ''),
					'href' => $__templater->fn('link', array('em/special-chars/edit', $__vars['category'], ), false),
					'_type' => 'action',
					'html' => '
								' . 'User criteria' . '
							',
				),
				array(
					'name' => 'active[' . $__vars['category']['group_id'] . ']',
					'selected' => $__vars['category']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['category']['title'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('em/special-chars/delete', $__vars['category'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp3 . '
				', array(
		)) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('em/special-chars/toggle', ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
	';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No items have been created yet.' . '</div>
';
	}
	return $__finalCompiled;
});