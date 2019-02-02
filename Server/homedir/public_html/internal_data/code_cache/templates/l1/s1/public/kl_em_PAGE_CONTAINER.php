<?php
// FROM HASH: ae1fba4e1eca800922c12a9d7affeefb
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['em_gfonts']) {
		$__finalCompiled .= '
 	<link rel="preload" href="' . $__templater->escape($__vars['em_gfonts']) . '" as="style" crossorigin="anonymous">
	<link rel="stylesheet" href="' . $__templater->escape($__vars['em_gfonts']) . '">
';
	}
	$__finalCompiled .= '

';
	if ($__templater->isTraversable($__vars['em_typekit'])) {
		foreach ($__vars['em_typekit'] AS $__vars['font']) {
			$__finalCompiled .= '
	<link rel="preload" href="https://use.typekit.net/' . $__templater->escape($__vars['font']) . '.js" as="script" crossorigin="anonymous">
	<script>
	  (function(d) {
		var config = {
		  kitId: \'' . $__templater->escape($__vars['font']) . '\',
		  scriptTimeout: 3000,
		  async: true
		},
		h=d.documentElement,t=setTimeout(function(){h.className=h.className.replace(/\\bwf-loading\\b/g,"")+" wf-inactive";},config.scriptTimeout),tk=d.createElement("script"),f=false,s=d.getElementsByTagName("script")[0],a;h.className+=" wf-loading";tk.src=\'https://use.typekit.net/\'+config.kitId+\'.js\';tk.async=true;tk.onload=tk.onreadystatechange=function(){a=this.readyState;if(f||a&&a!="complete"&&a!="loaded")return;f=true;clearTimeout(t);try{Typekit.load(config)}catch(e){}};s.parentNode.insertBefore(tk,s)
	  })(document);
	</script>
';
		}
	}
	$__finalCompiled .= '

';
	if ($__templater->isTraversable($__vars['em_webtype'])) {
		foreach ($__vars['em_webtype'] AS $__vars['font']) {
			$__finalCompiled .= '
 	<link rel="preload" href="https://cloud.webtype.com/css/' . $__templater->escape($__vars['font']) . '.css" as="style" crossorigin="anonymous">
	<link rel="stylesheet" href="https://cloud.webtype.com/css/' . $__templater->escape($__vars['font']) . '.css">
';
		}
	}
	$__finalCompiled .= '

';
	if ($__templater->isTraversable($__vars['em_fonts'])) {
		foreach ($__vars['em_fonts'] AS $__vars['font']) {
			$__finalCompiled .= '
 	<link rel="preload" href="https://fast.fonts.net/jsapi/' . $__templater->escape($__vars['font']) . '.js" as="script" crossorigin="anonymous">
	<script src="https://fast.fonts.net/jsapi/' . $__templater->escape($__vars['font']) . '.js"></script>
';
		}
	}
	$__finalCompiled .= '

';
	if ($__vars['em_serverFonts']) {
		$__finalCompiled .= '
	<style>
		';
		if ($__templater->isTraversable($__vars['em_serverFonts'])) {
			foreach ($__vars['em_serverFonts'] AS $__vars['font']) {
				$__finalCompiled .= '
			@font-face {
				font-family: \'' . $__templater->filter($__vars['font']['filename'], array(array('raw', array()),), true) . '\';
				src: ' . $__templater->filter($__vars['font']['src'], array(array('raw', array()),), true) . ';
				font-weight: normal;
				font-style: normal;
			}
		';
			}
		}
		$__finalCompiled .= '
	</style>
';
	}
	return $__finalCompiled;
});