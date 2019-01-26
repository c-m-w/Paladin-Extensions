<?php
// FROM HASH: 2982145731d370b1814bef574b767a0c
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['th_navigationDropdown_bookmarks'] !== 'disabled') {
		$__finalCompiled .= '
	<a href="' . $__templater->fn('link', array('bookmarks', ), true) . '"
	   class="p-navgroup-link p-navgroup-link--iconic p-navgroup-link--bookmarks"
	   data-xf-click="menu"
	   data-xf-key="#190"
	   data-menu-pos-ref="< .p-navgroup"
	   aria-expanded="false"
	   aria-haspopup="true">
		<i class="' . $__templater->fn('property', array('th_bookmarkIconClass_bookmarked_bookmarks', ), true) . '" aria-hidden="true"></i>
		<span class="p-navgroup-linkText">' . 'Bookmarks' . '</span>
	</a>
	<div class="menu menu--structural menu--medium" data-menu="menu" aria-hidden="true"
		 data-href="' . $__templater->fn('link', array('bookmarks/popup', ), true) . '"
		 data-nocache="true"
		 data-load-target=".js-bookmarksMenuBody">
		<div class="menu-content">
			<h3 class="menu-header">' . 'Bookmarks' . '</h3>
			<div class="js-bookmarksMenuBody">
				<div class="menu-row">' . 'Loading' . $__vars['xf']['language']['ellipsis'] . '</div>
			</div>
			<div class="menu-footer menu-footer--split">
				<span class="menu-footer-main">
					<a href="' . $__templater->fn('link', array('bookmarks', ), true) . '">' . 'Show all' . $__vars['xf']['language']['ellipsis'] . '</a>
				</span>
			</div>
		</div>
	</div>
';
	}
	return $__finalCompiled;
});