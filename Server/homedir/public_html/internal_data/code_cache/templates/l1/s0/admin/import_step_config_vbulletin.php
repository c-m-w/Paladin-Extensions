<?php
// FROM HASH: 4b465b726d01afe74a360caec59f0be1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__templater->fn('in_array', array('users', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Users' . '</h3>
	' . $__templater->callMacro('import_macros', 'step_users_config', array(
			'config' => $__vars['stepConfig']['users'],
		), $__vars) . '

	' . $__templater->formTextBoxRow(array(
			'name' => 'step_config[users][super_admins]',
			'value' => $__vars['baseConfig']['super_admins'],
			'placeholder' => '$config[\'SpecialUsers\'][\'superadministrators\']',
		), array(
			'label' => 'Super administrator user IDs',
			'explain' => 'If you have <b>super administrators</b> defined in your vBulletin <code>config.php</code> file, enter the value from the file here. It will take the form of a single user ID, or a list of IDs separated by commas.',
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('avatars', $__vars['steps'], ), false) AND $__vars['baseConfig']['avatarpath']) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Avatars' . '</h3>
	' . $__templater->formTextBoxRow(array(
			'name' => 'step_config[avatars][path]',
			'value' => $__vars['stepConfig']['avatars']['path'],
		), array(
			'label' => 'Path to avatars directory',
			'explain' => 'Enter the full path to the folder containing your vBulletin avatars. If this can not be found or read, you can clear this path completely to skip importing avatars.',
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('forums', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Forums' . '</h3>
	';
		$__compilerTemp1 = array(array(
			'value' => '0',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		$__compilerTemp2 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
		if ($__templater->isTraversable($__compilerTemp2)) {
			foreach ($__compilerTemp2 AS $__vars['treeEntry']) {
				$__compilerTemp1[] = array(
					'value' => $__vars['treeEntry']['record']['node_id'],
					'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'step_config[forums][parent_node_id]',
			'value' => $__vars['stepConfig']['forums']['parent_node_id'],
		), $__compilerTemp1, array(
			'label' => 'Parent node',
			'explain' => $__templater->filter('If you would like all forums and categories from the source database to be imported into an existing parent forum or category, select it here.

The existing parent / child relationships of the forums to be imported will be maintained regardless of whether or not you import them into an existing forum.', array(array('nl2br', array()),), true),
		)) . '
	';
		if ($__vars['vBulletin5']) {
			$__finalCompiled .= '
		' . $__templater->formRadioRow(array(
				'name' => 'step_config[forums][import_everything]',
				'value' => $__vars['stepConfig']['forums']['import_everything'],
			), array(array(
				'value' => '1',
				'label' => 'Import blogs and groups',
				'_type' => 'option',
			),
			array(
				'value' => '0',
				'label' => 'Import forums only',
				'_type' => 'option',
			)), array(
				'explain' => 'vBulletin 5 also stores content for blogs and social groups in a forum-like format. You can import this content into XenForo as threads and posts if you wish. If this option is not selected, only forums that are chilren of the \'Forum\' channel will be imported.',
			)) . '
	';
		}
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('attachments', $__vars['steps'], ), false) AND $__vars['baseConfig']['attachpath']) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Attachments' . '</h3>
	' . $__templater->formTextBoxRow(array(
			'name' => 'step_config[attachments][path]',
			'value' => $__vars['stepConfig']['attachments']['path'],
		), array(
			'label' => 'Path to attachments directory',
			'explain' => 'Enter the full path to the folder containing your vBulletin attachments. If this can not be found or read, you can clear this value completely, which will cause the importer to skip attachments.',
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('faq', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Custom FAQ pages' . '</h3>
	';
		$__compilerTemp3 = array(array(
			'value' => '0',
			'label' => $__vars['xf']['language']['parenthesis_open'] . 'None' . $__vars['xf']['language']['parenthesis_close'],
			'_type' => 'option',
		));
		$__compilerTemp4 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
		if ($__templater->isTraversable($__compilerTemp4)) {
			foreach ($__compilerTemp4 AS $__vars['treeEntry']) {
				$__compilerTemp3[] = array(
					'value' => $__vars['treeEntry']['record']['node_id'],
					'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formRadioRow(array(
			'name' => 'step_config[faq][import_as]',
			'value' => $__vars['stepConfig']['faq']['import_as'],
		), array(array(
			'value' => 'help',
			'label' => 'Help pages',
			'_type' => 'option',
		),
		array(
			'value' => 'page',
			'label' => 'Page nodes, with parent node' . $__vars['xf']['language']['ellipsis'],
			'_dependent' => array($__templater->formSelect(array(
			'name' => 'step_config[faq][parent_node_id]',
			'value' => $__vars['stepConfig']['faq']['parent_node_id'],
		), $__compilerTemp3)),
			'_type' => 'option',
		)), array(
			'label' => 'Import as',
			'explain' => $__templater->filter('Custom FAQ pages found in the source database can either be imported as XenForo page nodes or help pages.

If you choose to import as page nodes, please select a parent node into which these pages will be placed.

When importing FAQ as help pages, any parent / child relationships between your FAQ pages will be disregarded, though relative ordering will be preserved.', array(array('nl2br', array()),), true),
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('notices', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Notices' . '</h3>
	';
		$__compilerTemp5 = $__templater->mergeChoiceOptions(array(), $__vars['noticeTypes']);
		$__finalCompiled .= $__templater->formRadioRow(array(
			'name' => 'step_config[notices][notice_type]',
			'value' => $__vars['stepConfig']['notices']['notice_type'],
		), $__compilerTemp5, array(
			'label' => 'Import notices as',
		)) . '
	';
		$__compilerTemp6 = $__templater->mergeChoiceOptions(array(), $__vars['noticeTypes']);
		$__finalCompiled .= $__templater->formRadioRow(array(
			'name' => 'step_config[notices][persistent_notice_type]',
			'value' => $__vars['stepConfig']['notices']['persistent_notice_type'],
		), $__compilerTemp6, array(
			'label' => 'Import persistent notices as',
			'explain' => 'Select a format to use for any notices imported from your source database. See https://xenforo.com/xf2-docs/manual/communication/#notices for details of the notice types.',
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('smilies', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Smilies' . '</h3>
	' . $__templater->callMacro('import_macros', 'step_smilies_config', array(
			'config' => $__vars['stepConfig']['smilies'],
		), $__vars) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('blogUsers', $__vars['steps'], ), false)) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Blogs' . '</h3>
	';
		$__compilerTemp7 = array();
		$__compilerTemp8 = $__templater->method($__vars['nodeTree'], 'getFlattened', array(0, ));
		if ($__templater->isTraversable($__compilerTemp8)) {
			foreach ($__compilerTemp8 AS $__vars['treeEntry']) {
				$__compilerTemp7[] = array(
					'value' => $__vars['treeEntry']['record']['node_id'],
					'label' => $__templater->fn('repeat', array('--', $__vars['treeEntry']['depth'], ), true) . ' ' . $__templater->escape($__vars['treeEntry']['record']['title']),
					'_type' => 'option',
				);
			}
		}
		$__finalCompiled .= $__templater->formSelectRow(array(
			'name' => 'step_config[blogUsers][parent_node_id]',
			'value' => $__vars['stepConfig']['blogUsers']['parent_node_id'],
		), $__compilerTemp7, array(
			'label' => 'Parent node',
			'explain' => $__templater->filter('vBulletin blogs will be imported as forum nodes with \'Post new thread\' permissions limited to the original blog owner. For ease of grouping and moderation, select an existing node into which these forums should be inserted. If a suitable node does not already exist, go back to the node editor and create a new Category-type node, then select it when you return to this page.', array(array('nl2br', array()),), true),
		)) . '
';
	}
	$__finalCompiled .= '

';
	if ($__templater->fn('in_array', array('blogAttachments', $__vars['steps'], ), false) AND $__vars['baseConfig']['blogattachpath']) {
		$__finalCompiled .= '
	<h3 class="block-formSectionHeader">' . 'Blog attachments' . '</h3>
	' . $__templater->formTextBoxRow(array(
			'name' => 'step_config[blogAttachments][path]',
			'value' => $__vars['stepConfig']['blogAttachments']['path'],
		), array(
			'label' => 'import_blog_attachments_path',
			'explain' => 'import_blog_attachments_path_vbulletin_explain',
		)) . '
';
	}
	return $__finalCompiled;
});