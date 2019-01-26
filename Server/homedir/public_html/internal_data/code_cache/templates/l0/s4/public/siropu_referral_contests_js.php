<?php
// FROM HASH: ac131401aa5eb076819cdacf56a0db42
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<script src="https://cdn.jsdelivr.net/npm/clipboard@2/dist/clipboard.min.js"></script>

<script>
	$(function() {
		var clipboard = new Clipboard(\'.siropuCopyReferralLink\');
		clipboard.on(\'success\', function(e) {
			e.trigger.textContent = "' . $__templater->filter('Copied!', array(array('escape', array('js', )),), true) . '";
		});
	});
</script>';
	return $__finalCompiled;
});