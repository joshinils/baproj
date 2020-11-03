#include "TimePoint.h"
#include <iostream>
#include <string_view>

constexpr int makeHour(std::string_view const& str) { return (str.data()[0] - '0') * 10 + str.data()[1] - '0'; }
constexpr int makeMinute(std::string_view const& str)
{
    if(str[2] >= '0' && str[2] <= '9') return (str.data()[2] - '0') * 10 + str.data()[3] - '0';
    else
        return (str.data()[3] - '0') * 10 + str.data()[4] - '0';
}
constexpr int makeSecond(std::string_view const& str)
{
    if(str[2] >= '0' && str[2] <= '9') return (str.data()[4] - '0') * 10 + str.data()[5] - '0';
    else
        return (str.data()[6] - '0') * 10 + str.data()[7] - '0';
}

TimePoint::TimePoint(std::string_view const& str)
    : hours(makeHour(str))
    , minutes(makeMinute(str))
    , seconds(makeSecond(str))
    , secondsSum(hours * 60 * 60 + minutes * 60 + seconds)
{ }

constexpr bool TimePoint::isValid() const noexcept
{
    return hours >= 0 && hours <= 24 && minutes >= 0 && minutes <= 60 && seconds >= 0 && seconds <= 60;
}
