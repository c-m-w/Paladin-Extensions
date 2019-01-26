<?php
// FROM HASH: 6385adfdd57175f5d030fc0f2ea2ef88
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('count', array($__vars['preRepliesInfo']['repliesGrouped'], ), false) > 1) {
		$__finalCompiled .= '
	<div>
		<h3 class="tabs tabs--editor hScroller" data-xf-init="tabs h-scroller" role="tablist">
			<span class="hScroller-scroll">
			';
		$__vars['i'] = 0;
		if ($__templater->isTraversable($__vars['preRepliesInfo']['replyGroups'])) {
			foreach ($__vars['preRepliesInfo']['replyGroups'] AS $__vars['groupId'] => $__vars['group']) {
				if (!$__templater->test($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']], 'empty', array())) {
					$__vars['i']++;
					$__finalCompiled .= '
				<a class="tabs-tab ' . (($__vars['i'] == 1) ? 'is-active' : '') . '"
					role="tab" tabindex="0" aria-controls="' . $__templater->fn('unique_id', array('repliesGrouped' . $__vars['i'], ), true) . '">' . ($__vars['groupId'] ? $__templater->escape($__vars['group']['title']) : $__vars['xf']['language']['parenthesis_open'] . 'Ungrouped' . $__vars['xf']['language']['parenthesis_close']) . '</a>
			';
				}
			}
		}
		$__finalCompiled .= '
			</span>
		</h3>

		<ul class="tabPanes is-structureList">
			';
		$__vars['i'] = 0;
		if ($__templater->isTraversable($__vars['preRepliesInfo']['replyGroups'])) {
			foreach ($__vars['preRepliesInfo']['replyGroups'] AS $__vars['groupId'] => $__vars['group']) {
				if (!$__templater->test($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']], 'empty', array())) {
					$__vars['i']++;
					$__finalCompiled .= '

				<li class="' . (($__vars['i'] == 1) ? 'is-active' : '') . ' reply" role="tabpanel" id="' . $__templater->fn('unique_id', array('repliesGrouped' . $__vars['i'], ), true) . '">
					<ul class="listPlain is-structureList">
					';
					if ($__templater->isTraversable($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']])) {
						foreach ($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']] AS $__vars['reply']) {
							$__finalCompiled .= '
						<li class="reply" data-fullmessage="">
							<div class="replyTitle">' . $__templater->escape($__vars['reply']['title']) . '</div>
							<div class="block-rowMessage">' . $__templater->fn('snippet', array($__vars['reply']['message'], $__vars['xf']['options']['mjstReplySnippetLength'], array('stripBbCode' => true, ), ), true) . '</div>
							<div class="reply-full">' . $__templater->fn('bb_code', array($__vars['reply']['message'], 'support_pre_reply', $__vars['reply'], ), true) . '</div>
						</li>
					';
						}
					}
					$__finalCompiled .= '
					</ul>
				</li>
			';
				}
			}
		}
		$__finalCompiled .= '
		</ul>
	</div>
';
	} else {
		$__finalCompiled .= '
	<div class="block-body block-row">
	';
		$__vars['i'] = 0;
		if ($__templater->isTraversable($__vars['preRepliesInfo']['replyGroups'])) {
			foreach ($__vars['preRepliesInfo']['replyGroups'] AS $__vars['groupId'] => $__vars['group']) {
				if (!$__templater->test($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']], 'empty', array())) {
					$__vars['i']++;
					$__finalCompiled .= '
		<ul class="listPlain is-structureList">
		';
					if ($__templater->isTraversable($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']])) {
						foreach ($__vars['preRepliesInfo']['repliesGrouped'][$__vars['groupId']] AS $__vars['reply']) {
							$__finalCompiled .= '
			<li class="reply">
				<div class="replyTitle">' . $__templater->escape($__vars['reply']['title']) . '</div>
				<div class="block-rowMessage">' . $__templater->fn('snippet', array($__vars['reply']['message'], $__vars['xf']['options']['mjstReplySnippetLength'], array('stripBbCode' => true, ), ), true) . '</div>
				<div class="reply-full">' . $__templater->fn('bb_code', array($__vars['reply']['message'], 'support_pre_reply', $__vars['reply'], ), true) . '</div>
			</li>
		';
						}
					}
					$__finalCompiled .= '
		</ul>
	';
				}
			}
		}
		$__finalCompiled .= '
	</div>
';
	}
	return $__finalCompiled;
});