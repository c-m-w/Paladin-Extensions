<?php
// FROM HASH: 3b772d1f616dad2d488dc338833ab0a8
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Insert google font');
	$__finalCompiled .= '

<form class="block" id="editor_kl_em_gfont_form">
	<div class="block-container">
		<div class="block-body font-preview-list">
			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'id' => 'editor_kl_em_gfont_title',
		'ac' => 'single',
		'data-acurl' => $__templater->fn('link', array('editor/findGFont', ), false),
		'dir' => 'ltr',
	), array(
		'label' => 'Font name',
	)) . '

			<dl class="formRow">
				<dt>
					<div class="formRow-labelWrapper">
						<label class="formRow-label">' . 'Preview' . '</label></div>
				</dt>
				<dd id="editor_kl_em_gfont_preview" style="height: 75px; font-size: 28px; overflow: hidden; text-overflow: ellipsis">
					' . 'Pack my box with five dozen liquor jugs.' . '
				</dd>
			</dl>
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Continue',
		'id' => 'editor_kl_em_gfont_submit',
	), array(
	)) . '
	</div>
</form>

';
	$__templater->includeJs(array(
		'src' => 'editor-manager/vendor/textFit.js',
		'min' => '1',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/google-font.js',
		'min' => '1',
		'addon' => 'KL/EditorManager',
	));
	return $__finalCompiled;
});