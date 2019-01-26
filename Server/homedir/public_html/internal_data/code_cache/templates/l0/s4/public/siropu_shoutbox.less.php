<?php
// FROM HASH: 331c1cc3f53d8ea2c4f5b58f7bc0ddd1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.siropuShoutbox
{
	margin-bottom: 20px;

	.block-header span
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
		.input
		{
			width: 100%;
			display: inline-block;
		}
		
		margin-bottom: 10px;

		&.siropuShoutboxReverse
		{
			margin-top: 10px;
			margin-bottom: 0;
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
.siropuShoutboxFooter
{
	margin-top: 10px;
	text-align: center;
}
.p-body-sidebar .siropuShoutbox form .input
{
	width: 71.5%;
}';
	return $__finalCompiled;
});