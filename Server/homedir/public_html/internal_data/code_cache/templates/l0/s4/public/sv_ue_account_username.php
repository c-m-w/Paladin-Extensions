<?php
// FROM HASH: 33d9bd270f3f49b789a097f14fd80738
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Change user name');
	$__finalCompiled .= '

';
	$__templater->wrapTemplate('account_wrapper', $__vars);
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['xf']['visitor'], 'isUsernameChangeModerated', array())) {
		$__compilerTemp1 .= '
				' . $__templater->formTextAreaRow(array(
			'name' => 'note',
			'rows' => '1',
			'autosize' => 'true',
			'maxlength' => $__templater->fn('max_length', array('SV\\UserEssentials:UsernameChange', 'user_note', ), false),
		), array(
			'label' => 'Note',
			'explain' => 'Provide a note to assist moderators with approving your user name change.',
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__templater->isTraversable($__vars['messageList'])) {
		foreach ($__vars['messageList'] AS $__vars['message']) {
			$__compilerTemp2 .= '
							<li>' . $__templater->escape($__vars['message']) . '</li>
						';
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'username',
		'value' => $__vars['xf']['visitor']['username'],
		'autofocus' => 'autofocus',
		'maxlength' => $__templater->fn('max_length', array($__vars['xf']['visitor'], 'username', ), false),
	), array(
		'label' => 'User name',
		'explain' => 'This is the name that is shown with your messages. You may use any name you wish. Your former user name will still be displayed in any prior quoted messages.',
	)) . '

			' . $__compilerTemp1 . '

			' . $__templater->formRow('
				<div class="blockMessage blockMessage--important">
					<ul class="listHeap">
						' . $__compilerTemp2 . '
					</ul>
				</div>
			', array(
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'password',
		'type' => 'password',
	), array(
		'label' => 'Current password',
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
		'sticky' => 'true',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('account/username-change', ), false),
		'ajax' => 'true',
		'class' => 'block',
	)) . '
';
	return $__finalCompiled;
});