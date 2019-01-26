<?php
// FROM HASH: 0247959fb2f2209e7b43213546e8ed18
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:selectunit label="' . $__templater->escape($__vars['preparedOption']['title']) . '" name="' . $__templater->escape($__vars['fieldPrefix']) . '[' . $__templater->escape($__vars['preparedOption']['option_id']) . ']" hint="' . $__templater->escape($__vars['preparedOption']['hint']) . '" inputclass="' . $__templater->escape($__vars['preparedOption']['inputClass']) . '" multiple="multiple">
	<xen:options source="$formatParams" />
	<xen:explain>{xen:raw $preparedOption.explain}</xen:explain>
	<xen:html>
		<input type="hidden" name="' . $__templater->escape($__vars['listedFieldName']) . '" value="' . $__templater->escape($__vars['preparedOption']['option_id']) . '" />
		{xen:raw $editLink}
	</xen:html>
</xen:selectunit>';
	return $__finalCompiled;
});