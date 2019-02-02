<?php
// FROM HASH: dd46b4e5020ff0f71e276ff246c1a0f6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['plugins']['image']) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_froala_image.less');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['table']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'vendor/froala/plugins/table.min.js',
		));
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_froala_table.less');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['fullscreen']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'vendor/froala/plugins/fullscreen.min.js',
		));
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_froala_fullscreen.less');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['hide']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/hide.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['templates']) {
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_editor_templates.less');
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/templates.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
	<script class="js-klEditorTemplates" type="application/json">
			' . $__templater->filter($__vars['templates'], array(array('json', array()),array('raw', array()),), true) . '
	</script>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['charCounter']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'vendor/froala/plugins/char_counter.min.js',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['specialCharacters']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'vendor/froala/plugins/special_characters.min.js',
		));
		$__finalCompiled .= '
	';
		$__templater->includeCss('kl_em_froala_special_characters.less');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['ispoiler']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/inlineSpoiler.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['justify']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/justify.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['dropdowns']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/dropdowns.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['parseHtml']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/parseHtml.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['colors']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/colors.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['gFontFamily']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/gFontFamily.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['plugins']['unlinkAll']) {
		$__finalCompiled .= '
	';
		$__templater->includeJs(array(
			'src' => 'editor-manager/plugins/unlinkAll.plugin.js',
			'min' => '1',
			'addon' => 'KL/EditorManager',
		));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['config']['initOnClick']) {
		$__finalCompiled .= '
	';
		$__templater->inlineJs('
		$(\'.actionBar-action--reply, .button--multiQuote\').on(\'click\', function(event) {
			$(\'.fr-view\').trigger(\'focus\');
		});
	');
		$__finalCompiled .= '
';
	}
	return $__finalCompiled;
});