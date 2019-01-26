<?php
// FROM HASH: a6d9c4d4d64365ac7eef735438d3cf60
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Preview');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			<div class="block-row">
				';
	if ($__templater->method($__vars['tool'], 'isBanner', array())) {
		$__finalCompiled .= '
					<img src="' . $__templater->escape($__vars['tool']['absolute_file_path']) . '" />
				';
	} else {
		$__finalCompiled .= '
					<a>' . $__templater->escape($__vars['tool']['content']) . '</a>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});