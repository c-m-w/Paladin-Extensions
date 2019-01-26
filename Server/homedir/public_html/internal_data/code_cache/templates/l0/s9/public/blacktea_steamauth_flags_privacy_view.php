<?php
// FROM HASH: 41aed8688388bd5f3a4e9177fa3e89c7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('can_change_steam_profile_privacy', array(), false)) {
		$__finalCompiled .= '
	<dl class="inputLabelPair">
		<dt>' . 'View your Steam Profile' . ':</dt>
		<dd>
			' . $__templater->formSelect(array(
			'name' => 'privacy[allow_view_steam]',
			'value' => $__vars['xf']['visitor']['Privacy']['allow_view_steam'],
		), array(array(
			'value' => 'everyone',
			'label' => 'All visitors',
			'_type' => 'option',
		),
		array(
			'value' => 'members',
			'label' => 'Members only',
			'_type' => 'option',
		),
		array(
			'value' => 'none',
			'label' => 'Nobody',
			'_type' => 'option',
		))) . '
		</dd>
	</dl>
';
	}
	$__finalCompiled .= '
';
	if ($__templater->fn('can_change_steam_banner_privacy', array(), false)) {
		$__finalCompiled .= '
	<dl class="inputLabelPair">
		<dt>' . 'View your Steam Banner' . ':</dt>
		<dd>
			' . $__templater->formSelect(array(
			'name' => 'privacy[allow_view_steam_banner]',
			'value' => $__vars['xf']['visitor']['Privacy']['allow_view_steam_banner'],
		), array(array(
			'value' => 'everyone',
			'label' => 'All visitors',
			'_type' => 'option',
		),
		array(
			'value' => 'members',
			'label' => 'Members only',
			'_type' => 'option',
		),
		array(
			'value' => 'none',
			'label' => 'Nobody',
			'_type' => 'option',
		))) . '
		</dd>
	</dl>
';
	}
	return $__finalCompiled;
});