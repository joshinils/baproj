#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>

/// represents a time of day, i.e. HH:MM:SS
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
        std::ios init(NULL);
        init.copyfmt(ostr); /// copy initial format
        ostr << std::setfill('0'); /// change format
        ostr << std::setw(2) << std::right << tp.hours << ":" << std::setw(2) << std::right << tp.minutes << ":"
             << std::setw(2) << std::right << tp.seconds;
        ostr.copyfmt(init); /// reset to initial format
        return ostr;
    }

    operator std::string() const
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }
};
