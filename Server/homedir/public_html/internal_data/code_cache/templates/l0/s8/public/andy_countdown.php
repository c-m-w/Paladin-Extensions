<?php
// FROM HASH: 9bb29b1062157a0b6564034ec8c762d2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('andy_countdown.less');
	$__finalCompiled .= '
' . $__templater->includeTemplate('andy_countdown_js', $__vars) . '

<div class="block">
<div class="block-container block-container-countdown" align="center">
	
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

<div class="block-countdown" style="margin-left: -2em; margin-bottom: 1em">
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
		textScale: 1.0,
		color: "#2196F3",
		offset: 5
	} // <- no comma on last item!
	
});
</script>
</div>
</div>
</div>';
	return $__finalCompiled;
});