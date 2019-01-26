<?php
// FROM HASH: ae4045b10855ebeed7f5f42579f4326d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if (!$__templater->test($__vars['channels'], 'empty', array())) {
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
		$__compilerTemp3 = array(array(
			'value' => '0',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		if ($__templater->isTraversable($__vars['channels'])) {
			foreach ($__vars['channels'] AS $__vars['channel']) {
				$__compilerTemp3[] = array(
					'value' => $__vars['channel']['id'],
					'label' => '# ' . $__templater->escape($__vars['channel']['name']),
					'_type' => 'option',
				);
			}
		}
		$__compilerTemp4 = '';
		if ($__vars['addons']['EWRCarta']) {
			$__compilerTemp4 .= '
			<dl class="inputLabelPair">
				<dt>[8WR] XenCarta > ' . 'EWRdiscord_wiki_edits' . '</dt>
				<dd>
					';
			$__compilerTemp5 = array(array(
				'value' => '0',
				'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['channels'])) {
				foreach ($__vars['channels'] AS $__vars['channel']) {
					$__compilerTemp5[] = array(
						'value' => $__vars['channel']['id'],
						'label' => '# ' . $__templater->escape($__vars['channel']['name']),
						'_type' => 'option',
					);
				}
			}
			$__compilerTemp4 .= $__templater->formSelect(array(
				'name' => $__vars['inputName'] . '[ewrcarta]',
				'value' => $__vars['option']['option_value']['ewrcarta'],
			), $__compilerTemp5) . '
				</dd>
			</dl>
		';
		}
		$__compilerTemp6 = '';
		if ($__vars['addons']['EWRMedio']) {
			$__compilerTemp6 .= '
			<dl class="inputLabelPair">
				<dt>[8WR] XenMedio > ' . 'EWRdiscord_new_media' . '</dt>
				<dd>
					';
			$__compilerTemp7 = array(array(
				'value' => '0',
				'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['channels'])) {
				foreach ($__vars['channels'] AS $__vars['channel']) {
					$__compilerTemp7[] = array(
						'value' => $__vars['channel']['id'],
						'label' => '# ' . $__templater->escape($__vars['channel']['name']),
						'_type' => 'option',
					);
				}
			}
			$__compilerTemp6 .= $__templater->formSelect(array(
				'name' => $__vars['inputName'] . '[ewrmedio]',
				'value' => $__vars['option']['option_value']['ewrmedio'],
			), $__compilerTemp7) . '
				</dd>
			</dl>
			<dl class="inputLabelPair">
				<dt>[8WR] XenMedio > ' . 'New comments' . '</dt>
				<dd>
					';
			$__compilerTemp8 = array(array(
				'value' => '0',
				'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['channels'])) {
				foreach ($__vars['channels'] AS $__vars['channel']) {
					$__compilerTemp8[] = array(
						'value' => $__vars['channel']['id'],
						'label' => '# ' . $__templater->escape($__vars['channel']['name']),
						'_type' => 'option',
					);
				}
			}
			$__compilerTemp6 .= $__templater->formSelect(array(
				'name' => $__vars['inputName'] . '[ewrmediocomments]',
				'value' => $__vars['option']['option_value']['ewrmediocomments'],
			), $__compilerTemp8) . '
				</dd>
			</dl>
		';
		}
		$__compilerTemp9 = '';
		if ($__vars['addons']['EWRRio']) {
			$__compilerTemp9 .= '
			<dl class="inputLabelPair">
				<dt>[8WR] XenRio > ' . 'New streams' . '</dt>
				<dd>
					';
			$__compilerTemp10 = array(array(
				'value' => '0',
				'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
				'_type' => 'option',
			));
			if ($__templater->isTraversable($__vars['channels'])) {
				foreach ($__vars['channels'] AS $__vars['channel']) {
					$__compilerTemp10[] = array(
						'value' => $__vars['channel']['id'],
						'label' => '# ' . $__templater->escape($__vars['channel']['name']),
						'_type' => 'option',
					);
				}
			}
			$__compilerTemp9 .= $__templater->formSelect(array(
				'name' => $__vars['inputName'] . '[ewrrio]',
				'value' => $__vars['option']['option_value']['ewrrio'],
			), $__compilerTemp10) . '
				</dd>
			</dl>
		';
		}
		$__finalCompiled .= $__templater->formRow('
		<dl class="inputLabelPair">
			<dt>' . 'New threads' . '</dt>
			<dd>
				' . $__templater->formSelect(array(
			'name' => $__vars['inputName'] . '[threads]',
			'value' => $__vars['option']['option_value']['threads'],
		), $__compilerTemp1) . '
			</dd>
		</dl>
		<dl class="inputLabelPair">
			<dt>' . 'New posts' . '</dt>
			<dd>
				' . $__templater->formSelect(array(
			'name' => $__vars['inputName'] . '[posts]',
			'value' => $__vars['option']['option_value']['posts'],
		), $__compilerTemp2) . '
			</dd>
		</dl>
		<dl class="inputLabelPair">
			<dt>' . 'New profile posts' . '</dt>
			<dd>
				' . $__templater->formSelect(array(
			'name' => $__vars['inputName'] . '[profile]',
			'value' => $__vars['option']['option_value']['profile'],
		), $__compilerTemp3) . '
			</dd>
		</dl>
		' . $__compilerTemp4 . '
		' . $__compilerTemp6 . '
		' . $__compilerTemp9 . '
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