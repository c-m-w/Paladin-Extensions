<?php
// FROM HASH: 6d4bb6d8b4eeed12bbc914fb61a3091c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('xfv_thread_starter', 'xfv_ts_view', ))) {
		$__finalCompiled .= '
   ';
		$__templater->includeCss('xfv_threadstarter_corner_banners.less');
		$__finalCompiled .= '

   ';
		if ($__vars['user']['user_id'] == $__vars['TS']) {
			$__finalCompiled .= '
      <div class="box">
         <div class="ribbon" data-xf-init="tooltip" title="' . $__templater->fn('property', array('xfv_threadstarter_custom_label', ), true) . '"><span>' . $__templater->fn('property', array('xfv_threadstarter_custom_label', ), true) . '</span></div>		   		  
     </div>
   ';
		}
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});