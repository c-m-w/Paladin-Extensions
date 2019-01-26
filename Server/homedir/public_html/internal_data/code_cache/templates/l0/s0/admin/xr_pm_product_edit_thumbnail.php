<?php
// FROM HASH: 3903b36921bc67e3e73dd09fe69c44a4
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->pageParams['pageTitle'] = $__templater->preEscaped('Edit thumbnail' . $__vars['xf']['language']['label_separator'] . ' ' . $__templater->escape($__vars['product']['product_title']));
	$__finalCompiled .= '

';
	$__compilerTemp1 = '';
	if ($__vars['product']['has_thumbnail']) {
		$__compilerTemp1 .= '
							<img src="' . $__templater->escape($__vars['product']['thumbnail_url']) . '" alt="' . $__templater->escape($__vars['product']['product_title']) . '" />
						';
	} else {
		$__compilerTemp1 .= '
							<a style="pointer-events: none"><i class="fa fa-file-o fa-3x" aria-hidden="true"></i></a>
						';
	}
	$__finalCompiled .= $__templater->form('
	<div class="block-container">
		<div class="block-blody">
			' . $__templater->formRow('
				<div class="contentRow contentRow--alignMiddle">
					<div class="contentRow-figure contentRow-figure--fixedSmall">
						' . $__compilerTemp1 . '
					</div>
					<div class="contentRow-main">
						<a href="' . $__templater->fn('link', array('attachments/view', $__vars['product']['Thumbnail'], ), true) . '">' . $__templater->escape($__vars['product']['Thumbnail']['filename']) . '</a>
					</div>
				</div>
			', array(
		'label' => 'Thumbnail',
	)) . '
			' . $__templater->formRow('
				' . $__templater->callMacro('public:xr_pm_attach_upload_macros', 'upload_block', array(
		'attachmentData' => $__vars['thumbAttachData'],
		'hiddenName' => 'thumb_attach_hash',
		'label' => 'Upload thumbnail',
	), $__vars) . '
			', array(
		'label' => '',
		'rowtype' => 'button',
	)) . '
		</div>
		' . $__templater->formSubmitRow(array(
		'icon' => 'save',
	), array(
		'html' => '
			' . $__templater->button('', array(
		'type' => 'submit',
		'name' => 'delete',
		'icon' => 'delete',
	), '', array(
	)) . '
		',
	)) . '
	</div>
', array(
		'action' => $__templater->fn('link', array('product-manager/products/edit-thumbnail', $__vars['product'], ), false),
		'ajax' => 'true',
		'class' => 'block',
	));
	return $__finalCompiled;
});