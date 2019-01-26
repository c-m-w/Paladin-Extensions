<?php
// FROM HASH: 122448acb17b7e9cda4ba1260f61333f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['option']['option_value'] AND !$__templater->test($__vars['provider'], 'empty', array())) {
		$__finalCompiled .= '
	
	';
		$__templater->includeJs(array(
			'src' => '8wayrun/discord/discord.js',
		));
		$__finalCompiled .= '
	
	' . $__templater->formRow('
		<div class="inputGroup">
			' . $__templater->formTextBox(array(
			'name' => $__vars['inputName'],
			'value' => $__vars['option']['option_value'],
			'class' => 'input',
		)) . '
			<span class="inputGroup-splitter"></span>
			' . $__templater->button('
				' . 'Test connection' . '
			', array(
			'data-xf-init' => 'discord-botcheck',
			'data-token' => $__vars['provider']['options']['bot_token'],
		), '', array(
		)) . '
		</div>
	', array(
			'label' => $__templater->escape($__vars['option']['title']),
			'hint' => $__templater->escape($__vars['hintHtml']),
			'explain' => $__templater->escape($__vars['explainHtml']),
			'html' => $__templater->escape($__vars['listedHtml']),
		)) . '
	
';
	} else if (!$__templater->test($__vars['provider'], 'empty', array())) {
		$__finalCompiled .= '
	
	' . $__templater->formRow('
		' . $__templater->button('
			' . 'Assign Discord application bot to a guild' . '
		', array(
			'href' => $__vars['redirect'],
		), '', array(
		)) . '
	', array(
			'label' => $__templater->escape($__vars['option']['title']),
			'hint' => $__templater->escape($__vars['hintHtml']),
			'explain' => $__templater->escape($__vars['explainHtml']),
			'html' => $__templater->escape($__vars['listedHtml']),
		)) . '
	
';
	} else {
		$__finalCompiled .= '
	
	' . $__templater->formInfoRow('
		' . 'Before using this addon, you must first set up a <a href="https://discordapp.com/developers/applications/me" target="_blank">Discord Developer Application</a>.<br/>
When creating your application, be sure to set the following as your "Redirect URIs":<br/>
<br/>
<div><code>' . $__templater->escape($__vars['redirect']) . '/connected_account.php</code></div>
<div><code>' . $__templater->escape($__vars['redirect']) . '/connected_discord.php</code></div>' . '
	', array(
			'rowtype' => 'confirm',
		)) . '
	
';
	}
	return $__finalCompiled;
});