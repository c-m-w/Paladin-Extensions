<?php
// FROM HASH: ea16cd93217130ca12cb69c018b019e2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.post-table-container {
	max-width: 100%;
	height: auto;
	
	&::after {
		content: ".";
		clear: both;
		display: block;
		visibility: hidden;
		height: 0px;
	}

	.post-table {
		.xf-klEMTableBlock();

		td > p:first-child {
			margin-top: 0;
		}
		td > p:last-child {
			margin-bottom: 0;
		}
			
		> thead,
		> tbody {
			> tr {
				> td,
				> th {
					.xf-klEMTableCell();
				}

				> th {
					.xf-klEMTableTH();
				}
			}
		}
		
		
		&:not(.nobackground):not(.no-background) {
			> thead,
			> tbody {

				> tr:nth-child(2n) {
					> td,
					> th {
						.xf-klEMTableAlternatingCell();
					}
				}
			}
		}

		&.no-border,
		&.noborder {
			> tbody,
			> thead {
				> tr {
					> td,
					> th {
						border: none;
					}
				}
			}
		}

		&.centered,
		&.center {
			margin: 0 auto;
		}

		&.right {
			float: right;
		}
		
		&.nofullwidth,
		&.no-full-width {
			width: auto !important;
		}
	}
}

.klEMiSpoiler {
	.xf-klEMiSpoiler();
	
	&--button {
		.xf-klEMiSpoilerButton();

		> span::before {
			.xf-klEMiSpoilerButtonIcon();
		}

		&.is-active {
			.xf-klEMiSpoilerButtonActive();

			> span::before {
				.xf-klEMiSpoilerButtonIconActive();
			}
		}
	}

	&--title {
		.xf-klEMiSpoilerButtonTitle();
	}

	&--content {
		.xf-klEMiSpoilerContent();

		&.is-active {
			.xf-klEMiSpoilerContentActive();
		}
	}
}

.bbCodeBlock--hidden {
	.xf-klEMHideHidden();
}

.bbCodeBlock--visible {
	.xf-klEMHideShown();
}';
	return $__finalCompiled;
});