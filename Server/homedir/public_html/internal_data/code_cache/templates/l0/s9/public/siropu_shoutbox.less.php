<?php
// FROM HASH: 7d950653df6189b96aaed888ba4a429d
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.siropuShoutbox
{
	.block-header span, .block-minorHeader span
	{
		float: right;
	}
	.block-body
	{
		padding: 10px;
		position: relative;
	}
	form
	{
		margin-bottom: 10px;

		> span
		{
			display: inline-flex;
			width: 100%;

			> *
			{
				margin-right: 2px;

				&:last-child
				{
					margin-right: 0;
				}
			}
		}
		.input
		{
			width: 100%;

			.p-body-sidebar &
			{
				width: 65%;
				font-size: 12px;
			}
		}
		.button
		{
			font-size: 18px;

			.p-body-sidebar &
			{
				font-size: 14px;
			}
		}
		&.siropuShoutboxReverse
		{
			margin-top: 10px;
			margin-bottom: 0;
		}
		.editorSmilies
		{
			border-top: 1px solid @xf-borderColor;
			margin-top: 5px;
		}
	}
}
.siropuShoutboxShouts
{
	height: 300px;
	overflow: auto;
	padding: 0;
	margin: 0;

	> li
	{
		list-style-type: none;
		margin-bottom: 5px;

		.bbWrapper
		{
			display: inline;
		}
		.bbMediaWrapper
		{
			margin-top: 5px;
		}
		&:last-child
		{
			margin-bottom: 0;
		}
		.username
		{
			font-weight: bold;
		}
		time
		{
			color: @xf-textColorMuted;
			font-size: 12px;
		}
		a[data-xf-click="overlay"]
		{
			display: none;
			opacity: 0.5;

			&:hover
			{
				opacity: 1;
			}
		}
	}
}
.siropuShoutboxLoadingMoreShouts
{
	position: absolute;
	bottom: 5px;
	left: 0;
	right: 0;
	text-align: center;
	font-weight: bold;
	font-size: 12px;
	color: @xf-textColorEmphasized;

	&.siropuShoutboxReverse
	{
		top: 5px;
	}
}
.siropuShoutboxHeader
{
	margin-bottom: 10px;
	padding-bottom: 10px;
	border-bottom: 1px solid @xf-borderColor;
	color: @xf-textColorDimmed;
}
.siropuShoutboxFooter
{
	margin-top: 10px;
	padding-top: 10px;
	border-top: 1px solid @xf-borderColor;
	color: @xf-textColorDimmed;
}
#siropuShoutboxFullPage
{
	&::-webkit-scrollbar
	{
    	display: none;
	}
	> .block
	{
		margin: 0;
		padding: 0;
	}
}
@media (max-width: 360px)
{
	.siropuShoutbox
	{
		form
		{
			.input
			{
				width: 75%;
			}
		}
	}
}';
	return $__finalCompiled;
});