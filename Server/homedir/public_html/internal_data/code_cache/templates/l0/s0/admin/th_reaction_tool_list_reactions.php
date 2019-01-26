<?php
// FROM HASH: efe0532fa44c1614f1d8f94586b02140
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reaction tools');
	$__finalCompiled .= '

';
	if ($__vars['success']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--success blockMessage--iconic">' . 'Cache rebuilt successfully.' . '</div>
';
	}
	$__finalCompiled .= '

';
	if ($__vars['hasStoppedManualJobs']) {
		$__finalCompiled .= '
	<div class="blockMessage blockMessage--important blockMessage--iconic">
		' . 'There are manual rebuild jobs awaiting completion. <a href="' . $__templater->fn('link', array('tools/run-job', ), true) . '">Continue running them.</a>' . '
	</div>
';
	}
	$__finalCompiled .= '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Convert likes to reactions' . '</h2>
		<div class="block-body">
			' . $__templater->formInfoRow('This will convert XenForo likes into your default "Like handler" reaction for supported content types.', array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:ConvertLike', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Convert reactions to likes' . '</h2>
		<div class="block-body">
			' . $__templater->formInfoRow('This will convert any "Like handler" reactions into default XenForo likes. Use this if you migrate from a system that didn\'t have their ratings stored as likes.', array(
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:ConvertLikeReaction', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

';
	$__compilerTemp1 = array(array(
		'value' => '',
		'label' => 'All',
		'_type' => 'option',
	));
	$__compilerTemp1 = $__templater->mergeChoiceOptions($__compilerTemp1, $__templater->method($__vars['xf']['app'], 'getContentTypePhrases', array(true, 'react_handler_class', )));
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Rebuild reacts counted status' . '</h2>
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'options[type]',
	), $__compilerTemp1, array(
		'label' => 'Content type',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:ReactIsCounted', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

';
	$__compilerTemp2 = array(array(
		'value' => '',
		'label' => 'All',
		'_type' => 'option',
	));
	$__compilerTemp2 = $__templater->mergeChoiceOptions($__compilerTemp2, $__templater->method($__vars['xf']['app'], 'getContentTypePhrases', array(true, 'react_handler_class', )));
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Rebuild content react counts' . '</h2>
		<div class="block-body">
			' . $__templater->formSelectRow(array(
		'name' => 'options[type]',
	), $__compilerTemp2, array(
		'label' => 'Content type',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:ContentReactCount', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Rebuild user react total' . '</h2>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:UserReactTotal', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Rebuild user reaction count' . '</h2>
		' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'options[truncate]',
		'label' => 'Delete the index before rebuilding',
		'_type' => 'option',
	)), array(
	)) . '
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:UserReactionCount', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Remove unassociated reactions' . '</h2>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
	' . $__templater->formHiddenVal('job', 'ThemeHouse\\Reactions:RemoveUnassociatedReactions', array(
	)) . '
', array(
		'action' => $__templater->fn('link', array('tools/rebuild', ), false),
		'class' => 'block',
	)) . '

' . $__templater->form('
	<div class="block-container">
		<h2 class="block-header">' . 'Rebuild add-on columns' . '</h2>
		' . $__templater->formSubmitRow(array(
		'submit' => 'Rebuild now',
	), array(
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('reaction-tools/addon', ), false),
		'class' => 'block',
	));
	return $__finalCompiled;
});