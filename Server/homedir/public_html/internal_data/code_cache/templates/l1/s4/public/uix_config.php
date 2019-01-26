<?php
// FROM HASH: d55543703546cdb8bbdb14b4ff9f07c1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<script>
	if (typeof (window.themehouse) !== \'object\') {
		window.themehouse = {};
	}
	if (typeof (window.themehouse.settings) !== \'object\') {
		window.themehouse.settings = {};
	}
	window.themehouse.settings = {
		common: {
			\'20180112\': {
				init: false,
			},
		},
		data: {
			version: \'' . $__templater->fn('property', array('uix_version', ), true) . '\',
			jsVersion: \'No JS Files\',
			templateVersion: \'2.0.10.0_Release\',
			betaMode: ' . $__templater->fn('property', array('uix_betaMode', ), true) . ',
			theme: \'\',
			url: \'' . $__templater->filter($__templater->fn('base_url', array(null, true, ), false), array(array('escape', array('js', )),), true) . '\',
			user: \'' . $__templater->escape($__vars['xf']['visitor']['user_id']) . '\',
		},
		inputSync: {},
		minimalSearch: {
			breakpoint: "' . (0 + $__templater->fn('property', array('uix_search_maxResponsiveWidth', ), false)) . '",
			dropdownBreakpoint: "' . (0 + $__templater->fn('property', array('uix_search_maxResponsiveWidth', ), false)) . '",
		},
		sidebar: {
            enabled: \'' . $__templater->escape($__vars['uix_canCollapseSidebar']) . '\',
			link: \'' . $__templater->fn('link', array('uix/toggle-sidebar.json', ), true) . '\',
            state: \'' . $__templater->escape($__vars['uix_sidebarCollapsed']) . '\',
		},
        sidebarNav: {
            enabled: \'' . $__templater->escape($__vars['uix_canCollapseSidebarNav']) . '\',
			link: \'' . $__templater->fn('link', array('uix/toggle-sidebar-navigation.json', ), true) . '\',
            state: \'' . $__templater->escape($__vars['uix_sidebarNavCollapsed']) . '\',
		},
		fab: {
			enabled: ' . $__templater->fn('property', array('uix_fabScroll', ), true) . ',
		},
		checkRadius: {
			enabled: ' . $__templater->fn('property', array('uix_borderRadiusJs', ), true) . ',
			selectors: \'' . $__templater->fn('property', array('uix_borderRadiusSelectors', ), true) . '\',
		},
		nodes: {
			enabled: ' . $__templater->fn('property', array('uix_nodeClickable', ), true) . ',
		},
        nodesCollapse: {
            enabled: \'' . $__templater->escape($__vars['uix_canCollapseCategories']) . '\',
			link: \'' . $__templater->fn('link', array('uix/toggle-category.json', ), true) . '\',
			state: \'' . $__templater->escape($__vars['uix_collapsedCategoriesJson']) . '\',
        },
		widthToggle: {
			enabled: \'' . $__templater->escape($__vars['uix_canTogglePageWidth']) . '\',
			link: \'' . $__templater->fn('link', array('uix/toggle-width.json', ), true) . '\',
			state: \'' . $__templater->escape($__vars['uix_pageWidth']) . '\',
		},
	}

	window.document.addEventListener(\'DOMContentLoaded\', function() {
		';
	if ($__templater->fn('property', array('uix_betaMode', ), false)) {
		$__finalCompiled .= '
			window.themehouse.common[\'20180112\'].init();
		';
	} else {
		$__finalCompiled .= '
			try {
			   window.themehouse.common[\'20180112\'].init();
			} catch(e) {
			   console.log(\'Error caught\', e);
			}
		';
	}
	$__finalCompiled .= '


		var jsVersionPrefix = \'No JS Files\';
		if (typeof(window.themehouse.settings.data.jsVersion) === \'string\') {
			var jsVersionSplit = window.themehouse.settings.data.jsVersion.split(\'_\');
			if (jsVersionSplit.length) {
				jsVersionPrefix = jsVersionSplit[0];
			}
		}
		var templateVersionPrefix = \'No JS Template Version\';
		if (typeof(window.themehouse.settings.data.templateVersion) === \'string\') {
			var templateVersionSplit = window.themehouse.settings.data.templateVersion.split(\'_\');
			if (templateVersionSplit.length) {
				templateVersionPrefix = templateVersionSplit[0];
			}
		}
		if (jsVersionPrefix !== templateVersionPrefix) {
			var splitFileVersion = jsVersionPrefix.split(\'.\');
			var splitTemplateVersion = templateVersionPrefix.split(\'.\');
			console.log(\'version mismatch\', jsVersionPrefix, templateVersionPrefix);
		}

	});
</script>';
	return $__finalCompiled;
});