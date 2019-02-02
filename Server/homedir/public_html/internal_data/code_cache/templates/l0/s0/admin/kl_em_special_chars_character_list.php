<?php
// FROM HASH: 278b781abaf02061daae97751784c41b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Special characters' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['group']['title']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
							';
	if (!$__templater->test($__vars['specialChars'], 'empty', array())) {
		$__compilerTemp2 .= '
								<a href="' . $__templater->fn('link', array('em/special-chars/characters/sort', $__vars['group'], ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Sort' . '</a>
							';
	}
	$__compilerTemp2 .= '
						';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
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
						' . $__compilerTemp2 . '
					</div>
				</div>
			</div>
		';
	}
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add character', array(
		'href' => $__templater->fn('link', array('em/special-chars/characters/add', $__vars['group'], ), false),
		'icon' => 'add',
	), '', array(
	)) . '

		' . $__compilerTemp1 . '
	</div>
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['specialChars'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp3 = '';
		if ($__templater->isTraversable($__vars['specialChars'])) {
			foreach ($__vars['specialChars'] AS $__vars['character']) {
				$__compilerTemp3 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--link dataList-cell--main',
					'hash' => $__vars['character']['character_id'],
					'_type' => 'cell',
					'html' => '
								<a href="' . $__templater->fn('link', array('em/special-chars/characters/edit', $__vars['character'], ), true) . '">
										<div class="dataList-mainRow">' . $__templater->filter($__vars['character']['code'], array(array('raw', array()),), true) . ' <span class="dataList-hint" dir="auto">' . $__templater->escape($__vars['character']['title']) . '</span></div>
								</a>
							',
				),
				array(
					'name' => 'active[' . $__vars['character']['character_id'] . ']',
					'selected' => $__vars['character']['active'],
					'class' => 'dataList-cell--separated',
					'submit' => 'true',
					'tooltip' => 'Enable / disable \'' . $__vars['character']['title'] . '\'',
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('em/special-chars/characters/delete', $__vars['character'], ), false),
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
			'action' => $__templater->fn('link', array('em/special-chars/characters/toggle', $__vars['group'], ), false),
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