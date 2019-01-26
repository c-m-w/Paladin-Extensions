<?php
// FROM HASH: c0156534b0b47761d22936037cb2cc91
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'Congratulations! You are the winner of our referral contest "' . (((('<a href="' . $__templater->fn('link', array('referral-contests', $__vars['content'], ), true)) . '" class="fauxBlockLink-blockLink">') . $__templater->escape($__vars['content']['name'])) . '</a>') . '" with ' . $__templater->escape($__vars['content']['referral_count']) . ' referrals!';
	return $__finalCompiled;
});