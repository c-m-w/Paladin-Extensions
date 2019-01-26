<?php
// FROM HASH: 149a5ffdd75889c5f68a1aaa06ff84e1
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<div class="menu-row menu-row--highlighted">
	<xf:macro name="visitor_panel_row" />
</div>

<xf:macro name="visitor_panel_row">
	<div class="contentRow contentRow--alignMiddle">
		<div class="contentRow-figure">
			<xf:avatar user="{$xf.visitor}" size="s" href="" notooltip="true" update="{{ link(\'account/avatar\', $xf.visitor) }}" />
		</div>
		<div class="contentRow-main">
			<h3 class="contentRow-header"><xf:username user="$xf.visitor" rich="true" notooltip="true" /></h3>
			<div class="contentRow-lesser">
				<xf:usertitle user="$xf.visitor" />
			</div>
		</div>
	</div>
	<div class="contentRow-minor">
		<!--[XF:stats_pairs:above_messages]-->
		<dl class="pairs pairs--justified fauxBlockLink">
			<xf:if is="property(\'uix_visitorPanelIcons\')">
				<xf:macro template="uix_icons.less" name="icon" arg-icon="messages" />
				<xf:else />
				<dt>{{ phrase(\'messages\') }}</dt>
			</xf:if>
			<dd>
				<a href="{{ link(\'search/member\', null, {\'user_id\': $xf.visitor.user_id}) }}" class="fauxBlockLink-linkRow u-concealed">
					{$xf.visitor.message_count|number}
				</a>
			</dd>
		</dl>

		<!--[XF:stats_pairs:above_likes]-->
		<dl class="pairs pairs--justified fauxBlockLink">
			<xf:if is="property(\'uix_visitorPanelIcons\')">
				<xf:macro template="uix_icons.less" name="icon" arg-icon="like" />
				<xf:else />
				<dt>{{ phrase(\'likes\') }}</dt>
			</xf:if>
			<dd>
				<a href="{{ link(\'account/likes\') }}" class="fauxBlockLink-linkRow u-concealed">
					{$xf.visitor.like_count|number}
				</a>
			</dd>
		</dl>
		<!--[XF:stats_pairs:above_points]-->
		<xf:if is="$xf.options.enableTrophies">
			<dl class="pairs pairs--justified fauxBlockLink">
				<xf:if is="property(\'uix_visitorPanelIcons\')">
					<xf:macro template="uix_icons.less" name="icon" arg-icon="trophy" />
					<xf:else />
					<dt>{{ phrase(\'trophy_points\') }}</dt>
				</xf:if>
				<dd>
					<a href="{{ link(\'members/trophies\', $xf.visitor) }}" data-xf-click="overlay" class="fauxBlockLink-linkRow u-concealed">
						{$xf.visitor.trophy_points|number}
					</a>
				</dd>
			</dl>
		</xf:if>
	</div>
</xf:macro>

<!--[XF:menu_separator:below_visitor_panel]-->
<hr class="menu-separator menu-separator--hard" />

<ul class="listPlain listColumns listColumns--narrow listColumns--together">
	<!--[XF:content_links:top]-->
	<xf:if is="$xf.options.enableNewsFeed">
		<li><a href="{{ link(\'whats-new/news-feed\') }}" class="menu-linkRow">{{ phrase(\'news_feed\') }}</a></li>
	</xf:if>
	<li><a href="{{ link(\'search/member\', null, {\'user_id\': $xf.visitor.user_id}) }}" class="menu-linkRow">{{ phrase(\'your_content\') }}</a></li>
	<li><a href="{{ link(\'account/likes\') }}" class="menu-linkRow">{{ phrase(\'likes_received\') }}</a></li>
	<li><a href="{{ link(\'conversations\') }}" class="menu-linkRow">{{ phrase(\'conversations\') }}</a></li>
	<li><a href="{{ link(\'account/alerts\') }}" class="menu-linkRow">{{ phrase(\'alerts\') }}</a></li>
	<!--[XF:content_links:bottom]-->
</ul>

<!--[XF:menu_separator:below_content_links]-->
<hr class="menu-separator" />

<ul class="listPlain listColumns listColumns--narrow listColumns--together">
	<!--[XF:account_links:top]-->
	<li><a href="{{ link(\'account/account-details\') }}" class="menu-linkRow">{{ phrase(\'account_details\') }}</a></li>
	<li><a href="{{ link(\'account/security\') }}" class="menu-linkRow">{{ phrase(\'password_and_security\') }}</a></li>
	<li><a href="{{ link(\'account/privacy\') }}" class="menu-linkRow">{{ phrase(\'privacy\') }}</a></li>
	<li><a href="{{ link(\'account/preferences\') }}" class="menu-linkRow">{{ phrase(\'preferences\') }}</a></li>
	<xf:if is="$xf.visitor.canEditSignature()">
		<li><a href="{{ link(\'account/signature\') }}" class="menu-linkRow">{{ phrase(\'signature\') }}</a></li>
	</xf:if>
	<xf:if is="$xf.app.userUpgradeCount">
		<li><a href="{{ link(\'account/upgrades\') }}" class="menu-linkRow">{{ phrase(\'account_upgrades\') }}</a></li>
	</xf:if>
	<xf:if is="$xf.app.connectedAccountCount">
		<li><a href="{{ link(\'account/connected-accounts\') }}" class="menu-linkRow">{{ phrase(\'connected_accounts\') }}</a></li>
	</xf:if>
	<li><a href="{{ link(\'account/following\') }}" class="menu-linkRow">{{ phrase(\'following\') }}</a></li>
	<li><a href="{{ link(\'account/ignored\') }}" class="menu-linkRow">{{ phrase(\'ignoring\') }}</a></li>
	<!--[XF:account_links:bottom]-->
</ul>

<!--[XF:menu_separator:below_account_links]-->
<hr class="menu-separator" />

<a href="{{ link(\'logout\', null, {\'t\': csrf_token()}) }}" class="menu-linkRow">{{ phrase(\'log_out\') }}</a>

<xf:if is="$xf.visitor.canPostOnProfile()">
	<xf:form action="{{ link(\'members/post\', $xf.visitor) }}" ajax="true"
		data-redirect="off"
		data-reset-complete="true"
		data-no-auto-focus="true"
		class="menu-footer">

		<span class="u-srOnly" id="ctrl_message">{{ phrase(\'update_your_status:\') }}</span>
		<xf:textarea name="message" rows="1" autosize="true"
			maxlength="{$xf.options.profilePostMaxLength}"
			placeholder="{{ phrase(\'update_your_status...\') }}"
			data-xf-init="focus-trigger user-mentioner" data-display="< :next" aria-labelledby="ctrl_message" />
		<div class="u-hidden u-hidden--transition u-inputSpacer">
			<xf:button type="submit" class="button--primary">{{ phrase(\'post_verb\') }}</xf:button>
		</div>
	</xf:form>
</xf:if>';
	return $__finalCompiled;
});