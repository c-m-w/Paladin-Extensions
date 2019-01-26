<?php
// FROM HASH: 9d6777ccef0ca5899d958b0ce91c07a4
return array('macros' => array('subnav' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'categories' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="p-sectionLinks-inner hScroller" data-xf-init="h-scroller">
		<div class="hScroller-scroll">
			<ul class="p-sectionLinks-list">
				';
	if ($__templater->isTraversable($__vars['categories'])) {
		foreach ($__vars['categories'] AS $__vars['nav']) {
			$__finalCompiled .= '
					<li>
						<div class="p-navEl">
							<a href="' . $__templater->escape($__vars['nav']['href']) . '"
							   class="p-navEl-link"
							   data-nav-id="' . $__templater->escape($__vars['navId']) . '">
								' . $__templater->filter($__vars['nav']['title'], array(array('raw', array()),), true) . '
							</a>
						</div>
					</li>
				';
		}
	}
	$__finalCompiled .= '
			</ul>
		</div>
	</div>
';
	return $__finalCompiled;
},
'dropdown' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'categories' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="p-sectionLinks-inner hScroller" data-xf-init="h-scroller">
		<div class="hScroller-scroll">
			<ul class="p-sectionLinks-list">
				';
	if ($__templater->isTraversable($__vars['categories'])) {
		foreach ($__vars['categories'] AS $__vars['nav']) {
			$__finalCompiled .= '
					<li>
						<div class="p-navEl">
							<a href="' . $__templater->escape($__vars['nav']['href']) . '"
							   class="p-navEl-link"
							   data-nav-id="' . $__templater->escape($__vars['navId']) . '">
								' . $__templater->filter($__vars['nav']['title'], array(array('raw', array()),), true) . '
							</a>
						</div>
					</li>
				';
		}
	}
	$__finalCompiled .= '
			</ul>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

';
	return $__finalCompiled;
});