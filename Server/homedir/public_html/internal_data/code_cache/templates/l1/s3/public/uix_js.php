<?php
// FROM HASH: 5754aad3008d076c63561712dfe92e86
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/global/20171204.js',
		'min' => 'themehouse/global/20171204.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/index.js',
		'min' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/index.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/defer.js',
		'min' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/defer.min.js',
		'defer' => 'defer',
	));
	$__finalCompiled .= '


<script>

/******** extra info post toggle ***********/

$(document).ready(function() {
	$(\'.thThreads__userExtra--trigger\').click(function() {
		var parent =  $(this).parents(\'.message-cell--user\');
	  	var triggerContainer = $(this).parent(\'.thThreads__userExtra--toggle\');
		var container = triggerContainer.siblings(\'.thThreads__message-userExtras\');
		var child = container.find(\'.message-userExtras\');
		var eleHeight = child.height();
		if (parent.hasClass(\'userExtra--expand\')) {
			container.css({ height: eleHeight });
			parent.toggleClass(\'userExtra--expand\');
			window.setTimeout(function() {
				container.css({ height: \'0\' });
				window.setTimeout(function() {
					container.css({ height: \'\' });
				}, 200);
			}, 17);

		} else {
			parent.toggleClass(\'userExtra--expand\');
			container.css({ height: eleHeight });
			window.setTimeout(function() {
				container.css({ height: \'\' });
			}, 200);
		}
	});
});


/******** Backstretch images ***********/

$(document).ready(function() {
	if ( ' . $__templater->fn('property', array('uix_backstretch', ), true) . ' ) {
		 $("' . $__templater->fn('property', array('uix_backstretchSelector', ), true) . '").backstretch([
			 ' . $__templater->fn('property', array('uix_backstretchImages', ), true) . '
	  ], {
			duration: ' . $__templater->fn('property', array('uix_backstretchDuration', ), true) . ',
			fade: ' . $__templater->fn('property', array('uix_backstretchFade', ), true) . '
		});
	}
});
</script>
';
	return $__finalCompiled;
});