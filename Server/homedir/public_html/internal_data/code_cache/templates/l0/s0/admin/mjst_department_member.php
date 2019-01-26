<?php
// FROM HASH: b972ad8815c9bd941ddf542125887218
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Department members' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['department']['title']));
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Add member', array(
		'href' => $__templater->fn('link', array('mjst-support/departments/members/add', $__vars['department'], ), false),
		'icon' => 'add',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['users'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if (!$__vars['showingAll']) {
			$__compilerTemp1 .= '
			<div class="block-outer">
				<div class="block-outer-main">
					' . $__templater->button('
						' . 'Sort by' . $__vars['xf']['language']['label_separator'] . ' ' . ($__templater->escape($__vars['sortOptions'][$__vars['order']]) ?: 'User name') . '
					', array(
				'class' => 'button--link menuTrigger',
				'data-xf-click' => 'menu',
				'aria-expanded' => 'false',
				'aria-haspopup' => 'true',
			), '', array(
			)) . '

					<div class="menu" data-menu="menu" aria-hidden="true">
						<div class="menu-content">
							<h3 class="menu-header">' . 'Sort by' . $__vars['xf']['language']['ellipsis'] . '</h3>
							';
			if ($__templater->isTraversable($__vars['sortOptions'])) {
				foreach ($__vars['sortOptions'] AS $__vars['sortKey'] => $__vars['sortName']) {
					$__compilerTemp1 .= '
								<a href="' . $__templater->fn('link', array('mjst-support/departments/members', $__vars['department'], array('criteria' => $__vars['criteria'], 'order' => $__vars['sortKey'], ), ), true) . '"
									class="menu-linkRow ' . (($__vars['order'] == $__vars['sortKey']) ? 'is-selected' : '') . '">
									' . $__templater->escape($__vars['sortName']) . '
								</a>
							';
				}
			}
			$__compilerTemp1 .= '
						</div>
					</div>
				</div>
				' . $__templater->callMacro('filter_macros', 'quick_filter', array(
				'key' => 'users',
				'ajax' => $__templater->fn('link', array('mjst-support/departments/members', $__vars['department'], array('criteria' => $__vars['criteria'], ), ), false),
				'class' => 'block-outer-opposite',
			), $__vars) . '
			</div>
		';
		}
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['users'])) {
			foreach ($__vars['users'] AS $__vars['user']) {
				$__compilerTemp2 .= '
						' . $__templater->dataRow(array(
				), array(array(
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageSmall',
					'href' => $__templater->fn('link', array('mjst-support/departments/members/edit', $__vars['department'], array('user_id' => $__vars['user']['user_id'], ), ), false),
					'_type' => 'cell',
					'html' => '
								' . $__templater->fn('avatar', array($__vars['user'], 's', false, array(
					'href' => '',
				))) . '
							',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/departments/members/edit', $__vars['department'], array('user_id' => $__vars['user']['user_id'], ), ), false),
					'label' => $__templater->escape($__vars['user']['username']),
					'hint' => $__templater->escape($__vars['user']['email']),
					'_type' => 'main',
					'html' => '',
				),
				array(
					'href' => $__templater->fn('link', array('mjst-support/departments/members/remove', $__vars['department'], array('user_id' => $__vars['user']['user_id'], ), ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__compilerTemp3 = '';
		if ($__vars['filter'] AND ($__vars['total'] > $__vars['perPage'])) {
			$__compilerTemp3 .= '
						' . $__templater->dataRow(array(
				'rowclass' => 'dataList-row--note dataList-row--noHover js-filterForceShow',
			), array(array(
				'colspan' => '3',
				'_type' => 'cell',
				'html' => 'There are more records matching your filter. Please be more specific.' . '
							',
			))) . '
					';
		}
		$__finalCompiled .= $__templater->form('
		' . $__compilerTemp1 . '
		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp2 . '
					' . $__compilerTemp3 . '
				', array(
		)) . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['users'], $__vars['total'], ), true) . '</span>
			</div>
		</div>

		' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'mjst-support/departments/members',
			'params' => array('criteria' => $__vars['criteria'], 'order' => $__vars['order'], 'direction' => $__vars['direction'], ),
			'wrapperclass' => 'js-filterHide block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
	', array(
			'action' => $__templater->fn('link', array('mjst-support/departments/members', $__vars['department'], ), false),
			'class' => 'block',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No records matched.' . '</div>
';
	}
	return $__finalCompiled;
});