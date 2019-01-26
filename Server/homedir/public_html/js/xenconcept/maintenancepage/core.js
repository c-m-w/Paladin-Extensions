/*************************************************************************
 * Maintenance Page - XenConcept (c) 2017
 * All Rights Reserved.
 **************************************************************************
 * This file is subject to the terms and conditions defined in the Licence
 * Agreement available at Try it like it buy it :)
 *************************************************************************/

/** @param {jQuery} $ jQuery Object */
!function($, window, document)
{
    "use strict";

    XF.CountDown = XF.Element.newHandler({

        init: function ()
        {
            var $this   = this.$target;

            $this.countdown(new Date(this.$target.data('countdown')), function (event)
            {
                var months    = $(".timer-figure--months"),
                    days      = $(".timer-figure--days"),
                    hours     = $(".timer-figure--hours"),
                    minutes   = $(".timer-figure--minutes"),
                    seconds   = $(".timer-figure--seconds");

                months.empty().append(event.strftime('%m'));
                days.empty().append(event.strftime('%n'));
                hours.empty().append(event.strftime('%H'));
                minutes.empty().append(event.strftime('%M'));
                seconds.empty().append(event.strftime('%S'))

            })

        }
    });

    XF.Element.register('countdown', 'XF.CountDown');
    XF.Element.register('time-input', 'XF.TimeInput');


}
(jQuery, window, document);