<?php
// FROM HASH: c0285973cf381d981d4ef3d290726094
return array('macros' => array('upload_editor' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'label' => '',
		'buttonLabel' => '!',
		'attachmentData' => '!',
		'hiddenName' => '!',
		'isInsert' => true,
		'iconUrl' => '',
		'title' => '',
		'attachment' => '!',
		'uploaderExtra' => '',
		'extra' => '',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	if ($__vars['isInsert']) {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, 'uploader', array(
			'label' => $__vars['label'],
			'buttonLabel' => $__vars['buttonLabel'],
			'attachmentData' => $__vars['attachmentData'],
			'hiddenName' => $__vars['hiddenName'],
			'extra' => $__vars['uploaderExtra'],
		), $__vars) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->callMacro(null, 'displayer', array(
			'label' => $__vars['label'],
			'iconUrl' => $__vars['iconUrl'],
			'title' => $__vars['title'],
			'attachment' => $__vars['attachment'],
			'extra' => $__vars['extra'],
		), $__vars) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'uploader' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'label' => '',
		'buttonLabel' => '!',
		'attachmentData' => '!',
		'hiddenName' => '!',
		'extra' => '',
		'row' => true,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	if ($__vars['extra']) {
		$__compilerTemp1 .= '
			' . $__templater->filter($__vars['extra'], array(array('raw', array()),), true) . '
		';
	}
	$__vars['inner'] = $__templater->preEscaped('
		' . $__templater->callMacro('public:xr_pm_attach_upload_macros', 'upload_block', array(
		'attachmentData' => $__vars['attachmentData'],
		'hiddenName' => $__vars['hiddenName'],
		'label' => $__vars['buttonLabel'],
	), $__vars) . '
		' . $__compilerTemp1 . '
	');
	$__finalCompiled .= '
	';
	if ($__vars['row']) {
		$__finalCompiled .= '
		' . $__templater->formRow('
			' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
		', array(
			'label' => $__templater->escape($__vars['label']),
			'rowtype' => 'button',
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},
'displayer' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'label' => '',
		'iconUrl' => '',
		'title' => '',
		'attachment' => '!',
		'extra' => '',
		'row' => true,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__compilerTemp1 = '';
	if ($__vars['iconUrl']) {
		$__compilerTemp1 .= '
					<img src="' . $__templater->escape($__vars['iconUrl']) . '" alt="' . $__templater->escape($__vars['title']) . '" />
				';
	} else {
		$__compilerTemp1 .= '
					<a style="pointer-events: none"><i class="fa fa-file-o fa-3x" aria-hidden="true"></i></a>
				';
	}
	$__compilerTemp2 = '';
	if ($__vars['extra']) {
		$__compilerTemp2 .= '
					' . $__templater->filter($__vars['extra'], array(array('raw', array()),), true) . '
				';
	}
	$__vars['inner'] = $__templater->preEscaped('
		<div class="contentRow contentRow--alignMiddle">
			<div class="contentRow-figure contentRow-figure--fixedSmall">
				' . $__compilerTemp1 . '
			</div>
			<div class="contentRow-main">
				<a href="' . $__templater->fn('link', array('attachments/view', $__vars['attachment'], ), true) . '">' . $__templater->escape($__vars['attachment']['filename']) . '</a>
				' . $__compilerTemp2 . '
			</div>
		</div>
	');
	$__finalCompiled .= '
	';
	if ($__vars['row']) {
		$__finalCompiled .= '
		' . $__templater->formRow('
			' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
		', array(
			'label' => $__templater->escape($__vars['label']),
		)) . '
	';
	} else {
		$__finalCompiled .= '
		' . $__templater->filter($__vars['inner'], array(array('raw', array()),), true) . '
	';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '

' . '

';
	return $__finalCompiled;
});