<?php
// FROM HASH: ddb65c52b536417b7fe77c2313b53683
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('kl_em_bb_code.less');
	$__finalCompiled .= '

<div class=\'post-table-container\'>
	<table class=\'post-table ' . $__templater->filter($__vars['classes'], array(array('raw', array()),), true) . '\' ' . $__templater->filter($__vars['style'], array(array('raw', array()),), true) . '>
		' . $__templater->filter($__vars['content'], array(array('raw', array()),), true) . '
	</table>
</div>';
	return $__finalCompiled;
});