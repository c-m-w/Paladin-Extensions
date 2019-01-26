<?php
// FROM HASH: 92f21d5bf7453e498526c28370620a64
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.label
{
	display: inline-block;
	padding: 1px .35em;
	border: 1px solid transparent;
	border-radius: @xf-borderRadiusMedium;
	font-size: 80%;
	line-height: ((@xf-lineHeightDefault) * .9);
	text-decoration: none;

	&:hover,
	a:hover &
	{
		text-decoration: none;
	}

	&.label--fullSize
	{
		font-size: 100%;
	}

	&.label--small
	{
		font-size: @xf-fontSizeSmall;
	}

	&.label--smallest
	{
		font-size: @xf-fontSizeSmallest;
	}

	// variations
	&.label--hidden
	{
		background: none;
		border: none;
		box-shadow: none;
	}

	&.label--subtle
	{
		.m-labelVariation(@xf-textColorMuted, @xf-contentAltBg);
	}

	&.label--primary
	{
		.m-labelVariation(white, @xf-uix_prefixPrimary);
	}

	&.label--accent
	{
		.m-labelVariation(white, @xf-uix_prefixAccent);
	}

	&.label--red { .m-labelVariation(white, @xf-uix_prefixRed); }
	&.label--green { .m-labelVariation(white, @xf-uix_prefixGreen); }
	&.label--olive { .m-labelVariation(white, @xf-uix_prefixOlive); }
	&.label--lightGreen { .m-labelVariation(white, @xf-uix_prefixLightGreen); }
	&.label--blue { .m-labelVariation(black, @xf-uix_prefixBlue); }
	&.label--royalBlue { .m-labelVariation(white, @xf-uix_prefixRoyalBlue); }
	&.label--skyBlue { .m-labelVariation(white, @xf-uix_prefixRedSkyBlue); }
	&.label--gray { .m-labelVariation(white, @xf-uix_prefixGray); }
	&.label--silver { .m-labelVariation(black, @xf-uix_prefixSilver); }
	&.label--yellow { .m-labelVariation(black, @xf-uix_prefixYellow); }
	&.label--orange { .m-labelVariation(black, @xf-uix_prefixOrange); }
}

.label-append
{
	display: inline-block;
}

.labelLink,
.labelLink:hover
{
	text-decoration: none;
}';
	return $__finalCompiled;
});