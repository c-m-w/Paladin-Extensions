<?php
// FROM HASH: fa3c48f8bc0b2b53bd36cb888de78efd
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.similarthreads-wide
{
	display: inline;
}

.similarthreads-narrow
{
	display: none;
}

.similarthreads-post-thread
{
	padding: 10px 0px 0px 0px;
}

@media (max-width: @xf-responsiveMedium)
{
	.similarthreads-wide
	{
		display: none;
	}
	
	.similarthreads-narrow
	{
		display: inline;
	}
	
	.similarthreads-post-thread
	{
		display: none;
	}
}';
	return $__finalCompiled;
});