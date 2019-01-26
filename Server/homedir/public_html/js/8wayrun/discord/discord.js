var EWRdiscord = window.EWRdiscord || {};

!function($, window, document)
{
	// ################################## --- ###########################################
	
	EWRdiscord.Botcheck = XF.Element.newHandler(
	{
		$target: null,
		token: null,
		
		init: function()
		{
			$target = this.$target;
			token = $target.data('token');
		
			$target.on('click', $target, $.proxy(this, 'click'));
		},
		
		click: function(e)
		{
			var sequence = 0;
			var socket = new WebSocket("wss://gateway.discord.gg/?encoding=json&v=6");
			
			socket.onopen = function() { console.log("Discord: Websocket OPEN"); },
			socket.onerror = function(err) { console.error(err); },
			socket.onclose = function(err) { console.error(err); },
			socket.onmessage = function(msg)
			{
				try
				{
					var data = JSON.parse(msg.data);
					sequence = data.s;
					
					if (data.op == "10")
					{
						$target.addClass('button--cta');
						$target.find('.button-text').text('CONNECTED');
						console.log('Discord: Sending handshake');
						
						socket.send(JSON.stringify({
							op: 2,
							d:
							{
								token: token,
								properties:
								{
									$browser: "DiscordBot (8wayrunBot, v2)"
								},
								large_threshold: 50
							}
						})),
						setInterval(function()
						{
							$target.find('.button-text').text('HEARTBEAT');
							console.log('Discord: Sending heartbeat ('+sequence+')');
							
							socket.send(JSON.stringify(
							{
								op: 1,
								d: sequence
							}));
						}, data.d.heartbeat_interval);
					}
				}
				catch (err)
				{
					$target.removeClass('button--cta');
					$target.find('.button-text').text('ERROR');
					console.error(err);
				}
			};
		},
	});
	
	// ################################## --- ###########################################

	XF.Element.register('discord-botcheck', 'EWRdiscord.Botcheck');
}
(window.jQuery, window, document);