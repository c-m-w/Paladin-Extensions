<?php
// FROM HASH: a156be2dc0048c1f57efce27e90074df
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Conversation view');
	$__finalCompiled .= '

' . 'Message ID' . ': ' . $__templater->escape($__vars['messageId']) . '
<br /><br />
' . $__templater->filter($__vars['results'], array(array('raw', array()),), true);
	return $__finalCompiled;
});