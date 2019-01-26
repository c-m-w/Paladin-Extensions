<?php
// FROM HASH: cda8e74ecfbe8037b5a65f5b5da3fb60
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('can_change_steam_profile_privacy', array(), false)) {
		$__finalCompiled .= '
	<dl class="inputLabelPair">
		<dt>' . 'allow_view_steam' . ':</dt>
		<dd>
			' . $__templater->formSelect(array(
			'name' => 'privacy[allow_view_steam]',
			'value' => $__vars['xf']['visitor']['Privacy']['allow_view_steam'],
		), array(array(
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