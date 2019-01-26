<?php
// FROM HASH: 6eb7358036a7048b508e5de0937149a1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.discord-container embed { display: grid; }
.discord-body
{
	padding: 150px;
	text-align: center;

	.discord-join
	{
		font-size: 56px;
		font-weight: bold;
		padding: 50px;
	}
}


@media (max-width: @xf-responsiveMedium)
{
	.discord-body
	{
		padding: 50px;
		.discord-join { padding: 25px; font-size: 44px; }
	}
}

@media (max-width: @xf-responsiveNarrow)
{
	.discord-body
	{
		padding: 10px;
		.discord-join { padding: 0; font-size: 32px; }
	}
}';
	return $__finalCompiled;
});