<?php
// FROM HASH: 019361deb197b4b80db17e53f09e0873
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->fn('prefix', array('resource', $__vars['resource'], 'escaped', ), true) . $__templater->escape($__vars['resource']['title']) . ' - ' . 'Updates');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'updates';
	$__templater->wrapTemplate('xfrm_resource_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

' . $__templater->callMacro('lightbox_macros', 'setup', array(
		'canViewAttachments' => $__templater->method($__vars['resource'], 'canViewUpdateImages', array()),
	), $__vars) . '

<div class="block block--messages">
	';
	$__compilerTemp2 = '';
	$__compilerTemp2 .= '
				' . $__templater->callMacro('xfrm_resource_wrapper_macros', 'action_buttons', array(
		'resource' => $__vars['resource'],
	), $__vars) . '
			';
	if (strlen(trim($__compilerTemp2)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer">
			<div class="block-outer-opposite">
			' . $__compilerTemp2 . '
			</div>
		</div>
	';
	}
	$__finalCompiled .= '

	<div class="block-container"
		data-xf-init="lightbox"
		data-lb-id="resource-' . $__templater->escape($__vars['resource']['resource_id']) . '"
		data-lb-universal="' . $__templater->escape($__vars['xf']['options']['lightBoxUniversal']) . '">

		<div class="block-body">
		';
	if ($__templater->isTraversable($__vars['updates'])) {
		foreach ($__vars['updates'] AS $__vars['update']) {
			$__finalCompiled .= '
			' . $__templater->callMacro('xfrm_resource_update_macros', 'resource_update', array(
				'update' => $__vars['update'],
				'resource' => $__vars['resource'],
			), $__vars) . '
		';
		}
	}
	$__finalCompiled .= '
		</div>
	</div>
	';
	$__compilerTemp3 = '';
	$__compilerTemp3 .= '
				' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'resources/updates',
		'data' => $__vars['resource'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
			';
	if (strlen(trim($__compilerTemp3)) > 0) {
		$__finalCompiled .= '
		<div class="block-outer block-outer--after">
			' . $__compilerTemp3 . '
		</div>
	';
	}
	$__finalCompiled .= '
</div>';
	return $__finalCompiled;
});