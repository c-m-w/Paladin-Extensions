<?php
// FROM HASH: 42710ac811b4d39185d805ed7f7b3ad2
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Invitations');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body block-row">
			<ul class="listPlain">
				';
	if ($__templater->isTraversable($__vars['invitations'])) {
		foreach ($__vars['invitations'] AS $__vars['invitation']) {
			$__finalCompiled .= '
					<li>
						';
			if ($__vars['generateLink']) {
				$__finalCompiled .= '
							' . $__templater->escape($__vars['invitation']['invitation_url']) . '
						';
			} else {
				$__finalCompiled .= '
							' . $__templater->escape($__vars['invitation']['invitation_code']) . '
						';
			}
			$__finalCompiled .= '
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