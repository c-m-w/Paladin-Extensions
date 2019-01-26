<?php
// FROM HASH: e0e119167fac90f4a4a6e7061a5b7ad7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="sidePanel sidePanel--nav sidePanel--visitor">
	<div class="sidePanel__tabPanels">
		
		<div class="is-active sidePanel__tabPanel js-navigationTabPanel">
			' . $__templater->callMacro('PAGE_CONTAINER', 'canvasNavPanel', array(), $__vars) . '
		</div>
		
		';
	if ($__vars['xf']['visitor']['user_id']) {
		$__finalCompiled .= '
			
		<div class="is-left sidePanel__tabPanel js-visitorTabPanel">
			<div class="menu-content js-visitorMenuBody">
				<div class="menu-row">
					' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '
				</div>
			</div>
		</div>
		
		<div class="is-right sidePanel__tabPanel js-convoTabPanel">
			<div class="menu-content">
				<div class="menu menu--medium" data-menu="menu" aria-hidden="true"
					 data-href="' . $__templater->fn('link', array('conversations/popup', ), true) . '"
					 data-nocache="true"
					 data-load-target=".js-convMenuBody">
					<h3 class="menu-header">' . 'Conversations' . '</h3>
					<div class="js-convMenuBody">
						<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
					</div>
				</div>
				<div class="menu-footer">
					<a href="' . $__templater->fn('link', array('conversations/add', ), true) . '" class="u-pullRight">' . 'Start a new conversation' . '</a>
					<a href="' . $__templater->fn('link', array('conversations', ), true) . '">' . 'Show all' . $__vars['xf']['language']['ellipsis'] . '</a>
				</div>
			</div>
		</div>
		
		<div class="is-right sidePanel__tabPanel js-alertTabPanel">
			<div class="menu-content">
				<h3 class="menu-header">' . 'Alerts' . '</h3>
				<div class="js-alertsMenuBody">
					<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
				</div>
				<div class="menu-footer">
					<a href="' . $__templater->fn('link', array('account/preferences', ), true) . '" class="u-pullRight">' . 'Preferences' . '</a>
					<a href="' . $__templater->fn('link', array('account/alerts', ), true) . '">' . 'Show all' . $__vars['xf']['language']['ellipsis'] . '</a>
				</div>
			</div>
		</div>
			
		';
	}
	$__finalCompiled .= '
		
	</div>
</div>';
	return $__finalCompiled;
});