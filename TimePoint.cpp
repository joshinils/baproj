#include "TimePoint.h"
#include <iostream>
#include <string_view>

constexpr int makeHour(std::string_view const& str)
{
    bool p1IsNumeric = str[1] < '0' || str[1] > '9';
    if(p1IsNumeric) return str.data()[0] - '0';
    return (str.data()[0] - '0') * 10 + str.data()[1] - '0';
}
constexpr int makeMinute(std::string_view const& str)
{
    bool p1IsNumeric = str[1] >= '0' && str[1] <= '9';
    bool p2IsNumeric = str[2] >= '0' && str[2] <= '9';
    if(p1IsNumeric && p2IsNumeric)
        return (str.data()[2 - !p1IsNumeric] - '0') * 10 + str.data()[3 - !p1IsNumeric] - '0';
    else
        return (str.data()[3 - !p1IsNumeric] - '0') * 10 + str.data()[4 - !p1IsNumeric] - '0';
}
constexpr int makeSecond(std::string_view const& str)
{
    bool p1IsNumeric = str[1] >= '0' && str[1] <= '9';
    bool p2IsNumeric = str[2] >= '0' && str[2] <= '9';
    if(p1IsNumeric && p2IsNumeric)
        return (str.data()[4 - !p1IsNumeric] - '0') * 10 + str.data()[5 - !p1IsNumeric] - '0';
    else
        return (str.data()[6 - !p1IsNumeric] - '0') * 10 + str.data()[7 - !p1IsNumeric] - '0';
}

TimePoint::TimePoint(std::string_view const& str)
    : hours(makeHour(str))
    , minutes(makeMinute(str))
    , seconds(makeSecond(str))
    , secondsSum(hours * 60 * 60 + minutes * 60 + seconds)
{
    if(!isValid())
    {
        auto a = makeHour(str);
        auto b = makeMinute(str);
        auto c = makeSecond(str);
        throw std::invalid_argument("wtf");
    }
}

constexpr bool TimePoint::isValid() const noexcept
{
    // according to gtfs reference, a timepoint may be on the next day after midnight,
    // i.e. 26:07:13 means 01:07:13 + 1 Day
    //
    // hence this is correct
    //         └─────────vvvvv─vv─vv─v─v
    return hours >= 0 && hours <= 24 * 2 && minutes >= 0 && minutes <= 60 && seconds >= 0 && seconds <= 60;
}
