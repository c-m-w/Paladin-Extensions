<?php
// FROM HASH: 327f52646a4f677c5a83a5bd1e377b88
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Contest statistics' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['contest']['name']));
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			';
	$__compilerTemp1 = '';
	$__compilerTemp2 = true;
	$__vars['i'] = 0;
	if ($__templater->isTraversable($__vars['contest']['top_referrers'])) {
		foreach ($__vars['contest']['top_referrers'] AS $__vars['referrer']) {
			$__compilerTemp2 = false;
			$__vars['i']++;
			$__compilerTemp1 .= '
							' . $__templater->fn('username_link', array($__vars['referrer'], true, array(
			))) . ' (' . $__templater->escape($__vars['referrer']['referral_count']) . ')
						';
		}
	}
	if ($__compilerTemp2) {
		$__compilerTemp1 .= '
							--
						';
	}
	$__finalCompiled .= $__templater->dataList('
				' . $__templater->dataRow(array(
		'rowtype' => 'header',
	), array(array(
		'_type' => 'cell',
		'html' => 'Total referrals',
	),
	array(
		'_type' => 'cell',
		'html' => 'Valid referrals',
	),
	array(
		'_type' => 'cell',
		'html' => 'Top referrers',
	))) . '
				' . $__templater->dataRow(array(
	), array(array(
		'_type' => 'cell',
		'html' => $__templater->escape($__vars['contest']['total_referrals']),
	),
	array(
		'_type' => 'cell',
		'html' => $__templater->escape($__vars['contest']['valid_referrals']),
	),
	array(
		'_type' => 'cell',
		'html' => '
						' . $__compilerTemp1 . '
					',
	))) . '
			', array(
	)) . '
		</div>
	</div>
</div>';
	return $__finalCompiled;
});