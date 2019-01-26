<?php
// FROM HASH: da112e84bbd5d9d47dad9b0c7fc8f012
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('andy_admin_notes.less');
	$__finalCompiled .= '

<div class="block-container">
	<div class="block-header">
	' . 'Admin notes' . '
	</div>
	<div class="block-body admin-notes-block_body">
	' . $__templater->filter($__vars['xf']['options']['adminNotesNotes'], array(array('raw', array()),), true) . '
	</div>
</div>
<br />';
	return $__finalCompiled;
});