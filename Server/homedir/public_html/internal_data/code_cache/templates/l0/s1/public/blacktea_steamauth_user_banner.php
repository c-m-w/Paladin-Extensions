<?php
// FROM HASH: 784dd5191881755435d61a991ef3ff34
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('blacktea_steamauth_user_banner.less');
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'blacktea/steamauth/userbanner.js',
		'addon' => 'BlackTea/SteamAuth',
	));
	$__finalCompiled .= '
<a class="steam-user steam-user-banner"
   data-steamid="' . $__templater->escape($__vars['steamid']) . '"
   href="https://steamcommunity.com/profiles/' . $__templater->escape($__vars['steamid']) . '/"
   target="_blank"></a>';
	return $__finalCompiled;
});