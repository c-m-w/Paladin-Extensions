<?php
// FROM HASH: 1798363fcb9a569b673024c7a4e7d203
return array('macros' => array(), 'code' => function($__templater, array $__vars)
{
	$__finalCompiled = '';
	$__finalCompiled .= 'var discordWidget = discordWidget || (function() {
    var b = {};
    var a = "1.1";
    return {
        init: function(c) {
            c.serverId = typeof c.serverId !== "undefined" ? c.serverId : false;
            c.title = typeof c.title !== "undefined" ? c.title : false;
            c.join = typeof c.join !== "undefined" ? c.join : true;
            c.alphabetical = typeof c.alphabetical !== "undefined" ? c.alphabetical : false;
            c.theme = typeof c.theme !== "undefined" ? c.theme : "light";
            c.hideChannels = typeof c.hideChannels !== "undefined" ? c.hideChannels : false;
            c.showAllUsers = typeof c.showAllUsers !== "undefined" ? c.showAllUsers : false;
            c.allUsersDefaultState = typeof c.allUsersDefaultState !== "undefined" ? c.allUsersDefaultState : true;
            c.showNick = typeof c.showNick !== "undefined" ? c.showNick : true;
            b.serverId = c.serverId;
            b.title = c.title;
            b.join = c.join;
            b.alphabetical = c.alphabetical;
            b.theme = c.theme;
            b.hideChannels = c.hideChannels;
            b.showAllUsers = c.showAllUsers;
            b.allUsersDefaultState = c.allUsersDefaultState;
            b.showNick = c.showNick
        },
        render: function() {
            if (window.jQuery) {
                d()
            } else {
                var c = document.createElement("script");
                c.type = "text/javascript";
                c.src = "https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js";
                document.head.appendChild(c);
                c.onload = function() {
                    d()
                }
            }

            function d() {
                var k = "";
                switch (b.theme) {
                    case "dark":
                        k = "dark.min.css";
                        break;
                    case "light":
                        k = "light.min.css";
                        break;
                    case "none":
                        k = "none.min.css";
                        break;
                    default:
                        k = "light.min.css"
                }
                
                var h = "https://discordapp.com/api/servers/" + b.serverId + "/embed.json";
                var i = new XMLHttpRequest();
                i.onreadystatechange = function() {
                    if (i.readyState == 4 && i.status == 200) {
                        var l = JSON.parse(i.responseText);
                        j(l, b);
                        if (!b.allUsersDefaultState) {
                            $(".discord-allusers").toggle();
                            $(".discord-allusers-toggle").html("&#9656; Online Users")
                        }
                        $(".discord-allusers-toggle").click(function() {
                            $(".discord-allusers").toggle(100, function() {
                                if ($(".discord-allusers").is(":visible")) {
                                    $(".discord-allusers-toggle").html("&#9662; Online Users")
                                } else {
                                    $(".discord-allusers-toggle").html("&#9656; Online Users")
                                }
                            })
                        })
                    } else {
                        if (i.readyState == 4 && i.status == 404) {
                            j("404", b)
                        } else {
                            if (i.readyState == 4) {
                                j(i.status, b)
                            }
                        }
                    }
                };
                i.open("GET", h, true);
                i.send();

                function e(m, l) {
                    if (m.position < l.position) {
                        return -1
                    }
                    if (m.position > l.position) {
                        return 1
                    }
                    return 0
                }

                function g(l) {
                    return \'<li class="discord-channel">\' + l + \'</li><ul class="discord-userlist">\'
                }

                function f(o, m) {
                    var l = "";
                    if (b.showNick == true && o.nick) {
                        l = o.nick
                    } else {
                        l = o.username
                    }
                    var n = "";
                    if (o.game) {
                        n = " - " + o.game.name
                    }
                    if (o.channel_id == m) {
                        if (o.status != "online") {
                            return \'<li class="discord-user"><img src="\' + o.avatar_url + \'" class="discord-avatar"/><div class="discord-user-status discord-idle"></div>\' + l + "<span>" + n + "</span></li>"
                        } else {
                            return \'<li class="discord-user"><img src="\' + o.avatar_url + \'" class="discord-avatar"/><div class="discord-user-status discord-online"></div>\' + l + "<span>" + n + "</span></li>"
                        }
                    } else {
                        return ""
                    }
                }

                function j(y, n) {
                    var z = $(".discord-widget")[0];
                    $(z).attr("version", a);
                    var A = \'<ul class="discord-tree"></ul><p class="discord-users-online"></p><p class="discord-join"></p><div class="discord-fade"></div>\';
                    var u = "";
                    var r = "";
                    var l, w, x;
                    var v, m, q, o;
                    if (n.title !== false) {
                        z.innerHTML = \'<div class="discord-title"><h3>\' + n.title + "</h3></div>" + A;
                        l = $(".discord-tree")[0]
                    } else {
                        z.innerHTML = A;
                        l = $(".discord-tree")[0];
                        l.style.marginTop = "0"
                    }
                    switch (y) {
                        case "404":
                            l.innerHTML = \'<span class="discord-error">Invalid Server ID</span>\';
                            break;
                        case "522":
                            l.innerHTML = \'<span class="discord-error">Discord is having issues.</span>\';
                            break
                    }
                    if (!y) {
                        l.innerHTML = y;
                        return
                    }
                    w = $(".discord-users-online")[0];
                    x = $(".discord-join")[0];
                    if (typeof(n.hideChannels) !== "boolean" || !n.hideChannels) {
                        if (n.alphabetical) {
                            v = [];
                            o = [];
                            for (var t = 0; t < y.channels.length; t++) {
                                q = false;
                                for (var s = 0; s < n.hideChannels.length; s++) {
                                    if (y.channels[t].name.indexOf(n.hideChannels[s]) >= 0) {
                                        q = true
                                    }
                                }
                                if (!q) {
                                    v.push(y.channels[t])
                                } else {
                                    o.push(y.channels[t].id)
                                }
                            }
                            for (var t = 0; t < v.length; t++) {
                                u += g(v[t].name);
                                for (var s = 0; s < y.members.length; s++) {
                                    u += f(y.members[s], v[t].id)
                                }
                                u += "</ul>"
                            }
                        } else {
                            v = [];
                            o = [];
                            for (var t = 0; t < y.channels.length; t++) {
                                q = false;
                                for (var s = 0; s < n.hideChannels.length; s++) {
                                    if (y.channels[t].name.indexOf(n.hideChannels[s]) >= 0) {
                                        q = true
                                    }
                                }
                                if (!q) {
                                    v.push(y.channels[t])
                                } else {
                                    o.push(y.channels[t].id)
                                }
                            }
                            v.sort(e);
                            for (var t = 0; t < v.length; t++) {
                                u += g(v[t].name);
                                for (var s = 0; s < y.members.length; s++) {
                                    u += f(y.members[s], v[t].id)
                                }
                                u += "</ul>"
                            }
                        }
                    }
                    if (n.showAllUsers) {
                        u += \'<li class="discord-channel discord-allusers-toggle">&#9662; Online Users</li><ul class="discord-userlist discord-allusers">\';
                        for (var t = 0; t < y.members.length; t++) {
                            if (!y.members[t].channel_id || $.inArray(y.members[t].channel_id, o) >= 0) {
                                u += f(y.members[t], y.members[t].channel_id)
                            }
                        }
                        u += "</ul>"
                    }
                    var B = "";
                    if (y.instant_invite != "null") {
                        B = \'<a href="\' + \'' . $__templater->escape($__vars['xf']['options']['ahDW_inviteLink']) . '\' + \'" target="_blank" class="button button--primary">' . $__templater->escape($__vars['xf']['options']['ahDW_joinText']) . '</a>\'
                    }
                    l.innerHTML = u;
                    w.innerHTML = "Users Online: " + y.members.length;
                    if (n.join) {
                        x.innerHTML = B
                    } else {
                        x.style.display = "none"
                    }
                }
            }
        }
    }
}());
							
							
discordWidget.init({
	serverId: \'' . $__templater->escape($__vars['xf']['options']['ahDW_serverID']) . '\',
    join: ';
	if ($__vars['xf']['options']['ahDW_showJoin']) {
		$__finalCompiled .= 'true';
	} else {
		$__finalCompiled .= 'false';
	}
	$__finalCompiled .= ',
    alphabetical: ';
	if ($__vars['xf']['options']['ahDW_alph']) {
		$__finalCompiled .= 'true';
	} else {
		$__finalCompiled .= 'false';
	}
	$__finalCompiled .= ',
   	theme: \'light\',
    hideChannels: ';
	if ($__vars['xf']['options']['ahDW_hideAll']) {
		$__finalCompiled .= 'true';
	} else {
		$__finalCompiled .= '[' . $__templater->filter($__vars['xf']['options']['ahDW_hideSpecific'], array(array('raw', array()),), true) . ']';
	}
	$__finalCompiled .= ',
    showAllUsers: ';
	if ($__vars['xf']['options']['ahDW_hideUsers']) {
		$__finalCompiled .= 'false';
	} else {
		$__finalCompiled .= 'true';
	}
	$__finalCompiled .= ',
    allUsersDefaultState: ';
	if ($__vars['xf']['options']['ahDW_collapseUsers']) {
		$__finalCompiled .= 'false';
	} else {
		$__finalCompiled .= 'true';
	}
	$__finalCompiled .= '
});
discordWidget.render();';
	return $__finalCompiled;
});