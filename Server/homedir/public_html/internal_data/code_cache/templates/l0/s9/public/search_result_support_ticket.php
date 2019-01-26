<?php
// FROM HASH: c0b6caec5081baebf6c9d24cb9c4ee40
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li class="block-row block-row--separated ' . ($__templater->method($__vars['ticket'], 'isIgnored', array()) ? 'is-ignored' : '') . ' js-inlineModContainer" data-author="' . ($__templater->escape($__vars['ticket']['User']['username']) ?: $__templater->escape($__vars['ticket']['username'])) . '">
	<div class="contentRow">
		<span class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['ticket']['User'], 's', false, array(
		'defaultname' => $__vars['ticket']['username'],
	))) . '
		</span>
		<div class="contentRow-main">
			<h3 class="contentRow-title">
				<a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '">' . ($__templater->fn('prefix', array('support_ticket', $__vars['ticket'], ), true) . $__templater->fn('highlight', array($__vars['ticket']['title'], $__vars['options']['term'], ), true)) . '</a>
			</h3>

			<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['ticket']['FirstMessage']['message'], 300, array('term' => $__vars['options']['term'], 'stripQuote' => true, ), ), true) . '</div>

			<div class="contentRow-minor contentRow-minor--hideLinks">
				<ul class="listInline listInline--bullet">
					';
	if (($__vars['options']['mod'] == 'ticket') AND $__templater->method($__vars['ticket'], 'canUseInlineModeration', array())) {
		$__finalCompiled .= '
						<li>' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'value' => $__vars['ticket']['ticket_id'],
			'class' => 'js-inlineModToggle',
			'data-xf-init' => 'tooltip',
			'title' => $__templater->filter('Select for moderation', array(array('for_attr', array()),), false),
			'_type' => 'option',
		))) . '</li>
					';
	}
	$__finalCompiled .= '
					<li>' . $__templater->fn('username_link', array($__vars['ticket']['User'], false, array(
		'defaultname' => $__vars['ticket']['username'],
	))) . '</li>
					<li>' . 'Ticket' . '</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['ticket']['open_date'], array(
	))) . '</li>
					<li>' . 'Replies' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->filter($__vars['ticket']['reply_count'], array(array('number', array()),), true) . '</li>
					<li>' . 'Department' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('support-tickets/departments', $__vars['ticket']['Department'], ), true) . '">' . $__templater->escape($__vars['ticket']['Department']['title']) . '</a></li>
				</ul>
			</div>
		</div>
	</div>
</li>';
	return $__finalCompiled;
});