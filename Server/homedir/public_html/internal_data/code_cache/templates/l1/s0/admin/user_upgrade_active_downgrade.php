<?php
// FROM HASH: 6ab13f07806a6598ca98212494b79946
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Confirm action');
	$__finalCompiled .= '

' . $__templater->form('

	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . 'Please confirm that you want to downgrade the following user' . $__vars['xf']['language']['label_separator'] . '
				<strong>
					' . $__templater->escape($__vars['activeUpgrade']['User']['username']) . '
					<span role="presentation" aria-hidden="true">&middot;</span>
					' . $__templater->escape($__vars['activeUpgrade']['Upgrade']['title']) . '
				</strong>
			', array(
		'rowtype' => 'confirm',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Downgrade',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('user-upgrades/downgrade', null, array('user_upgrade_record_id' => $__vars['activeUpgrade']['user_upgrade_record_id'], ), ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});