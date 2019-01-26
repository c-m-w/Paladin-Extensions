/** @param {jQuery} $ jQuery Object */
!function($, window, document, _undefined) {
    "use strict";

    // ################################## REACTION HANDLER ###########################################
    var register = function(container) {
        if (window.th_reactionsCloseAdded !== true) {
            $(document).click(function(e) {
                var closestReactionBar = $(e.target).closest('.reactions-right');
                if (closestReactionBar.length === 0) {
                    var openbar = $('.reactions-bar--show');
                    if (openbar.length) {
                        var barTrigger = openbar.closest('.reactions-right').find('.th_reactions__trigger');
                        if (barTrigger.length) {
                            th_reactionToggle(barTrigger.last());
                        }
                    }
                }
            });

            $(window).resize(function() {
                resize();
            });

            document.addEventListener('touchmove', function(e) {
                reactionTouchMove(e);
            });

            document.addEventListener('touchend', function(e) {
                reactionTouchEnd(e);
            })
            window.th_reactionsCloseAdded = true;
        }


        if (th_reactionsSecondaryTrigger) {
            window.th_reactionsEnableHover = true;
            var triggers = $('.th_reactions__triggerSecondary');
        } else {
            var triggers = $('.th_reactions__trigger');
        }

        triggers.off('hover');

        triggers.hover(function(e) {
            $(e.target).removeClass('th_reactions__trigger--hoverOut').addClass('th_reactions__trigger--hoverIn');
        }, function(e) {
            var ele = $(e.target);
            ele.removeClass('th_reactions__trigger--hoverIn').addClass('th_reactions__trigger--hoverOut');
            window.setTimeout(function() {
                ele.removeClass('th_reactions__trigger--hoverOut');
            }, 300);
        });

        if (th_reactionsEnableHover) {
            triggers.off('mouseenter');

            triggers.mouseenter(function(e) {
                var trigger = $(e.target);
                var blockedByContainer = false;
                if (typeof (window.th_reactionsIgnoreInContainer) !== 'undefined' && window.th_reactionsIgnoreInContainer !== null && th_reactionsIgnoreInContainer.length) {
                    if (window.th_reactionsIgnoreInContainer.find(trigger).length) {
                        blockedByContainer = true;
                    }
                }
                if (blockedByContainer === false && !trigger.closest('.reactions-right').find('.reactions-right__list').hasClass('reactions-bar--show')) {
                    window.th_reactions_intentTimer = window.setTimeout(function() {
                        if (!trigger.closest('.reactions-right').find('.reactions-right__list').hasClass('reactions-bar--show')) {
                            th_reactionToggle(trigger);
                        }
                    }, 200);

                    trigger.mousemove(function() {
                        clearTimeout(window.th_reactions_intentTimer);
                        window.th_reactions_intentTimer = window.setTimeout(function() {
                            if (!trigger.closest('.reactions-right').find('.reactions-right__list').hasClass('reactions-bar--show')) {
                                th_reactionToggle(trigger);
                            }
                        }, 200);
                    });
                }
            });

            triggers.mouseleave(function(e) {
                window.th_reactionsIgnoreInContainer = null;
                var trigger = $(e.target);
                if (window.th_reactions_intentTimer !== null) {
                    clearTimeout(window.th_reactions_intentTimer);
                }
                window.th_reactions_intentTimer = null;
                trigger.off("mousemove");
            });
        }

        var reactions = document.querySelectorAll('.th_reactions__reaction');
        for (var i = 0, len = reactions.length; i < len; i++) {
            var reaction = reactions[i];
            reaction.removeEventListener('mouseover', reactionTouchMove);
            reaction.addEventListener('mouseover', reactionTouchMove);
            reaction.removeEventListener('touchstart', reactionTouchMove);
            reaction.addEventListener('touchstart', function(e) {
                e.preventDefault();
                reactionTouchMove(e);
            }, { passive: false });
            reaction.removeEventListener('touchend', reactionTouchEnd);
            reaction.addEventListener('touchend', reactionTouchEnd);
        }

        var th_reactionToggle = function(trigger) {
            clearTimeout(window.th_reactions_intentTimer);

            var ele = trigger.closest('.reactions-right').find('.reactions-right__list');
            var parentEle = ele.parent();
            if (ele.hasClass('reactions-bar--show')) {
                removeLabels();
                ele.removeClass('reactions-bar--show');
                void ele.width(); // force reflow
                ele.addClass('reactions-bar--hide');
                parentEle.removeClass('reactions-barChildren--show');
            } else {
                ele.removeClass('reactions-bar--hide');
                void ele.width(); // force reflow
                ele.addClass('reactions-bar--show');
                parentEle.addClass('reactions-barChildren--show');
            }
        }

        var secondaryTriggers = $('.th_reactions__triggerSecondary');

        secondaryTriggers.off('click');
        secondaryTriggers.click(function(e) {
            var trigger = $(this);
            trigger.off("mousemove");
            clearTimeout(window.th_reactions_intentTimer);
            th_reactionToggle(trigger);
        });

        var primaryTriggers = triggers;
        primaryTriggers.off('touchstart');
        primaryTriggers.off('touchend');
        primaryTriggers.on('touchstart', function(e) {
            var trigger = $(e.currentTarget);
            var timer = Date.now();

            var timeout = window.setTimeout(function() {
                trigger.off('touchend');
                th_reactionToggle(trigger);
                document.body.addEventListener('touchmove', reactionScrollBlock, { passive: false });
            }, 250);

            trigger.on('touchend', function(e) {
                clearTimeout(timeout);

                if ((Date.now() - timer) < 250) {
                    if (th_reactionsEnableHover) {
                        trigger.off('click');
                        trigger.find('span').click();
                    } else {
                        var ele = trigger.closest('.reactions-right').find('.reactions-right__list');
                        var parentEle = ele.parent();
                        if (!ele.hasClass('reactions-bar--show')) {
                            window.setTimeout(function() {
                                th_reactionToggle(trigger);
                            }, 0)
                            e.preventDefault();
                        } else {
                            trigger.off('click');
                            trigger.find('span').click();
                        }
                    }
                }

                e.preventDefault();
            });

            e.preventDefault();
            return false;
        });

        primaryTriggers.off('click');
        primaryTriggers.click(function(e) {
            var trigger = $(e.currentTarget);

            if (th_reactionsEnableHover) {
                trigger.off('click');
                trigger.find('span').click();
            } else {
                var ele = trigger.closest('.reactions-right').find('.reactions-right__list');
                var parentEle = ele.parent();
                if (!ele.hasClass('reactions-bar--show')) {
                    window.setTimeout(function() {
                        th_reactionToggle(trigger);
                    }, 0)
                    e.preventDefault();
                } else {
                    trigger.off('click');
                    trigger.find('span').click();
                }
            }
        });

        resize();

        var rightScrollers = $('.th_reactions__rightScrollRight');
        rightScrollers.off('click');
        rightScrollers.click(function(e) {
            removeLabels();
            var ele = $(e.target);
            var bar = ele.closest('.reactions-right').find('.reactions-right__list');
            var barEle = bar.get(0);
            var currentScroll = barEle.scrollLeft;
            var currentWidth = barEle.offsetWidth;
            var numSteps = 15;
            for (var i = 0; i <= numSteps; i++) {
                var step = function(index) {
                    window.setTimeout(function() {
                        barEle.scrollLeft = currentScroll + ((currentWidth - 40) / numSteps) * index;
                    }, (17 * index));
                }
                step(i);
            }
        });

        var leftScrollers = $('.th_reactions__leftScrollLeft');
        leftScrollers.off('click');
        leftScrollers.click(function(e) {
            removeLabels();
            var ele = $(e.target);
            var bar = ele.closest('.reactions-right').find('.reactions-right__list');
            var barEle = bar.get(0);
            var currentScroll = barEle.scrollLeft;
            var currentWidth = barEle.offsetWidth;
            var numSteps = 15;
            for (var i = 0; i <= numSteps; i++) {
                var step = function(index) {
                    window.setTimeout(function() {
                        barEle.scrollLeft = currentScroll - ((currentWidth - 50) / numSteps) * index;
                    }, (17 * index));
                }
                step(i);
            }
        });
    }

    var reactionTouchEnd = function(e) {
        var target = $('.th_reactions__reaction--hovered');

        if (target.length) {
            target.removeClass('th_reactions__reaction--hovered');
            target.find('a').click();
        }
    }

    var reactionScrollBlock = function(e) {
        e.preventDefault();
    }

    var reactionTouchMove = function(e) {
        var ele = $(e.target);
        if ((e.originalEvent && e.originalEvent.changedTouches && e.originalEvent.changedTouches.length) || (e.touches && e.touches.length)){
            var myLocation = (typeof (e.originalEvent) !== 'undefined') ? e.originalEvent.changedTouches[0] : e.touches[0];
            var realTarget = document.elementFromPoint(myLocation.clientX, myLocation.clientY);
            ele = $(realTarget);
        }
        if (!ele.hasClass('th_reactions__reaction')) {
            ele = ele.closest('.th_reactions__reaction');
        }

        if (ele.length) {
            if (!ele.hasClass('th_reactions__reaction--hovered')) {
                removeLabels();
                ele.addClass('th_reactions__reaction--hovered');
                var labelParent = ele.closest('.reactions-right');
                if (labelParent.length) {
                    var parentPos = labelParent.get(0).getBoundingClientRect();
                    var elePos = ele.get(0).getBoundingClientRect();

                    var newLabel = $('<div class="th_reactions__reactionLabel" style="top: ' + Math.round(elePos.top - parentPos.top - 32) + 'px; left: ' + Math.round(elePos.left - parentPos.left + elePos.width / 2) + 'px;">' + ele.find('.reaction').attr('title') + '</div>');
                    labelParent.append(newLabel);
                }
            }
        } else {
            removeLabels();
        }
    };

    var removeLabels = function() {
        document.body.removeEventListener('touchmove', reactionScrollBlock);

        var hoveredEle = $('.th_reactions__reaction--hovered');
        var labelEle = $('.th_reactions__reactionLabel');

        if (hoveredEle.length) {
            hoveredEle.addClass('th_reactions__reaction--hoveredOut');
            window.setTimeout(function(e) {
                hoveredEle.removeClass('th_reactions__reaction--hovered');
            }, 17);
            window.setTimeout(function(e) {
                hoveredEle.removeClass('th_reactions__reaction--hoveredOut');
            }, 317)
        }
        if (labelEle.length) {
            labelEle.addClass('th_reactions__reactionLabel--out');
            void labelEle.width(); // force a reflow
            window.setTimeout(function(e) {
                labelEle.remove();
            }, 200)
        }
    }

    var resize = function() {
        var reactionBars = $('.reactions-right');
        var barData = [];
        for (var i = 0, len = reactionBars.length; i < len; i++) {
            var reactionBar = $(reactionBars[i]);
            var reactionList = reactionBar.find('.reactions-right__list');
            var reactionScrollContainer = reactionBar.find('.th_reactions__scrollContainer');
            var reactionListRaw = reactionList.get(0);
            barData.push({
                ele: reactionBar,
                list: reactionList,
                rawEle: reactionListRaw,
                parentEle: reactionBar,
                parentRight: reactionBar.get(0).getBoundingClientRect().right,
                containerEle: reactionScrollContainer,
                containerWidth: reactionScrollContainer.get(0).getBoundingClientRect().width,
                offsetWidth: reactionListRaw.offsetWidth,
                scrollWidth: reactionListRaw.scrollWidth,
                scrollLeft: reactionListRaw.scrollLeft,
            });
        }

        for (var i = 0, len = barData.length; i < len; i++) {
            var data = barData[i];
            var windowWidth = window.innerWidth;

            if ((data.scrollWidth) < (windowWidth * 0.9)) {
                data.list.off('scroll');
                data.list.css('width', (data.scrollWidth) + 'px');
                data.ele.removeClass('th_reactions__reactionsBar--overflowing');
            } else {
                data.list.css('width', '');
                // if (data.offsetWidth < data.scrollWidth) {
                    if (!data.ele.hasClass('th_reactions__reactionsBar--overflowing')) {
                        data.ele.addClass('th_reactions__reactionsBar--overflowing');
                        data.containerEle.css('right', 15 - (windowWidth - data.parentRight)) + 'px';
                        data.list.off('scroll');
                        data.list.scroll(function(e) {
                            var ele = $(e.target);
                            reactionBar = ele.closest('.reactions-right');
                            var reactionScrollContainer = reactionBar.find('.th_reactions__scrollContainer');

                            checkScroll({
                                ele: ele,
                                rawEle: e.target,
                                parentEle: reactionBar,
                                parentRight: reactionBar.get(0).getBoundingClientRect().right,
                                containerEle: reactionScrollContainer,
                                containerWidth: reactionScrollContainer.get(0).offsetWidth,
                                offsetWidth: e.target.offsetWidth,
                                scrollWidth: e.target.scrollWidth,
                                scrollLeft: e.target.scrollLeft,
                            });
                        });
                        checkScroll(data);
                    }
                // } else {
                //     if (data.ele.hasClass('th_reactions__reactionsBar--overflowing')) {
                //         data.containerEle.css('right', '');
                //         data.ele.removeClass('th_reactions__reactionsBar--overflowing');
                //         checkScroll(data);
                //     }
                // }
            }
        }
    }

    var checkScroll = function(data) {
        var parentEle = data.parentEle;
        var rawEle = data.rawEle;
        var scrollWidth = data.scrollWidth;
        var scrollLeft = data.scrollLeft;
        var rightPos = data.scrollLeft + data.offsetWidth;

        if (parentEle.hasClass('th_reactions__rightScroll--inactive')) {
            if (rightPos < scrollWidth) {
                parentEle.removeClass('th_reactions__rightScroll--inactive')
            }
        } else {
            if (rightPos >= scrollWidth) {
                parentEle.addClass('th_reactions__rightScroll--inactive')
            }
        }

        if (parentEle.hasClass('th_reactions__leftScroll--inactive')) {
            if (scrollLeft > 0) {
                parentEle.removeClass('th_reactions__leftScroll--inactive')
            }
        } else {
            if (scrollLeft <= 0) {
                parentEle.addClass('th_reactions__leftScroll--inactive')
            }
        }
    }

    XF.ReactClick = XF.Click.newHandler({
        eventNameSpace: 'XFReactClick',

        options: {
			container: '.reactions-bar',
			target: null,
			href: null
        },

		$loaderTarget: null,
		$container: null,
		href: null,
		loading: false,

        init: function() {
			var container = this.options.container,
				$container = container ? this.$target.closest(container) : this.$target,
				target = this.options.target,
				$target = target ? XF.findRelativeIf(target, this.$container) : $container;

			this.$container = $container;

			if (!this.options.href) {
				this.href = this.$target.attr('href');
			}

			if (!this.href) {
				console.error('No reaction href for %o', this.$target);
			}
        },

        click: function(e) {
            if (!th_reactionsEnableHover) {
                var targetEle = $(e.target);
                var trigger = targetEle.closest('.th_reactions__trigger');
                if (trigger.length) {
                    var ele = targetEle.closest('.reactions-right').find('.reactions-right__list');
                    if (!ele.hasClass('reactions-bar--show')) {
                        return;
                    }
                }
            }

            e.preventDefault();
			$('.tooltip').hide();

			if (this.loading) {
				return;
			}

			this.loading = true;

			var t = this;
            XF.ajax('POST', this.href, null, $.proxy(this, 'handleAjax'),
				{
					skipDefaultSuccess: true
				}
			).always(function() {
				t.loading = false;
			});
        },

        handleAjax: function(data) {
			var $container = this.$container;
            if (typeof data.html !== 'undefined' && this.$container.length) {
                if (data.html.content) {
                    XF.setupHtmlInsert(data.html, function($html, container) {
						$container.html($html);
                        window.th_reactionsIgnoreInContainer = $container;
                        register();
                    });
                }
            }
        }
    });

    if (window.th_reactionsEnableHover !== false) {
        window.th_reactionsEnableHover = true;
    }

    XF.Click.register('react', 'XF.ReactClick');
    $(document).on('xf:reinit', function() {
        window.setTimeout(function() {
            register();
        }, 300);
    });

    if ((document.readyState === 'ready' || document.readyState === 'complete')) {
        window.setTimeout(function() {
            register();
        }, 300);
    } else {
        $(document).ready(register);
    }
}(jQuery, window, document);
