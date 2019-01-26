<?php
// FROM HASH: a7af805bbefa5898ae05557318194404
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Statistics');
	$__finalCompiled .= '

';
	$__templater->inlineCss('
	.statsOuter{
	}
	.mjstStats{
		width: 33.333333%;
		float: left;
		text-align: center;
	}
	.ticket-stats{
		font-size: 32px;
	}
');
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body statsOuter u-clearFix">
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Total tickets' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['ticketCount'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Active tickets' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['activeTickets'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Waiting reply tickets' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['waitTickets'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
		</div>
	</div>
</div>

<div class="block">
	<div class="block-container">
		<div class="block-body statsOuter u-clearFix">
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Total departments' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['departmentCount'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Total knowledge bases' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['kbCount'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
			<div class="mjstStats">
				<div class="block-row">
					<h3 class="block-textHeader">
						' . 'Total predefined replies' . '
					</h3>
					<div class="ticket-stats">
						' . $__templater->filter($__vars['preReplyCount'], array(array('number', array()),), true) . '
					</div>
				</div>
			</div>
		</div>
	</div>
</div>';
	return $__finalCompiled;
});