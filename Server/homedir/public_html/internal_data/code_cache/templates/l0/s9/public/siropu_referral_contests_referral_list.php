<?php
// FROM HASH: 7f5bf9de8201c0f9667a912c16f07443
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Members referred by ' . $__templater->escape($__vars['user']['username']) . '');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<ol class="block-body">
			';
	$__compilerTemp1 = true;
	if ($__templater->isTraversable($__vars['referrals'])) {
		foreach ($__vars['referrals'] AS $__vars['referral']) {
			$__compilerTemp1 = false;
			$__finalCompiled .= '
				<li class="block-row block-row--separated">
					' . $__templater->callMacro('member_list_macros', 'item', array(
				'user' => $__vars['referral'],
				'extraData' => $__templater->fn('date_time', array($__vars['referral']['register_date'], ), false),
			), $__vars) . '
				</li>
				';
		}
	}
	if ($__compilerTemp1) {
		$__finalCompiled .= '
				<li class="blockMessage">' . 'No referrals have been found.' . '</li>
			';
	}
	$__finalCompiled .= '
		</ol>
	</div>

	' . $__templater->fn('page_nav', array(array(
		'link' => 'referrals/users',
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'data' => $__vars['user'],
		'wrapperclass' => 'block-outer block-outer--after',
		'perPage' => $__vars['perPage'],
	))) . '
</div>';
	return $__finalCompiled;
});