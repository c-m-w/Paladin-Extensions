<?php
// FROM HASH: 9141ea500aa3098ae50b7848901e5854
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="tooltip-content-inner">
	' . $__templater->fn('bb_code', array($__vars['firstMessage']['message'], 'support_ticket_message:ticket_preview', $__vars['firstMessage'], array('lightbox' => false, ), ), true) . '
	<span class="tooltip-content-cover"></span>
</div>';
	return $__finalCompiled;
});