<?php
// FROM HASH: e8eba51b68f04b06378d05d92462d9e7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="block-row block-row--separated">
	' . $__templater->fn('structured_text', array($__vars['report']['content_info']['rating']['message'], ), true) . '
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