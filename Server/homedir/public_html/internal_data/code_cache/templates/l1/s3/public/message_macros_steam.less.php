<?php
// FROM HASH: e4dc69db88c0054f110d0157fd799063
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.steam {
	padding: 0;
	margin: 0;
	overflow: hidden;

	&.steam--plainLabel
	{
		> dt
		{
			color: inherit;
		}
	}

	&.steam--spaced + .steam
	{
		margin-top: @xf-paddingMedium;
	}

	&.steam--noColon
	{
		> dt
		{
			&:after
			{
				content: "";
			}
		}
	}

	> dt
	{
		padding: 0;
		margin: 0;
		color: @xf-textColorMuted;

		.m-appendColon();
	}

	> dd
	{
		padding: 0;
		margin: 0;
	}

	&.steam--inline
	{
		display: inline;

		> dt,
		> dd
		{
			display: inline;
		}
	}

	&.steam--columns
	{
		display: table;
		table-layout: fixed;
		width: 100%;

		> dt,
		> dd
		{
			display: table-cell;
		}

		> dt
		{
			width: 50%;
			padding-right: @xf-paddingMedium;
		}

		&.steam--fixedSmall > dt
		{
			width: 200px;
		}
		&.steam--fluidSmall > dt
		{
			width: 25%;
		}
		&.steam--fluidHuge > dt
		{
			width: 70%;
		}

		@media (max-width: 500px)
		{
			display: block;

			> dt,
			> dd
			{
				display: block;
			}

			&.steam > dt
			{
				width: auto;
				padding-right: 0;
			}

			& + .steam
			{
				margin-top: @xf-paddingMedium;
			}
		}
	}

	&.steam--justified
	{
		.m-clearFix();

		> dt
		{
			float: left;
			max-width: 100%;
			margin-right: @xf-paddingMedium;
		}

		> dd
		{
			float: right;
			text-align: right;
			max-width: 100%;
		}
	}

	&.steam--rows
	{
		display: inline-table;
		margin-right: @xf-paddingMedium;

		&.steam--rows--centered
		{
			> dt,
			> dd
			{
				text-align: center;
			}
		}

		&:last-of-type
		{
			margin-right: 0;
		}

		> dt
		{
			display: table-row;
			font-size: 80%;

			&:after
			{
				content: \'\';
				display: none;
			}
		}

		> dd
		{
			display: table-row;
		}
	}
}';
	return $__finalCompiled;
});