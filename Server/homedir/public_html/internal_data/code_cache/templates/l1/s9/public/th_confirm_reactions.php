<?php
// FROM HASH: 928fd0d48d78cb703f98867ed9855c39
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped(($__vars['isReacted'] ? 'Unreact from ' . $__templater->escape($__vars['contentType']) . ' content' : 'React to ' . $__templater->escape($__vars['contentType']) . ' content'));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['isReacted']) {
		$__compilerTemp1 .= '
					';
		if ($__vars['reactionId']) {
			$__compilerTemp1 .= '
						' . 'Are you sure you want to unreact ' . $__templater->fn('reaction', array($__vars['reactionId'], 'alert', ), true) . ' from this content?' . '
					';
		} else {
			$__compilerTemp1 .= '
						' . 'Are you sure you want to unreact all reactions from this content?' . '
					';
		}
		$__compilerTemp1 .= '
				';
	} else {
		$__compilerTemp1 .= '
					' . 'Are you sure you want to react ' . $__templater->fn('reaction', array($__vars['reactionId'], 'alert', ), true) . ' to this content?' . '
					';
		if ($__vars['contentTitle']) {
			$__compilerTemp1 .= '<strong>' . $__templater->escape($__vars['contentTitle']) . '</strong>';
		}
		$__compilerTemp1 .= '
				';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formInfoRow('
				' . $__compilerTemp1 . '
			', array(
		'rowtype' => 'confirm',
	)) . '
		</div>

		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'rowtype' => 'simple',
	)) . '
	</div>
', array(
		'action' => $__vars['confirmUrl'],
		'class' => 'block',
	));
	return $__finalCompiled;
});