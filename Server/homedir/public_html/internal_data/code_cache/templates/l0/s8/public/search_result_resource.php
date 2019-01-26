<?php
// FROM HASH: 088381fa3b018860ba44300d1850699c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li class="block-row block-row--separated ' . ($__templater->method($__vars['resource'], 'isIgnored', array()) ? 'is-ignored' : '') . ' js-inlineModContainer" data-author="' . ($__templater->escape($__vars['resource']['User']['username']) ?: $__templater->escape($__vars['resource']['username'])) . '">
	<div class="contentRow ' . ((!$__templater->method($__vars['resource'], 'isVisible', array())) ? 'is-deleted' : '') . '">
		<span class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['resource']['User'], 's', false, array(
		'defaultname' => $__vars['resource']['username'],
	))) . '
		</span>
		<div class="contentRow-main">
			<h3 class="contentRow-title">
				<a href="' . $__templater->fn('link', array('resources', $__vars['resource'], ), true) . '">' . $__templater->fn('prefix', array('resource', $__vars['resource'], ), true) . $__templater->fn('highlight', array($__vars['resource']['title'], $__vars['options']['term'], ), true) . '</a>
				';
	if ($__templater->method($__vars['resource'], 'isVersioned', array())) {
		$__finalCompiled .= '
					<span class="u-muted">' . $__templater->escape($__vars['resource']['CurrentVersion']['version_string']) . '</span>
				';
	}
	$__finalCompiled .= '
			</h3>

			<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['resource']['Description']['message'], 300, array('term' => $__vars['options']['term'], 'stripQuote' => true, ), ), true) . '</div>

			<div class="contentRow-minor contentRow-minor--hideLinks">
				<ul class="listInline listInline--bullet">
					';
	if (($__vars['options']['mod'] == 'resource') AND $__templater->method($__vars['resource'], 'canUseInlineModeration', array())) {
		$__finalCompiled .= '
						<li>' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'value' => $__vars['resource']['resource_id'],
			'class' => 'js-inlineModToggle',
			'_type' => 'option',
		))) . '</li>
					';
	}
	$__finalCompiled .= '
					<li>' . $__templater->fn('username_link', array($__vars['resource']['User'], false, array(
		'defaultname' => $__vars['resource']['username'],
	))) . '</li>
					<li>' . 'Resource' . '</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['resource']['resource_date'], array(
	))) . '</li>
					<li>' . 'Category' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('resources/categories', $__vars['resource']['Category'], ), true) . '">' . $__templater->escape($__vars['resource']['Category']['title']) . '</a></li>
				</ul>
			</div>
		</div>
	</div>
</li>';
	return $__finalCompiled;
});