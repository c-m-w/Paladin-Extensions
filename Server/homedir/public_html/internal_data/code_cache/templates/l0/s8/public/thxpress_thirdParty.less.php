<?php
// FROM HASH: ebc543fcf95768936be86a626c50e39c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// WooCommerce

body.woocommerce #respond input#submit, body.woocommerce a.button, body.woocommerce button.button, body.woocommerce input.button {
	.xf-buttonBase();
	.xf-buttonDefault();
	.xf-buttonPrimary();
	
	&:hover {
		.xf-uix_buttonHover();
		.xf-uix_buttonPrimaryHover();
	}
	
	&:active {
		.xf-uix_buttonActive();
		.xf-uix_buttonPrimaryActive();
	}
}

.woocommerce ul.products li {text-align: center;}

// Product listing

body.woocommerce ul.products, .woocommerce-page ul.products {
	li.product {
		.xf-contentBase();
		.xf-blockBorder()
		border-radius: @xf-blockBorderRadius;
		.m-transition(); .m-transitionProperty(border margin); // edgeSpacerRemoval
		padding: @xf-blockPaddingV @xf-blockPaddingH;
		.xf-uix_blockContainer();
	}
}

// Product single

.article-full.product {
	.thxpress_authorBlock {display: none;}
}';
	return $__finalCompiled;
});