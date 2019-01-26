<?php
// FROM HASH: c15016f74e856c62cdf23623b878e67b
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('kl_amdp_merge_message.less');
	$__finalCompiled .= '
<div class="kl_amdp_merge_message">
	' . 'Post automatically merged: ' . $__templater->fn('date_dynamic', array($__vars['time'], ), true) . '' . '
</div>';
	return $__finalCompiled;
});