<?php
// FROM HASH: e9d2d5937e562a52a80fc3d74404ff31
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<dl class="formRow">
	<dt>
		<div class="formRow-labelWrapper">
			<dfn class="formRow-hint">
				Actions
			</dfn>
		</div>
	</dt>
	<dd>
		<ul class="inputChoices">
			<a href="' . $__templater->fn('link', array('steam/migrate', ), true) . '"
			   class="button"
			   onclick="return confirm(\'This will migrate the Xenforo 1 Steam Authentication addon data into our addon. This will only work if the XF1 module was not removed before upgrading to XF2. Once the migration is complete you will be redirected to the ACP homepage.\')">
				<span class="button-text">XF1 Migration</span>
			</a>
		</ul>
	</dd>
</dl>';
	return $__finalCompiled;
});