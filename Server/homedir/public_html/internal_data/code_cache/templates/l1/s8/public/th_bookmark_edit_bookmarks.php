<?php
// FROM HASH: 3c938dca3e41e8780a5a061ca9c5ceb1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__templater->method($__vars['handler'], 'getBookmarkPhrase', array($__vars['content'], ))));
	$__finalCompiled .= '


';
	$__compilerTemp1 = '';
	if ($__templater->method($__vars['bookmark'], 'isInsert', array())) {
		$__compilerTemp1 .= '
				' . $__templater->filter($__templater->method($__vars['handler'], 'renderExtraCreateFields', array($__vars['content'], )), array(array('raw', array()),), true) . '
				';
	} else {
		$__compilerTemp1 .= '
				' . $__templater->filter($__templater->method($__vars['handler'], 'renderExtraEditFields', array($__vars['content'], )), array(array('raw', array()),), true) . '
			';
	}
	$__compilerTemp2 = '';
	if (!$__templater->method($__vars['bookmark'], 'isInsert', array())) {
		$__compilerTemp2 .= '
						' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('bookmarks/delete', $__vars['bookmark'], ), false),
			'value' => '1',
			'icon' => 'delete',
		), '', array(
		)) . '
					';
	}
	$__compilerTemp3 = '';
	if ($__vars['redirect']) {
		$__compilerTemp3 .= '
				' . $__templater->formHiddenVal('redirect', $__vars['redirect'], array(
		)) . '
			';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-body">
			' . $__templater->formTextBoxRow(array(
		'name' => 'note',
		'value' => $__vars['bookmark']['note'],
	), array(
		'label' => 'Note',
	)) . '

			' . $__templater->formCheckBoxRow(array(
	), array(array(
		'name' => 'sticky',
		'selected' => $__vars['bookmark']['sticky'],
		'label' => 'Sticky',
		'_type' => 'option',
	),
	array(
		'name' => 'public',
		'selected' => $__vars['bookmark']['public'],
		'label' => 'Public',
		'_type' => 'option',
	)), array(
	)) . '

			' . $__compilerTemp1 . '

			' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'html' => '
					' . $__compilerTemp2 . '
				',
	)) . '
			' . $__templater->formHiddenVal('content_type', $__vars['contentType'], array(
	)) . '
			' . $__templater->formHiddenVal('content_id', $__vars['contentId'], array(
	)) . '

			' . $__compilerTemp3 . '
		</div>
	</div>
', array(
		'action' => $__templater->fn('link', array('bookmarks/save', $__vars['bookmark'], ), false),
		'class' => 'block',
		'data-xf-init' => 'ajax-submit',
	));
	return $__finalCompiled;
});