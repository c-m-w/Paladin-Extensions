<?php
// FROM HASH: 4882b5487ec42810eb84b806a3a2b63a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['mjstPreReplyEditor']) {
		$__templater->includeCss('mjst_editor_pre_reply.less');
		$__finalCompiled .= '
';
		$__templater->includeJs(array(
			'src' => 'mj/mjst/pre-reply.js',
			'min' => '1',
		));
		$__finalCompiled .= '
<script class="js-mjstPreReply" type="application/json">
	{
		"submitter": "' . $__templater->filter($__vars['mjstTicket']['username'], array(array('escape', array('json', )),), true) . '"
	}
</script>';
	}
	return $__finalCompiled;
});