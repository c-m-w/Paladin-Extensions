<?php
// FROM HASH: e6254aac391105cb9d9887280f82fe41
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__templater->includeJs(array(
		'src' => 'themehouse/global/20180112.js',
		'min' => 'themehouse/global/20180112.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/index.js',
		'min' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/index.min.js',
	));
	$__finalCompiled .= '
';
	$__templater->includeJs(array(
		'src' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/defer.js',
		'min' => 'themehouse/' . $__templater->fn('property', array('uix_jsPath', ), false) . '/defer.min.js',
		'defer' => 'defer',
	));
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_clickableThreads', ), false)) {
		$__finalCompiled .= '
';
		$__templater->inlineJs('
	$(document).ready(function() {
		$(\'.structItem--thread\').click(function() {
			var href = $(this).find(\'.structItem-title\').attr(\'uix-data-href\');
			window.location = href;
		});
	});
');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

' . '

';
	if ($__templater->fn('property', array('uix_sidebarMobileCanvas', ), false)) {
		$__finalCompiled .= '
	';
		$__templater->inlineJs('
		$(document).ready(function() {
			var sidebar = $(\'.p-body-sidebar\');
			var backdrop = $(\'.p-body-sidebar [data-ocm-class="offCanvasMenu-backdrop"]\');

			$(\'.uix_sidebarCanvasTrigger\').click(function(e) {
				e.preventDefault();
				sidebar.addClass(\'offCanvasMenu offCanvasMenu--blocks is-active is-transitioning\');
				$(\'body\').addClass(\'sideNav--open\');

				window.setTimeout(function() {
					sidebar.removeClass(\'is-transitioning\');
				}, 250);

				$(\'.uix_sidebarInner\').addClass(\'offCanvasMenu-content\');
				backdrop.addClass(\'offCanvasMenu-backdrop\');
				$(\'body\').addClass(\'is-modalOpen\');
			});

			backdrop.click(function() {
				sidebar.addClass(\'is-transitioning\');
				sidebar.removeClass(\'is-active\');

				window.setTimeout(function() {
					sidebar.removeClass(\'offCanvasMenu offCanvasMenu--blocks is-transitioning\');
					$(\'.uix_sidebarInner\').removeClass(\'offCanvasMenu-content\');
					backdrop.removeClass(\'offCanvasMenu-backdrop\');
					$(\'body\').removeClass(\'is-modalOpen\');
				}, 250);
			})
		});
	');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

';
	$__templater->inlineJs('
	/****** OFF CANVAS ***/
	$(document).ready(function() {
		var panels = {
			navigation: {
				position: 1
			},
			account: {
				position: 2
			},
			inbox: {
				position: 3
			},
			alerts: {
				position: 4
			}
		};


		var tabsContainer = $(\'.sidePanel__tabs\');

		var activeTab = \'navigation\';

		var activeTabPosition = panels[activeTab].position;

		var generateDirections = function() {
			$(\'.sidePanel__tabPanel\').each(function() {
				var tabPosition = $(this).attr(\'data-content\');
				var activeTabPosition = panels[activeTab].position;

				if (tabPosition != activeTab) {
					if (panels[tabPosition].position < activeTabPosition) {
						$(this).addClass(\'is-left\');
					}

					if (panels[tabPosition].position > activeTabPosition) {
						$(this).addClass(\'is-right\');
					}
				}
			});
		};

		generateDirections();

		$(\'.sidePanel__tab\').click(function() {
			$(tabsContainer).find(\'.sidePanel__tab\').removeClass(\'sidePanel__tab--active\');
			$(this).addClass(\'sidePanel__tab--active\');

			activeTab = $(this).attr(\'data-attr\');

			$(\'.sidePanel__tabPanel\').removeClass(\'is-active\');

			$(\'.sidePanel__tabPanel[data-content="\' + activeTab + \'"]\').addClass(\'is-active\');
			$(\'.sidePanel__tabPanel\').removeClass(\'is-left\').removeClass(\'is-right\');
			generateDirections();
		});
	});

	/******** extra info post toggle ***********/

	$(document).ready(function() {
		$(\'.thThreads__userExtra--trigger\').click(function() {
			var parent =  $(this).parents(\'.message-cell--user\');
			var triggerContainer = $(this).parent(\'.thThreads__userExtra--toggle\');
			var container = triggerContainer.siblings(\'.thThreads__message-userExtras\');
			var child = container.find(\'.message-userExtras\');
			var eleHeight = child.height();
			if (parent.hasClass(\'userExtra--expand\')) {
				container.css({ height: eleHeight });
				parent.toggleClass(\'userExtra--expand\');
				window.setTimeout(function() {
					container.css({ height: \'0\' });
					window.setTimeout(function() {
						container.css({ height: \'\' });
					}, 200);
				}, 17);

			} else {
				parent.toggleClass(\'userExtra--expand\');
				container.css({ height: eleHeight });
				window.setTimeout(function() {
					container.css({ height: \'\' });
				}, 200);
			}
		});
	});

	/******** Backstretch images ***********/
	$(document).ready(function() {
		if ( ' . $__templater->fn('property', array('uix_backstretch', ), false) . ' ) {

			$("' . $__templater->fn('property', array('uix_backstretchSelector', ), false) . '").addClass(\'uix__hasBackstretch\');

			 $("' . $__templater->fn('property', array('uix_backstretchSelector', ), false) . '").backstretch([
				 ' . $__templater->filter($__vars['__globals']['uix_backstretchImages'], array(array('raw', array()),), false) . '
		  ], {
				duration: ' . $__templater->fn('property', array('uix_backstretchDuration', ), false) . ',
				fade: ' . $__templater->fn('property', array('uix_backstretchFade', ), false) . '
			});

			$("' . $__templater->fn('property', array('uix_backstretchSelector', ), false) . '").css("zIndex","");
		}
	});

	// sidenav canvas blur fix

	$(document).ready(function(){
		$(\'.p-body-sideNavTrigger .button\').click(function(){
			$(\'body\').addClass(\'sideNav--open\');
		});
	})

	$(document).ready(function(){
		$("[data-ocm-class=\'offCanvasMenu-backdrop\']").click(function(){
			$(\'body\').removeClass(\'sideNav--open\');
		});
	})

	$(document).on(\'editor:start\', function (m, ed) {
		if (typeof (m) !== \'undefined\' && typeof (m.target) !== \'undefined\') {
			var ele = $(m.target);
			if (ele.hasClass(\'js-editor\')) {
				var wrapper = ele.closest(\'.message-editorWrapper\');
				if (wrapper.length) {
					window.setTimeout(function() {
						var innerEle = wrapper.find(\'.fr-element\');
						if (innerEle.length) {
							innerEle.focus(function (e) {
								$(\'html\').addClass(\'uix_editor--focused\')
							});
							innerEle.blur(function (e) {
								$(\'html\').removeClass(\'uix_editor--focused\')
							});
						}
					}, 0);
				}
			}
		}
	});
');
	$__finalCompiled .= '

';
	if ($__templater->fn('property', array('uix_parallax', ), false)) {
		$__finalCompiled .= '
	';
		$__templater->inlineJs('
		var parallaxSelector = "' . $__templater->fn('property', array('uix_parallaxSelector', ), false) . '"
		var parallaxImage = "' . $__templater->fn('base_url', array($__templater->fn('property', array('uix_parallaxImage', ), false), ), false) . '"
		var parallaxPosition = "' . $__templater->fn('property', array('uix_parallaxPosition', ), false) . '"
		$(parallaxSelector).parallax({imageSrc: parallaxImage, positionY: parallaxPosition});
	');
		$__finalCompiled .= '
';
	}
	$__finalCompiled .= '

	
';
	$__templater->inlineJs('
	$(document).ready(function() {
	$(\'.uix_threadCollapseTrigger\').click(function(e) {
		e.preventDefault();
		var container = $(\'.uix_stickyContainerOuter\');
		var child = container.find(\'.structItemContainer-group--sticky\');
		var eleHeight = child.height();
		if (container.hasClass(\'uix_threadListSeparator--collapsed\')) {
			container.toggleClass(\'uix_threadListSeparator--collapsed\');
			container.css({ height: eleHeight });
			window.setTimeout(function() {
				container.css({ height: \'\' });
			}, 200);
		} else {
			container.css({ height: eleHeight });
			container.toggleClass(\'uix_threadListSeparator--collapsed\');
			window.setTimeout(function() {
				container.css({ height: \'0\' });
				window.setTimeout(function() {
					container.css({ height: \'\' });
				}, 200);
			}, 17);

		}
	});
});
');
	return $__finalCompiled;
});