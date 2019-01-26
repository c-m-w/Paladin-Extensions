<?php
// FROM HASH: ae2fef11a527d7fc26ecec64002f5f43
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '<xen:title>{xen:phrase nixfifty_giftupgrades_gift_x_to_a_user, \'upgrade=' . $__templater->escape($__vars['upgrade']['title']) . '\'}</xen:title>
<xen:h1>{xen:phrase nixfifty_giftupgrades_gift_x_to_a_user, \'upgrade=' . $__templater->escape($__vars['upgrade']['title']) . '\'}</xen:h1>

<form name="giftForm" action="' . $__templater->escape($__vars['requestPaths']['fullBasePath']) . '{xen:link account/upgrades/gift-confirm}" method="post" class="xenForm formOverlay">

	<dl class="ctrlUnit">
		<dt>{xen:phrase upgrade}</dt>
		<dd>' . $__templater->escape($__vars['upgrade']['title']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase cost}</dt>
		<dd>' . $__templater->escape($__vars['upgrade']['costPhrase']) . '</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt>{xen:phrase nixfifty_giftupgrades_payment_processor}</dt>
		<dd>
			<xen:if is="' . $__templater->escape($__vars['processors']) . '">
				<select name="processor_id" class="textCtrl" id="ctrl_processor_id">
					<xen:foreach loop="$processors" key="$processorId" value="$processor">
						<option value="' . $__templater->escape($__vars['processorId']) . '">' . $__templater->escape($__vars['processor']['title']) . '</option>
					</xen:foreach>
				</select>
			<xen:else />
				{xen:phrase nixfifty_giftupgrades_paypal}
			</xen:if>
		</dd>
	</dl>

	<dl class="ctrlUnit findMember">
		<dt>
			<label for="ctrl_title_gift_to">{xen:phrase nixfifty_giftupgrades_gift_to}:</label>
			<dfn>{xen:phrase required}</dfn>
		</dt>
		<dd>
			<input type="search" name="username" placeholder="{xen:phrase user}" results="0" autofocus="on" class="textCtrl AutoComplete AcSingle" />
		</dd>
	</dl>

	<dl class="ctrlUnit">
		<dt></dt>
		<dd><ul>
			<li><label><input type="checkbox" name="anonymous" value="1" id="ctrl_anonymous"/> {xen:phrase nixfifty_giftupgrades_send_gift_anonymously}</label>
				<p class="explain">{xen:phrase nixfifty_giftupgrades_send_gift_anonymously_desc}</p>
			</li>
		</ul></dd>
	</dl>

	<dl class="ctrlUnit submitUnit">
		<dt></dt>
		<dd>
			<input type="submit" name="save" id="submit" value="{xen:phrase nixfifty_giftupgrades_gift}" accesskey="s" class="button primary" />
		</dd>
	</dl>

	<input type="hidden" name="upgrade_id" value="' . $__templater->escape($__vars['upgrade']['user_upgrade_id']) . '" />
	<input type="hidden" name="_xfConfirm" value="1" />
	<input type="hidden" name="_xfToken" value="' . $__templater->escape($__vars['visitor']['csrf_token_page']) . '" />

</form>';
	return $__finalCompiled;
});