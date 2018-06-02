//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDayInMonth.h"

std::set<CDate> CEventRepeatDayInMonth::TestRange(const CDate &date, const CDate::Interval & interval) const
{
    CDate from = interval.first;
    CDate to = interval.second;

    if (date > to)
        return {};

    std::set<CDate> results;

    if (date >= from)
        results.insert(date);

    CDate current = from;
    current.SetHour(date.GetHour()).SetMinute(date.GetMinute());

    if (m_Day > 0)
        Positive(date, to, results, current);
    else
        Negative(date, to, results, current);

    return results;
}

void CEventRepeatDayInMonth::Negative(const CDate &date, const CDate &to, std::set<CDate> &results, CDate current) const
{
    // -1 is last day of month.
    int offset = m_Day + 1;
    int monthLen = CDate::MonthLength(current.GetMonth(), current.GetYear());
    int day = monthLen + offset;

    if (day < 1)
        {
            // Set current to first day of next month.
            current.SetDay(1);
            current += CDuration::Months(1);

            // Determine length of said day and date.
            monthLen = CDate::MonthLength(current.GetMonth(), current.GetYear());
            day = monthLen + offset;
        }

    current.SetDay(day);

    while (current <= to)
    {
        if (current > date)
            results.insert(current);

        // Loop necessary in case m_Day is -31 and month is February.
        while (true)
        {
            // Set current to first day of next month.
            current.SetDay(1);
            current += CDuration::Months(1);

            // Determine length of said day and date.
            monthLen = CDate::MonthLength(current.GetMonth(), current.GetYear());
            day = monthLen + offset;

            if (day > 0)
                break;
        }

        current.SetDay(day);
    }
}

void CEventRepeatDayInMonth::Positive(const CDate &date, const CDate & to, std::set<CDate> &results, CDate current) const
{
    current.SetDay(m_Day);

    while (current <= to)
    {
        if (current > date)
            results.insert(current);

        current += CDuration::Months(1);

        // Date overflows into next month when it's invalid (30. 02. would be 01. 03. or 02. 03.)
        if (current.GetDay() != m_Day)
            current.SetDay(m_Day);
    }
}

bool CEventRepeatDayInMonth::Delete(const CDate & date)
{
    m_Skipped.insert(date);
    return false;
}

std::string CEventRepeatDayInMonth::ToStr() const
{
    return toStr("month_day ") + toStr(m_Day);
}