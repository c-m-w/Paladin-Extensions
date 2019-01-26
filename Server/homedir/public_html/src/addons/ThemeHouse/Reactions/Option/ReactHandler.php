<?php

namespace ThemeHouse\Reactions\Option;

class ReactHandler extends \XF\Option\AbstractOption
{
	public static function renderCheckbox(\XF\Entity\Option $option, array $htmlParams)
	{
        $reactHandlers = self::getReactChoices(false);
		$value = $choices = [];

		foreach ($reactHandlers as $type => $phrase) {
			if (!isset($option->option_value[$type]) || !empty($option->option_value[$type])) {
				$value[] = $type;
			}

			$choices[$type] = $phrase;
		}

		return self::getCheckboxRow($option, $htmlParams, $choices, $value);
	}

	public static function verifyOption(array &$choices, \XF\Entity\Option $option)
	{
		if ($option->isInsert()) {
			// insert - just trust the default value
			return true;
		}

		$exclusions = [];
		$reactHandlers = self::getReactChoices();

		foreach ($reactHandlers as $type => $phrase) {
            $exclusions[$type] = (!in_array($type, $choices) ? false : true);
		}

		$choices = $exclusions;
		return true;
	}

	public static function renderSelect(\XF\Entity\Option $option, array $htmlParams)
	{
		$data = self::getSelectData($option, $htmlParams);

		return self::getTemplater()->formSelectRow(
			$data['controlOptions'], $data['choices'], $data['rowOptions']
		);
	}

	public static function renderSelectMultiple(\XF\Entity\Option $option, array $htmlParams)
	{
		$data = self::getSelectData($option, $htmlParams);
		$data['controlOptions']['multiple'] = true;
		$data['controlOptions']['size'] = 8;

		return self::getTemplater()->formSelectRow(
			$data['controlOptions'], $data['choices'], $data['rowOptions']
		);
	}

	protected static function getSelectData(\XF\Entity\Option $option, array $htmlParams)
	{
		return [
			'choices' => self::getReactChoices(),
			'controlOptions' => self::getControlOptions($option, $htmlParams),
			'rowOptions' => self::getRowOptions($option, $htmlParams)
		];
	}

    protected static function getReactChoices($asSelect = true)
    {
		/** @var \ThemeHouse\Repository\ReactHandler $nodeRepo */
		$reactHandlerRepo = \XF::repository('ThemeHouse\Reactions:ReactHandler');
        $reactHandlers = $reactHandlerRepo->getReactHandlersList(['excludeAddOnDisabled']);

        if (!$asSelect) {
            return $reactHandlers;
        }

		return array_map(function($v) {
			return ['label' => \XF::escapeString($v)];
		}, $reactHandlers);
    }
}