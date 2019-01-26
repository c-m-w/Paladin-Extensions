<?php
// FROM HASH: f5a35221fb5bf3bffb79e703c0c48656
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Invitations');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			<ul class="listPlain block-row">
				';
	if ($__templater->isTraversable($__vars['invitations'])) {
		foreach ($__vars['invitations'] AS $__vars['invitation']) {
			$__finalCompiled .= '
					<li>
						' . $__templater->escape($__vars['invitation']['invitation_url']) . '
					</li>
				';
		}
	}
	$__finalCompiled .= '
			</ul>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});