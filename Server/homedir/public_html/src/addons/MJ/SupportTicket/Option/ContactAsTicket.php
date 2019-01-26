<?php

namespace MJ\SupportTicket\Option;

class ContactAsTicket extends \XF\Option\AbstractOption
{
	public static function renderOption(\XF\Entity\Option $option, array $htmlParams)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');

		$choices = [];

		foreach ($departmentRepo->findDepartmentList()->fetch() as $department)
		{
			$choices[$department->department_id] = $department->title;
		}

		return self::getTemplate('admin:mjst_option_template_contactAsTicket', $option, $htmlParams, [
			'choices' => $choices
		]);
	}
}
