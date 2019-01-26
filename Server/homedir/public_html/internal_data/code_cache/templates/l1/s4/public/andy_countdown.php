<?php
// FROM HASH: 2c5580bc0f6da6c822eabbb70b47147e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('andy_countdown.less');
	$__finalCompiled .= '

<script src="' . $__templater->escape($__vars['xf']['options']['countdownLink']) . '" type="text/javascript"></script>

<div class="block">
<div class="block-container block-container-countdown"align="center">
	
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

<div class="block-countdown" style="margin-left: -2em;">
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
	width: 370,
	height: 70,
	padding: 0.75, // sets the text size 
	numbers: 	
	{
		font: "Arial",
		color: "#FFFFFF",
		bkgd: "#2196F3",
		fontSize: 200,
		rounded: 0.20,	// percentage of size 
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
		textScale: 1,
		color: "#2196F3",
		offset: 5
	} // <- no comma on last item!
	
});
</script>
	<a style="color: #383C42">.</a>
</div>
</div>
</div>';
	return $__finalCompiled;
});