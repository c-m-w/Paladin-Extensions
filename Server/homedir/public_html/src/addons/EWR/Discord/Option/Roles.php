<?php

namespace EWR\Discord\Option;

class Roles extends \XF\Option\AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		$discordRepo = \XF::repository('EWR\Discord:Discord');
		$provider = $discordRepo->assertSetup();
		
		$roles = $discordRepo->getGuild('/roles');
		$values = $option['option_value'];
		$choices = [];
		
		if (!empty($roles) && isset($roles[0]['position']))
		{
			foreach ($roles AS $role)
			{
				if (!$role['managed'] && $role['name'] != '@everyone')
				{
					if (!empty($values[$role['id']]))
					{
						$role['usergroup'] = $values[$role['id']];
					}
					
					$choices[$role['id']] = $role;
				}
			}
			
			usort($choices, function($a, $b) { return($a['position'] > $b['position']); });
		}

		return self::getTemplate('admin:option_template_EWRdiscord_roles', $option, $htmlParams, [
			'provider' => $provider,
			'roles' => $choices,
			'usergroups' => \XF::repository('XF:UserGroup')->getUserGroupOptionsData(),
		]);
	}
}