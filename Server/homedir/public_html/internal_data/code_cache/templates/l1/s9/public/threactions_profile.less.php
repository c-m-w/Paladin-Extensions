<?php
// FROM HASH: 119aacace18a29a9270cd2f6df5c6af6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.reactionCount--profile {
	display: flex;
	flex-wrap: wrap;

	.reactionCount-row {
		display: flex;
		flex-grow: 0;
		flex-basis: 33%;

		&--heading {
			font-weight: bold;
			padding-bottom: @xf-paddingSmall;
		}

		&-cell {
			flex-grow: 0;
			flex-basis: 33%;
			text-align: center;
		}
	}
}

@media (max-width: @xf-responsiveMedium) {
	.reactionCount--profile {
		.reactionCount-row {
			flex-basis: 50%;

			&--heading:nth-child(3) {
				display: none;
			}

			&-cell {
				flex-basis: 50%;
			}
		}
	}
}

@media (max-width: @xf-responsiveNarrow) {
	.reactionCount--profile {
		.reactionCount-row {
			flex-basis: 100%;

			&--heading:nth-child(2) {
				display: none;
			}

			&-cell {
				flex-basis: 100%;
			}
		}
	}
}';
	return $__finalCompiled;
});