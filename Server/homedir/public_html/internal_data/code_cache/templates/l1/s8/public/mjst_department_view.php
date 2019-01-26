<?php
// FROM HASH: 3e08de499830e119686f870492f2bf55
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['department']['title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped($__templater->filter($__vars['department']['short_description'], array(array('raw', array()),), true));
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'canonical_url', array(
		'canonicalUrl' => $__templater->fn('link', array('canonical:support-tickets/departments', $__vars['department'], array('page' => $__vars['page'], ), ), false),
	), $__vars) . '

';
	$__templater->breadcrumbs($__templater->method($__vars['department'], 'getBreadcrumbs', array(false, )));
	$__finalCompiled .= '

' . $__templater->callMacro('mjst_ticket_page_macros', 'ticket_page_options', array(
		'department' => $__vars['department'],
	), $__vars) . '

';
	if ($__templater->method($__vars['department'], 'canOpenTicket', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Open ticket' . $__vars['xf']['language']['ellipsis'], array(
			'href' => $__templater->fn('link', array('support-tickets/open', null, array('department_id' => $__vars['department']['department_id'], ), ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => ($__vars['xf']['options']['mjstOpenTicketOverlay'] ? 'true' : ''),
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	if ($__vars['canInlineMod']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'xf/inline_mod.js',
			'min' => '1',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

<div class="block" data-xf-init="' . ($__vars['canInlineMod'] ? 'inline-mod' : '') . '" data-type="support_ticket" data-href="' . $__templater->fn('link', array('inline-mod', ), true) . '">
	<div class="block-outer">';
	$__compilerTemp1 = '';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
					';
	if ($__vars['canInlineMod']) {
		$__compilerTemp2 .= '
						' . $__templater->callMacro('inline_mod_macros', 'button', array(), $__vars) . '
					';
	}
	$__compilerTemp2 .= '
					';
	if ($__templater->method($__vars['department'], 'canWatch', array())) {
		$__compilerTemp2 .= '
						';
		$__compilerTemp3 = '';
		if ($__vars['department']['Watch'][$__vars['xf']['visitor']['user_id']]) {
			$__compilerTemp3 .= 'Unwatch';
		} else {
			$__compilerTemp3 .= 'Watch';
		}
		$__compilerTemp2 .= $__templater->button('
							' . $__compilerTemp3 . '
						', array(
			'href' => $__templater->fn('link', array('support-tickets/departments/watch', $__vars['department'], ), false),
			'class' => 'button--link',
			'data-xf-click' => 'switch-overlay',
			'data-sk-watch' => 'Watch',
			'data-sk-unwatch' => 'Unwatch',
		), '', array(
		)) . '
					';
	}
	$__compilerTemp2 .= '
				';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__compilerTemp1 .= '
			<div class="block-outer-opposite">
				<div class="buttonGroup">
				' . $__compilerTemp2 . '
				</div>
			</div>
		';
	}
	$__finalCompiled .= trim('

		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets/departments',
		'data' => $__vars['department'],
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '

		' . $__compilerTemp1 . '

	') . '</div>

	<div class="block-container">
		<div class="block-body">
			';
	if (!$__templater->test($__vars['tickets'], 'empty', array())) {
		$__finalCompiled .= '
				<div class="structItemContainer">
					';
		if ($__templater->isTraversable($__vars['tickets'])) {
			foreach ($__vars['tickets'] AS $__vars['ticket']) {
				$__finalCompiled .= '
						' . $__templater->callMacro('mjst_ticket_list_macros', 'ticket', array(
					'ticket' => $__vars['ticket'],
				), $__vars) . '
					';
			}
		}
		$__finalCompiled .= '
				</div>
			';
	} else if ($__vars['filters']) {
		$__finalCompiled .= '
				<div class="block-row">' . 'There are no tickets matching your filters.' . '</div>
			';
	} else {
		$__finalCompiled .= '
				<div class="block-row">' . 'No tickets have been created yet.' . '</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets',
		'params' => $__vars['filters'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
		' . $__templater->fn('show_ignored', array(array(
		'wrapperclass' => 'block-outer-opposite',
	))) . '
	</div>
</div>

';
	$__templater->setPageParam('sideNavTitle', 'Departments');
	$__finalCompiled .= '
';
	$__templater->modifySideNavHtml(null, '
	' . $__templater->callMacro('mjst_department_list_macros', 'simple_list_block', array(
		'departments' => $__vars['departments'],
		'selected' => $__vars['department']['department_id'],
	), $__vars) . '

	<div class="block">
		<div class="block-container">
			<h3 class="block-header">' . 'Filters' . '</h3>
			<div class="block-body">
				' . $__templater->includeTemplate('mjst_filters', $__vars) . '
			</div>
		</div>
	</div>
', 'replace');
	$__finalCompiled .= '

';
	$__templater->modifySideNavHtml('_xfWidgetPositionSideNavMjstOverviewSidenav', $__templater->widgetPosition('mjst_overview_sidenav', array()), 'replace');
	return $__finalCompiled;
});