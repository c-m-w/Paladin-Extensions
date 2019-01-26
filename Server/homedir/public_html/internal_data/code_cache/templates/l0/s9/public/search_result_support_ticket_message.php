<?php
// FROM HASH: fa1bee386d34aaded2f90c3e2ac7518d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li class="block-row block-row--separated ' . ($__templater->method($__vars['message'], 'isIgnored', array()) ? 'is-ignored' : '') . ' js-inlineModContainer" data-author="' . ($__templater->escape($__vars['message']['User']['username']) ?: $__templater->escape($__vars['message']['username'])) . '">
	<div class="contentRow ' . ((!$__templater->method($__vars['message'], 'isVisible', array())) ? 'is-deleted' : '') . '">
		<span class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['message']['User'], 's', false, array(
		'defaultname' => $__vars['message']['username'],
	))) . '
		</span>
		<div class="contentRow-main">
			<h3 class="contentRow-title">
				<a href="' . $__templater->fn('link', array('support-tickets/message', $__vars['message']['Ticket'], array('message_id' => $__vars['message']['message_id'], ), ), true) . '">' . ($__templater->fn('prefix', array('support_ticket2', $__vars['message']['Ticket'], ), true) . $__templater->fn('highlight', array($__vars['message']['Ticket']['title'], $__vars['options']['term'], ), true)) . '</a>
			</h3>

			<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['message']['message'], 300, array('term' => $__vars['options']['term'], 'stripQuote' => true, ), ), true) . '</div>

			<div class="contentRow-minor contentRow-minor--hideLinks">
				<ul class="listInline listInline--bullet">
					';
	if (($__vars['options']['mod'] == 'message') AND $__templater->method($__vars['message'], 'canUseInlineModeration', array())) {
		$__finalCompiled .= '
						<li>' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'value' => $__vars['message']['message_id'],
			'class' => 'js-inlineModToggle',
			'data-xf-init' => 'tooltip',
			'title' => $__templater->filter('Select for moderation', array(array('for_attr', array()),), false),
			'_type' => 'option',
		))) . '</li>
					';
	}
	$__finalCompiled .= '
					<li>' . $__templater->fn('username_link', array($__vars['message']['User'], false, array(
		'defaultname' => $__vars['message']['username'],
	))) . '</li>
					<li>' . 'Message ' . $__templater->fn('number', array($__vars['message']['position'] + 1, ), true) . '' . '</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['message']['message_date'], array(
	))) . '</li>
					<li>' . 'Department' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['message']['Ticket']['Department'], ), true) . '">' . $__templater->escape($__vars['message']['Ticket']['Department']['title']) . '</a></li>
				</ul>
			</div>
		</div>
	</div>
</li>';
	return $__finalCompiled;
});