<?php
// FROM HASH: b33a660e01fefdbf1650743671fec96d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '// ######################################### FOOTER #################################

' . '

.p-footer
{
	display: flex;
	flex-direction: column;
	.xf-publicFooter();

	// a {.xf-publicFooterLink();}
}

.p-footer-inner
{
	order: @xf-uix_footerMenuOrder;
	padding-top: @xf-paddingMedium;
	padding-bottom: @xf-paddingMedium;
	.xf-uix_footerMenu();
	';
	if (($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered') AND (!$__templater->fn('property', array('uix_forceCoverFooterMenu', ), false))) {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '

	.pageContent {
		display: flex;
		flex-wrap: wrap;
		justify-content: space-between;
		align-items: center;
		';
	if (($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered') OR $__templater->fn('property', array('uix_forceCoverFooterMenu', ), false)) {
		$__finalCompiled .= '
			.m-pageWidth();
			';
		if ($__templater->fn('property', array('uix_pageStyle', ), false) != 'wrapped') {
			$__finalCompiled .= '
				padding:0;
			';
		}
		$__finalCompiled .= '
		';
	}
	$__finalCompiled .= '
	}

	a {
		.xf-publicFooterLink();
	}
}

.p-footer-linkList
{
	.m-listPlain();
	// .m-clearFix();
	display: inline-flex;
	flex-wrap: wrap;
    align-items: center;
	> li
	{
		/* commented out in beta 1 (Ian)
		float: left;
		margin-right: .5em;
		margin: @xf-paddingMedium;
		*/

		&:last-child
		{
			margin-right: 0;
		}

		a
		{
			padding: 6px;
			border-radius: @xf-borderRadiusSmall;
			display: inline-block;

			&:hover
			{
				.xf-uix_footerLinkHover();
				text-decoration: none;
				// background-color: fade(@xf-publicFooterLink--color, 10%);
			}
		}
	}

	&.p-footer-choosers {
		margin: -6px;
		a {
			margin: 6px;
			.xf-uix_footerChooser();


			&:hover {.xf-uix_footerChooser();}

			// i {display: none;}
		}
	}
}

.p-footer-rssLink
{
	span
	{
		position: relative;
		top: -1px;

		display: inline-block;
		width: 1.44em;
		height: 1.44em;
		line-height: 1.44em;
		text-align: center;
		font-size: .8em;
		background-color: #FFA500;
		border-radius: 2px;
	}

	.fa-rss
	{
		color: white;
	}
}

@media (max-width: @xf-responsiveMedium)
{
	.p-footer-row-main,
	.p-footer-row-opposite
	{
		float: none;
	}
}';
	return $__finalCompiled;
});