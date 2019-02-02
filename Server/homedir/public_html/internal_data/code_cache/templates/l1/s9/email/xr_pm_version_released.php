<?php
// FROM HASH: 9bcda12c74abd7afa2735e86e73e62fa
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<mail:subject>
	' . '' . $__templater->escape($__vars['product']['product_title']) . ' ' . $__templater->escape($__vars['version']['version_string']) . ' released' . '
</mail:subject>

' . '' . $__templater->escape($__vars['receiver']['username']) . ',<br />
<br />
Thank you for your purchase at <a href="' . $__templater->escape($__vars['xf']['options']['boardUrl']) . '">' . $__templater->escape($__vars['xf']['options']['boardTitle']) . '</a>.<br />
<br />
We are emailing to let you know that a new update has been released for <a href="' . $__templater->fn('link', array('canonical:products', $__vars['product'], ), true) . '">' . $__templater->escape($__vars['product']['product_title']) . '</a>.' . '

<h2><a href="' . $__templater->fn('link', array('canonical:products/version', $__vars['version'], ), true) . '">' . $__templater->escape($__vars['product']['product_title']) . ' ' . $__templater->escape($__vars['version']['version_string']) . '</a></h2>

<div class="message">
	' . $__templater->fn('bb_code_type', array('emailHtml', $__vars['version']['version_details'], 'xr_pm_product_version', $__vars['version'], ), true) . '
	';
	if ($__vars['version']['changelog']) {
		$__finalCompiled .= '
		<ul>
			';
		if ($__templater->isTraversable($__vars['version']['changelog'])) {
			foreach ($__vars['version']['changelog'] AS $__vars['changelog']) {
				$__finalCompiled .= '
				';
				if ($__vars['changelog']) {
					$__finalCompiled .= '
					<li>' . $__templater->escape($__vars['changelog']) . '</li>
				';
				}
				$__finalCompiled .= '
			';
			}
		}
		$__finalCompiled .= '
		</ul>
	';
	}
	$__finalCompiled .= '
</div>

<div class="minorText">' . '<a href="' . $__templater->fn('link', array('canonical:email-stop/content', $__vars['receiver'], array('t' => 'xr_pm_product', ), ), true) . '">Unsubscribe from all extension updates</a>' . '</div>';
	return $__finalCompiled;
});