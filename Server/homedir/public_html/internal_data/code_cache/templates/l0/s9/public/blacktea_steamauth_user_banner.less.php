<?php
// FROM HASH: 927683c2ec2a60a80d01b940a7fd4d50
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.message-user .steam-user-banner {
	min-width: 0;
	width: 180px;
}

.steam-user-banner {
	display: inline-block;
	max-width: 100%;
	min-width: 180px;
	padding: 4px;
	margin: 6px 0;
	min-height: 44px;
	overflow: hidden;
	font-family: Arial, Helvetica, Verdana, sans-serif;
	background-color: #222222;
	border-radius: 2px;
	&:empty {
		visibility: hidden;
	}
	&:hover {
		text-decoration: none;
		background-color: #333333;
	}
	&.visibility-0 {
		color: #898989;
		.image-container {
			background-color: #898989;
			background: -webkit-linear-gradient( top, rgba(106,106,106,1) 5%, rgba(85,85,85,1) 95%);
			background: linear-gradient( to bottom, rgba(106,106,106,1) 5%, rgba(85,85,85,1) 95%);
		}
	}
	&.visibility-1, &.visibility-2, &.visibility-3, &.visibility-4, &.visibility-5, &.visibility-6 {
		color: #57cbde;
		.image-container {
			background-color: #57cbde;
			background: -webkit-linear-gradient( top, rgba(83,164,196,1) 5%, rgba(69,128,151,1) 95%);
			background: linear-gradient( to bottom, rgba(83,164,196,1) 5%, rgba(69,128,151,1) 95%);
		}
	}
	&.visibility-7 {
		color: #90ba3c;
		.image-container {
			background-color: #90ba3c;
			background: -webkit-linear-gradient( top, rgba(143,185,59,1) 5%, rgba(110,140,49,1) 95%);
			background: linear-gradient( to bottom, rgba(143,185,59,1) 5%, rgba(110,140,49,1) 95%);
		}
	}
	.image-container {
		float: left;
		width: 36px;
		height: 36px;
    	padding: 2px;
    	margin-right: 6px;
		img {
			display: block;
			border-radius: 2px;
		}
	}
	.info-container {
		white-space: nowrap;
		line-height: 13px;
		> div {
			text-align: left;
		}
		.name {
			font-size: 11px;
		}
		.visibility {
			font-size: 10px;
		}
	}
}';
	return $__finalCompiled;
});