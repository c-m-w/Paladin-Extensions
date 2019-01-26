<?php
// FROM HASH: 4476d09bd9f5dca807cf6781455c62f4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeCss('thtopics.less');
	$__finalCompiled .= '

<div class="p-body-header--inner uix_headerInner">
	';
	if (($__vars['template'] === 'thread_view') OR ($__vars['template'] === 'topic_view')) {
		$__finalCompiled .= '
		<ul class="thTopicHeading__container__topics">
			<li class="thTopicHeading__container__topics__topic"><a href="' . $__templater->fn('link', array('forums', null, array('topics' => ($__vars['topic']['title'] . '.') . $__vars['topic']['topic_id'], ), ), true) . '" class="thTopic thTopic--primary thTopic--inverted thTopic--' . $__templater->escape($__vars['topic']['topic_id']) . '">' . $__templater->escape($__vars['topic']['title']) . '</a></li>
			';
		if ($__templater->isTraversable($__vars['thread']['secondary_topics'])) {
			foreach ($__vars['thread']['secondary_topics'] AS $__vars['secondaryTopic']) {
				$__finalCompiled .= '
				<li class="thTopicHeading__container__topics__topic"><a href="' . $__templater->fn('link', array('forums', null, array('topics' => ($__vars['secondaryTopic']['title'] . '.') . $__vars['secondaryTopic']['topic_id'], ), ), true) . '">' . $__templater->escape($__vars['secondaryTopic']['title']) . '</a></li>
			';
			}
		}
		$__finalCompiled .= '
		</ul>
		<div class="p-title">
			<h1 class="p-title-value">' . $__templater->fn('prefix', array('thread', $__vars['thread'], ), true) . $__templater->escape($__vars['thread']['title']) . '</h1>
		</div>
		<div class="p-description">' . $__templater->escape($__vars['description']) . '</div>
	';
	} else {
		$__finalCompiled .= '
		<div class="p-title">
			<h1 class="p-title-value">' . $__templater->escape($__vars['topic']['title']) . '</h1>
		</div>
		<div class="p-description">' . $__templater->escape($__vars['topic']['description_or_parent']) . '</div>
	';
	}
	$__finalCompiled .= '
</div>
';
	$__compilerTemp1 = '';
	$__compilerTemp1 .= (isset($__templater->pageParams['pageAction']) ? $__templater->pageParams['pageAction'] : '');
	if (strlen(trim($__compilerTemp1)) > 0) {
		$__finalCompiled .= '
	<div class="uix_headerInner--opposite">
		<div class="p-title-pageAction">' . $__compilerTemp1 . '</div>
	</div>
';
	}
	return $__finalCompiled;
});