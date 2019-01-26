!function($, window, document, _undefined)
{
	"use strict";


	XF.MJSTCustomField = XF.Element.newHandler({

		options: {
			listenTo: '',
			tid: 0,
			rowType: '',
			emode: '',
			href: ''
		},

		$select: null,

		init: function()
		{
			if (this.options.href)
			{
				var $listenTo = this.options.listenTo ? XF.findRelativeIf(this.options.listenTo, this.$target) : $([]);
				if (!$listenTo.length)
				{
					console.error('Cannot load custom fields dynamically as no element set to listen to for changes');
				}
				else
				{
					$listenTo.on('change', XF.proxy(this, 'loadCustomFields'));
				}
			}
		},

		loadCustomFields: function(e)
		{
			XF.ajax('POST', this.options.href, {
				val     : $(e.target).val(),
				tid     : this.options.tid,
				row_type : this.options.rowType,
				emode   : this.options.emode
			}, XF.proxy(this, 'loadSuccess'));
		},

		loadSuccess: function(data)
		{
			if (data.html)
			{
				var self = this;
				XF.setupHtmlInsert(data.html, function($html)
				{
					self.$target.html($html);
				});
			}
		},
	});

	XF.Element.register('mjst-custom-field', 'XF.MJSTCustomField');
}
(jQuery, window, document);