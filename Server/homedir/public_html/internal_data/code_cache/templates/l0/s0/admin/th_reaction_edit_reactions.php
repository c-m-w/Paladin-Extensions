<?php
// FROM HASH: f151fa2b294390e07173f717f4f5709e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['reaction'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add reaction');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit reaction' . ': ' . $__templater->escape($__vars['reaction']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('public:th_reactions.less');
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['reaction'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<span class="js-reactionPreview"></span>
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('reactions/delete', $__vars['reaction'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array(array(
		'_type' => 'option',
	));
	$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__vars['reactionTypes']);
	$__compilerTemp2 = array();
	if ($__templater->isTraversable($__vars['reactHandlers'])) {
		foreach ($__vars['reactHandlers'] AS $__vars['id'] => $__vars['title']) {
			$__compilerTemp2[] = array(
				'value' => $__vars['id'],
				'label' => $__templater->escape($__vars['title']),
				'selected' => $__vars['reaction']['react_handler'][$__vars['id']],
				'data-xf-init' => 'react-handler',
				'data-href' => $__templater->fn('link', array('reactions/handler', ), false),
				'data-container' => '.js-reactHandler-' . $__vars['id'],
				'data-hide' => 'yes',
				'_type' => 'option',
			);
		}
	}
	$__compilerTemp3 = '';
	if ($__templater->isTraversable($__vars['reactHandlers'])) {
		foreach ($__vars['reactHandlers'] AS $__vars['id'] => $__vars['title']) {
			$__compilerTemp3 .= '
					<div class="js-reactHandler-' . $__templater->escape($__vars['id']) . '">
						 ' . $__templater->filter($__vars['reactHandlersOptions'][$__vars['id']], array(array('raw', array()),), true) . '
					</div>
				';
		}
	}
	$__finalCompiled .= $__templater->form('
	<h2 class="block-tabHeader tabs hScroller" data-xf-init="tabs h-scroller" role="tablist">
		<span class="hScroller-scroll">
			<a class="tabs-tab is-active" role="tab" tabindex="0" data-controls="reaction-general">' . 'General' . '</a>
			<a class="tabs-tab" role="tab" tabindex="0" data-controls="reaction-styling">' . 'Styling' . '</a>
			<a class="tabs-tab" role="tab" tabindex="0" data-controls="reaction-criteria">' . 'Criteria' . '</a>
			' . $__templater->callMacro('helper_criteria', 'user_tabs', array(), $__vars) . '
			<a class="tabs-tab" role="tab" tabindex="0" data-controls="reaction-options">' . 'Options' . '</a>
		</span>
	</h2>

	<ul class="tabPanes">
		<li class="is-active" role="tabpanel" id="reaction-general">
			<div class="block-body">
				' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'value' => $__vars['reaction']['title'],
	), array(
		'label' => 'Title',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formTextBoxRow(array(
		'name' => 'display_order',
		'value' => $__vars['reaction']['display_order'],
		'min' => '0',
		'step' => '10',
		'type' => 'number',
	), array(
		'label' => 'Display order',
	)) . '

				' . $__templater->formSelectRow(array(
		'name' => 'reaction_type_id',
		'value' => $__vars['reaction']['reaction_type_id'],
	), $__compilerTemp1, array(
		'label' => 'Reaction type',
		'explain' => 'This is the type of reaction this will be.<br>
<b>Please note that changing this will require a reactions count rebuild.</b>',
	)) . '

				<hr class="formRowSep" />

				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'enabled',
		'label' => 'Enabled',
		'selected' => $__vars['reaction']['enabled'],
		'hint' => 'Choose whether this reaction will be visible to users.',
		'_type' => 'option',
	),
	array(
		'name' => 'random',
		'label' => 'Random reaction',
		'selected' => $__vars['reaction']['random'],
		'hint' => 'This will choose a random reaction to be used. Please note that this will respect the criteria and options of all reactions.',
		'_type' => 'option',
	),
	array(
		'name' => 'like_wrapper',
		'label' => 'Like wrapper',
		'selected' => $__vars['reaction']['like_wrapper'],
		'hint' => 'The reaction will be stored within the default XenForo like handler.',
		'_type' => 'option',
	)), array(
	)) . '
			</div>
		</li>

		<li role="tabpanel" id="reaction-styling">
			<div class="block-body">
				' . $__templater->formRadioRow(array(
		'name' => 'styling_type',
	), array(array(
		'value' => 'image',
		'label' => 'Image',
		'selected' => $__vars['reaction']['styling_type'] == 'image',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-imageContainer',
		'data-hide' => 'yes',
		'_type' => 'option',
	),
	array(
		'value' => 'text',
		'label' => 'Text / Emoji',
		'selected' => $__vars['reaction']['styling_type'] == 'text',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-textContainer',
		'data-hide' => 'yes',
		'_type' => 'option',
	),
	array(
		'value' => 'css_class',
		'label' => 'CSS class',
		'selected' => $__vars['reaction']['styling_type'] == 'css_class',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-CSSClassContainer',
		'data-hide' => 'yes',
		'_type' => 'option',
	),
	array(
		'value' => 'html_css',
		'label' => 'HTML/CSS',
		'selected' => $__vars['reaction']['styling_type'] == 'html_css',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-HTMLCSSClassContainer',
		'data-hide' => 'yes',
		'_type' => 'option',
	)), array(
		'label' => 'Styling type',
		'explain' => 'How the reaction will be styled and displayed.',
	)) . '

				<div class="js-imageContainer">
					' . $__templater->formTextBoxRow(array(
		'name' => 'image_url',
		'value' => $__vars['reaction']['image_url'],
	), array(
		'label' => 'Image replacement URL',
	)) . '

					<div class="js-image2x">
						' . $__templater->formTextBoxRow(array(
		'name' => 'image_url_2x',
		'value' => $__vars['reaction']['image_url_2x'],
	), array(
		'label' => '2x image replacement URL',
		'hint' => 'Optional',
		'explain' => 'If provided, the 2x image will be automatically displayed instead of the image URL above on devices capable of displaying a higher pixel resolution.<br />
<br />
<strong>Note: This option has no effect with sprite mode enabled.</strong>',
	)) . '
					</div>

					' . $__templater->formRadioRow(array(
		'name' => 'image_type',
	), array(array(
		'value' => 'normal',
		'label' => 'Normal image',
		'selected' => $__vars['reaction']['image_type'] == 'normal',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-imageNormalContainer, .js-image2x',
		'data-hide' => 'yes',
		'_type' => 'option',
	),
	array(
		'value' => 'sprite',
		'label' => 'Sprite image',
		'selected' => $__vars['reaction']['image_type'] == 'sprite',
		'data-xf-init' => 'disabler',
		'data-container' => '.js-imageSpriteContainer',
		'data-hide' => 'yes',
		'_type' => 'option',
	)), array(
		'label' => 'Image type',
		'explain' => 'The type of image to be displayed with the necessary styling options included.',
	)) . '

					<div class="js-imageNormalContainer">
						' . $__templater->formRow('
							<div class="inputGroup">
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_normal][w]',
		'value' => $__vars['reaction']['styling']['image_normal']['w'],
		'min' => '1',
		'title' => 'Width',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">x</span>
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_normal][h]',
		'value' => $__vars['reaction']['styling']['image_normal']['h'],
		'min' => '1',
		'title' => 'Height',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">|</span>
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_normal][u]',
		'value' => $__vars['reaction']['styling']['image_normal']['u'],
		'placeholder' => 'Unit',
	)) . '
							</div>
						', array(
		'label' => 'Image dimensions',
		'rowtype' => 'input',
	)) . '

						' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'styling[image_normal][style_dimensions]',
		'label' => 'Style Dimensions',
		'selected' => $__vars['reaction']['styling']['image_normal']['style_dimensions'],
		'hint' => 'Use the width and height defined within the style properties for whichever one you are currently using.',
		'_type' => 'option',
	)), array(
	)) . '
					</div>

					<div class="js-imageSpriteContainer">
						' . $__templater->formRow('
							<div class="inputGroup">
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_sprite][w]',
		'value' => $__vars['reaction']['styling']['image_sprite']['w'],
		'min' => '1',
		'title' => 'Width',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">x</span>
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_sprite][h]',
		'value' => $__vars['reaction']['styling']['image_sprite']['h'],
		'min' => '1',
		'title' => 'Height',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">' . 'Pixels' . '</span>
							</div>
						', array(
		'label' => 'Sprite dimensions',
		'rowtype' => 'input',
	)) . '

						' . $__templater->formRow('
							<div class="inputGroup">
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_sprite][x]',
		'value' => $__vars['reaction']['styling']['image_sprite']['x'],
		'title' => 'Background position x',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">x</span>
								' . $__templater->formTextBox(array(
		'name' => 'styling[image_sprite][y]',
		'value' => $__vars['reaction']['styling']['image_sprite']['y'],
		'title' => 'Background position y',
		'type' => 'number',
		'data-xf-init' => 'tooltip',
	)) . '
								<span class="inputGroup-text">' . 'Pixels' . '</span>
							</div>
						', array(
		'label' => 'Sprite position',
		'rowtype' => 'input',
	)) . '

						' . $__templater->formTextBoxRow(array(
		'name' => 'styling[image_sprite][u]',
		'value' => $__vars['reaction']['styling']['image_sprite']['u'],
	), array(
		'label' => 'Unit',
	)) . '
	
						' . $__templater->formTextBoxRow(array(
		'name' => 'styling[image_sprite][bs]',
		'value' => $__vars['reaction']['styling']['image_sprite']['bs'],
	), array(
		'label' => 'Background size',
		'explain' => 'If required, enter a value for the <code>background-size</code> CSS property for this sprite.',
	)) . '
					</div>
				</div>

				<div class="js-textContainer">
					' . $__templater->formTextBoxRow(array(
		'name' => 'reaction_text',
		'value' => $__vars['reaction']['reaction_text'],
	), array(
		'label' => 'Reaction text',
		'explain' => 'You may input text or an emoji to be displayed instead of an image.',
	)) . '
				</div>

				<div class="js-CSSClassContainer">
					' . $__templater->formTextBoxRow(array(
		'name' => 'reaction_text',
		'value' => $__vars['reaction']['reaction_text'],
	), array(
		'label' => 'CSS class',
		'explain' => 'Enter a CSS class to use. This is to be used with icon packs like Font Awesome.',
	)) . '
				</div>

				<div class="js-HTMLCSSClassContainer">
					<div class="block-body" data-xf-init="code-editor-switcher-container" data-template-suffix-mode="1">
						' . $__templater->formCodeEditorRow(array(
		'name' => 'styling[html_css][html]',
		'value' => $__vars['reaction']['styling']['html_css']['html'],
		'mode' => 'html',
		'data-submit-selector' => '.js-submitButton',
	), array(
		'label' => 'HTML code',
		'rowclass' => 'js-codeEditorContainer js-htmlEditorContainer',
		'explain' => '
								' . 'Enter the HTML structure of your reaction. This can then be manipulated with CSS entered below.<br>
<b>You may also use {reactionId} in the content to insert the reaction ID for unique identification.</b>' . '
							',
	)) . '
					</div>

					<hr class="formRowSep" />

					<div class="block-body" data-xf-init="code-editor-switcher-container" data-template-suffix-mode="1">
						' . $__templater->formCodeEditorRow(array(
		'name' => 'styling[html_css][css]',
		'value' => $__vars['reaction']['styling']['html_css']['css'],
		'mode' => 'css',
		'data-submit-selector' => '.js-submitButton',
	), array(
		'label' => 'CSS code',
		'rowclass' => 'js-codeEditorContainer js-cssEditorContainer',
		'explain' => '
								' . 'Enter the CSS code that will directly manipulate the HTML elements you have entered.<br>
<b>You may also use {reactionId} in the content to insert the reaction ID for unique identification.</b>' . '
							',
	)) . '
					</div>
				</div>
			</div>
		</li>

		<li role="tabpanel" id="reaction-criteria">
			<div class="block-body">
				' . $__templater->formCheckBoxRow(array(
		'name' => 'react_handler[]',
		'listclass' => 'listColumns',
		'value' => $__vars['reaction']['react_handler'],
	), $__compilerTemp2, array(
		'rowid' => 'reactHandler',
		'label' => 'Content handlers',
		'hint' => '<label><input type="checkbox" name="react_handler_all" value="1" data-xf-init="check-all"
						data-container="#reactHandler" /> ' . 'Select all' . '</label>',
		'explain' => 'Choose which content this reaction will be usable on.',
	)) . '

				' . $__compilerTemp3 . '
			</div>
		</li>

		' . $__templater->callMacro('helper_criteria', 'user_panes', array(
		'criteria' => $__templater->method($__vars['userCriteria'], 'getCriteriaForTemplate', array()),
		'data' => $__templater->method($__vars['userCriteria'], 'getExtraTemplateData', array()),
	), $__vars) . '

		<li role="tabpanel" id="reaction-general">
			<div class="block-body">
				' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[alerts]',
		'label' => 'Send alerts',
		'selected' => $__vars['reaction']['options']['alerts'],
		'hint' => 'Users who receive a reaction will also get an alert showing them where it was given and who gave it.',
		'_type' => 'option',
	),
	array(
		'name' => 'options[newsfeed]',
		'label' => 'Publish to newsfeed',
		'selected' => $__vars['reaction']['options']['newsfeed'],
		'hint' => 'When enabled a newsfeed entry will be made about a reaction being given.',
		'_type' => 'option',
	),
	array(
		'name' => 'options[prevent_unreact]',
		'label' => 'Prevent unreact',
		'selected' => $__vars['reaction']['options']['prevent_unreact'],
		'hint' => 'When enabled the reaction cannot be removed from any content. Please note that if the user has the permission to unreact to all reactions this will not affect them.',
		'_type' => 'option',
	),
	array(
		'label' => 'Max per day per user',
		'selected' => $__vars['reaction']['options']['user_max_per_day'],
		'hint' => 'Choose how many times this reaction can be used in a single day per user. Please note that this value will not overwrite the max number set per user group.',
		'_dependent' => array($__templater->formTextBox(array(
		'name' => 'options[user_max_per_day]',
		'value' => $__vars['reaction']['options']['user_max_per_day'],
		'min' => '1',
		'step' => '1',
		'type' => 'number',
	))),
		'_type' => 'option',
	)), array(
	)) . '
			</div>
		</li>

		' . $__templater->formSubmitRow(array(
		'class' => 'js-submitButton',
		'sticky' => 'true',
		'icon' => 'save',
	), array(
		'html' => '
				' . $__templater->button('Save and exit', array(
		'type' => 'submit',
		'icon' => 'save',
		'name' => 'exit',
		'accesskey' => 's',
	), '', array(
	)) . '
			',
	)) . '
	</ul>
