<?php
// FROM HASH: be3d808fe2cb07c3adadceb8ef557a79
return array('macros' => array('kb_category' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'kbCategory' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block-row block-row--clickable block-row--separated fauxBlockLink">
		<div class="contentRow contentRow--alignMiddle">
			<div class="contentRow-main">
				<h3 class="contentRow-title">
					<a href="' . $__templater->fn('link', array('support-tickets/knowledge-base/category', $__vars['kbCategory'], ), true) . '" class="fauxBlockLink-blockLink" title="' . $__templater->escape($__vars['kbCategory']['title']) . '">
						' . $__templater->escape($__vars['kbCategory']['title']) . '
					</a>
				</h3>
				';
	if ($__vars['kbCategory']['description']) {
		$__finalCompiled .= '
					<div class="contentRow-minor contentRow-minor--singleLine">
						' . $__templater->filter($__vars['kbCategory']['description'], array(array('strip_tags', array()),), true) . '
					</div>
				';
	}
	$__finalCompiled .= '
			</div>
			<div class="contentRow-suffix">
				<dl class="pairs pairs--rows pairs--rows--centered">
					<dt>' . 'Knowledge bases' . '</dt>
					<dd>' . $__templater->filter($__templater->method($__vars['kbCategory']['KnowledgeBases'], 'count', array()), array(array('number_short', array()),), true) . '</dd>
				</dl>
			</div>
		</div>
	</div>
';
	return $__finalCompiled;
},
'kb_item' => function($__templater, array $__arguments, array $__vars)
{
	$__vars = $__templater->setupBaseParamsForMacro($__vars, false);
	$__finalCompiled = '';
	$__vars = $__templater->mergeMacroArguments(array(
		'kb' => '!',
	), $__arguments, $__vars);
	$__finalCompiled .= '
	<div class="block-row block-row--clickable block-row--separated fauxBlockLink">
		<div class="contentRow contentRow--alignMiddle">
			<div class="contentRow-main">
				<h3 class="contentRow-title">
					';
	if ($__vars['xf']['options']['mjstDisplayFullKb']) {
		$__finalCompiled .= '
					<a class="collapseTrigger collapseTrigger--block" title="' . $__templater->escape($__vars['kb']['title']) . '" data-xf-click="toggle" data-target="< :up:next">
						<span class="block-formSectionHeader-aligner">' . $__templater->escape($__vars['kb']['title']) . '</span>
					</a>
					';
	} else {
		$__finalCompiled .= '
					<a href="' . $__templater->fn('link', array('support-tickets/knowledge-base', $__vars['kb'], ), true) . '" title="' . $__templater->escape($__vars['kb']['title']) . '" class="fauxBlockLink-blockLink">
						' . $__templater->escape($__vars['kb']['title']) . '
					</a>
					';
	}
	$__finalCompiled .= '
				</h3>
				';
	if ($__vars['kb']['message']) {
		$__finalCompiled .= '
					';
		if (!$__vars['xf']['options']['mjstDisplayFullKb']) {
			$__finalCompiled .= '
						<div class="contentRow-minor contentRow-minor--singleLine">
							' . $__templater->fn('snippet', array($__vars['kb']['message'], $__vars['xf']['options']['mjstKbPreLength'], array('stripQuote' => true, ), ), true) . '
						</div>
					';
		} else {
			$__finalCompiled .= '
						<div class="block-body block-body--collapsible">
							' . $__templater->fn('bb_code', array($__vars['kb']['message'], 'support_kb', $__vars['kb'], ), true) . '
						</div>
					';
		}
		$__finalCompiled .= '
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
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Knowledge bases');
	$__templater->pageParams['pageNumber'] = $__vars['page'];
	$__finalCompiled .= '

';
	$__templater->setPageParam('searchConstraints', array('Tickets' => array('search_type' => 'support_kb', ), ));
	$__finalCompiled .= '

';
	if ($__templater->method($__vars['xf']['visitor'], 'hasPermission', array('mjstKb', 'create', ))) {
		$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	' . $__templater->button('Create knowledge base' . $__vars['xf']['language']['ellipsis'], array(
			'href' => $__templater->fn('link', array('support-tickets/knowledge-base/create', ), false),
			'class' => 'button--cta',
			'icon' => 'write',
			'overlay' => 'true',
		), '', array(
		)) . '
');
	}
	$__finalCompiled .= '

';
	$__templater->includeCss('mjst_kb.less');
	$__finalCompiled .= '

<div class="block block--treeEntryChooser">
	<div class="block-outer">' . trim('
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets/knowledge-base',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	') . '</div>

	<div class="block-container">
		<div class="kbBlocks">
			';
	if ($__vars['kbs'] AND !$__templater->test($__vars['kbs'], 'empty', array())) {
		$__finalCompiled .= '
			<div class="kbBlock">
			';
	}
	$__finalCompiled .= '
				<h3 class="block-textHeader">
					<span class="kbBlockBlock-title">' . 'Knowledge base categories' . '</span>
				</h3>
				';
	if (!$__templater->test($__vars['kbCategories'], 'empty', array())) {
		$__finalCompiled .= '
				';
		if ($__templater->isTraversable($__vars['kbCategories'])) {
			foreach ($__vars['kbCategories'] AS $__vars['id'] => $__vars['kbCategory']) {
				$__finalCompiled .= '
					' . $__templater->callMacro(null, 'kb_category', array(
					'kbCategory' => $__vars['kbCategory'],
				), $__vars) . '
				';
			}
		}
		$__finalCompiled .= '
				';
	} else {
		$__finalCompiled .= '
					<div class="block-row">' . 'N/A' . '</div>
				';
	}
	$__finalCompiled .= '
			';
	if ($__vars['kbs'] AND !$__templater->test($__vars['kbs'], 'empty', array())) {
		$__finalCompiled .= '
			</div>
			<div class="kbBlock">
				<h3 class="block-textHeader">
					<span class="kbBlockBlock-title">' . 'Frequently asked questions' . '</span>
				</h3>
				';
		if ($__templater->isTraversable($__vars['kbs'])) {
			foreach ($__vars['kbs'] AS $__vars['id'] => $__vars['kb']) {
				$__finalCompiled .= '
					' . $__templater->callMacro(null, 'kb_item', array(
					'kb' => $__vars['kb'],
				), $__vars) . '
				';
			}
		}
		$__finalCompiled .= '
			</div>
			';
	}
	$__finalCompiled .= '
		</div>
	</div>

	<div class="block-outer block-outer--after">
		' . $__templater->fn('page_nav', array(array(
		'page' => $__vars['page'],
		'total' => $__vars['total'],
		'link' => 'support-tickets/knowledge-base',
		'wrapperclass' => 'block-outer-main',
		'perPage' => $__vars['perPage'],
	))) . '
	</div>
</div>

' . '

';
	return $__finalCompiled;
});