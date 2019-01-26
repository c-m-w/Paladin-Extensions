<?php
// FROM HASH: 1236e6720b1a30c97e1b1d2e37730832
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Invitations');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Create invitation links', array(
		'href' => $__templater->fn('link', array('referral-contests/invitations/add', ), false),
		'icon' => 'add',
		'data-xf-click' => 'overlay',
	), '', array(
	)) . '
');
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<div class="block-body block-row">
			' . $__templater->formTextBox(array(
		'name' => 'username',
		'placeholder' => 'Referrer' . $__vars['xf']['language']['ellipsis'],
		'type' => 'search',
		'value' => '',
		'data-xf-init' => 'auto-complete',
		'data-single' => 'true',
		'class' => 'input--inline',
	)) . '
			' . $__templater->button('Find invitations', array(
		'type' => 'submit',
	), '', array(
	)) . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('referral-contests/invitations', ), false),
		'class' => 'block',
	)) . '

';
	$__templater->inlineJs('
$(function()
{
	$(\'.srcViewMessage\').click(function()
	{
		$(this).parent().find(\'div\').toggle();
	});
});
');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['invitations'], 'empty', array())) {
		$__finalCompiled .= '
	<div class="block">
		<div class="block-container">
			<div class="block-body">
				';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['invitations'])) {
			foreach ($__vars['invitations'] AS $__vars['invitation']) {
				$__compilerTemp1 .= '
						';
				$__compilerTemp2 = '';
				if ($__vars['invitation']['message']) {
					$__compilerTemp2 .= '
									<a role="button" class="srcViewMessage">' . 'View' . '</a>
									<div style="display: none;">
										' . $__templater->escape($__vars['invitation']['message']) . '
									</div>
								';
				} else {
					$__compilerTemp2 .= '
									--
								';
				}
				$__compilerTemp3 = '';
				if ($__vars['invitation']['Registered']) {
					$__compilerTemp3 .= '
									' . $__templater->fn('username_link', array($__vars['invitation']['Registered'], true, array(
					))) . '
								';
				} else {
					$__compilerTemp3 .= '
									--
								';
				}
				$__compilerTemp1 .= $__templater->dataRow(array(
				), array(array(
					'_type' => 'cell',
					'html' => $__templater->fn('date_dynamic', array($__vars['invitation']['invitation_date'], array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->fn('username_link', array($__vars['invitation']['User'], true, array(
				))),
				),
				array(
					'_type' => 'cell',
					'html' => ($__templater->escape($__vars['invitation']['recipient']) ?: 'N/A'),
				),
				array(
					'_type' => 'cell',
					'html' => '
								' . $__compilerTemp2 . '
							',
				),
				array(
					'_type' => 'cell',
					'html' => $__templater->escape($__vars['invitation']['invitation_code']),
				),
				array(
					'_type' => 'cell',
					'html' => '
								' . $__compilerTemp3 . '
							',
				),
				array(
					'href' => ($__templater->method($__vars['invitation'], 'isValid', array()) ? $__templater->fn('link', array('referral-contests/invitations/link', $__vars['invitation'], ), false) : null),
					'class' => 'dataList-cell--separated',
					'style' => 'text-align: center;',
					'overlay' => 'true',
					'_type' => 'cell',
					'html' => '
								<i class="fa fa-link" aria-hidden="true"></i>
							',
				),
				array(
					'href' => $__templater->fn('link', array('referral-contests/invitations/delete', $__vars['invitation'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
					';
			}
		}
		$__finalCompiled .= $__templater->dataList('
					<thead>
						' . $__templater->dataRow(array(
			'rowtype' => 'header',
		), array(array(
			'_type' => 'cell',
			'html' => 'Date',
		),
		array(
			'_type' => 'cell',
			'html' => 'Referrer',
		),
		array(
			'_type' => 'cell',
			'html' => 'Recipient',
		),
		array(
			'_type' => 'cell',
			'html' => 'Message',
		),
		array(
			'_type' => 'cell',
			'html' => 'Invitation code',
		),
		array(
			'_type' => 'cell',
			'html' => 'Referral',
		),
		array(
			'_type' => 'cell',
			'html' => '&nbsp;',
		),
		array(
			'_type' => 'cell',
			'html' => '&nbsp;',
		))) . '
					</thead>
					' . $__compilerTemp1 . '
				', array(
			'data-xf-init' => 'responsive-data-list',
		)) . '
			</div>
			<div class="block-footer">
				<span class="block-footer-counter">' . $__templater->fn('display_totals', array($__vars['invitations'], $__vars['total'], ), true) . '</span>
			</div>
		</div>
	</div>

	' . $__templater->fn('page_nav', array(array(
			'page' => $__vars['page'],
			'total' => $__vars['total'],
			'params' => $__vars['linkParams'],
			'link' => 'referral-contests/invitations',
			'wrapperclass' => 'block-outer block-outer--after',
			'perPage' => $__vars['perPage'],
		))) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No entries have been logged.' . '</div>
';
	}
	return $__finalCompiled;
});