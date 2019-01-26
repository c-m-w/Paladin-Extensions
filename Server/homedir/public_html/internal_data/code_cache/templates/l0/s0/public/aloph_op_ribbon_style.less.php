<?php
// FROM HASH: cd20ece71d1c7a1d65fc5ed98f41c60e
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'div.mobileRibbon  {display: none}


div.ribbonBox .ribbon-wrapper .ribbon>span{
    white-space: nowrap;
}

div.ribbonBox {
    color: white;
    font-weight: bold;
}

div.ribbonBox .ribbon-wrapper {
    overflow: hidden;
    position: absolute;
}

div.ribbonBox .ribbon-wrapper .ribbon  {
    cursor: default;
    text-align: center;
    text-shadow: rgba(255, 255, 255, 0.5) 0px 1px 0px;
    position: relative;
    padding: 1px 0;
    font-size: 10px;
    background-image: none;
	.xf-originalPosterHighlight();
}


div.leftCornerDesktop .ribbon-wrapper,
div.rightCornerDesktop .ribbon-wrapper,
{
    width: 50%;
    height: 50%;
}

div.leftCornerDesktop .ribbon-wrapper .ribbon,
div.rightCornerDesktop .ribbon-wrapper .ribbon
{
    width: 130%;
}

div.leftCornerDesktop .ribbon-wrapper .ribbon,
div.leftCornerMobile .ribbon-wrapper .ribbon
{
    -webkit-transform: rotate(-45deg);
    -moz-transform: rotate(-45deg);
    -ms-transform: rotate(-45deg);
    -o-transform: rotate(-45deg);
}

div.rightCornerDesktop .ribbon-wrapper .ribbon,
div.rightCornerMobile .ribbon-wrapper .ribbon
{
    -webkit-transform: rotate(45deg);
    -moz-transform: rotate(45deg);
    -ms-transform: rotate(45deg);
    -o-transform: rotate(45deg);
}

div.leftCornerDesktop .ribbon-wrapper .ribbon{
    left: -30%;
    top: 19%;
}

div.rightCornerDesktop .ribbon-wrapper {
	right: 0;
    
}
div.rightCornerDesktop .ribbon-wrapper .ribbon{
    right: 0;
    top: 18%;
}

div.bottomDesktop .ribbon-wrapper,
div.topDesktop .ribbon-wrapper,
div.bottomMobile .ribbon-wrapper,
div.topMobile .ribbon-wrapper
{  

	width: 100%;
}

div.bottomDesktop .ribbon-wrapper  {
    bottom: 0;
}

div.bottomDesktop .ribbon-wrapper .ribbon,
div.topDesktop .ribbon-wrapper .ribbon,
div.bottomMobile .ribbon-wrapper .ribbon,
div.topMobile .ribbon-wrapper .ribbon
{
    width: 100%;
}

@media (max-width: @xf-responsiveNarrow)
{
	div.desktopRibbon  {display: none}
    div.mobileRibbon  {display: block}

	div.leftCornerMobile .ribbon-wrapper,
	div.rightCornerMobile .ribbon-wrapper
	{
		width: 65%;
		height: 65%;
	}
	div.leftCornerMobile .ribbon-wrapper .ribbon,
	div.rightCornerMobile .ribbon-wrapper .ribbon
	{
		width: 145%;
	}

	
	div.ribbonBox .ribbon-wrapper .ribbon  {
	    font-size: 8px;
	}

    div.bottomMobile .ribbon-wrapper,
    div.topMobile .ribbon-wrapper
    {
        width: 100%;
    }
    div.bottomMobile .ribbon-wrapper {
        bottom: 0;
    }
    div.leftCornerMobile .ribbon-wrapper .ribbon{
        left: -37%;
        top: 15%;
	}
	div.rightCornerMobile .ribbon-wrapper .ribbon{
	    right: 0;
	    top: 14%;
	}
	div.rightCornerMobile .ribbon-wrapper {
	    right: 0;
	}
}';
	return $__finalCompiled;
});