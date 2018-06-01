//
// Created by matyas on 06/01/2018.
//

#include <functional>
#include <vector>
#include "CDuration.h"
#include "../utils/utils.h"

const int CDuration::SECS_IN_MINUTE = 60;
const int CDuration::MINUTES_IN_HOUR = 60;
const int CDuration::HOURS_IN_DAY = 24;
const int CDuration::DAYS_IN_WEEK = 7;
const int CDuration::MONTHS_IN_YEAR = 12;
const int CDuration::SECS_IN_HOUR = CDuration::MINUTES_IN_HOUR * CDuration::SECS_IN_MINUTE;
const int CDuration::SECS_IN_DAY = CDuration::HOURS_IN_DAY * CDuration::SECS_IN_HOUR;
const int CDuration::SECS_IN_WEEK = CDuration::DAYS_IN_WEEK * CDuration::SECS_IN_DAY;
// These two values are only used for estimates.
const int CDuration::SECS_IN_MONTH = 2629746;
const int CDuration::SECS_IN_YEAR = 31556952;

CDuration::CDuration()
{
    m_Seconds = m_Months = m_Years = 0;
}

CDuration::CDuration(const std::string &str) : CDuration()
{
    std::vector<std::string> parts = split(str, ',');

    for (auto part : parts)
    {
        std::stringstream ss(part);
        int number;
        std::string unit;

        if (!(ss >> number) || !(ss >> unit))
            throw std::invalid_argument("Invalid duration string!");

        if (unit == "year" || unit == "years")
            m_Years += number;
        else if (unit == "month" || unit == "months")
            m_Months += number;
        else if (unit == "week" || unit == "weeks")
            m_Seconds += number * SECS_IN_WEEK;
        else if (unit == "day" || unit == "days")
            m_Seconds += number * SECS_IN_DAY;
        else if (unit == "hour" || unit == "hours")
            m_Seconds += number * SECS_IN_HOUR;
        else if (unit == "minute" || unit == "minutes")
            m_Seconds += number * SECS_IN_MINUTE;
        else if (unit == "second" || unit == "seconds")
            m_Seconds += number;
        else
            throw std::invalid_argument("Invalid duration string!");
    }
}

CDuration CDuration::Years(long long int value)
{
    CDuration dur;
    dur.m_Years = value;
    return dur;
}

CDuration CDuration::Months(long long int value)
{
    CDuration dur;
    dur.m_Months = value;
    return dur;
}

CDuration CDuration::Weeks(long long int value)
{
    CDuration dur;
    dur.m_Seconds = value * SECS_IN_WEEK;
    return dur;
}

CDuration CDuration::Days(long long int value)
{
    CDuration dur;
    dur.m_Seconds = value * SECS_IN_DAY;
    return dur;
}

CDuration CDuration::Hours(long long int value)
{
    CDuration dur;
    dur.m_Seconds = value * SECS_IN_HOUR;
    return dur;
}

CDuration CDuration::Minutes(long long int value)
{
    CDuration dur;
    dur.m_Seconds = value * SECS_IN_MINUTE;
    return dur;
}

CDuration CDuration::Seconds(long long int value)
{
    CDuration dur;
    dur.m_Seconds = value;
    return dur;
}

bool CDuration::operator==(const CDuration &d2) const
{
    return m_Seconds == d2.m_Seconds && m_Months == d2.m_Months && m_Years == d2.m_Years;
}

CDuration CDuration::operator+(const CDuration &d2) const
{
    CDuration cpy(*this);
    cpy.m_Seconds += d2.m_Seconds;
    cpy.m_Years += d2.m_Years;
    cpy.m_Months += d2.m_Months;

    return cpy;
}

CDuration CDuration::operator-(const CDuration &d2) const
{
    CDuration cpy(*this);
    cpy.m_Seconds -= d2.m_Seconds;
    cpy.m_Years -= d2.m_Years;
    cpy.m_Months -= d2.m_Months;

    return cpy;
}

CDuration& CDuration::operator+=(const CDuration &d2)
{
    m_Months += d2.m_Months;
    m_Years += d2.m_Years;
    m_Seconds += d2.m_Seconds;

    return *this;
}

CDuration& CDuration::operator-=(const CDuration &d2)
{
    m_Months -= d2.m_Months;
    m_Years -= d2.m_Years;
    m_Seconds -= d2.m_Seconds;

    return *this;
}

CDuration CDuration::operator-() const
{
    CDuration cpy(*this);
    cpy.m_Seconds = -m_Seconds;
    cpy.m_Years = -m_Years;
    cpy.m_Months = -m_Months;

    return cpy;
}

CDuration::Separated CDuration::Separate() const
{
    long long seconds = m_Seconds;

    long long months = m_Months % MONTHS_IN_YEAR;
    long long years = m_Years + m_Months / MONTHS_IN_YEAR;

    long long weeks = seconds / CDuration::SECS_IN_WEEK;
    seconds -= weeks * CDuration::SECS_IN_WEEK;

    long long days = seconds / CDuration::SECS_IN_DAY;
    seconds -= days * CDuration::SECS_IN_DAY;

    long long hours = seconds / CDuration::SECS_IN_HOUR;
    seconds -= hours * CDuration::SECS_IN_HOUR;

    long long minutes = seconds / CDuration::SECS_IN_MINUTE;
    seconds -= minutes * CDuration::SECS_IN_MINUTE;

    Separated separated;
    separated.years = years;
    separated.months = months;
    separated.weeks = weeks;
    separated.days = days;
    separated.hours = hours;
    separated.minutes = minutes;
    separated.seconds = seconds;

    return separated;
}

std::ostream & operator<<(std::ostream & stream, const CDuration & duration)
{
    CDuration::Separated separated(duration.Separate());

    std::string delimiter;

    auto write = [](long long value, const std::string & name, std::ostream & stream, std::string & delim)
    {
        if (value != 0)
        {
            stream << delim << value << ' ' << name << ((value == 1) ? "" : "s");
            delim = ", ";
        }
    };

    write(separated.years, "year", stream, delimiter);
    write(separated.months, "month", stream, delimiter);
    write(separated.weeks, "week", stream, delimiter);
    write(separated.days, "day", stream, delimiter);
    write(separated.hours, "hour", stream, delimiter);
    write(separated.minutes, "minute", stream, delimiter);
    write(separated.seconds, "second", stream, delimiter);

    return stream;
}