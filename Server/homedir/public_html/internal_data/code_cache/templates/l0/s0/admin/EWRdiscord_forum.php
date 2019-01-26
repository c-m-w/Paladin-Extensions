<?php
// FROM HASH: 85a65929e9a3a1953adef25cac151ce1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit Discord options' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['node']['title']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['channels'])) {
		foreach ($__vars['channels'] AS $__vars['channel']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['channel']['id'],
				'label' => '# ' . $__templater->escape($__vars['channel']['name']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp1[] = array(
		'value' => '-1',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'Disabled' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	);
	$__compilerTemp2 = array(array(
		'value' => '0',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['channels'])) {
		foreach ($__vars['channels'] AS $__vars['channel']) {
			$__compilerTemp2[] = array(
				'value' => $__vars['channel']['id'],
				'label' => '# ' . $__templater->escape($__vars['channel']['name']),
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp2[] = array(
		'value' => '-1',
		'label' => $__vars['xf']['language']['parenthesis_open'] . 'Disabled' . $__vars['xf']['language']['parenthesis_close'],
		'_type' => 'option',
	);
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'discord[threads][channel]',
		'value' => $__vars['node']['discord_options']['threads']['channel'],
	), $__compilerTemp1, array(
		'label' => 'Threads',
		'explain' => 'If "<strong>None</strong>", your bot will automatically post to the default channel defined in the options for Discord.<br/>
You may instead choose to post to a different channel; or "<strong>Disable</strong>" auto-posting for this forum entirely.',
	)) . '
			' . $__templater->formTextAreaRow(array(
		'name' => 'discord[threads][message]',
		'value' => $__vars['node']['discord_options']['threads']['message'],
		'autosize' => 'true',
		'placeholder' => '**{user}** posted a new thread: *{title}* (<{url}>)',
	), array(
		'label' => 'Message',
		'explain' => 'Leave blank to use the default phrasing. Available substitution parameters: <strong>{user}</strong>, <strong>{title}</strong> and <strong>{url}</strong>.',
	)) . '
			' . $__templater->formNumberBoxRow(array(
		'name' => 'discord[threads][payload]',
		'value' => $__vars['node']['discord_options']['threads']['payload'],
		'min' => '50',
		'step' => '50',
	), array(
		'label' => 'Payload size',
		'explain' => 'The maximum length of the quoted text in a bot auto-posted message.',
	)) . '
			
			<hr class="formRowSep" />
			
			' . $__templater->formSelectRow(array(
		'name' => 'discord[posts][channel]',
		'value' => $__vars['node']['discord_options']['posts']['channel'],
	), $__compilerTemp2, array(
		'label' => 'Posts',
		'explain' => 'If "<strong>None</strong>", your bot will automatically post to the default channel defined in the options for Discord.<br/>
You may instead choose to post to a different channel; or "<strong>Disable</strong>" auto-posting for this forum entirely.',
	)) . '
			' . $__templater->formTextAreaRow(array(
		'name' => 'discord[posts][message]',
		'value' => $__vars['node']['discord_options']['posts']['message'],
		'autosize' => 'true',
		'placeholder' => '**{user}** posted a new thread: *{title}* (<{url}>)',
	), array(
		'label' => 'Message',
		'explain' => 'Leave blank to use the default phrasing. Available substitution parameters: <strong>{user}</strong>, <strong>{title}</strong> and <strong>{url}</strong>.',
	)) . '
			' . $__templater->formNumberBoxRow(array(
		'name' => 'discord[posts][payload]',
		'value' => $__vars['node']['discord_options']['posts']['payload'],
		'min' => '50',
		'step' => '50',
	), array(
		'label' => 'Payload size',
		'explain' => 'The maximum length of the quoted text in a bot auto-posted message.',
	)) . '
		</div>
		
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('nodes/discord-save', $__vars['node'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});