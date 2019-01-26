<?php
// FROM HASH: 78cd2c61fc18d9b8dfb609b4752808c6
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:title>{xen:phrase nf_members_who_gifted_this_content}</xen:title>

<xen:navigation>
	<xen:breadcrumb source="$breadcrumbs" />
</xen:navigation>

<xen:container var="$head.noindex"><meta name="robots" content="noindex" /></xen:container>

<div class="section">
	<ol class="overlayScroll">
		<xen:foreach loop="$gifts" value="$gift">
			<xen:include template="member_list_item">
				<xen:set var="$extraTemplate"><xen:datetime time="$gift.gift_date" /></xen:set>
				<xen:map from="$gift" to="$user" />
			</xen:include>
		</xen:foreach>
	</ol>

	<div class="sectionFooter ">
		<span class="note">{xen:phrase nf_some_gifters_may_be_anonymous}</span>

		<a class="button primary overlayOnly OverlayCloser">{xen:phrase close}</a>
		<xen:if is="' . $__templater->escape($__vars['hasMore']) . '">
			<a class="button OverlayCloser OverlayTrigger" href="' . $__templater->escape($__vars['moreLink']) . '">{xen:phrase more}...</a>
		</xen:if>
	</div>
</div>';
	return $__finalCompiled;
});