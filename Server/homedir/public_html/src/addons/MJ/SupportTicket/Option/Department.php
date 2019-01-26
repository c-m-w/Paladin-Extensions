<?php

namespace MJ\SupportTicket\Option;

class Department extends \XF\Option\AbstractOption
{
	public static function renderSelect(\XF\Entity\Option $option, array $htmlParams)
	{
		$data = self::getSelectData($option, $htmlParams);

		return self::getTemplater()->formSelectRow(
			$data['controlOptions'],
			$data['choices'],
			$data['rowOptions']
		);
	}

	protected static function getSelectData(\XF\Entity\Option $option, array $htmlParams)
	{
		/** @var \MJ\SupportTicket\Repository\Department $departmentRepo */
		$departmentRepo = \XF::repository('MJ\SupportTicket:Department');
		$choices = [];
		foreach ($departmentRepo->findDepartmentList()->fetch() as $department)
		{
			$choices[$department->department_id] = $department->title;
		}

		$choices = self::convertChoicesToTemplaterForm($choices);

		return [
			'choices' => $choices,
			'controlOptions' => self::getControlOptions($option, $htmlParams),
			'rowOptions' => self::getRowOptions($option, $htmlParams)
		];
	}
}
