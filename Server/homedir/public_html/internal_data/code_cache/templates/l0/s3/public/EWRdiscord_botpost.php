<?php
// FROM HASH: 9dc33f72aa6f002ad1992fde23c450af
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Post as bot');
	$__finalCompiled .= '

';
	$__compilerTemp1 = array();
	if ($__templater->isTraversable($__vars['channels'])) {
		foreach ($__vars['channels'] AS $__vars['channel']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['channel']['id'],
				'label' => '# ' . $__templater->escape($__vars['channel']['name']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'channel',
	), $__compilerTemp1, array(
		'label' => 'Channel',
	)) . '
			
			' . $__templater->formTextAreaRow(array(
		'name' => 'data[content]',
		'autosize' => 'true',
	), array(
		'label' => 'Message',
		'explain' => 'This message will be posted directly to your Discord server. As such you may use any markdown available to your bot.',
	)) . '
			
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'data[tts]',
		'value' => '1',
		'label' => ' Convert message to text-to-speech',
		'_type' => 'option',
	)), array(
	)) . '
		</div>
		
		' . $__templater->formSubmitRow(array(
		'submit' => 'Proceed' . $__vars['xf']['language']['ellipsis'],
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('ewr-discord/botpost', ), false),
		'ajax' => 'true',
		'class' => 'block',
		'data-redirect' => 'off',
	));
	return $__finalCompiled;
});