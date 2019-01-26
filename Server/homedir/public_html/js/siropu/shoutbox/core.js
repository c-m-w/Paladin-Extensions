!function($, window, document, _undefined)
{
	"use strict";

	XF.SiropuShoutbox = XF.Element.newHandler({
		options:
		{
			lastId: 0,
			refreshInterval: 0,
			loadMore: 0,
			lastActive: 0,
			reverse: false,
			collapsed: false,
			sound: 'on'
		},

		audio: '',

		init: function()
		{
			if (!this.options.collapsed)
			{
				this.startRefreshInterval();
			}

			if (this.options.sound == 'on')
			{
				this.loadAudio();
			}

			var self = this;
			var container = this.$target.find('.siropuShoutboxShouts');

			if (self.options.reverse)
			{
				container.scrollTop(100000);
			}

			$(document).on('shoutbox:sound-on', function()
			{
				self.soundOn();
			});

			$(document).on('shoutbox:sound-off', function()
			{
				self.soundOff();
			});

			$(document).on('shoutbox:toggle-reverse', function(e, state)
			{
				var loadMore = self.options.loadMore;

				container.html('');

				self.options.reverse = state;
				self.options.loadMore = 0;
				self.options.lastId = 0;

				self.refresh(false);

				setTimeout(function()
				{
					self.options.loadMore = loadMore;
				}, 1000);
			});

			$(document).on('shoutbox:collapse', function()
			{
				self.stopRefreshInterval();
			});

			$(document).on('shoutbox:expand', function()
			{
				if (container.find('> li:not([data-id])').length)
				{
					self.refresh(false);
				}

				self.startRefreshInterval();
			});

			$(document).on('shoutbox:submit', function(e)
			{
				var input = $(this).find('input[name="shout"]');
				var shout = input.val().trim();

				if (!shout)
				{
					return input.focus();
				}

				input.val('').attr('placeholder', XF.phrase('siropu_shoutbox_please_wait')).prop('disabled', true);
				self.stopRefreshInterval();

				XF.ajax('POST',
					XF.canonicalizeUrl('index.php?shoutbox/submit'),
					{
						last_id: self.options.lastId,
						shout: shout
					},
					function(data)
					{
						self.update(data);
						self.startRefreshInterval();

						self.options.lastActive = data.time;

						if (data.prune)
						{
							container.find('li[data-id]').not(container.find('li[data-id="' + data.lastId + '"]')).remove();
						}
					},
					{
						global: false
					}
				);

				setTimeout(function()
				{
					input.prop('disabled', false).attr('placeholder', XF.phrase('siropu_shoutbox_placeholder')).focus();
				}, 1000);
			});

			this.$target.on('mouseover mouseout', '.siropuShoutboxShouts > li[data-id]', function()
			{
				$(this).find('a[data-xf-click="overlay"]').toggle();
			});

			var loading = false;

			container.on('scroll', function()
			{
				var scrollDiff = $(this)[0].scrollHeight - $(this).innerHeight();
				var scrollTop = parseInt($(this).scrollTop());

				if (self.options.loadMore && !loading && (!self.options.reverse && (scrollTop == scrollDiff || scrollTop + 1 == scrollDiff || scrollTop - 1 == scrollDiff) || self.options.reverse && scrollTop == 0))
				{
					loading = true;

					var lastId = $(this).find('> li:' + (self.options.reverse ? 'first' : 'last')).data('id');
					var notice = $('<div class="siropuShoutboxLoadingMoreShouts" />');

					notice.html('<i class="fa fa-cog fa-spin"></i> ' + XF.phrase('siropu_shoutbox_loading_more_shouts'));

					if (self.options.reverse)
					{
						notice.addClass('siropuShoutboxReverse').insertBefore($(this));
					}
					else
					{
						notice.insertAfter($(this));
					}

					var isNotice = $(this).parents().find('.siropuShoutboxLoadingMoreShouts');

					setTimeout(function() {
						isNotice.fadeOut();
						isNotice.remove();
					}, 1000);

					XF.ajax('POST',
						XF.canonicalizeUrl('index.php?shoutbox/load-more'),
						{
							last_id: lastId
						},
						function(data)
						{
							if (data.html && data.html.content)
							{
								XF.setupHtmlInsert(data.html, function($html, data, onComplete)
								{
									if (self.options.reverse)
									{
										container.prepend($html);
									}
									else
									{
										container.append($html);
									}
								});
							}
							else
							{
								self.options.loadMore = 0;
							}

							loading = false;
						}
					);
				}
			});
		},

		update: function(data, soundOff)
		{
			var self = this;
			var container = this.$target.find('.siropuShoutboxShouts');

			if (data.html && data.html.content)
			{
				XF.setupHtmlInsert(data.html, function($html, data, onComplete)
				{
					var shouts = $.grep($html, function(value)
					{
						return container.find('li[data-id="' + $(value).data('id') + '"]').length ? false : true;
					});

					var empty = container.find('> li:not([data-id])');

					if (empty.length)
					{
						empty.remove();
					}

					if (self.options.reverse)
					{
						$(shouts).appendTo(container);
						$(shouts).show();

						container.scrollTop(100000);
					}
					else
					{
						$(shouts).hide();
						$(shouts).prependTo(container);
						$(shouts).slideDown();
					}

					if (soundOff === undefined)
					{
						self.playSound();
					}
				});
			}

			if (data.lastId)
			{
				self.setLastId(data.lastId);
			}

			if (data.time - self.options.lastActive >= 600)
			{
				self.stopRefreshInterval();
			}
		},

		refresh: function(soundOff)
		{
			var self = this;

			XF.ajax('POST',
				XF.canonicalizeUrl('index.php?shoutbox/refresh'),
				{
					last_id: self.options.lastId
				},
				function(data)
				{
					self.update(data, soundOff);
				},
				{
					global: false
				}
			);
		},

		startRefreshInterval: function()
		{
			if (this.options.refreshInterval)
			{
				this.refreshSet = setInterval($.proxy(this, 'refresh'), this.options.refreshInterval);
			}
		},

		stopRefreshInterval: function()
		{
			clearInterval(this.refreshSet);
		},

		setLastId: function(id, container)
		{
			this.options.lastId = id;

			if (this.$target)
			{
				this.$target.attr('data-last-id', id);
			}
		},

		loadAudio: function()
		{
			this.audio = new Audio('styles/default/siropu/shoutbox/new.mp3');
		},

		soundOn: function()
		{
			this.$target.attr('data-sound', 'on');
			this.options.sound = 'on';

			if (!this.audio)
			{
				this.loadAudio();
			}
		},

		soundOff: function()
		{
			this.$target.attr('data-sound', 'off');
			this.options.sound = 'off';
		},

		playSound: function()
		{
			if (this.options.sound == 'on')
			{
				this.audio.play();
			}
		}
     });

	XF.SiropuShoutboxToggleSound = XF.Click.newHandler({
		eventNameSpace: 'siropuShoutboxToggleSound',

		options: {},

		init: function() {},

		click: function()
		{
			var icon = $('.siropuShoutbox a[data-xf-click="siropu-shoutbox-toggle-sound"] .fa');

			if (icon.hasClass('fa-volume-up'))
			{
				$(document).trigger('shoutbox:sound-off');

				icon.removeClass('fa-volume-up').addClass('fa-volume-off');
				XF.Cookie.set('siropuShoutboxNoSound', true);
			}
			else
			{
				$(document).trigger('shoutbox:sound-on');

				icon.removeClass('fa-volume-off').addClass('fa-volume-up');
				XF.Cookie.remove('siropuShoutboxNoSound');
			}
		}
	});

	XF.SiropuShoutboxToggleDirection = XF.Click.newHandler({
		eventNameSpace: 'SiropuShoutboxToggleDirection',

		options: {},

		init: function() {},

		click: function()
		{
			var icon = $('.siropuShoutbox a[data-xf-click="siropu-shoutbox-toggle-direction"] .fa');
			var form = $('.siropuShoutbox form');
			var shouts = $('.siropuShoutboxShouts');

			form.remove();

			if (icon.hasClass('fa-arrow-down'))
			{
				form.insertAfter(shouts);

				icon.removeClass('fa-arrow-down').addClass('fa-arrow-up');
				XF.Cookie.set('siropuShoutboxReverse', 1);

				$(document).trigger('shoutbox:toggle-reverse', true);
			}
			else
			{
				form.insertBefore(shouts);

				icon.removeClass('fa-arrow-up').addClass('fa-arrow-down');
				XF.Cookie.set('siropuShoutboxReverse', 0);

				$(document).trigger('shoutbox:toggle-reverse', false);
			}

			form.toggleClass('siropuShoutboxReverse');

			XF.activate(form);
		}
	});

	XF.SiropuShoutboxToggleVisibility = XF.Click.newHandler({
		eventNameSpace: 'siropuShoutboxToggleVisibility',

		options: {},

		init: function() {},

		click: function()
		{
			var icon = $('.siropuShoutbox a[data-xf-click="siropu-shoutbox-toggle-visibility"] .fa');

			if (icon.hasClass('fa-minus'))
			{
				$(document).trigger('shoutbox:collapse');

				icon.removeClass('fa-minus').addClass('fa-plus');
				XF.Cookie.set('siropuShoutboxCollapsed', true);
			}
			else
			{
				$(document).trigger('shoutbox:expand');

				icon.removeClass('fa-plus').addClass('fa-minus');
				XF.Cookie.remove('siropuShoutboxCollapsed');
			}

			$('.siropuShoutbox .block-body').toggle();
		}
	});

	XF.SiropuShoutboxEdit = XF.Element.newHandler({
          options: {},

          init: function()
          {
               this.$target.on('ajax-submit:response', $.proxy(this, 'ajaxResponse'));
          },

          ajaxResponse: function(e, data)
          {
               $('.siropuShoutboxShouts > li[data-id=' + data.shout_id  + ']').find('> span').html(data.shout_message);
          }
     });

	XF.SiropuShoutboxDelete = XF.Element.newHandler({
          options: {},

          init: function()
          {
               this.$target.on('ajax-submit:response', $.proxy(this, 'ajaxResponse'));
          },

          ajaxResponse: function(e, data)
          {
			$('.siropuShoutboxShouts > li[data-id=' + data.shout_id  + ']').fadeOut();
          }
     });

	XF.SiropuShoutboxSubmit = XF.Element.newHandler({
		options: {},

		init: function()
		{
			this.$target.on('submit', function(e)
			{
				e.preventDefault();

				$(document).trigger('shoutbox:submit');
			});
		}
	});

	XF.Element.register('siropu-shoutbox', 'XF.SiropuShoutbox');
	XF.Element.register('siropu-shoutbox-submit', 'XF.SiropuShoutboxSubmit');
	XF.Element.register('siropu-shoutbox-edit-shout', 'XF.SiropuShoutboxEdit');
	XF.Element.register('siropu-shoutbox-delete-shout', 'XF.SiropuShoutboxDelete');

	XF.Click.register('siropu-shoutbox-toggle-sound', 'XF.SiropuShoutboxToggleSound');
	XF.Click.register('siropu-shoutbox-toggle-direction', 'XF.SiropuShoutboxToggleDirection');
	XF.Click.register('siropu-shoutbox-toggle-visibility', 'XF.SiropuShoutboxToggleVisibility');
}
(jQuery, window, document);
