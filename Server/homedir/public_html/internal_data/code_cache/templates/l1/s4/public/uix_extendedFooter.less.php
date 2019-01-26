<?php
// FROM HASH: 0b9106a1ce0c1e940054dfdecb1f99ba
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.uix_extendedFooter {
	order: @xf-uix_extendedFooterOrder;
	.xf-uix_extendedFooterStyle();
	';
	if (($__templater->fn('property', array('uix_pageStyle', ), false) != 'covered') AND (!$__templater->fn('property', array('uix_forceCoverExtendedFooter', ), false))) {
		$__finalCompiled .= '
		.m-pageWidth();
	';
	}
	$__finalCompiled .= '

	.pageContent {
		';
	if (($__templater->fn('property', array('uix_pageStyle', ), false) == 'covered') OR $__templater->fn('property', array('uix_forceCoverExtendedFooter', ), false)) {
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

	.uix_extendedFooterRow {
		display: flex;
		flex-wrap: wrap;
		margin: calc(-@xf-uix_footerWidgetPadding / 2);

		.block {
			flex-basis: @xf-uix_footerWidgetWidth;
			padding: calc(@xf-uix_footerWidgetPadding / 2);
			margin: 0;
			flex-grow: 1;
			
			.block-container {
				margin-left: 0;
				margin-right: 0;
				.xf-uix_footerWidget();
				
				.block-minorHeader {
					.xf-uix_footerWidgetHeader();	
			
					a {color: inherit;}
				}
				
				.block-body {
					.xf-uix_footerWidgetBody();	
				}
				
				.block-footer {
					.xf-uix_footerWidgetFooter();	
				}
				
			}
		}
	}
}';
	return $__finalCompiled;
});