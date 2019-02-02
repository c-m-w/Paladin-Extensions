<?php
// FROM HASH: 3651496131015f36e306c394bb8a633a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->method($__vars['font'], 'isInsert', array())) {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Add font');
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	';
		$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit font' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['font']['title']));
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto+Mono|Roboto:400,500" />
';
	$__templater->includeCss('kl_em_font_edit.less');
	$__finalCompiled .= '
';
	$__templater->includeCss('public:bb_code.less');
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'editor-manager/edit-font.js',
		'min' => '1',
		'addon' => 'KL/EditorManager',
	));
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['font'], 'isUpdate', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('em/fonts/delete', $__vars['font'], ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__compilerTemp1 = array(array(
		'value' => '',
		'label' => '-Chose file-',
		'_type' => 'option',
	));
	if ($__templater->isTraversable($__vars['files'])) {
		foreach ($__vars['files'] AS $__vars['name'] => $__vars['infos']) {
			$__compilerTemp1[] = array(
				'value' => $__vars['name'],
				'label' => $__templater->escape($__vars['name']) . ' ' . $__templater->escape($__vars['infos']['typeString']),
				'_type' => 'option',
			);
		}
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">

		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'font_id',
		'required' => 'required',
		'value' => $__vars['font']['font_id'],
		'maxlength' => $__templater->fn('max_length', array($__vars['font'], 'font_id', ), false),
	), array(
		'label' => 'Font ID',
	)) . '

			' . $__templater->formTextBoxRow(array(
		'name' => 'title',
		'required' => 'required',
		'value' => ($__templater->method($__vars['font'], 'exists', array()) ? $__vars['font']['title'] : ''),
	), array(
		'label' => 'Title',
	)) . '

			' . $__templater->formRadioRow(array(
		'name' => 'type',
		'value' => ($__vars['font']['font_id'] ? $__vars['font']['type'] : 'client'),
	), array(array(
		'value' => 'client',
		'label' => 'Clientside',
		'_type' => 'option',
	),
	array(
		'value' => 'upload',
		'label' => 'Serverside',
		'_type' => 'option',
	),
	array(
		'value' => 'web',
		'label' => 'External (web)',
		'_type' => 'option',
	)), array(
		'label' => 'Type',
	)) . '
			
			' . $__templater->formTextBoxRow(array(
		'name' => 'family',
		'required' => 'required',
		'value' => ($__templater->method($__vars['font'], 'exists', array()) ? $__vars['font']['family'] : ''),
	), array(
		'label' => 'Font family',
	)) . '

			<hr class="formRowSep" />
			<div id="container-client" style="' . ($__vars['font']['font_id'] ? (($__vars['font']['type'] == 'client') ? '' : 'display: none;') : '') . '">
				<dl class="formRow formRow--input">
					<dt></dt>
					<dd>
						<p>' . 'Clientside fonts are fonts, that are already available on your users devices. The advantage is clearly, that they do not need to be downloaded to the device, when the page is loaded. However, this brings a severe disadvantage: If a user does not already have the font, it cannot be rendered for him. If none of the fonts in the font stack is available to him, his system will use the default font instead. It is recommended to carefully consider the font collection before chosing this option.' . '</p>
						<h3>' . 'Web safe font stacks' . '</h3>
						<p>' . 'In the following you find a list of font stacks, that are so widely spread, that the likelyhood of one of your users not having the font is very low. Due to this circumstance, they\'re considered to be <strong>web safe</strong> - safe to be used on your website.' . '</p>
						<h4>Sans Serif</h4>
						<dl><dt style=\'font-family: Arial,"Helvetica Neue",Helvetica,sans-serif\'>Arial</dt><dd><pre>Arial,"Helvetica Neue",Helvetica,sans-serif</pre></dd></dl>
						<dl><dt style=\'font-family: "Arial Black","Arial Bold",Gadget,sans-serif\'>Arial Black</dt><dd><pre>"Arial Black","Arial Bold",Gadget,sans-serif</pre></dd></dl>
						<dl><dt style=\'font-family: "Arial Narrow",Arial,sans-serif\'>Arial Narrow</dt><dd><pre>"Arial Narrow",Arial,sans-serif</pre></dd></dl>
						<dl><dt style=\'font-family: Tahoma,Verdana,Segoe,sans-serif\'>Tahoma</dt><dd><pre>Tahoma,Verdana,Segoe,sans-serif</pre></dd></dl>
						<dl><dt style=\'font-family: "Trebuchet MS","Lucida Grande","Lucida Sans Unicode","Lucida Sans",Tahoma,sans-serif\'>Trebuchet MS</dt><dd><pre>"Trebuchet MS","Lucida Grande","Lucida Sans Unicode","Lucida Sans",Tahoma,sans-serif</pre></dd></dl>
						<dl><dt style=\'font-family: Verdana,Geneva,sans-serif\'>Verdana</dt><dd><pre>Verdana,Geneva,sans-serif</pre></dd></dl>
						<h4>Serif</h4>
						<dl><dt style=\'font-family: Georgia,Times,"Times New Roman",serif\'>Georgia</dt><dd><pre>Georgia,Times,"Times New Roman",serif</pre></dd></dl>
						<dl><dt style=\'font-family: "Lucida Bright",Georgia,serif\'>Lucida Bright</dt><dd><pre>"Lucida Bright",Georgia,serif</pre></dd></dl>
						<dl><dt style=\'font-family: Palatino,"Palatino Linotype","Palatino LT STD","Book Antiqua",Georgia,serif\'>Palatino</dt><dd><pre>Palatino,"Palatino Linotype","Palatino LT STD","Book Antiqua",Georgia,serif</pre></dd></dl>
						<dl><dt style=\'font-family: TimesNewRoman,"Times New Roman",Times,Baskerville,Georgia,serif\'>Times New Roman</dt><dd><pre>TimesNewRoman,"Times New Roman",Times,Baskerville,Georgia,serif</pre></dd></dl>
						<h4>Monospace</h4>
						<dl><dt style=\'font-family: "Courier New",Courier,"Lucida Sans Typewriter","Lucida Typewriter",monospace\'>Courier New</dt><dd><pre>"Courier New",Courier,"Lucida Sans Typewriter","Lucida Typewriter",monospace</pre></dd></dl>
						<dl><dt style=\'font-family: "Lucida Sans Typewriter","Lucida Console",monaco,"Bitstream Vera Sans Mono",monospace\'>Lucida Sans Typewriter</dt><dd><pre>"Lucida Sans Typewriter","Lucida Console",monaco,"Bitstream Vera Sans Mono",monospace</pre></dd></dl>
					</dd>
				</dl>
			</div>
			<div id="container-upload" style="' . (($__vars['font']['type'] == 'upload') ? '' : 'display: none;') . '">
				<dl class="formRow formRow--input">
					<dt></dt>
					<dd>
						<p>' . 'Serverside fonts are hosted directly from your server. You will have to manually upload these fonts to the <code class="bbCodeInline">data/fonts/</code>-directory inside your XenForo installation. Supported file types are <code class="bbCodeInline">woff2, woff, ttf, otf, eot & svg</code>. It is recommended, to provide a <code class="bbCodeInline">woff2</code> file. Your uploaded files will be matched into a set by the system and will be listed below. Ensure, that they all share the same name in order to have them listed in a single group. You will have to resave the font, if you decide to upload additional file types later on. The filename will match the font family.' . '</p>
					</dd>
				</dl>
				' . $__templater->formRow('
					' . $__templater->formSelect(array(
		'name' => 'file',
		'value' => $__vars['font']['extra_data']['filename'],
	), $__compilerTemp1) . '
				', array(
		'rowtype' => 'input',
		'label' => 'File',
	)) . '
			</div>
			<div id="container-web" style="' . (($__vars['font']['type'] == 'web') ? '' : 'display: none;') . '">
				<dl class="formRow formRow--input">
					<dt></dt>
					<dd>
						<p>' . 'External fonts are fonts, that are neither already on your clients device nor hosted on your own server. They are resources, that are located somewhere else on the web. The main advantages of using these fonts are the large choice of available fonts from different hosters, the bandwidth you save by not having to provide them to the users yourself and the likelyhood of those fonts already being in the cache of your users from a different website they visited before.' . '</p>
					</dd>
				</dl>
				' . $__templater->formRow('
					' . $__templater->formSelect(array(
		'name' => 'web_service',
		'value' => ($__vars['font']['font_id'] ? $__vars['font']['extra_data']['web_service'] : 'gfonts'),
	), array(array(
		'value' => 'gfonts',
		'label' => 'Fonts.Google.com',
		'_type' => 'option',
	),
	array(
		'value' => 'typekit',
		'label' => 'Typekit.com',
		'_type' => 'option',
	),
	array(
		'value' => 'webtype',
		'label' => 'Webtype.com',
		'_type' => 'option',
	),
	array(
		'value' => 'fonts',
		'label' => 'Fonts.com',
		'_type' => 'option',
	))) . '
				', array(
		'rowtype' => 'input',
		'label' => 'Hosting service',
	)) . '
				
				' . $__templater->formTextBoxRow(array(
		'name' => 'web_url',
		'value' => $__vars['font']['extra_data']['web_url'],
	), array(
		'label' => 'URL',
	)) . '
				
				<dl class="formRow formRow--input">
					<dt>
					</dt>
					<dd>
						<p style="margin-top: -20px">' . 'Where to find the URL:' . '</p>
						<div id="examples">
							<div id="example-gfonts" class="' . (($__vars['font']['font_id'] AND ($__vars['font']['type'] === 'web')) ? (($__vars['font']['extra_data']['web_service'] == 'gfonts') ? 'active' : '') : 'active') . '">
								<section class="collection-drawer-section">
									<h2 class="collection-drawer-title">Embed Font</h2>
									<p class="collection-drawer-help-text"> To embed your selected fonts into a webpage, copy this code into the <code>&lt;head&gt;</code> of your HTML document. </p>
									<div class="link-bar">
										<a class="link-bar-link">STANDARD</a> <a class="link-bar-link link-is-inactive">@IMPORT</a>
									</div>
									<div ng-switch="embedCode.embedStyle">
										<div class="code-block" style="">&lt;link href="<strong>https://fonts.googleapis.com/css?family=Roboto</strong>" rel="stylesheet"&gt;
										</div>
									</div>
								</section>
							</div>
							<div id="example-typekit" class="' . (($__vars['font']['extra_data']['web_service'] == 'typekit') ? 'active' : '') . '">
								<div>
									<ul class="neue-tabs">
									  <li class="neue-tabs__tab neue-tabs__tab--active">
										<span>Default</span>
									  </li>
									  <li class="neue-tabs__tab">
										<span>Advanced</span>
									  </li>
									</ul>
									  <pre class="neue-family-font-details__pre"><code>&lt;script src="<strong>https://use.typekit.net/ero6oyp.js</strong>"&gt;&lt;/script&gt;<br>&lt;script&gt;try{Typekit.load({ async: true });}catch(e){}&lt;/script&gt;</code></pre>
									<p>
										The default embed code is simple and easy to use. It does a good job of hiding the flash of unstyled text by blocking rendering while loading. <span class="a">Learn more</span>.
									</p>
								  </div>
							</div>
							<div id="example-webtype" class="' . (($__vars['font']['extra_data']['web_service'] == 'webtype') ? 'active' : '') . '">
								<div class="clearafter" style=" background:#CCCCCC; padding:15px;">
									<div>
										<p><b>Resource Code:</b>
											Copy &amp; paste in the &lt;head&gt;
											tag of each page you want to use the Resource.
										</p>
										<div class="text-area">
											&lt;link href="<strong>//cloud.webtype.com/css/47743fd5-0482-4c57-9220-ed5734160876.css</strong>" rel="stylesheet" type="text/css" /&gt;
										</div>
									</div>
								</div>
							</div>
							<div id="example-fonts" class="' . (($__vars['font']['extra_data']['web_service'] == 'fonts') ? 'active' : '') . '">
								<div class="with-border">
									<p>
										Copy the code below and paste it into your website\'s HTML
										between the &lt;head&gt; and &lt;/head&gt; tags.
										<b>The code only needs to be pasted once.</b>
										Subsequent changes to your style sheet will automatically
										be reflected on your webpage without modifying the code.
									</p>
									<div class="text-area">
										&lt;script type="text/javascript" src="<strong>//fast.fonts.net/jsapi/8f77360e-33b9-4143-8842-2dcfc7f8480f.js</strong>"&gt;&lt;/script&gt;
									</div>
									<a class="link-action">Select code</a>
								</div>
							</div>
						</div>
					</dd>
				</dl>
			</div>			
			<hr class="formRowSep" />
			
			' . $__templater->callMacro('display_order_macros', 'row', array(
		'name' => 'display_order',
		'value' => $__vars['font']['display_order'],
		'explain' => 'The position of this item.',
	), $__vars) . '
					
			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'active',
		'value' => '1',
		'selected' => ($__vars['font']['font_id'] ? $__vars['font']['active'] : 1),
		'label' => '
					' . 'Enabled' . '
				',
		'_type' => 'option',
	)), array(
	)) . '
			
			' . $__templater->formSubmitRow(array(
		'sticky' => 'true',
		'icon' => 'save',
	), array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('em/fonts/save', $__vars['font'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});