<?php
// FROM HASH: 6a32d35e48839af5c91adce6dce31894
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('xfv_thread_starter', 'xfv_ts_view', ))) {
		$__finalCompiled .= '
';
		$__templater->includeCss('xfv_threadstarter.less');
		$__finalCompiled .= '

';
		if (($__templater->fn('property', array('xfv_threadstarter_switch', ), false) == 'enable') AND ($__vars['thread']['user_id'] == $__vars['post']['user_id'])) {
			$__finalCompiled .= '
    <div style="color: white" class="TS" data-xf-init="tooltip" title="' . $__templater->fn('property', array('xfv_threadstarter_custom_label', ), true) . '"><i class="fa ' . $__templater->fn('property', array('xfv_threadstarter_fa_icon', ), true) . '" aria-hidden="true"></i> ' . $__templater->fn('property', array('xfv_threadstarter_custom_label', ), true) . '</div>
';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});