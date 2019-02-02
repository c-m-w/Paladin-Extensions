<?php
// FROM HASH: 279f90fa31af185661786ab7be5ffe37
return array('macros' => array('row_output' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'title' => '!',
		'desc' => '!',
		'example' => '!',
		'anchor' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="' . $__templater->escape($__vars['anchor']) . '"></span>
		<h3 class="block-textHeader">' . $__templater->escape($__vars['title']) . '</h3>
		<div>' . $__templater->escape($__vars['desc']) . '</div>
		' . $__templater->callMacro(null, 'example_output', array(
		'bbCode' => $__vars['example'],
	), $__vars) . '
	</li>
';
	return $__finalCompiled;
},
'example_output' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'bbCode' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="bbCodeDemoBlock">
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd>' . $__templater->filter($__vars['bbCode'], array(array('nl2br', array()),), true) . '</dd>
		</dl>
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd>' . $__templater->fn('bb_code', array($__vars['bbCode'], 'help', null, ), true) . '</dd>
		</dl>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ((($__vars['enabled_bb_codes']['bold'] OR $__vars['enabled_bb_codes']['italic']) OR $__vars['enabled_bb_codes']['underline']) OR $__vars['enabled_bb_codes']['strike']) {
		$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="basic"></span>
		<h3 class="block-textHeader">
			';
		if ($__vars['enabled_bb_codes']['bold']) {
			$__finalCompiled .= '[B]';
			if (($__vars['enabled_bb_codes']['italic'] OR $__vars['enabled_bb_codes']['underline']) OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['italic']) {
			$__finalCompiled .= '[I]';
			if ($__vars['enabled_bb_codes']['underline'] OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['underline']) {
			$__finalCompiled .= '[U]';
			if ($__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['strike']) {
			$__finalCompiled .= '[S]';
		}
		$__finalCompiled .= '
			' . '-' . '
			';
		if ($__vars['enabled_bb_codes']['bold']) {
			$__finalCompiled .= 'bold';
			if (($__vars['enabled_bb_codes']['italic'] OR $__vars['enabled_bb_codes']['underline']) OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['italic']) {
			$__finalCompiled .= 'Italic';
			if ($__vars['enabled_bb_codes']['underline'] OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['underline']) {
			$__finalCompiled .= 'Underline';
			if ($__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['strike']) {
			$__finalCompiled .= 'Struck-through';
		}
		$__finalCompiled .= '
		</h3>
		<div>' . 'Applies basic formatting to the wrapped text.' . '</div>
		<div class="bbCodeDemoBlock">
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['bold']) {
			$__finalCompiled .= 'This is [B]bold[/B] text.';
			if (($__vars['enabled_bb_codes']['italic'] OR $__vars['enabled_bb_codes']['underline']) OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['italic']) {
			$__finalCompiled .= 'This is [I]italic[/I] text.';
			if ($__vars['enabled_bb_codes']['underline'] OR $__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['underline']) {
			$__finalCompiled .= 'This is [U]underlined[/U] text.';
			if ($__vars['enabled_bb_codes']['strike']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['strike']) {
			$__finalCompiled .= 'This is [S]struck-through[/S] text.';
		}
		$__finalCompiled .= '
				</dd>
			</dl>
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['bold']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [B]bold[/B] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['italic']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [I]italic[/I] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['underline']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [U]underlined[/U] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['strike']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [S]struck-through[/S] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
				</dd>
			</dl>
		</div>
	</li>
';
	}
	$__finalCompiled .= '

';
	if ((($__vars['enabled_bb_codes']['color'] OR $__vars['enabled_bb_codes']['bgcolor']) OR $__vars['enabled_bb_codes']['font']) OR $__vars['enabled_bb_codes']['size']) {
		$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="style"></span>
		<h3 class="block-textHeader">
			';
		if ($__vars['enabled_bb_codes']['color']) {
			$__finalCompiled .= '[COLOR=<span class="block-textHeader-highlight">color</span>]';
			if (($__vars['enabled_bb_codes']['bgcolor'] OR $__vars['enabled_bb_codes']['size']) OR $__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['bgcolor']) {
			$__finalCompiled .= '[BGCOLOR=<span class="block-textHeader-highlight">color</span>]';
			if ($__vars['enabled_bb_codes']['size'] OR $__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['font']) {
			$__finalCompiled .= '[FONT=<span class="block-textHeader-highlight">name</span>]';
			if ($__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['size']) {
			$__finalCompiled .= '[SIZE=<span class="block-textHeader-highlight">size</span>]';
		}
		$__finalCompiled .= '
			' . '-' . '
			';
		if ($__vars['enabled_bb_codes']['bgcolor']) {
			$__finalCompiled .= 'Background color';
			if (($__vars['enabled_bb_codes']['bgcolor'] OR $__vars['enabled_bb_codes']['size']) OR $__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['color']) {
			$__finalCompiled .= 'Text color';
			if ($__vars['enabled_bb_codes']['size'] OR $__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['font']) {
			$__finalCompiled .= 'Font';
			if ($__vars['enabled_bb_codes']['font']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['size']) {
			$__finalCompiled .= 'Size';
		}
		$__finalCompiled .= '
		</h3>
		<div>' . 'Applies advanced formatting to the wrapped text.' . '</div>
		<div class="bbCodeDemoBlock">
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['color']) {
			$__finalCompiled .= 'This is [COLOR=red]red[/COLOR] and [COLOR=#0000cc]blue[/COLOR] text.';
			if (($__vars['enabled_bb_codes']['bgcolor'] OR $__vars['enabled_bb_codes']['font']) OR $__vars['enabled_bb_codes']['size']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['bgcolor']) {
			$__finalCompiled .= 'This is text with [BGCOLOR=#ffaaaa]red[/BGCOLOR] and [BGCOLOR=#aaaaff]blue[/BGCOLOR] background.';
			if ($__vars['enabled_bb_codes']['font'] OR $__vars['enabled_bb_codes']['size']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['font']) {
			$__finalCompiled .= 'This is [FONT=Courier New]Courier New[/FONT] text.';
			if ($__vars['enabled_bb_codes']['size']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['size']) {
			$__finalCompiled .= 'This is [SIZE=1]small[/SIZE] and [SIZE=' . $__templater->escape($__vars['max_font_size']) . ']big[/SIZE] text.';
		}
		$__finalCompiled .= '
				</dd>
			</dl>
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['color']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [COLOR=red]red[/COLOR] and [COLOR=#0000cc]blue[/COLOR] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['bgcolor']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is text with [BGCOLOR=#ffaaaa]red[/BGCOLOR] and [BGCOLOR=#aaaaff]blue[/BGCOLOR] background.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['font']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [FONT=Courier New]Courier New[/FONT] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['size']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This is [SIZE=1]small[/SIZE] and [SIZE=' . $__vars['max_font_size'] . ']big[/SIZE] text.', 'help', null, ), true);
		}
		$__finalCompiled .= '
				</dd>
			</dl>
		</div>
	</li>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['sub'] OR $__vars['enabled_bb_codes']['sup']) {
		$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="style"></span>
		<h3 class="block-textHeader">
			';
		if ($__vars['enabled_bb_codes']['sub']) {
			$__finalCompiled .= '[SUB]';
			if ($__vars['enabled_bb_codes']['sup']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['sup']) {
			$__finalCompiled .= '[SUP]';
		}
		$__finalCompiled .= '
			' . '-' . '
			';
		if ($__vars['enabled_bb_codes']['sub']) {
			$__finalCompiled .= 'Subscript';
			if ($__vars['enabled_bb_codes']['sup']) {
				$__finalCompiled .= ',';
			}
		}
		$__finalCompiled .= '
			';
		if ($__vars['enabled_bb_codes']['sup']) {
			$__finalCompiled .= 'Superscript';
		}
		$__finalCompiled .= '
		</h3>
		<div>' . 'Offset wrapped text.' . '</div>
		<div class="bbCodeDemoBlock">
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['sub']) {
			$__finalCompiled .= 'This text contains [SUB]subscript[/SUB].';
			if ($__vars['enabled_bb_codes']['sup']) {
				$__finalCompiled .= '<br />';
			}
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['sup']) {
			$__finalCompiled .= 'This text contains [SUP]superscript[/SUP].';
		}
		$__finalCompiled .= '
				</dd>
			</dl>
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>
					';
		if ($__vars['enabled_bb_codes']['sub']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This text contains [SUB]subscript[/SUB].', 'help', null, ), true);
		}
		$__finalCompiled .= '
					';
		if ($__vars['enabled_bb_codes']['sup']) {
			$__finalCompiled .= $__templater->fn('bb_code', array('This text contains [SUP]superscript[/SUP].', 'help', null, ), true);
		}
		$__finalCompiled .= '
					</dd>
			</dl>
		</div>
	</li>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['url']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[URL], [EMAIL] - Linking', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Creates a link using the wrapped text as the target.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[URL]https://www.example.com[/URL]
[EMAIL]example@example.com[/EMAIL]', array(array('preEscaped', array()),), false),
			'anchor' => 'email-url',
		), $__vars) . '

	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[URL=<span class="block-textHeader-highlight">link</span>], [EMAIL=<span class="block-textHeader-highlight">address</span>] - Linking (Advanced)', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Links the wrapped text to the specified web page or email address.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[URL=https://www.example.com]Go to example.com[/URL]
[EMAIL=example@example.com]Email me[/EMAIL]', array(array('preEscaped', array()),), false),
			'anchor' => 'email-url-advanced',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro(null, 'row_output', array(
		'title' => $__templater->filter('[USER=<span class="block-textHeader-highlight">ID</span>] - Profile Linking', array(array('preEscaped', array()),), false),
		'desc' => $__templater->filter('Links to a user\'s profile. This is generally inserted automatically when mentioning a user.', array(array('preEscaped', array()),), false),
		'example' => $__templater->filter('[USER=' . ($__vars['xf']['visitor']['user_id'] ? $__vars['xf']['visitor']['user_id'] : '1') . ']' . ($__vars['xf']['visitor']['user_id'] ? $__vars['xf']['visitor']['username'] : 'User name') . '[/USER]', array(array('preEscaped', array()),), false),
		'anchor' => 'user-mention',
	), $__vars) . '

';
	if ($__vars['enabled_bb_codes']['img']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[IMG] - Image', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Display an image, using the wrapped text as the URL.', array(array('preEscaped', array()),), false),
			'example' => '[IMG]' . $__templater->fn('base_url', array(($__templater->fn('property', array('publicMetadataLogoUrl', ), false) ?: $__templater->fn('property', array('publicLogoUrl', ), false)), true, ), false) . '[/IMG]',
			'anchor' => 'image',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['video']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[VIDEO] - Video', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Displays a video, using the wrapped text as the URL.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[VIDEO]' . ($__templater->fn('link', array('canonical:styles/editor-manager', ), false) . '/missing-video.mp3') . '[/VIDEO]

[VIDEO=\'width:300\']' . ($__templater->fn('link', array('canonical:styles/editor-manager', ), false) . '/missing-video.mp3') . '[/VIDEO]', array(array('preEscaped', array()),), false),
			'anchor' => 'video',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['audio']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[AUDIO] - Audio', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Displays an audio player, using the wrapped text as URL.', array(array('preEscaped', array()),), false),
			'example' => '[AUDIO]' . $__templater->fn('link', array('canonical:styles/editor-manager', ), false) . '/missing-audio.mp3[/AUDIO]',
			'anchor' => 'audio',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['media']) {
		$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="media"></span>
		<h3 class="block-textHeader">' . '[MEDIA=<span class="block-textHeader-highlight">site</span>] - Embedded Media' . '</h3>
		<div>
			' . 'Embeds media from approved sites into your message. It is recommended that you use the media button in the editor tool bar.' . '<br />
			' . 'Approved sites' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->fn('media_sites', array(), true) . '
		</div>
		<div class="bbCodeDemoBlock">
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>[MEDIA=youtube]oHg5SJYRHA0[/MEDIA]</dd>
			</dl>
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd><i>' . 'An embedded YouTube player would appear here.' . '</i></dd>
			</dl>
		</div>
	</li>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['list']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[LIST] - Lists', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Displays a bulleted or numbered list.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[LIST]
[*]Bullet 1
[*]Bullet 2
[/LIST]
[LIST=1]
[*]Entry 1
[*]Entry 2
[/LIST]', array(array('preEscaped', array()),), false),
			'anchor' => 'list',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['align']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[LEFT], [CENTER], [RIGHT], [JUSTIFY] - Text alignment', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Changes the alignment of the wrapped text.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[LEFT]Left-aligned[/LEFT]
[CENTER]Center-aligned[/CENTER]
[RIGHT]Right-aligned[/RIGHT]
[JUSTIFY]This is a justified text block with a long content to demonstrate the justification.[/JUSTIFY]', array(array('preEscaped', array()),), false),
			'anchor' => 'align',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['quote']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[QUOTE] - Quoted text', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Displays text that has been quoted from another source. You may also attribute the name of the source.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[QUOTE]Quoted text[/QUOTE]
[QUOTE=A person]Something they said[/QUOTE]', array(array('preEscaped', array()),), false),
			'anchor' => 'quote',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['spoiler']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[SPOILER] - Text containing spoilers', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Hides text that may contain spoilers so that it must be clicked by the viewer to be seen.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[SPOILER]Simple spoiler[/SPOILER]
[SPOILER=Spoiler Title]Spoiler with a title[/SPOILER]', array(array('preEscaped', array()),), false),
			'anchor' => 'spoiler',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['ispoiler']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[ISPOILER] - Inline text containing spoilers', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Hides text that may contain spoilers so that it must be clicked by the viewer to be seen.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('This is a [ISPOILER]Simple spoiler[/ISPOILER].
This is a [ISPOILER=Spoiler]with a title[/ISPOILER].', array(array('preEscaped', array()),), false),
			'anchor' => 'ispoiler',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['code']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[CODE] - Programming code display', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Displays text in one of several programming languages, highlighting the syntax where possible.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('General code:
[CODE]General
code[/CODE]

Rich code:
[CODE=rich][COLOR=red]Rich[/COLOR]
code[/CODE]

PHP code:
[CODE=php]echo $hello . \' world\';[/CODE]

JS code:
[CODE=javascript]var hello = \'world\';[/CODE]', array(array('preEscaped', array()),), false),
			'anchor' => 'code',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['icode']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[ICODE] - Inline programming code display', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Allows you to display code inline among normal post content. Syntax will not be highlighted.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('Inline code blocks [ICODE]are a convenient way[/ICODE] of displaying code inline.', array(array('preEscaped', array()),), false),
			'anchor' => 'icode',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['table']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[TABLE], [TR], [TH], [TD] - Tables', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Use [TR] tags to start new rows inside a table tag. Use [TD] tags to start new cells inside row tags. Use [TH] to start new table header cells inside table rows.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[TABLE]
[TR]
[TH]Header 1[/TH]
[TH]Header 2[/TH]
[/TR]
[TR]
[TD]Cell 1 1[/TD]
[TD]Cell 1 2[/TD]
[/TR]
[TR]
[TD]Cell 2 1[/TD]
[TD]Cell 2 2[/TD]
[/TR]
[/TABLE]', array(array('preEscaped', array()),), false),
			'anchor' => 'table',
		), $__vars) . '

	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[TH=<span class="block-textHeader-highlight">vertical align</span>], [TD=<span class="block-textHeader-highlight">vertical align</span>] - Tables (Advanced)', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Changes vertical align of table cells and table header cells.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[TABLE][TR]
[TD]1
2
3[/TD][TD=top]Top[/TD]
[TD=middle]Middle[/TD]
[TD=bottom]Bottom[/TD]
[/TR][/TABLE]', array(array('preEscaped', array()),), false),
			'anchor' => 'table',
		), $__vars) . '

	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[TABLE=class] - Tables (Advanced)', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Changes the appearance of tables depending on the classes chosen. Multiple classes can be used, separated by a space.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[TABLE=nofullwidth]
[TR][TD]A table that is not full width[/TD][/TR][/TABLE]

[TABLE=center-nofullwidth]
[TR][TD]A centered table.[/TD][/TR][/TABLE]

[TABLE=right-nofullwidth]
[TR][TD]A right aligned table.[/TD][/TR][/TABLE]

[TABLE=noborder]
[TR][TD]A table with no border.[/TD][/TR][/TABLE]

[TABLE=nobackground]
[TR][TD]A table that[/TD][/TR][TR][TD]doesn\'t color rows differently[/TD][/TR][/TABLE]

[TABLE=collapse]
[TR][TD]A table that[/TD][TD] has non-equal width columns.[/TD][/TR][/TABLE]', array(array('preEscaped', array()),), false),
			'anchor' => 'table',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__vars['enabled_bb_codes']['list']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[INDENT] - Text indent', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Indents the wrapped text. This can be nested for larger indentings.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('Regular text
[INDENT]Indented text[/INDENT]
[INDENT=2]More indented[/INDENT]', array(array('preEscaped', array()),), false),
			'anchor' => 'indent',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

' . $__templater->callMacro(null, 'row_output', array(
		'title' => $__templater->filter('[PLAIN] - Plain text', array(array('preEscaped', array()),), false),
		'desc' => $__templater->filter('Disables BB code translation on the wrapped text.', array(array('preEscaped', array()),), false),
		'example' => $__templater->filter('[PLAIN]This is not [B]bold[/B] text.[/PLAIN]', array(array('preEscaped', array()),), false),
		'anchor' => 'plain',
	), $__vars) . '

<li class="bbCodeHelpItem block-row block-row--separated">
	<span class="u-anchorTarget" id="attach"></span>
	<h3 class="block-textHeader">' . '[ATTACH] - Attachment insertion' . '</h3>
	<div>' . 'Inserts an attachment at the specified point. If the attachment is an image, a thumbnail or full size version will be inserted. This will generally be inserted by clicking the appropriate button.' . '</div>
	<div class="bbCodeDemoBlock">
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd>
				' . 'Thumbnail' . $__vars['xf']['language']['label_separator'] . ' [ATTACH]123[/ATTACH]<br />
				' . 'Full size' . $__vars['xf']['language']['label_separator'] . ' [ATTACH=full]123[/ATTACH]
			</dd>
		</dl>
		<dl class="bbCodeDemoBlock-item">
			<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
			<dd><i>' . 'The contents of the attachments would appear here.' . '</i></dd>
		</dl>
	</div>
</li>

';
	if ($__vars['enabled_bb_codes']['hide']) {
		$__finalCompiled .= '
	' . $__templater->callMacro(null, 'row_output', array(
			'title' => $__templater->filter('[HIDE], [HIDEREPLY], [HIDETHANKS], [HIDEPOSTS], [HIDEREPLYPOSTS] - Hide content from users', array(array('preEscaped', array()),), false),
			'desc' => $__templater->filter('Hide content from users depending on various circumstances. [HIDEREPLY] - Hides content until user has replied to the subject. [HIDETHANKS] - Hides content until user has liked the content. [HIDEREPLYTHANKS] - Hides content until user has replied to the subject or liked the content. [HIDEPOSTS] - Hides content until user has a certain number of posts. [HIDE] - Works like ' . $__vars['hide'] . '.', array(array('preEscaped', array()),), false),
			'example' => $__templater->filter('[HIDE]You can view this content.[/HIDE]
[HIDEREPLY]You can view this content.[/HIDEREPLY]
[HIDETHANKS]You can view this content.[/HIDETHANKS]
[HIDEREPLYTHANKS]You can view this content.[/HIDEREPLYTHANKS]
[HIDEPOSTS]You can view this content.[/HIDEPOSTS]', array(array('preEscaped', array()),), false),
			'anchor' => 'indent',
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->isTraversable($__vars['bbCodes'])) {
		foreach ($__vars['bbCodes'] AS $__vars['bbCode']) {
			if (!$__templater->test($__vars['bbCode']['example'], 'empty', array())) {
				$__finalCompiled .= '
	<li class="bbCodeHelpItem block-row block-row--separated">
		<span class="u-anchorTarget" id="' . $__templater->escape($__vars['bbCode']['bb_code_id']) . '"></span>
		<h3 class="block-textHeader">
			';
				if (($__vars['bbCode']['has_option'] == 'no') OR ($__vars['bbCode']['has_option'] == 'optional')) {
					$__finalCompiled .= '[' . $__templater->filter($__vars['bbCode']['bb_code_id'], array(array('to_upper', array()),), true) . ']';
				}
				$__finalCompiled .= '
			';
				if ($__vars['bbCode']['has_option'] == 'optional') {
					$__finalCompiled .= '<span role="presentation" aria-hidden="true">&middot;</span>';
				}
				$__finalCompiled .= '
			';
				if (($__vars['bbCode']['has_option'] == 'yes') OR ($__vars['bbCode']['has_option'] == 'optional')) {
					$__finalCompiled .= '[' . $__templater->filter($__vars['bbCode']['bb_code_id'], array(array('to_upper', array()),), true) . '=<span class="block-textHeader-highlight">option</span>]';
				}
				$__finalCompiled .= '
			- ' . $__templater->escape($__vars['bbCode']['title']) . '
		</h3>
		';
				$__compilerTemp1 = '';
				$__compilerTemp1 .= $__templater->escape($__vars['bbCode']['description']);
				if (strlen(trim($__compilerTemp1)) > 0) {
					$__finalCompiled .= '
			<div>' . $__compilerTemp1 . '</div>
		';
				}
				$__finalCompiled .= '
		<div class="bbCodeDemoBlock">
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Example' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>' . $__templater->filter($__vars['bbCode']['example'], array(array('nl2br', array()),), true) . '</dd>
			</dl>
			<dl class="bbCodeDemoBlock-item">
				<dt>' . 'Output' . $__vars['xf']['language']['label_separator'] . '</dt>
				<dd>' . (!$__templater->test($__vars['bbCode']['output'], 'empty', array()) ? $__templater->escape($__vars['bbCode']['output']) : $__templater->fn('bb_code', array($__vars['bbCode']['example'], 'help', null, ), true)) . '</dd>
			</dl>
		</div>
	</li>
';
			}
		}
	}
	$__finalCompiled .= '


' . '

';
	return $__finalCompiled;
});