#pragma once

class Calendar
{
public:
    Calendar();
    ~Calendar();

private:
    /** Uniquely identifies a set of dates when service is available for one or more routes. Each service_id value can
     * appear at most once in a calendar.txt file. */
    int service_id; /// Required

    /** Indicates whether the service operates on all Mondays in the date range specified by the start_date and
        end_date fields. Note that exceptions for particular dates may be listed in calendar_dates.txt.
        Valid options are:

        1 (true) - Service is available for all Mondays in the date range.
        0 (false) - Service is not available for Mondays in the date range.*/
    bool monday; /// Required

    /** Functions in the same way as monday except applies to Tuesdays */
    bool tuesday; /// Required

    /** Functions in the same way as monday except applies to Wednesdays */
    bool wednesday; /// Required

    /** Functions in the same way as monday except applies to Thursdays */
    bool thursday; /// Required

    /** Functions in the same way as monday except applies to Fridays */
    bool friday; /// Required

    /** Functions in the same way as monday except applies to Saturdays. */
    bool saturday; /// Required

    /** Functions in the same way as monday except applies to Sundays. */
    bool sunday; /// Required

    /** Start service day for the service interval. */
    /** Date */ int start_date; /// Required

    /** End service day for the service interval. This service day is included in the interval. */
    /** Date */ int end_date; /// Required
};
