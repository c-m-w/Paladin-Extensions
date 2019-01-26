<?php
// FROM HASH: 233bca93e0350447b9aac93f3c1bd40d
return array('macros' => array('simple_list_block' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'selected' => 0,
	), $__arguments, $__vars);
	$__finalCompiled .= '
	';
	$__vars['categories'] = $__templater->method($__templater->method($__vars['xf']['app']['em'], 'getRepository', array('MJ\\SupportTicket:KnowledgeBase', )), 'getKbCategories', array());
	$__finalCompiled .= '

	<div class="block">
		<div class="block-container">
			<h3 class="block-header">' . 'Knowledge base categories' . '</h3>
			<div class="block-body">
				';
	if (!$__templater->test($__vars['categories'], 'empty', array())) {
		$__finalCompiled .= '
					<ol class="categoryList is-active">
						';
		if ($__templater->isTraversable($__vars['categories'])) {
			foreach ($__vars['categories'] AS $__vars['id'] => $__vars['kbCategory']) {
				$__finalCompiled .= '
							';
				$__vars['isSelected'] = ($__vars['kbCategory']['kb_category_id'] == $__vars['selected']);
				$__finalCompiled .= '
							<li class="categoryList-item">
								<div class="categoryList-itemRow">
									<a href="' . $__templater->fn('link', array('support-tickets/knowledge-base/category', $__vars['kbCategory'], ), true) . '" title="' . $__templater->escape($__vars['kbCategory']['title']) . '" class="categoryList-link' . ($__vars['isSelected'] ? ' is-selected' : '') . '">
										' . $__templater->escape($__vars['kbCategory']['title']) . '
									</a>
									<span class="categoryList-label">
										<span class="label label--subtle label--smallest">' . $__templater->filter($__templater->method($__vars['kbCategory']['KnowledgeBases'], 'count', array()), array(array('number_short', array()),), true) . '</span>
									</span>
								</div>
							</li>
						';
			}
		}
		$__finalCompiled .= '
					</ol>
				';
	} else {
		$__finalCompiled .= '
					<div class="block-row">' . 'N/A' . '</div>
				';
	}
	$__finalCompiled .= '
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped($__templater->escape($__vars['kbCategory']['title']));
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '
';
	$__templater->pageParams['pageDescription'] = $__templater->preEscaped($__templater->filter($__vars['kbCategory']['description'], array(array('raw', array()),), true));
	$__templater->pageParams['pageDescriptionMeta'] = true;
	$__finalCompiled .= '

';
	$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_kb', ), ));
	$__finalCompiled .= '

';
	$__templater->breadcrumb($__templater->preEscaped('Knowledge base'), $__templater->fn('link', array('support-tickets/knowledge-base', ), false), array(
	));
	$__finalCompiled .= '
';
	$__templater->breadcrumb($__templater->preEscaped($__templater->escape($__vars['kbCategory']['title'])), $__templater->fn('link', array('support-tickets/knowledge-base/category', $__vars['kbCategory'], ), false), array(
	));
	$__finalCompiled .= '

';
	$__templater->includeCss('mjst_kb.less');
	$__finalCompiled .= '

';
	$__vars['fpSnippet'] = $__templater->fn('snippet', array($__vars['kbCategory']['description'], 0, array('stripBbCode' => true, ), ), false);
	$__finalCompiled .= '

' . $__templater->callMacro('metadata_macros', 'metadata', array(
		'description' => $__vars['fpSnippet'],
		'shareUrl' => $__templater->fn('link', array('canonical:support-tickets/knowledge-base/category', $__vars['kbCategory'], array('page' => $__vars['page'], ), ), false),
		'canonicalUrl' => $__templater->fn('link', array('canonical:support-tickets/knowledge-base/category', $__vars['kbCategory'], ), false),
	), $__vars) . '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('mjstKb', 'create', ))) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Create knowledge base' . $__vars['xf']['language']['ellipsis'], array(
			'href' => $__templater->fn('link', array('support-tickets/knowledge-base/create', '', array('kb_category_id' => $__vars['kbCategory']['kb_category_id'], ), ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

<div class="block">
	<div class="block-outer">' . trim('
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets/knowledge-base/category',
		'data' => $__vars['kbCategory'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	') . '</div>

	<div class="block-container">
		<ul class="kbItems u-clearFix">
			';
	if ($__templater->isTraversable($__vars['kbs'])) {
		foreach ($__vars['kbs'] AS $__vars['id'] => $__vars['kb']) {
			$__finalCompiled .= '
				' . $__templater->callMacro('mjst_kb_index', 'kb_item', array(
				'kb' => $__vars['kb'],
			), $__vars) . '
			';
		}
	}
	$__finalCompiled .= '
		</ul>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets/knowledge-base/category',
		'data' => $__vars['kbCategory'],
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	</div>
</div>

';
	$__templater->modifySideNavHtml(null, '
	' . $__templater->callMacro(null, 'simple_list_block', array(), $__vars) . '
', 'replace');
	$__finalCompiled .= '

';
	return $__finalCompiled;
});