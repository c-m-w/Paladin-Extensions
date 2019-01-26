<?php
// FROM HASH: ffc129d92a267b74d1fdacd7e8d3fcec
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:title>{xen:phrase nf_gift_upgrade_to_x, \'user=' . $__templater->escape($__vars['giftUser']['username']) . '\'}</xen:title>

<xen:navigation>
	<xen:breadcrumb source="$breadcrumbs" />
</xen:navigation>

<form method="post" class="xenForm formOverlay" action="' . $__templater->escape($__vars['pageUrl']) . '">
	<dl class="ctrlUnit">
		<dt><label for="ctrl_upgrade">{xen:phrase upgrade}:</label></dt>
		<dd>
			<select name="upgrade_id" class="textCtrl" id="ctrl_upgrade">
				<xen:foreach loop="$upgrades" value="$upgrade">
					<xen:if is="' . $__templater->escape($__vars['upgrade']['can_gift']) . '">
						<option value="' . $__templater->escape($__vars['upgrade']['user_upgrade_id']) . '">' . $__templater->escape($__vars['upgrade']['title']) . ' (' . $__templater->escape($__vars['upgrade']['costPhrase']) . ')</option>
					</xen:if>
				</xen:foreach>
			</select>
		</dd>
	</dl>

	<xen:if is="' . $__templater->escape($__vars['processors']) . '">
		<dl class="ctrlUnit">
			<dt><label for="ctrl_processor">{xen:phrase nixfifty_giftupgrades_payment_processor}:</label></dt>
			<dd>
				<select name="processor_id" class="textCtrl" id="ctrl_processor">
					<xen:foreach loop="$processors" key="$processorId" value="$processor">
						<option value="' . $__templater->escape($__vars['processorId']) . '">' . $__templater->escape($__vars['processor']['title']) . '</option>
					</xen:foreach>
				</select>
			</dd>
		</dl>
	</xen:if>

	<xen:if is="' . $__templater->escape($__vars['visitor']['user_id']) . '">
		<dl class="ctrlUnit">
			<dt></dt>
			<dd>
				<ul>
					<li>
						<label><input type="checkbox" name="anonymous" value="1" id="ctrl_anonymous"/> {xen:phrase nixfifty_giftupgrades_send_gift_anonymously}</label>
						<p class="hint">{xen:phrase nixfifty_giftupgrades_send_gift_anonymously_desc}</p>
					</li>
				</ul>
			</dd>
		</dl>
	<xen:else />
		<dl class="ctrlUnit">
			<dt><label for="ctrl_email">{xen:phrase email}:</label></dt>
			<dd>
				<input type="text" name="email" id="ctrl_email" class="textCtrl" required="true" />
				<p class="explain">{xen:phrase nixfifty_giftupgrades_email_address_desc}</p>
			</dd>
		</dl>
	</xen:if>

	<dl class="ctrlUnit submitUnit">
		<dt></dt>
		<dd>
			<input type="submit" name="save" id="submit" value="{xen:phrase nixfifty_giftupgrades_gift}" accesskey="s" class="button primary" />
		</dd>
	</dl>

	<input type="hidden" name="_xfToken" value="' . $__templater->escape($__vars['visitor']['csrf_token_page']) . '" />
</form>';
	return $__finalCompiled;
});