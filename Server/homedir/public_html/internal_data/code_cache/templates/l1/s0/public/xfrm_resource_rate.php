<?php
// FROM HASH: 320d42bd522faf0fd5f3b68db1d8266a
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Rate this extension');
	$__finalCompiled .= '

';
	$__templater->breadcrumbs($__templater->method($__vars['resource'], 'getBreadcrumbs', array()));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['existingRating']) {
		$__compilerTemp1 .= '
				' . $__templater->formInfoRow('
					' . 'You have already rated this version. Re-rating it will remove your existing rating or review.' . '
				', array(
			'rowtype' => 'confirm',
		)) . '
			';
	}
	$__compilerTemp2 = '';
	if ($__vars['xf']['options']['xfrmReviewRequired']) {
		$__compilerTemp2 .= '
						' . 'A review is required.' . '
					';
	}
	$__compilerTemp3 = '';
	if ($__vars['xf']['options']['xfrmMinimumReviewLength']) {
		$__compilerTemp3 .= '
						<span id="js-resourceReviewLength">' . 'Your review must be at least ' . $__templater->escape($__vars['xf']['options']['xfrmMinimumReviewLength']) . ' characters.' . '</span>
					';
	}
	$__compilerTemp4 = '';
	if ($__vars['xf']['options']['xfrmAllowAnonReview']) {
		$__compilerTemp4 .= '
				' . $__templater->formCheckBoxRow(array(
		), array(array(
			'name' => 'is_anonymous',
			'label' => 'Submit review anonymously',
			'hint' => 'If selected, only staff will be able to see who wrote this review.',
			'_type' => 'option',
		)), array(
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__compilerTemp1 . '

			' . $__templater->callMacro('rating_macros', 'rating', array(), $__vars) . '

			' . $__templater->formTextAreaRow(array(
		'name' => 'message',
		'rows' => '2',
		'autosize' => 'true',
		'data-xf-init' => 'min-length',
		'data-min-length' => $__vars['xf']['options']['xfrmMinimumReviewLength'],
		'data-allow-empty' => ($__vars['xf']['options']['xfrmReviewRequired'] ? 'false' : 'true'),
		'data-toggle-target' => '#js-resourceReviewLength',
		'maxlength' => $__vars['xf']['options']['messageMaxLength'],
	), array(
		'label' => 'Review',
		'explain' => '
					' . 'Explain why you\'re giving this rating. Reviews which are not constructive may be removed without notice.' . '
					' . $__compilerTemp2 . '
					' . $__compilerTemp3 . '
				',
	)) . '

			' . $__compilerTemp4 . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Submit rating',
		'icon' => 'rate',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('resources/rate', $__vars['resource'], ), false),
		'class' => 'block',
		'ajax' => 'true',
	));
	return $__finalCompiled;
});