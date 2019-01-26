<?php
// FROM HASH: cfc9fda8eda48308d82a66fa1feed494
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('andy_countdown.less');
	$__finalCompiled .= '

<script src="' . $__templater->escape($__vars['xf']['options']['countdownLink']) . '" type="text/javascript"></script>

<div class="block">
<div class="block-container block-container-countdown">
	
';
	if ($__vars['link']) {
		$__finalCompiled .= '
<h3 class="block-minorHeader">
<a href="' . $__templater->escape($__vars['link']) . '">' . $__templater->escape($__vars['title']) . '</a>
</h3>
';
	}
	$__finalCompiled .= '

';
	if (!$__vars['link']) {
		$__finalCompiled .= '
<h3 class="block-minorHeader">
' . $__templater->escape($__vars['title']) . '
</h3>
';
	}
	$__finalCompiled .= '

<div class="block-countdown">
<script type="application/javascript">
var myCountdown = new Countdown(
{
	year: "' . $__templater->escape($__vars['year']) . '",
	month: "' . $__templater->escape($__vars['month']) . '",
	day: "' . $__templater->escape($__vars['day']) . '",
	hour: "' . $__templater->escape($__vars['hour']) . '",
	minute: "' . $__templater->escape($__vars['minute']) . '",
	rangeHi: "month",
	hideLine: true,
	width: 230,
	height: 40,
	padding: 0.8, // sets the text size 
	numbers: 	
	{
		font: "Arial",
		color: "#FFFFFF",
		bkgd: "#176093",
		fontSize: 200,
		rounded: 0.10,	// percentage of size 
		shadow: 
		{
			x : 0,			// x offset (in pixels)
			y : 3,			// y offset (in pixels)
			s : 4,			// spread
			c : "#000000",	// color
			a : 0.4			// alpha	// <- no comma on last item!
		}
	},
	
	labels:
	{
		textScale: 0.8,
		color: "#6CB2E4",
		offset: 5
	} // <- no comma on last item!
	
});
</script>
</div>
</div>
</div>';
	return $__finalCompiled;
});