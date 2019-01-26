!function($, window, document, _undefined)
{
	"use strict";

	XF.MJSTKbSuggest = XF.Element.newHandler({
		options: {
			itemSelector: null
		},

		$form: null,
		$title: null,

		init: function()
		{
			this.$title = this.$target.closest('form').find('input[name="title"]').on('change', XF.proxy(this, 'findSuggest'));
			this.$item = $(this.options.itemSelector);
			if (!this.$item.length)
			{
				return;
			}

			this.$target.on('ajax-submit:before', XF.proxy(this, 'beforeSubmit'));
			this.$target.on('ajax-submit:response', XF.proxy(this, 'afterSubmit'));
		},

		findSuggest: function(e)
		{
			e.preventDefault();
			var self = this;
			XF.ajax(
				'get', XF.canonicalizeUrl('index.php?support-tickets/knowledge-base/suggest'),
				{
					q: this.$title.val()
				},
				XF.proxy(self, 'handleSuggest'),
				{skipDefaultSuccessError: true}
			);
		},

		handleSuggest: function(data)
		{
			if (data.errors || data.exception)
			{
				return;
			}

			var self = this;
			XF.setupHtmlInsert(data.html, function($html, container, onComplete)
			{
				self.$target.html($html).xfFadeDown(XF.config.speed.xfast, function()
				{
					onComplete(true);
					XF.layoutChange();
				});
			});
		}
	});

	XF.Element.register('mjst-kb-suggest', 'XF.MJSTKbSuggest');
}
(jQuery, window, document);