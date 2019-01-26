<?php
// FROM HASH: fe509154f271793c2c50773a200cf6da
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="block-row block-row--separated">
	' . $__templater->fn('bb_code', array($__vars['report']['content_info']['update']['message'], 'resource_update', ($__vars['content'] ?: $__vars['report']['User']), ), true) . '
</div>
<div class="block-row block-row--separated block-row--minor">
	<div>
		<dl class="pairs pairs--inline">
			<dt>' . 'Resource' . '</dt>
			<dd><a href="' . $__templater->fn('link', array('resources', $__vars['report']['content_info']['resource'], ), true) . '">' . $__templater->escape($__vars['report']['content_info']['resource']['title']) . '</a></dd>
		</dl>
	</div>
	<div>
		<dl class="pairs pairs--inline">
			<dt>' . 'Category' . '</dt>
			<dd><a href="' . $__templater->fn('link', array('resources/categories', $__vars['report']['content_info']['category'], ), true) . '">' . $__templater->escape($__vars['report']['content_info']['category']['title']) . '</a></dd>
		</dl>
	</div>
</div>';
	return $__finalCompiled;
});