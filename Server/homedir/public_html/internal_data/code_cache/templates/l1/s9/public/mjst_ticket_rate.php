<?php
// FROM HASH: ab723801eca19b31ccc39c21a84d56c4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Rate this ticket');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['ticket'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['existingRating']) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					' . 'You have already rated this ticket. Re-rating it will remove your existing rating.' . '
				', array(
			'rowtype' => 'confirm',
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '

			' . $__templater->callMacro('rating_macros', 'rating', array(
		'currentRating' => $__vars['ticket']['submitter_rating'],
	), $__vars) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Submit rating',
		'icon' => 'rate',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('support-tickets/rate', $__vars['ticket'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});