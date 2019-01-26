<?php
// FROM HASH: 3b293657a50ef0a921fe117bb089dd52
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['kbs'] AND !$__templater->test($__vars['kbs'], 'empty', array())) {
		$__finalCompiled .= '
<div class="mjstKnowledgeBase">
	<h3 class="block-header block-header--separated">
		<span class="collapseTrigger collapseTrigger--block is-active" data-xf-click="toggle" data-target="< :up :next" data-xf-init="toggle-storage" data-storage-key="sp-publicFooter">
			<span class="u-anchorTarget" id="sp-publicFooter"></span><span>' . 'Knowledge Base Suggestions' . '</span>
			<span class="block-desc">' . 'The following articles were found in the knowledge base which may answer your question. Please review the suggestions before submission.' . '</span>
		</span>
	</h3>
	<div class="block-body block-body--collapsible is-active">
		<div class="block-row">
			<ul class="listPlain">
				';
		if ($__templater->isTraversable($__vars['kbs'])) {
			foreach ($__vars['kbs'] AS $__vars['kb']) {
				$__finalCompiled .= '
				<li class="block-row">
					<a href="' . $__templater->fn('link', array('support-tickets/knowledge-base', $__vars['kb'], ), true) . '" class="fauxBlockLink-blockLink" title="' . $__templater->escape($__vars['kb']['title']) . '" target="_blank">
						' . $__templater->escape($__vars['kb']['title']) . '
					</a>
					';
				if ($__vars['xf']['options']['mjstKbPreLength']) {
					$__finalCompiled .= '
						<div class="kbSnippet">' . $__templater->fn('snippet', array($__vars['kb']['message'], $__vars['xf']['options']['mjstKbPreLength'], array('stripBbCode' => true, ), ), true) . '</div>
					';
				}
				$__finalCompiled .= '
				</li>
				';
			}
		}
		$__finalCompiled .= '
			</ul>
		</div>
	</div>
</div>
';
	} else {
		$__finalCompiled .= '
	<div></div>
';
	}
	return $__finalCompiled;
});