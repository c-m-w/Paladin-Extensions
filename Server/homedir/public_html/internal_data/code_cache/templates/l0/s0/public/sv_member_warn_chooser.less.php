<?php
// FROM HASH: 9e7deff4b5b73240c0f6bc3978925446
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '@_input-numberWidth: 150px;
@_input-numberNarrowWidth: 90px;
@_input-textColor: xf-default(@xf-input--color, @xf-textColor);
@_input-elementSpacer: @xf-paddingMedium;
@_input-checkBoxSpacer: 1.5em;

.m-inputReadOnly()
{
	color: mix(xf-default(@xf-input--color, @xf-textColor), xf-default(@xf-inputDisabled--color, @xf-textColorMuted));
	background: mix(xf-default(@xf-input--background-color, @xf-contentBg), xf-default(@xf-inputDisabled--background-color, @xf-paletteNeutral1));
}

#warning-view-radio
{
	.formRow[data-custom-title-container="1"]
	{
		dt
		{
			display: none;
		}

		dd
		{
			padding: 0px;
		}
	}
}

.select2-hidden-accessible
{
	border: 0 !important;
	clip: rect(0 0 0 0) !important;
	height: 1px !important;
	margin: -1px !important;
	overflow: hidden !important;
	padding: 0 !important;
	position: absolute !important;
	width: 1px !important;
}

.select2
{
	line-height: normal;

	*:focus
	{
		outline: none;
	}

	.select2-selection
	{
		padding: 0;
		margin: 0;
		display: block;

		&.input
		{
			cursor: text;
		}

		ul
		{
			list-style: none;
			margin: 0;
			padding: 0 5px;
			width: 100%;
			overflow: hidden;
			text-overflow: ellipsis;
			white-space: nowrap;

			display: inline-flex;
			flex-wrap: wrap;
			margin-bottom: 5px;

			> li
			{
				&.select2-selection__choice
				{
					float: left;

					font-size: 15px;
					border-radius: @xf-borderRadiusMedium;

					.xf-chip();

					margin-right: 5px;
					margin-top: 5px;
					padding: 0 5px;

					cursor: default;

					.select2-selection__choice__remove
					{
						font-size: 0;
						cursor: pointer;

						&:before
						{
							.m-faBase();
							font-size: 15px;
							.m-faContent("@{fa-var-close}\\20");
							opacity: .5;
							.m-transition(opacity);
						}

						&:hover:before
						{
							opacity: 1;
						}
					}
				}
			}

			.select2-search
			{
				flex-grow: 1;
				min-width: 0;

				&.select2-search--inline
				{
					float: left;
				}

				.select2-search__field
				{
					border: none;
					padding: 1px 0;
					margin-top: 5px;
					background: transparent;
					min-width: 100%;
					max-width: 100%;

					&:focus
					{
						outline: none;
					}
				}
			}
		}
	}
}

.select2-container
{
	display: inline-block;

	&.select2-container--disabled
	{
		.input
		{
			.xf-inputDisabled();
		}
	}

	&.select2-container--open
	{
		.select2-dropdown
		{
			-ltr-rtl-left: 0;

			&.select2-dropdown--above
			{
				border-bottom: none;
				border-bottom-left-radius: 0;
				border-bottom-right-radius: 0;
			}

			&.select2-dropdown--below
			{
				border-top: none;
				border-top-left-radius: 0;
				border-top-right-radius: 0;
			}
		}
	}
}

.select2-dropdown
{
	border-radius: @xf-borderRadiusSmall;
	box-sizing: border-box;
	display: block;
	position: absolute;
	-ltr-rtl-left: -100000px;
	width: 100%;
	z-index: 1051;
	padding-top: 2px;

	&.select2-dropdown--above
	{
		padding-bottom: 5px;

		.select2-results__option.loading-results:not(:last-child)
		{
			display: none;
		}
	}
}

.select2-results
{
}

.select2-results__options
{
	.m-autoCompleteList();

	display: block;
	
	&--nested
	{
		box-shadow: none;
	}
}

.select2-results__option
{
	user-select: none;
	-webkit-user-select: none;

	&.select2-results__option--highlighted
	{
		background: @xf-contentHighlightBg;
	}
}

.select2-selection__rendered
{
	.xf-input();
	display: block;
	width: 100%;
	line-height: @xf-lineHeightDefault;
	text-align: left; // this will be flipped in RTL
	word-wrap: break-word;
	-webkit-appearance: none;
	-moz-appearance: none;
	appearance: none;
	.m-transition();
	.m-placeholder({color: fade(@_input-textColor, 40%); });
	cursor: default;

	&:focus,
	&.is-focused
	{
		outline: 0;
		.xf-inputFocus();
		.m-placeholder({color: fade(@_input-textColor, 50%); });
	}

	&[readonly],
	&.is-readonly
	{
		.m-inputReadOnly();
	}

	&[disabled]
	{
		.xf-inputDisabled();
	}
}

.select2-search__field
{
	.xf-input();
	display: block;
	width: 100%;
	line-height: @xf-lineHeightDefault;
	text-align: left; // this will be flipped in RTL
	word-wrap: break-word;
	-webkit-appearance: none;
	-moz-appearance: none;
	appearance: none;
	.m-transition();
	.m-placeholder({color: fade(@_input-textColor, 40%); });
	margin-top: -38px;

	&:focus,
	&.is-focused
	{
		outline: 0;
		.xf-inputFocus();
		.m-placeholder({color: fade(@_input-textColor, 50%); });
	}

	&[readonly],
	&.is-readonly
	{
		.m-inputReadOnly();
	}

	&[disabled]
	{
		.xf-inputDisabled();
	}
}

.select2-results > .select2-results__options
{
	max-height: 200px;
	overflow-y: auto;
	margin-top: -3px;
	border-bottom-left-radius: @xf-borderRadiusSmall;
	border-bottom-right-radius: @xf-borderRadiusSmall;
}

.select2-selection--single .select2-selection__arrow
{
	height: 26px;
	position: absolute;
	top: 20px;
	right: 20px;
	width: 20px;
}

.select2-selection--single .select2-selection__arrow b
{
	border-color: #888 transparent transparent transparent;
	border-style: solid;
	border-width: 5px 4px 0 4px;
	height: 0;
	left: 50%;
	margin-left: -4px;
	margin-top: -2px;
	position: absolute;
	top: 50%;
	width: 0;
}';
	return $__finalCompiled;
});