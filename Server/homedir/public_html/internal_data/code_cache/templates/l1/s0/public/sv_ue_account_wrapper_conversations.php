<?php
// FROM HASH: c3445ebe5de86b8adc2f843883d9c97c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['useress_conversationWrapper']) {
		$__finalCompiled .= '
	<h3 class="block-minorHeader">' . 'Conversations' . '</h3>

	<div class="block-body">
		<a class="blockLink ' . (($__vars['pageSelected'] == 'conversations_view') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('conversations', ), true) . '">
			' . 'View conversations' . '
		</a>

		<a class="blockLink ' . (($__vars['pageSelected'] == 'conversations_add') ? 'is-selected' : '') . '" href="' . $__templater->fn('link', array('conversations/add', ), true) . '">
			' . 'Start a new conversation' . '
		</a>
	</div>
';
	}
	$__finalCompiled .= '
';
	return $__finalCompiled;
});