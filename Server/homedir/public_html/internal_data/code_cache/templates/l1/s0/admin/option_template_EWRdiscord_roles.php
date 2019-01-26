<?php
// FROM HASH: 1f9dc757c0d4bf3e5e6cd87c68d70009
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['roles'], 'empty', array())) {
		$__finalCompiled .= '
	
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['roles'])) {
			foreach ($__vars['roles'] AS $__vars['role']) {
				$__compilerTemp1 .= '
			<dl class="inputLabelPair">
				<dt>' . $__templater->escape($__vars['role']['name']) . '</dt>
				<dd>
					';
				$__compilerTemp2 = array();
				if ($__templater->isTraversable($__vars['usergroups'])) {
					foreach ($__vars['usergroups'] AS $__vars['usergroup']) {
						$__compilerTemp2[] = array(
							'value' => $__vars['usergroup']['value'],
							'label' => $__templater->escape($__vars['usergroup']['label']),
							'_type' => 'option',
						);
					}
				}
				$__compilerTemp1 .= $__templater->formSelect(array(
					'name' => $__vars['inputName'] . '[' . $__vars['role']['id'] . ']',
					'value' => $__vars['role']['usergroup'],
				), $__compilerTemp2) . '
				</dd>
			</dl>
		';
			}
		}
		$__finalCompiled .= $__templater->formRow('
		' . $__compilerTemp1 . '
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
		' . 'You must setup Discord in the "<a href="' . $__templater->fn('link', array('connected-accounts', ), true) . '">connected accounts</a>" section of your admin control panel.' . '
	', array(
			'rowtype' => 'confirm',
		)) . '
	
';
	}
	return $__finalCompiled;
});