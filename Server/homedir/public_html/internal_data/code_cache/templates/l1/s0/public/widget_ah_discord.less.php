<?php
// FROM HASH: 867ef976f9ce4e29558464bd96e21072
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= '.block[data-widget-definition="ahDiscordWidget"] .block-minorHeader {
	display: flex;
	align-items: center;
}

.discord-widget {
	.xf-ahDW_container();
	
	.discord-tree {
		.discord-channel {
			.xf-ahDW_channel();
		}
	
		.discord-userlist {
			.xf-ahDW_userList();
			
			.discord-user {
				.xf-ahDW_user();
				
				.discord-avatar {
					.xf-ahDW_userAvatar();
				}
				
				.discord-user-status {
					.xf-ahDW_userStatus();
				}	
				
				.discord-online {
					background-color: @xf-ahDW_userStatusOnline;
				}
				
				.discord-idle {
					background-color: @xf-ahDW_userStatusIdle;
				}
				
				span {
					.xf-ahDW_userPlaying();
				}
			}
		}
		
		.discord-allusers {
			.xf-ahDW_allUsersList();
		}
	}
	
	.discord-users-online {
		.xf-ahDW_usersOnlineText();
	}
	
	.discord-join {
		text-align: center;
		margin-top: 9px;
			
		.joinButton {
			.xf-ahDW_joinServerButton();
		}
	}
}

.discord-widget div, .discord-widget span, .discord-widget applet, .discord-widget object, .discord-widget iframe, .discord-widget h1, .discord-widget h2, .discord-widget h3, .discord-widget h4, .discord-widget h5, .discord-widget h6, .discord-widget p, .discord-widget blockquote, .discord-widget pre, .discord-widget abbr, .discord-widget acronym, .discord-widget address, .discord-widget big, .discord-widget cite, .discord-widget code, .discord-widget del, .discord-widget dfn, .discord-widget em, .discord-widget img, .discord-widget ins, .discord-widget kbd, .discord-widget q, .discord-widget s, .discord-widget samp, .discord-widget small, .discord-widget strike, .discord-widget strong, .discord-widget sub, .discord-widget sup, .discord-widget tt, .discord-widget var, .discord-widget b, .discord-widget u, .discord-widget i, .discord-widget center, .discord-widget dl, .discord-widget dt, .discord-widget dd, .discord-widget ol, .discord-widget ul, .discord-widget li, .discord-widget fieldset, .discord-widget form, .discord-widget label, .discord-widget legend, .discord-widget table, .discord-widget caption, .discord-widget tbody, .discord-widget tfoot, .discord-widget thead, .discord-widget tr, .discord-widget th, .discord-widget td, .discord-widget article, .discord-widget aside, .discord-widget canvas, .discord-widget details, .discord-widget embed, .discord-widget figure, .discord-widget figcaption, .discord-widget footer, .discord-widget header, .discord-widget hgroup, .discord-widget menu, .discord-widget nav, .discord-widget output, .discord-widget ruby, .discord-widget section, .discord-widget summary, .discord-widget time, .discord-widget mark, .discord-widget audio, .discord-widget video {
    margin: 0;
    padding: 0;
    border: 0;
    font-size: 100%;
    font: inherit;
    vertical-align: middle;
}';
	return $__finalCompiled;
});