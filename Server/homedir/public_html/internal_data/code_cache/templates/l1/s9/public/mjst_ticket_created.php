<?php
// FROM HASH: 42e4d7ef89e6ba01d18b235e1c276dd1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Support ticket created');
	$__finalCompiled .= '

';
	$__templater->inlineCss('
	.blockMessage{
		text-align: center;
		font-size: 18px;
	}
	.bigText{
		font-size: 22px;
	}
	.codeText{
		font-family: @xf-fontFamilyCode;
		direction: ltr;
		//white-space: nowrap;
		word-wrap: normal;
	}
');
	$__finalCompiled .= '

<div class="blockMessage blockMessage--success">
	' . 'Support ticket was create successfully' . '
</div>

<div class="blockMessage blockMessage--important bigText">
	<div>
		' . 'Ticket' . $__vars['xf']['language']['label_separator'] . '
		<a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '" title="" class="codeText">#' . $__templater->escape($__vars['ticket']['ticket_id']) . '</a>
	</div>
	';
	if (!$__vars['ticket']['user_id']) {
		$__finalCompiled .= '
		' . 'Password' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('support-tickets', $__vars['ticket'], ), true) . '" title="" class="codeText">' . $__templater->escape($__vars['ticket']['guest_password']) . '</a>
	';
	}
	$__finalCompiled .= '
</div>
';
	return $__finalCompiled;
});