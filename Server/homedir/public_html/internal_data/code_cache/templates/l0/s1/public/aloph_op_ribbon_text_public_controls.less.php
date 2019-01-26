<?php
// FROM HASH: f2c26adee8641f07868da0ac799347bf
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.textPublicControlsMobile,
.textPublicControlsDesktop{
	color: @xf-textColorMuted;
	float: left;
}

.textPublicControlsMobile {
    display: none;
}
.textPublicControlsDesktop {
    display: block;
}

@media (max-width: @xf-responsiveNarrow)
{
    .textPublicControlsMobile {
          display: block;
    }
    .textPublicControlsDesktop {
          display: none;
    }
}';
	return $__finalCompiled;
});