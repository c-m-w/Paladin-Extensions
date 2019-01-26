<?php
// FROM HASH: 05148a921bb01d1b5e98f9ac98e72b92
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['kb']['title']));
	$__finalCompiled .= '

';
	$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_kb', ), ));
	$__finalCompiled .= '

';
	$__vars['fpSnippet'] = $__templater->fn('snippet', array($__vars['kb']['message'], 0, array('stripBbCode' => true, ), ), false);
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'metadata', array(
		'description' => $__vars['fpSnippet'],
		'shareUrl' => $__templater->fn('link', array('canonical:support-tickets/knowledge-base', $__vars['kb'], ), false),
		'canonicalUrl' => $__templater->fn('link', array('canonical:support-tickets/knowledge-base', $__vars['kb'], ), false),
	), $__vars) . '

';
	$__templater->includeCss('mjst_kb.less');
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('Knowledge base'), $__templater->fn('link', array('support-tickets/knowledge-base', ), false), array(
	));
	$__finalCompiled .= '
';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['kb']['Category']['title'])), $__templater->fn('link', array('support-tickets/knowledge-base/category', $__vars['kb']['Category'], ), false), array(
	));
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['kb'], 'canEdit', array())) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('', array(
			'href' => $__templater->fn('link', array('support-tickets/knowledge-base/edit', $__vars['kb'], ), false),
			'icon' => 'edit',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

<div class="block">
	<div class="block-container">
		<div class="block-body">
			<div class="block-row">
				<div class="message-userContent lbContainer js-lbContainer ' . ($__vars['isIgnored'] ? 'is-ignored' : '') . '"
					data-lb-id="message-' . $__templater->escape($__vars['message']['message_id']) . '"
					data-lb-caption-desc="' . ($__vars['kb']['User'] ? $__templater->escape($__vars['kb']['User']['username']) : $__templater->escape($__vars['kb']['username'])) . ' &middot; ' . $__templater->fn('date_time', array($__vars['kb']['kb_date'], ), true) . '">

					<article class="message-body">
						' . $__templater->fn('bb_code', array($__vars['kb']['message'], 'support_kb', $__vars['kb'], ), true) . '
					</article>
				</div>
			</div>
		</div>
		';
	if ($__templater->method($__vars['kb'], 'canRate', array())) {
		$__finalCompiled .= '
			' . $__templater->form('
				<div class="inputGroup">
					<span class="kbBlock-vote-text">' . 'Was this answer helpful ?' . '</span>
					<span class="inputGroup-splitter"></span>
					' . $__templater->formSelect(array(
			'class' => 'input--autoSize',
		), array(array(
			'value' => '1',
			'label' => 'Yes',
			'_type' => 'option',
		),
		array(
			'value' => '0',
			'label' => 'No',
			'_type' => 'option',
		))) . '
					<span class="inputGroup-splitter"></span>
					' . $__templater->button('Vote', array(
			'type' => 'submit',
		), '', array(
		)) . '
				</div>
			', array(
			'action' => $__templater->fn('link', array('support-tickets/knowledge-base/rate', $__vars['kb'], ), false),
			'ajax' => 'true',
			'class' => 'kbBlock-vote block-footer',
		)) . '
		';
	}
	$__finalCompiled .= '
	</div>
</div>

';
	$__templater->modifySideNavHtml(null, '
	' . $__templater->callMacro('mjst_kb_category_view', 'simple_list_block', array(), $__vars) . '
', 'replace');
	$__finalCompiled .= '

<div class="blockMessage blockMessage--none">
	' . $__templater->callMacro('share_page_macros', 'buttons', array(
		'iconic' => true,
		'label' => 'Share' . $__vars['xf']['language']['label_separator'],
	), $__vars) . '
</div>';
	return $__finalCompiled;
});