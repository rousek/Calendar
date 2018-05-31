//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDayInMonth.h"

std::set<CDate> CEventRepeatDayInMonth::TestRange(const CDate &date, const CDate &from, const CDate &to) const
{
    if (date > to)
        return {};

    std::set<CDate> results;

    if (date >= from)
        results.insert(date);

    tm tm = from.GetTm();
    int day;

    if (m_Day < 0)
        day = CDate::MonthLength(from.GetMonth(), from.GetYear()) + m_Day + 1;
    else
        day = m_Day;

    tm.tm_mday = day;
    tm.tm_hour = date.GetHour();
    tm.tm_min = date.GetMinute();
    CDate current(tm);

    while (current <= to)
    {
        if (current > date && current >= from)
        {
            if (m_Day < 0)
            {
                if (current.GetDay() == CDate::MonthLength(current.GetMonth(), current.GetYear()) + m_Day + 1)
                    results.insert(current);
            }
            else
            {
                if (current.GetDay() == m_Day)
                    results.insert(current);
            }
        }

        tm.tm_mon++;
        if (tm.tm_mon == 11)
        {
            tm.tm_mon = 0;
            tm.tm_year++;
        }

        if (m_Day < 0)
            tm.tm_mday = CDate::MonthLength(tm.tm_mon + 1, tm.tm_year + 1900) + m_Day + 1;
        else
            tm.tm_mday = m_Day;

        current = CDate(tm);
    }

    return results;
}

std::string CEventRepeatDayInMonth::ToStr() const
{
    return toStr("month_day ") + toStr(m_Day);
}