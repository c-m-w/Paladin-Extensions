!function($, window, document, _undefined)
{
	"use strict";

	XF.MJSTeditorStart = {
		started: false,

		startAll: function()
		{
			if (!XF.MJSTeditorStart.started)
			{
				XF.MJSTeditorStart.registerCommands();
				XF.MJSTeditorStart.started = true;
			}
		},

		togglePreReplyBox: function(ed, active)
		{
			var $replyBox = ed.$oel.data('mjstPreReplyBox');
			if ($replyBox)
			{
				ed.$wp.toggleClassTransitioned('replyBox-active', active);
				$replyBox.toggleClassTransitioned('is-active', active);
				ed.$tb.find('.fr-command[data-cmd=mjstPreReply]').toggleClass('fr-active xxx', active);
			}
		},

		registerCommands: function()
		{
			var options;

			try
			{
				options = $.parseJSON($('.js-mjstPreReply').first().html()) || {};
			}
			catch (e)
			{
				console.error(e);
				options = {};
			}

			$.FE.DefineIcon('mjstPreReply', { NAME: 'ticket'});
			$.FE.RegisterCommand('mjstPreReply', {
				title: 'Pre Reply',
				icon: 'mjstPreReply',
				undo: false,
				focus: false,
				refresh: function($btn)
				{
					var ed = this,
						$replyBox = ed.$oel.data('mjstPreReplyBox'),
						isActive = false;

					if ($replyBox)
					{
						isActive = $replyBox.hasClass('is-active');
					}

					$btn.toggleClass('fr-active', isActive);
				},
				callback: function()
				{
					var ed = this,
						$replyBox = ed.$oel.data('mjstPreReplyBox');

					if ($replyBox)
					{
						var isActive = $replyBox.hasClass('is-active');
						XF.MJSTeditorStart.togglePreReplyBox(ed, isActive ? false : true);
					}
					else
					{
						$replyBox = $('<div class="mjstEditorPreReplies" />');
						ed.$oel.data('mjstPreReplyBox', $replyBox);
						ed.$wp.after($replyBox);

						XF.ajax('GET',
							XF.canonicalizeUrl('index.php?support-tickets/pre-replies'),
							{
								submitter: options.submitter
							},
							function (data)
							{
								if (data.html)
								{
									XF.setupHtmlInsert(data.html, function($html)
									{
										ed.events.bindClick($replyBox, 'li.reply', function(e)
										{
											var $target = $(e.currentTarget),
												$reply = $target.clone();

											var message = $reply.find('.reply-full').html();
											XF.EditorHelpers.focus(ed);
											ed.html.insert($('<div />').html(message).html());
										});

										$replyBox.html($html);
										XF.MJSTeditorStart.togglePreReplyBox(ed, true);
									});
								}
							}
						);
					}
				}
			});
		}
	};


	XF.MJSTeditorButtons = {
		started: false,

		initButtons: function(eventData, ed)
		{
			if (!XF.MJSTeditorButtons.started)
			{
				ed.buttons += ',|,mjstPreReply';
				XF.MJSTeditorButtons.started = true;
			}
		}
	};

	// ################################## --- ###########################################

	$(document).one('editor:start', XF.MJSTeditorStart.startAll);
	$(document).one('editor:buttons', XF.MJSTeditorButtons.initButtons);
}
(jQuery, window, document);