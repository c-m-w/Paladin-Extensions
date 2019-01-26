<?php

namespace XR\PM;

class TemplaterSetup
{
	public function fnPmThumbnail($templater, &$escape, \XR\PM\Entity\Product $product, $href = '', $extraClasses = '', $canonical = false)
	{
		$escape = false;

		if ($href)
		{
			$tag = 'a';
			$hrefAttr = 'href="' . htmlspecialchars($href) . '"';
		}
		else
		{
			$tag = 'span';
			$hrefAttr = '';
		}

		if (!$product->hasThumbnail())
		{
			return "<{$tag} {$hrefAttr} class=\"xrpmThumbnail xrpmThumbnail--default {$extraClasses}\"><span></span></{$tag}>";
		}
		else
		{
			$src = $product->getThumbnailUrl($canonical);

			return "<{$tag} {$hrefAttr} class=\"xrpmThumbnail {$extraClasses}\">"
				. '<img src="' . htmlspecialchars($src)
				. '" alt="' . htmlspecialchars($product->product_title) . '" />'
				. "</{$tag}>";
		}
	}

	public function fnPmCurrencyData($templater, &$escape, $code)
	{
		$language = \XF::language();

		$data = \XF::app()->data('XF:Currency')->getCurrencyData();
		$currency = isset($data[$code]) ? $data[$code] : null;

		if (!$currency)
		{
			trigger_error('Invalid currency \'' . htmlspecialchars($code) . '\' provided.', E_USER_WARNING);
		}

		return [
			'symbol' => $currency['symbol'],
			'precision' => $currency['precision'],
			'format' => $language->currency_format
		];
	}

	public function filterPmCurrency($templater, $value, &$escape, $code = '', $format = null)
	{
		$value = floatval($value);
		if (!$value)
		{
			return \XF::phrase('xr_pm_free');
		}
		$currency = \XF::app()->data('XF:Currency');
		return $currency->languageFormat($value, $code, \XF::language(), $format);
	}
}