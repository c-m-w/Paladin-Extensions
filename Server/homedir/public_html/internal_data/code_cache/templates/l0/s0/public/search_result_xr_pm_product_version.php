<?php
// FROM HASH: 001b5dc9985b52a2268cdec478ee6fc7
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<li class="block-row block-row--separated">
	<div class="contentRow ' . ((!$__vars['product']['active']) ? 'is-deleted' : '') . '">
		<span class="contentRow-figure">
			' . $__templater->fn('avatar', array($__vars['product']['User'], 's', false, array(
		'defaultname' => $__vars['product']['username'],
	))) . '
		</span>
		<div class="contentRow-main">
			<h3 class="contentRow-title">
				<a href="' . $__templater->fn('link', array('products/changelog', $__vars['product'], ), true) . '">' . $__templater->fn('highlight', array($__vars['product']['product_title'], $__vars['options']['term'], ), true) . '</a>
				<span class="u-muted">' . $__templater->escape($__vars['product']['Version']['version_string']) . '</span>
			</h3>

			<div class="contentRow-snippet">' . $__templater->fn('snippet', array($__vars['version']['version_details'], 300, array('term' => $__vars['options']['term'], 'stripQuote' => true, ), ), true) . '</div>

			<div class="contentRow-minor contentRow-minor--hideLinks">
				<ul class="listInline listInline--bullet">
					<li>' . $__templater->fn('username_link', array($__vars['product']['User'], false, array(
		'defaultname' => $__vars['product']['username'],
	))) . '</li>
					<li>' . 'Version' . '</li>
					<li>' . $__templater->fn('date_dynamic', array($__vars['version']['release_date'], array(
	))) . '</li>
					';
	if ($__vars['product']['category_id']) {
		$__finalCompiled .= '
						<li>' . 'Category' . $__vars['xf']['language']['label_separator'] . ' <a href="' . $__templater->fn('link', array('products/categories', $__vars['product']['Category'], ), true) . '">' . $__templater->escape($__vars['product']['Category']['title']) . '</a></li>
					';
	}
	$__finalCompiled .= '
				</ul>
			</div>
		</div>
	</div>
</li>';
	return $__finalCompiled;
});