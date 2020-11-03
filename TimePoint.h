#pragma once
#include <iostream>
#include <string_view>

// represents a time of day, i.e. HH:MM:SS
class TimePoint
{
public:
    TimePoint(std::string_view const& str);
    ~TimePoint() = default;

    const int hours;
    const int minutes;
    const int seconds;
    const int secondsSum;

    constexpr bool isValid() const noexcept;

    constexpr bool operator==(const TimePoint& other) const noexcept { return this->secondsSum == other.secondsSum; }
    constexpr bool operator!=(const TimePoint& other) const noexcept { return !this->operator==(other); }
    constexpr bool operator<(const TimePoint& other) const noexcept { return this->secondsSum < other.secondsSum; }
    constexpr bool operator>(const TimePoint& other) const noexcept { return this->secondsSum > other.secondsSum; }
    constexpr bool operator<=(const TimePoint& other) const noexcept { return !this->operator>(other); }
    constexpr bool operator>=(const TimePoint& other) const noexcept { return !this->operator<(other); }

    friend std::ostream& operator<<(std::ostream& ostr, const TimePoint& tp)
    {
        return ostr << tp.hours << ":" << tp.minutes << ":" << tp.seconds;
    }
};
