<?php
// FROM HASH: 6e54f76f70c5bdda44a5ebc67e182f48
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="buttonGroup-buttonWrapper">
	' . $__templater->button('Add' . $__vars['xf']['language']['ellipsis'], array(
		'class' => 'menuTrigger',
		'data-xf-click' => 'menu',
		'aria-expanded' => 'false',
		'aria-haspopup' => 'true',
		'title' => $__templater->filter('More options', array(array('for_attr', array()),), false),
	), '', array(
	)) . '
	<div class="menu" data-menu="menu" aria-hidden="true">
		<div class="menu-content">
			<a href="' . $__templater->fn('link', array('warnings/category-add', ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Category' . '</a>
			<a href="' . $__templater->fn('link', array('warnings/add', ), true) . '" class="menu-linkRow">' . 'Warning' . '</a>
			<a href="' . $__templater->fn('link', array('warnings/actions/add', ), true) . '" class="menu-linkRow">' . 'Warning Action' . '</a>
			<a href="' . $__templater->fn('link', array('warnings/default/add', ), true) . '" class="menu-linkRow">' . 'Warning Default' . '</a>
		</div>
	</div>
	
	' . $__templater->button('Sort' . $__vars['xf']['language']['ellipsis'], array(
		'class' => 'menuTrigger',
		'data-xf-click' => 'menu',
		'aria-expanded' => 'false',
		'aria-haspopup' => 'true',
		'title' => $__templater->filter('More options', array(array('for_attr', array()),), false),
	), '', array(
	)) . '
	<div class="menu" data-menu="menu" aria-hidden="true">
		<div class="menu-content">
			<a href="' . $__templater->fn('link', array('warnings/category-sort', ), true) . '" class="menu-linkRow" data-xf-click="overlay">' . 'Categories' . '</a>
			<a href="' . $__templater->fn('link', array('warnings/sort', ), true) . '" class="menu-linkRow">' . 'Warning Definitions' . '</a>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});