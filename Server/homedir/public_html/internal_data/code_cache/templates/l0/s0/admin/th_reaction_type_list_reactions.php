<?php
// FROM HASH: 20eb26da1d377df88e802ea8dd9e5142
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Reaction types');
	$__finalCompiled .= '

';
	$__templater->pageParams['pageAction'] = $__templater->preEscaped('
	<div class="buttonGroup">
		' . $__templater->button('Add reaction type', array(
		'href' => $__templater->fn('link', array('reaction-types/add', ), false),
		'icon' => 'add',
	), '', array(
	)) . '
	</div>
');
	$__finalCompiled .= '

';
	$__templater->includeCss('public:th_reactions.less');
	$__finalCompiled .= '

';
	if (!$__templater->test($__vars['reactionTypes'], 'empty', array())) {
		$__finalCompiled .= '
	';
		$__compilerTemp1 = '';
		if ($__templater->isTraversable($__vars['reactionTypes'])) {
			foreach ($__vars['reactionTypes'] AS $__vars['reactionTypeId'] => $__vars['reactionType']) {
				$__compilerTemp1 .= '
						<tbody class="dataList-rowGroup">
							' . $__templater->dataRow(array(
				), array(array(
					'href' => $__templater->fn('link', array('reaction-types/edit', $__vars['reactionType'], ), false),
					'class' => 'dataList-cell--min dataList-cell--image dataList-cell--imageSmall',
					'_type' => 'cell',
					'html' => '
									<img src="data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==" style="background-color: ' . $__templater->escape($__vars['reactionType']['color']) . ';" />
								',
				),
				array(
					'href' => $__templater->fn('link', array('reaction-types/edit', $__vars['reactionType'], ), false),
					'_type' => 'cell',
					'html' => '
									' . $__templater->escape($__vars['reactionType']['title']) . '
								',
				),
				array(
					'href' => $__templater->fn('link', array('reaction-types/delete', $__vars['reactionType'], ), false),
					'_type' => 'delete',
					'html' => '',
				))) . '
						</tbody>
					';
			}
		}
		$__finalCompiled .= $__templater->form('
		<div class="block-outer">
			' . $__templater->callMacro('filter_macros', 'quick_filter', array(
			'key' => 'reaction-types',
			'class' => 'block-outer-opposite',
		), $__vars) . '
		</div>

		<div class="block-container">
			<div class="block-body">
				' . $__templater->dataList('
					' . $__compilerTemp1 . '
				', array(
		)) . '
			</div>
		</div>
	', array(
			'action' => $__templater->fn('link', array('reaction-types/toggle', ), false),
			'ajax' => 'true',
			'class' => 'block',
		)) . '
';
	} else {
		$__finalCompiled .= '
	<div class="blockMessage">' . 'No reaction types have been added yet.' . '</div>
';
	}
	return $__finalCompiled;
});