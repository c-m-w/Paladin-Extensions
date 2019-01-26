<?php
// FROM HASH: ddd8f9ece271701d77648e720c6407e7
return array('macros' => array('option_form_block' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'group' => '',
		'options' => '!',
		'containerBeforeHtml' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if (!$__templater->test($__vars['options'], 'empty', array())) {
		$__finalCompiled .= '
		';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['options'])) {
			foreach ($__vars['options'] AS $__vars['option']) {
				$__compilerTemp1 .= '
							';
				if ($__vars['option']['Relations']['mjstSupport']['display_order'] < 1000) {
					$__compilerTemp1 .= '
								' . $__templater->callMacro('option_macros', 'option_row', array(
						'group' => $__vars['group'],
						'option' => $__vars['option'],
					), $__vars) . '
							';
				}
				$__compilerTemp1 .= '
							';
			}
		}
		$__compilerTemp2 = '';
		if ($__templater->isTraversable($__vars['options'])) {
			foreach ($__vars['options'] AS $__vars['option']) {
				$__compilerTemp2 .= '
							';
				if (($__vars['option']['Relations']['mjstSupport']['display_order'] >= 1000) AND ($__vars['option']['Relations']['mjstSupport']['display_order'] < 2000)) {
					$__compilerTemp2 .= '
								' . $__templater->callMacro('option_macros', 'option_row', array(
						'group' => $__vars['group'],
						'option' => $__vars['option'],
					), $__vars) . '
							';
				}
				$__compilerTemp2 .= '
							';
			}
		}
		$__compilerTemp3 = '';
		if ($__templater->isTraversable($__vars['options'])) {
			foreach ($__vars['options'] AS $__vars['option']) {
				$__compilerTemp3 .= '
							';
				if ($__vars['option']['Relations']['mjstSupport']['display_order'] >= 2000) {
					$__compilerTemp3 .= '
								' . $__templater->callMacro('option_macros', 'option_row', array(
						'group' => $__vars['group'],
						'option' => $__vars['option'],
					), $__vars) . '
							';
				}
				$__compilerTemp3 .= '
							';
			}
		}
		$__finalCompiled .= $__templater->form('
			' . $__templater->filter($__vars['containerBeforeHtml'], array(array('raw', array()),), true) . '
			<div class="block-container">
				<div class="block-tabHeader block-tabHeader--productTabs tabs hScroller"
					data-xf-init="tabs"
					data-state="replace"
					role="tablist">
					<div class="hScroller" data-xf-init="h-scroller">
						<span class="hScroller-scroll">
							' . '
							<a class="tabs-tab is-active" role="tab" tabindex="0" id="mjs-general" aria-controls="generalOptions">' . 'General options' . '</a>
							<a class="tabs-tab" role="tab" tabindex="0" id="mjst-ticket" aria-controls="ticketOptions">' . 'Ticket' . '</a>
							<a class="tabs-tab" role="tab" tabindex="0" id="mjst-kb" aria-controls="kbOptions">' . 'Knowledge base' . '</a>
							' . '
						</span>
					</div>
				</div>
				<ul class="tabPanes">
					' . '
					<li class="is-active" role="tabpanel" id="generalOptions">
						<div class="block-body">
							' . $__compilerTemp1 . '
						</div>
					</li>
					<li role="tabpanel" id="kbOptions">
						<div class="block-body">
							' . $__compilerTemp2 . '
						</div>
					</li>
					<li role="tabpanel" id="kbOptions">
						<div class="block-body">
							' . $__compilerTemp3 . '
						</div>
					</li>
					' . '
				</ul>
				' . $__templater->formSubmitRow(array(
			'sticky' => 'true',
			'icon' => 'save',
		), array(
		)) . '
			</div>
		', array(
			'action' => $__templater->fn('link', array('options/update', ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';

	return $__finalCompiled;
});