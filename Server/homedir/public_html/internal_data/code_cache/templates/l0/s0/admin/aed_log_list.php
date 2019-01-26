<?php
// FROM HASH: 6a03232263235ff8f4aa539772451dba
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Alter Ego Detector Log');
	$__finalCompiled .= '


';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
    ' . $__templater->button('
        ' . 'Clear' . '
    ', array(
			'href' => $__templater->fn('link', array('logs/aed-logs/clear', ), false),
			'icon' => 'delete',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['entries'], 'empty', array())) {
		$__finalCompiled .= '
    <div class="block">
        <div class="block-container">
            <div class="block-body">
                ';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['entries'])) {
			foreach ($__vars['entries'] AS $__vars['entry']) {
				$__compilerTemp1 .= '
                        ' . $__templater->dataRow(array(
				), array(array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['entry']['FromUser'], false, array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['entry']['FromUser'], ), false),
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['entry']['ToUser'], false, array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['entry']['ToUser'], ), false),
				))),
				),
				array(
					'class' => 'u-ltr',
					'_type' => 'cell',
					'html' => ($__vars['entry']['ip_address'] ? $__templater->filter($__vars['entry']['ip_address'], array(array('ip', array()),), true) : ''),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['entry']['user_fingerprint']),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['entry']['login_date'], array(
				))),
				))) . '
                    ';
			}
		}
		$__finalCompiled .= $__templater->dataList('
                    ' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'From User',
		),
		array(
			'_type' => 'cell',
			'html' => 'To User',
		),
		array(
			'_type' => 'cell',
			'html' => 'IP address',
		),
		array(
			'_type' => 'cell',
			'html' => 'Fingerprint',
		),
		array(
			'_type' => 'cell',
			'html' => 'Date / time',
		))) . '
                    ' . $__compilerTemp1 . '
                ', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '
            </div>
            <div class="block-footer">
                <span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['entries'], $__vars['total'], ), true) . '</span>
            </div>
        </div>
        ' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'logs/aed-logs',
			'params' => $__vars['linkFilters'],
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
    </div>
    ';
	} else {
		$__finalCompiled .= '
    <div class="blockMessage">' . 'No entries have been logged.' . '</div>
';
	}
	return $__finalCompiled;
});