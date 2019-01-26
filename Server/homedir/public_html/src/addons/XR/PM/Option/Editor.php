<?php

namespace XR\PM\Option;

use XF\Option\AbstractOption;

class Editor extends AbstractOption
{
	public static function verifyOption(&$value, \XF\Entity\Option $option)
	{
		if ($option->isInsert())
		{
			return true;
		}

		$value = self::fromInput('xr_pm_default_terms');

		return true;
	}

	public static function fromInput($key, $htmlMaxLength = -1)
	{
		$htmlKey = "options.{$key}_html";
		$key = "options.$key";
		$request = \XF::app()->request();
		if ($request->exists($key))
		{
			return $request->filter($key, 'str');
		}
		else if ($request->exists($htmlKey))
		{
			$html = $request->filter($htmlKey, 'str,no-clean');
			return self::convertToBbCode($html, $htmlMaxLength);
		}
		else
		{
			return '';
		}
	}

	public static function convertToBbCode($html, $htmlMaxLength = -1)
	{
		if ($htmlMaxLength < 0)
		{
			$htmlMaxLength = 4 * \XF::options()->messageMaxLength;
			// quadruple the limit as HTML can be a lot more verbose
		}

		if ($htmlMaxLength && utf8_strlen($html) > $htmlMaxLength)
		{
			throw \XF::phrasedException('submitted_message_is_too_long_to_be_processed');
		}

		$bbCode = \XF\Html\Renderer\BbCode::renderFromHtml($html);
		return \XF::cleanString($bbCode);
	}
}