<?php
// FROM HASH: 274f348de819a1ad5a2018f732759cfc
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['newCoupons']) {
		$__finalCompiled .= '
	';
		if ($__templater->isTraversable($__vars['newCoupons'])) {
			foreach ($__vars['newCoupons'] AS $__vars['coupon']) {
				$__finalCompiled .= '
		<li>
			<a href="javascript:" class="js-deleteCoupon labelLink" data-coupon-id="' . $__templater->escape($__vars['coupon']['coupon_id']) . '" style="text-decoration: none">
				<span class="label label--primary"
					data-xf-init="tooltip"
					title="' . $__templater->escape($__vars['coupon']['coupon_description']) . '"
				>
					' . $__templater->escape($__vars['coupon']['coupon_code']) . ' - ' . $__templater->escape($__vars['coupon']['coupon_title']) . '
				</span>
			</a>
		</li>
	';
			}
		}
		$__finalCompiled .= '
';
	} else {
		$__finalCompiled .= '
	<!-- no coupons loaded -->
';
	}
	return $__finalCompiled;
});