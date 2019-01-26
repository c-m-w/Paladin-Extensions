<?php
// FROM HASH: 2474475009a68c4f6adead08573574e6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Login as User Logs');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['laulogs'], 'empty', array())) {
		$__finalCompiled .= '
    ';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['laulogs'])) {
			foreach ($__vars['laulogs'] AS $__vars['laulog']) {
				$__compilerTemp1 .= '
                        ' . $__templater->dataRow(array(
				), array(array(
					'name' => 'delete[]',
					'value' => $__vars['laulog']['log_id'],
					'_type' => 'toggle',
					'html' => '',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['laulog']['FromUser'], false, array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['laulog']['FromUser'], ), false),
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['laulog']['ToUser'], false, array(
					'href' => $__templater->fn('link', array('users/edit', $__vars['laulog']['ToUser'], ), false),
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['laulog']['dateline'], array(
				))),
				),
				array(
					'class' => 'u-ltr',
					'_type' => 'cell',
					'html' => ($__vars['laulog']['ip_address'] ? $__templater->filter($__vars['laulog']['ip_address'], array(array('ip', array()),), true) : ''),
				),
				array(
					'_type' => 'cell',
					'html' => ($__vars['laulog']['reason'] ? $__templater->escape($__vars['laulog']['reason']) : 'N/A'),
				),
				array(
					'href' => $__templater->fn('link', array('laulogs/delete', $__vars['laulog'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
                    ';
			}
		}
		$__finalCompiled .= $__templater->form('
        <div class="block-container">
            <div class="block-body">

                ' . $__templater->dataList('

                    <colgroup>
                        <col>
                        <col style="width: 5%">
                        <col style="width: 5%">
                        <col style="width: 9%">
                        <col style="width: 5%">
                        <col style="width: 15%">
                        <col>
                    </colgroup>

                    ' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => '
                            ' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '< .block-container',
			'data-xf-init' => 'tooltip',
			'title' => $__templater->filter('Select all', array(array('for_attr', array()),), false),
			'_type' => 'option',
		))) . '
                        ',
		),
		array(
			'_type' => 'cell',
			'html' => 'Login from',
		),
		array(
			'_type' => 'cell',
			'html' => 'Login to',
		),
		array(
			'_type' => 'cell',
			'html' => 'Date / time',
		),
		array(
			'_type' => 'cell',
			'html' => 'IP',
		),
		array(
			'_type' => 'cell',
			'html' => 'Reason',
		),
		array(
			'_type' => 'cell',
			'html' => 'Action',
		))) . '

                    ' . $__compilerTemp1 . '

                ', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '

            </div>
            <div class="block-footer block-footer--split">
                <span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['laulogs'], $__vars['total'], ), true) . '</span>

                <span class="block-footer-select">
                    ' . $__templater->formCheckBox(array(
			'standalone' => 'true',
		), array(array(
			'check-all' => '< .block-container',
			'label' => 'Select all',
			'_type' => 'option',
		))) . '
                </span>

                <span class="block-footer-controls">
                    ' . $__templater->button('', array(
			'type' => 'submit',
			'icon' => 'delete',
		), '', array(
		)) . '
                </span>
            </div>
        </div>

        ' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'link' => 'laulogs',
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
    ', array(
			'action' => $__templater->fn('link', array('laulogs/mass-delete', ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
    ';
	} else {
		$__finalCompiled .= '
    <div class="blockMessage">' . 'No records matched.' . '</div>
';
	}
	return $__finalCompiled;
});