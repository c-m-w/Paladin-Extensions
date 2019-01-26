var XRPM = window.XRPM || {};

!function($, window, document, _undefined)
{
	"use strict";

	XRPM.ProductBuy = XF.Element.newHandler({
		options: {
			price: 0.00,
			currencyData: {},
			phrase: 'xr_pm_buy_for_x',
			freePhrase: 'xr_pm_get_free_now',
			purchaseType: 'product_or_renewal'
		},

		canUseCoupons: false,
		$coupons: null,
		$couponRow: null,
		$couponInput: null,
		$couponButton: null,
		$couponList: null,
		xhr: null,

		$extras: null,

		basePrice: 0.00,
		extras: 0.00,
		coupons: 0.00,

		submitAfter: false,

		init: function()
		{
			this.basePrice = parseFloat(this.options.price);

			var $extras = this.$target.find('.js-extras'),
				$checkboxes = $extras.find('input[type="checkbox"]');

			var t = this;

			$checkboxes.each(function()
			{
				var $checkbox = $(this);
				if ($checkbox.is(':checked'))
				{
					t.extras += parseFloat($checkbox.data('price'));
				}
			});

			$checkboxes.on('change', XF.proxy(this, 'extraChange'));

			this.$extras = $extras;

			var $coupons = this.$target.find('.js-coupons');
			this.canUseCoupons = !!$coupons.length;

			if (this.canUseCoupons)
			{
				this.$coupons = $coupons;
				this.$couponRow = this.$target.find('.js-coupon');
				this.$couponInput = this.$couponRow.find('.js-couponCode');
				this.$couponButton = this.$couponRow.find('.js-checkCoupon');
				this.$couponList = this.$couponRow.find('.js-couponList');

				this.$couponButton.on('click', XF.proxy(this, 'recalcCoupons'));

				var $button = this.$couponButton;
				this.$couponInput.on('keypress', function(e)
				{
					// we don't want enter here to trigger the purchase creation
					// and payment so catch enter and take it to mean coupon validation.
					if (e.which === 13)
					{
						e.preventDefault();
						$button.click();
						return false;
					}
				});

				$(document).on('click', '.js-deleteCoupon', XF.proxy(this, 'deleteCoupon'));

				this.recalcCoupons();
			}
			else
			{
				this.recalc();
			}
		},

		recalcCoupons: function(e)
		{
			if (!this.canUseCoupons)
			{
				this.recalc();
				return;
			}

			if (e)
			{
				e.preventDefault();
			}

			if (this.xhr)
			{
				this.xhr.abort();
			}

			var $couponRow = this.$couponRow,
				href = $couponRow.data('checker'),
				data;

			data = XF.getDefaultFormData(this.$target);
			this.xhr = XF.ajax('post', href, data, XF.proxy(this, 'couponsChecked'), { skipDefaultSuccess: true });
		},

		couponsChecked: function(data)
		{
			this.xhr = null;

			var $couponList = this.$couponList,
				$couponInput = this.$couponInput;

			if (!data.html.content)
			{
				return;
			}

			XF.setupHtmlInsert(data.html, function($html, container, onComplete)
			{
				$couponList.html($html);
				onComplete();
			});

			this.$coupons.val(JSON.stringify(data.coupons));
			this.coupons = data.discount;
			this.recalc();

			$couponInput.val('');

			this.xhr = null;
		},

		deleteCoupon: function(e)
		{
			if (!this.canUseCoupons)
			{
				return;
			}

			// Paul assures me this is the correct American spelling
			var $queuepon = $(e.currentTarget),
				queueponId = $queuepon.data('coupon-id'),
				queuepons = JSON.parse(this.$coupons.val());

			delete queuepons[queueponId];
			this.$coupons.val(JSON.stringify(queuepons));
			XF.hideTooltips();

			this.recalcCoupons();
		},

		extraChange: function(e)
		{
			var $checkbox = $(e.currentTarget);

			if ($checkbox.is(':checked'))
			{
				this.extras += parseFloat($checkbox.data('price'));
			}
			else
			{
				this.extras -= parseFloat($checkbox.data('price'));
			}

			this.recalcCoupons();
		},

		recalc: function()
		{
			var currency = this.options.currencyData,
				format = currency.format,
				precision = currency.precision,
				symbol = currency.symbol,
				price = this.basePrice + this.extras - this.coupons,
				priceText, buttonText, $button;

			price = parseFloat(price).toFixed(precision);

			if (price < 0)
			{
				price = 0;
			}

			priceText = XF.stringTranslate(format, {
				'{symbol}': symbol,
				'{value}': price
			});

			buttonText = XF.phrase(this.options.phrase, {
				'{price}': priceText
			});

			$button = this.$target.find('.js-payButton');
			$button.find('.button-text').html(buttonText);

			if (parseInt(price))
			{
				$button.prop('disabled', false);
				$button.removeClass('is-disabled');
			}
			else
			{
				if (this.options.purchaseType === 'extra' && !this.$extras.find('input[type="checkbox"]:checked').length)
				{
					$button.prop('disabled', true);
					$button.addClass('is-disabled');
				}
				else
				{
					$button.prop('disabled', false);
					$button.removeClass('is-disabled');

					$button.find('.button-text').html(XF.phrase(this.options.freePhrase));
				}
			}
		}
	});

	XF.Element.register('xrpm-product-buy', 'XRPM.ProductBuy');
}
(jQuery, window, document);