<?php
// FROM HASH: 4a57f2cb6499daed30a87469fdc7ea40
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="react-modify">
	<div class="menu-row">
		<ul class="listPlain">
			';
	if ($__templater->isTraversable($__vars['reacts'])) {
		foreach ($__vars['reacts'] AS $__vars['react']) {
			$__finalCompiled .= '
				<a href="' . $__templater->escape($__templater->method($__templater->method($__vars['react'], 'getHandler', array()), 'getUnreactSingleLink', array($__vars['react']['react_id'], ))) . '" data-xf-click="overlay">
					<li class="reaction-item menu-linkRow">
						' . $__templater->fn('reaction', array($__vars['react']['reaction_id'], 'modify', ), true) . '
						<span class="reaction-title">' . $__templater->escape($__vars['xf']['reactions'][$__vars['react']['reaction_id']]['title']) . '</span>
					</li>
				</a>
			';
		}
	}
	$__finalCompiled .= '
		</ul>
	</div>
</div>';
	return $__finalCompiled;
});