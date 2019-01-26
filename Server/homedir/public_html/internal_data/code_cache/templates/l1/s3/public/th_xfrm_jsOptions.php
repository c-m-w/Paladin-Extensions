<?php
// FROM HASH: f2db370599628142035e5ced3d92f4b6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<script>
	window.th_reactionsEnableHover = !!' . $__templater->escape($__vars['xf']['options']['th_reactionsEnableHover']) . ';
	window.th_reactionsSecondaryTrigger = !!' . $__templater->fn('property', array('th_reactions_secondaryTrigger', ), true) . ';
</script>
';
	return $__finalCompiled;
});