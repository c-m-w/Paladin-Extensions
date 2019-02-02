<?php
// FROM HASH: 23a16b5c2bd27bdc7053264ea3b1404f
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Options');
	$__finalCompiled .= '

';
	$__templater->includeCss('kl_em_options.less');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">

		<div class="block-body">
			
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'disable_smilies',
		'value' => '1',
		'selected' => $__vars['disable_smilies'],
		'label' => '
					' . 'Disable smilie button' . '
				',
		'_type' => 'option',
	),
	array(
		'name' => 'enable_fullscreen',
		'value' => '1',
		'selected' => $__vars['enable_fullscreen'],
		'label' => '
					' . 'Enable fullscreen button' . '
				',
		'_type' => 'option',
	),
	array(
		'name' => 'keep_format_on_delete',
		'value' => '1',
		'selected' => $__vars['keep_format_on_delete'],
		'label' => '
					' . 'Keep text format on character deletion' . '
				',
		'_type' => 'option',
	),
	array(
		'name' => 'enable_charcounter',
		'value' => '1',
		'selected' => $__vars['enable_charcounter'],
		'label' => '
					' . 'Enable character counter' . '
				',
		'_type' => 'option',
	)), array(
		'label' => 'General options',
	)) . '
			
			<hr class="formRowSep" />
			
			' . $__templater->formRow('
				' . $__templater->formSelect(array(
		'name' => 'hide_default',
		'value' => $__vars['hide_default'],
	), array(array(
		'value' => 'Reply',
		'label' => 'Hide until replied',
		'_type' => 'option',
	),
	array(
		'value' => 'Posts',
		'label' => 'Hide until number of posts',
		'_type' => 'option',
	),
	array(
		'value' => 'Thanks',
		'label' => 'Hide until liked',
		'_type' => 'option',
	),
	array(
		'value' => 'ReplyThanks',
		'label' => 'Hide until replied or liked',
		'_type' => 'option',
	))) . '
			', array(
		'rowtype' => 'input',
		'label' => 'Default hide version',
	)) . '
			
			<hr class="formRowSep" />
			
			' . $__templater->formTextBoxRow(array(
		'name' => 'font_sizes',
		'value' => $__vars['font_sizes'],
	), array(
		'label' => 'Font sizes',
	)) . '
			
			<hr class="formRowSep" />
			<div class="multiRow">
				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'enabled_bbcodes[bold]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['bold'],
		'label' => '
						' . 'Bold' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[italic]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['italic'],
		'label' => '
						' . 'Italic' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[underline]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['underline'],
		'label' => '
						' . 'Underline' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[strike]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['strike'],
		'label' => '
						' . 'Strike-through' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[color]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['color'],
		'label' => '
						' . 'Text color' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[bgcolor]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['bgcolor'],
		'label' => '
						' . 'Background color' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[font]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['font'],
		'label' => '
						' . 'Font family' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[size]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['size'],
		'label' => '
						' . 'Font size' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[url]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['url'],
		'label' => '
						' . 'Link' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[img]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['img'],
		'label' => '
						' . 'Image' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[media]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['media'],
		'label' => '
						' . 'Media' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[quote]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['quote'],
		'label' => '
						' . 'Quote' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[spoiler]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['spoiler'],
		'label' => '
						' . 'Spoiler' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[ispoiler]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['ispoiler'],
		'label' => '
						' . 'Inline spoiler' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[code]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['code'],
		'label' => '
						' . 'Code' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[icode]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['icode'],
		'label' => '
						' . 'Inline code' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[align]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['align'],
		'label' => '
						' . 'Alignment' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[list]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['list'],
		'label' => '
						' . 'List' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[table]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['table'],
		'label' => '
						' . 'Table' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[hide]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['hide'],
		'label' => '
						' . 'Hide' . '
					',
		'_type' => 'option',
	),
	array(
		'name' => 'enabled_bbcodes[parsehtml]',
		'value' => '1',
		'selected' => $__vars['enabled_bbcodes']['parsehtml'],
		'label' => '
						' . 'ParseHtml' . '
					',
		'_type' => 'option',
	)), array(
		'label' => 'Enabled BB codes',
	)) . '
			</div>
			
			<hr class="formRowSep" />
			
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'external_font_polling',
		'value' => '1',
		'selected' => $__vars['external_font_polling'],
		'label' => '
					' . 'Enable external font polling' . '
				',
		'_type' => 'option',
	)), array(
		'label' => 'External fonts',
		'explain' => 'If enabled, users with the required permission can use Google Fonts as they wish, which will be loaded when required. This differs from integrated Google Fonts which will be loaded on all XenForo-driven pages.',
	)) . '
			
			' . $__templater->formRadioRow(array(
		'name' => 'external_font_mode',
	), array(array(
		'value' => 'whitelist',
		'selected' => ($__vars['external_font_mode'] == 'whitelist'),
		'label' => '
					' . 'Whitelist' . '
				',
		'_type' => 'option',
	),
	array(
		'value' => 'blacklist',
		'selected' => ($__vars['external_font_mode'] == 'blacklist'),
		'label' => '
					' . 'Blacklist' . '
				',
		'_type' => 'option',
	)), array(
		'label' => 'Mode',
	)) . '
			
			' . $__templater->formTextAreaRow(array(
		'name' => 'external_font_list',
		'value' => $__vars['external_font_list'],
		'rows' => '5',
		'autosize' => 'true',
	), array(
		'label' => 'Included/excluded fonts',
		'explain' => 'If whitelist mode is enabled, this is a list of all fonts that can be used by your users via font polling. If blacklist mode is enabled instead, this is a list of all fonts that cannot be used. Separate multiple entries with line breaks.',
	)) . '
			
			' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/options/save', ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});