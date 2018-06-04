//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDayInMonth.h"

using namespace std;

std::set<CDate> CEventRepeatDayInMonth::TestRange(const CDate &date, const CDate::Interval & interval) const
{
    CDate from = MAX(interval.first, date);
    CDate to = interval.second;

    if (from > to)
        return {};

    std::set<CDate> results;

    if (date >= from)
        results.insert(date);

    CDate firstOfMonth = date;
    firstOfMonth.SetDay(1).SetMonth(from.GetMonth()).SetYear(from.GetYear());

    while(true)
    {
        int monthLen = CDate::MonthLength(firstOfMonth.GetMonth(), firstOfMonth.GetYear());
        int day = (m_Day < 0) ? (monthLen + m_Day + 1) : m_Day;

        if (day <= 0 || day > monthLen)
        {
            firstOfMonth += CDuration::Months(1);
            continue;
        }

        CDate candidate(firstOfMonth);
        candidate.SetDay(day);

        bool lowerBound = candidate >= from;
        bool upperBound = candidate <= to;

        if (upperBound && lowerBound)
            results.insert(candidate);
        else if (!upperBound)
            break;

        firstOfMonth += CDuration::Months(1);
    }

    return results;
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