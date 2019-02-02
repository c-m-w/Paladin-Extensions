<?php
// FROM HASH: ada436d82ccc6437580c1469e50798e9
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<script class="js-klEditorDropdowns" type="applicaton/json">
	' . $__templater->filter($__vars['dropdowns'], array(array('json', array()),array('raw', array()),), true) . '
</script>

<script class="js-klEditorConfig" type="application/json">
	' . $__templater->filter($__vars['config'], array(array('json', array()),array('raw', array()),), true) . '
</script>

' . $__templater->includeTemplate('kl_em_editor_plugins', $__vars) . '

';
	$__templater->includeJs(array(
		'src' => 'editor-manager/base.js',
		'min' => '1',
		'addon' => 'KL/EditorManager',
	));
	return $__finalCompiled;
});