', array(
		'action' => $__templater->fn('link', array('reactions/save', $__vars['reaction'], ), false),
		'ajax' => 'true',
		'class' => 'block-container',
	)) . '

';
	$__templater->inlineJs('
/** @param {jQuery} $ jQuery Object */
!function($, window, document)
{
	"use strict";

    XF.ReactHandler = XF.extend(XF.Disabler, {
        __backup: {
            \'click\': \'_click\'
        },

        options: $.extend({}, XF.Disabler.prototype.options, {
            href: \'\'
        }),

        click: function()
        {
            if (this.$target.is(\':checked:enabled\') && this.options.href) {
                if (this.xhr)
                {
                    this.xhr.abort();
                }

                this.xhr = XF.ajax(
                    \'post\',
                    this.options.href,
                    { react_handler_id: this.$target.val() },
                    $.proxy(this, \'showReactHandlerOptions\'),
                    { global: false, error: true }
                );
            }

            this._click();
        },

		showReactHandlerOptions: function(results)
		{
			if (this.xhr)
			{
				this.xhr = false;
			}

            var $container = this.$container;

            if (results.options_rendered)
            {
                $container.html(results.options_rendered);
            }
        },
    });

	XF.Element.register(\'react-handler\', \'XF.ReactHandler\');
}
(jQuery, window, document);

$(document).ready(function () {
	$(\'.js-codeEditorContainer .CodeMirror\').click(function() {
		var codeMirror = $(this)[0].CodeMirror;
		codeMirror.refresh();
	});

	$("input").on("input", debounce(function () {
		generatePreview();
	}, 500));

	$(\'.js-codeEditorContainer .CodeMirror\').each(function () {
		var codeMirror = $(this)[0].CodeMirror;
		codeMirror.on(\'change\', function(cm, change) {
			generatePreview();
		});
	});

	function debounce(func, wait, immediate) {
		var timeout;
		return function() {
			var context = this, args = arguments;
			var later = function() {
				timeout = null;
				if (!immediate) func.apply(context, args);
			};
	
			var callNow = immediate && !timeout;
			clearTimeout(timeout);
			timeout = setTimeout(later, wait);
			if (callNow) func.apply(context, args);
		};
	};

	function generatePreview() {
		var output = \'<span class="reaction" title="\' + ' . $__templater->filter($__vars['reaction']['title'], array(array('json', array()),), false) . ' + \'">\';
		var css = \'\';

		var reactionId = "' . $__templater->filter($__vars['reaction']['reaction_id'], array(array('json', array()),), false) . '";

		var stylingType = $("input[name=\'styling_type\']:checked").val();
		if (stylingType == \'image\') {
			var imageUrl = $("input[name=\'image_url\']").val();

			var imageType = $("input[name=\'image_type\']:checked").val();
			if (imageType == \'normal\') {
				var width = $("input[name=\'styling[image_normal][w]\']").val();
				var height = $("input[name=\'styling[image_normal][h]\']").val();
				var unit = $("input[name=\'styling[image_normal][u]\']").val();

				output += \'<img src="\' + imageUrl + \'" width="\' + width + unit + \'" height="\' + height + unit + \'" />\';
			}

			if (imageType == \'sprite\') {
				var width = $("input[name=\'styling[image_sprite][w]\']").val();
				var height = $("input[name=\'styling[image_sprite][h]\']").val();
				var unit = $("input[name=\'styling[image_sprite][u]\']").val();
				var bsX = $("input[name=\'styling[image_sprite][x]\']").val();
				var bsY = $("input[name=\'styling[image_sprite][y]\']").val();

				var reactionClass = \'reaction--sprite reaction--sprite\' + reactionId;

				output += \'<img class="\' + reactionClass + \'" src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" style="width: \' + width + unit + \'; height: \' + height + unit + \'; background: url(\\\'\' + imageUrl + \'\\\') no-repeat \' + bsX + unit + \' \' + bsY + unit + \';" />\';
			}
		}

		if (stylingType == \'text\') {
			var reactionText = $("input[name=\'reaction_text\']:visible").val();

			output += reactionText;
		}

		if (stylingType == \'css_class\') {
			var reactionText = $("input[name=\'reaction_text\']:visible").val();

			output += \'<i class="\' + reactionText + \'"></i>\';
		}

		output += \'</span>\';

		if (stylingType == \'html_css\') {
			var htmlCM = $(\'.js-htmlEditorContainer .CodeMirror\')[0].CodeMirror;
			var cssCM = $(\'.js-cssEditorContainer .CodeMirror\')[0].CodeMirror;

			if (reactionId) {
				editorHtml = htmlCM.getValue().replace(/\\{reactionId\\}/g, reactionId);
				editorCss = cssCM.getValue().replace(/\\{reactionId\\}/g, reactionId);
			}

			output += editorHtml;
			css = editorCss;
		}

		var html = \'<span class="reaction reaction-dev">\' + output + \'</span>\' + css + \'</style>\';
		$(\'.js-reactionPreview\').html(html);
	}

	generatePreview();
});
');
	return $__finalCompiled;
});