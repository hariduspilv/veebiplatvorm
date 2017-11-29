(function ($) {
    Drupal.behaviors.hitsa_catering = {
        attach: function (context, settings) {
            $('.end-date-wrapper input').datepicker({showOn: "off"});
            var used_dates = settings.hitsa_catering.dates;
            var dateToday = new Date();
            var curr = new Date; // get current date
            var first = curr.getDate() - curr.getDay() + 1; // First day is the day of the month - the day of the week
            var firstday = new Date(curr.setDate(first));
            $('.start-date-wrapper input').datepicker({

                minDate: firstday,
                dateFormat: 'dd/mm/yy',
                beforeShowDay: function (date) {
                    var date_unix = date.getTime() / 1000;
                    var day = date.getDay();

                    if ($.inArray(date_unix, used_dates) > -1) {
                        return [false, ""];
                    }

                    if (day == 1) {
                        return [true, ""];
                    } else {
                        return [false, ""];
                    }
                },
                onSelect: function (_date, _datepicker) {
                    var newDate = toDate(_date);
                    $('.end-date-wrapper input').val($.datepicker.formatDate('dd/mm/yy', newDate));
                    //$('.end-date-wrapper input').attr('disabled', 'disabled');
                }
            });
        },
    }

    function toDate(dateStr) {
        const [day, month, year] = dateStr.split("/");
        var newDate = new Date(year, month - 1, day);
        //add 6 days (friday)
        newDate.setDate(newDate.getDate() + 6);
        return newDate;
    }


})(jQuery);