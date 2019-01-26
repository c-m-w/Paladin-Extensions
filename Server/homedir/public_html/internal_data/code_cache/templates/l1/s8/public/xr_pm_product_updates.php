<?php
// FROM HASH: 9d7649ce3ab2231761f173b54967ba04
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['product']['product_title']) . ' - ' . 'Updates');
	$__finalCompiled .= '

';
	$__compilerTemp1 = $__vars;
	$__compilerTemp1['pageSelected'] = 'updates';
	$__templater->wrapTemplate('xr_pm_product_wrapper', $__compilerTemp1);
	$__finalCompiled .= '

<div class="block block--messages">
	<div class="block-container">
		<div class="block-body">
			';
	if ($__templater->isTraversable($__vars['versions'])) {
		foreach ($__vars['versions'] AS $__vars['version']) {
			$__finalCompiled .= '
				';
			$__templater->includeCss('message.less');
			$__finalCompiled .= '
				';
			if ($__vars['version']['version_details']) {
				$__finalCompiled .= '
					<div class="message message--simple">
					<span class="u-anchorTarget" id="version-' . $__templater->escape($__vars['version']['product_version_id']) . '"></span>
					<div class="message-inner">
						<div class="message-cell message-cell--main">
							<div class="message-content">
								<div class="message-attribution">
									<h2 class="message-attribution-main block-textHeader">
										' . $__templater->escape($__vars['version']['Product']['product_title']) . ' ' . $__templater->escape($__vars['version']['version_string']) . '
									</h2>
									<span class="message-attribution-opposite">
										<a href="' . $__templater->fn('link', array('products/version', $__vars['version'], ), true) . '" class="u-concealed" rel="nofollow">' . $__templater->fn('date_dynamic', array($__vars['version']['release_date'], array(
				))) . '</a>
									</span>
								</div>

								<div class="message-userContent">
									<article class="message-body">
										' . $__templater->fn('bb_code', array($__vars['version']['version_details'], 'xr_pm_version', $__vars['version'], ), true) . '
										';
				if ($__vars['version']['changelog']) {
					$__finalCompiled .= '
											<ul>
												';
					if ($__templater->isTraversable($__vars['version']['changelog'])) {
						foreach ($__vars['version']['changelog'] AS $__vars['changelog']) {
							if ($__vars['changelog']) {
								$__finalCompiled .= '
													<li>' . $__templater->escape($__vars['changelog']) . '</li>
												';
							}
						}
					}
					$__finalCompiled .= '
											</ul>
										';
				}
				$__finalCompiled .= '
									</article>
								</div>
							</div>
						</div>
					</div>
				</div>
				';
			}
			$__finalCompiled .= '
			';
		}
	}
	$__finalCompiled .= '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});