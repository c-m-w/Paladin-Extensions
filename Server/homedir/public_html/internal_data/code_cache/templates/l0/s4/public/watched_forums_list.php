<?php
// FROM HASH: 7f2cac8d689fa0d4a39bcb6a6db437eb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['useress_watchedWrapper']) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = $__vars;
		$__compilerTemp1['pageSelected'] = 'watched_forums';
		$__templater->wrapTemplate('account_wrapper', $__compilerTemp1);
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '
';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Watched forums');
	$__finalCompiled .= '

';
	$__templater->includeCss('node_list.less');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['watchedForums'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp2 = '';
		$__compilerTemp3 = $__templater->method($__vars['nodeTree'], 'getFlattened', array());
		if ($__templater->isTraversable($__compilerTemp3)) {
			foreach ($__compilerTemp3 AS $__vars['id'] => $__vars['treeEntry']) {
				$__compilerTemp2 .= '
					';
				$__vars['node'] = $__vars['treeEntry']['record'];
				$__compilerTemp2 .= '
					';
				$__vars['forumWatch'] = $__vars['watchedForums'][$__vars['node']['node_id']];
				$__compilerTemp2 .= '
					';
				if ($__vars['forumWatch']) {
					$__compilerTemp2 .= '
						';
					$__compilerTemp4 = '';
					if ($__vars['forumWatch']['notify_on'] == 'thread') {
						$__compilerTemp4 .= '
									<li>' . 'New threads' . '</li>
								';
					} else if ($__vars['forumWatch']['notify_on'] == 'message') {
						$__compilerTemp4 .= '
									<li>' . 'New messages' . '</li>
								';
					}
					$__compilerTemp5 = '';
					if ($__vars['forumWatch']['send_alert']) {
						$__compilerTemp5 .= '<li>' . 'Alerts' . '</li>';
					}
					$__compilerTemp6 = '';
					if ($__vars['forumWatch']['send_email']) {
						$__compilerTemp6 .= '<li>' . 'Emails' . '</li>';
					}
					$__vars['bonusInfo'] = $__templater->preEscaped('
							<ul class="listInline listInline--bullet">
								' . $__compilerTemp4 . '
								' . $__compilerTemp5 . '
								' . $__compilerTemp6 . '
							</ul>
						');
					$__compilerTemp2 .= '
						' . $__templater->callMacro('node_list_forum', 'forum', array(
						'node' => $__vars['node'],
						'extras' => $__vars['nodeExtras'][$__vars['node']['node_id']],
						'children' => $__vars['nodeTree'][$__vars['id']]['children'],
						'childExtras' => $__vars['nodeExtras'],
						'depth' => '2',
						'chooseName' => 'node_ids',
						'bonusInfo' => $__vars['bonusInfo'],
					), $__vars) . '
					';
				}
				$__compilerTemp2 .= '
				';
			}
		}
		$__finalCompiled .= $__templater->form('

		<div class="block-outer">

			<div class="block-outer-opposite">
				' . $__templater->button('Manage watched forums', array(
			'class' => 'button--link menuTrigger',
			'data-xf-click' => 'menu',
			'aria-expanded' => 'false',
			'aria-haspopup' => 'true',
		), '', array(
		)) . '
				<div class="menu" data-menu="menu" aria-hidden="true">
					<div class="menu-content">
						<h3 class="menu-header">' . 'Manage watched forums' . '</h3>
						' . '
						<a href="' . $__templater->fn('link', array('watched/forums/manage', null, array('state' => 'watch_no_email', ), ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Disable email notification' . '</a>
						<a href="' . $__templater->fn('link', array('watched/forums/manage', null, array('state' => 'delete', ), ), true) . '" data-xf-click="overlay" class="menu-linkRow">' . 'Stop watching forums' . '</a>
						' . '
					</div>
				</div>
			</div>
		</div>

		<div class="block-container">
			<div class="block-body">
				' . $__compilerTemp2 . '
			</div>
			<div class="block-footer block-footer--split">
				<span class="block-footer-counter"></span>
				<span class="block-footer-select">' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'class' => 'input--inline',
			'check-all' => '< .block-container',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '</span>
				<span class="block-footer-controls">
					' . $__templater->formSelect(array(
			'name' => 'action',
			'class' => 'input--inline',
		), array(array(
			'label' => 'With selected' . $__vars['xf']['language']['ellipsis'],
			'_type' => 'option',
		),
		array(
			'value' => 'email',
			'label' => 'Enable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'no_email',
			'label' => 'Disable email notification',
			'_type' => 'option',
		),
		array(
			'value' => 'alert',
			'label' => 'Enable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'no_alert',
			'label' => 'Disable alerts',
			'_type' => 'option',
		),
		array(
			'value' => 'delete',
			'label' => 'Stop watching',
			'_type' => 'option',
		))) . '
					' . $__templater->button('Go', array(
			'type' => 'submit',
		), '', array(
		)) . '
				</span>
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('watched/forums/update', ), false),
			'ajax' => 'true',
			'class' => 'block',
			'autocomplete' => 'off',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'You are not watching any forums.' . '</div>
';
	}
	return $__finalCompiled;
});