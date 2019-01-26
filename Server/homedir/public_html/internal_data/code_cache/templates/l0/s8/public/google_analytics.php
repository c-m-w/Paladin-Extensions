<?php
// FROM HASH: e38955401573cc34c3c2aa5b85ac9d38
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	if ($__vars['xf']['options']['googleAnalyticsWebPropertyId']) {
		$__finalCompiled .= '
	';
		if ($__vars['xf']['cookie']['domain']) {
			$__finalCompiled .= '
		';
			$__vars['gaConfig'] = $__templater->preEscaped('{\'cookie_domain\': \'' . $__templater->escape($__vars['xf']['cookie']['domain']) . '\'}');
			$__finalCompiled .= '
	';
		} else {
			$__finalCompiled .= '
		';
			$__vars['gaConfig'] = $__templater->preEscaped('{}');
			$__finalCompiled .= '
	';
		}
		$__finalCompiled .= '
	<script async src="https://www.googletagmanager.com/gtag/js?id=' . $__templater->escape($__vars['xf']['options']['googleAnalyticsWebPropertyId']) . '"></script>
	<script>
		window.dataLayer = window.dataLayer || [];
		function gtag(){dataLayer.push(arguments);}
		gtag(\'js\', new Date());
		gtag(\'config\', \'' . $__templater->filter($__vars['xf']['options']['googleAnalyticsWebPropertyId'], array(array('escape', array('js', )),), true) . '\', {
			// ' . '
			';
		if ($__vars['xf']['cookie']['domain']) {
			$__finalCompiled .= '
				\'cookie_domain\': \'' . $__templater->escape($__vars['xf']['cookie']['domain']) . '\',
			';
		}
		$__finalCompiled .= '
			';
		if ($__vars['xf']['options']['googleAnalyticsAnonymize']) {
			$__finalCompiled .= '
				\'anonymize_ip\': true,
			';
		}
		$__finalCompiled .= '
		});
	</script>
';
	}
	return $__finalCompiled;
});