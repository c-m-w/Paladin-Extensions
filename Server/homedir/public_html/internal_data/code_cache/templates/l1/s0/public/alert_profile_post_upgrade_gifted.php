<?php
// FROM HASH: 4f60934812cb1a06c2fab96adb50e130
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:if is="' . $__templater->escape($__vars['visitor']['user_id']) . ' == ' . $__templater->escape($__vars['content']['profile_user_id']) . '">
	{xen:phrase nf_alert_profile_post_upgrade_gifted,
		\'name={xen:helper username, $user, \'subject\'}\',
		\'status_attributes=href="{xen:link profile-posts, $content}" class="PopupItemLink"\'
	}
<xen:else />
	{xen:phrase nf_alert_profile_post_upgrade_gifted_other,
		\'name={xen:helper username, $user, \'subject\'}\',
		\'post_attributes=href="{xen:link profile-posts, $content}" class="PopupItemLink"\',
		\'profile=' . $__templater->escape($__vars['content']['profile_username']) . '\'
	}
</xen:if>';
	return $__finalCompiled;
});