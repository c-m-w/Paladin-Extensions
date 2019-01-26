<?php
// FROM HASH: a29cba5aa113e6713debf55ee2ef13e7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['isWatched']) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Unwatch ticket');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Watch ticket');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['isWatched']) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					' . 'Are you sure you want to unwatch this ticket?' . '
				', array(
			'rowtype' => 'confirm',
		)) . '

				' . $__templater->formHiddenVal('stop', '1', array(
		)) . '
			';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->formRadioRow(array(
			'name' => 'email_subscribe',
			'value' => (($__vars['xf']['visitor']['Option']['interaction_watch_state'] == 'watch_email') ? 1 : 0),
		), array(array(
			'value' => '1',
			'label' => 'and receive email notifications',
			'_type' => 'option',
		),
		array(
			'value' => '0',
			'label' => 'without receiving email notifications',
			'_type' => 'option',
		)), array(
			'rowtype' => 'noColon',
			'label' => 'Watch this ticket' . $__vars['xf']['language']['ellipsis'],
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__vars['isWatched']) {
		$__compilerTemp2 .= '
			' . $__templater->formSubmitRow(array(
			'submit' => 'Unwatch',
		), array(
			'rowtype' => 'simple',
		)) . '
		';
	} else {
		$__compilerTemp2 .= '
			' . $__templater->formSubmitRow(array(
			'submit' => 'Watch',
		), array(
		)) . '
		';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '
		</div>
		' . $__compilerTemp2 . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/watch', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});