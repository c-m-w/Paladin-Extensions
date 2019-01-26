<?php
// FROM HASH: 1d1d0e0c5fef67320ac7506340bce4c4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= $__templater->callMacro('tools_rebuild', 'rebuild_job', array(
		'header' => '[BRST] Rebuild tickets',
		'job' => 'MJ\\SupportTicket:Ticket',
	), $__vars) . '
' . '

' . $__templater->callMacro('tools_rebuild', 'rebuild_job', array(
		'header' => '[BRST] Rebuild ticket departments',
		'job' => 'MJ\\SupportTicket:Department',
	), $__vars) . '
' . '

' . $__templater->callMacro('tools_rebuild', 'rebuild_job', array(
		'header' => '[BRST] Rebuild user ticket counts',
		'job' => 'MJ\\SupportTicket:UserTicketCount',
	), $__vars) . '
' . '

';
	$__vars['mdBody'] = $__templater->preEscaped('
	' . $__templater->formCheckBoxRow(array(
		'name' => 'options[types]',
		'listclass' => 'listColumns',
	), array(array(
		'value' => 'attachments',
		'label' => 'Attachments',
		'selected' => true,
		'_type' => 'option',
	)), array(
	)) . '
');
	$__finalCompiled .= '
' . $__templater->callMacro('tools_rebuild', 'rebuild_job', array(
		'header' => '[BRST] Rebuild ticket embed metadata',
		'body' => $__vars['mdBody'],
		'job' => 'MJ\\SupportTicket:TicketMessageEmbedMetadata',
	), $__vars) . '
';
	return $__finalCompiled;
});