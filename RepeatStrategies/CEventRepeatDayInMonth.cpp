//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDayInMonth.h"

std::vector<CDate> CEventRepeatDayInMonth::TestRange(const CDate &date, const CDate &from, const CDate &to) const
{
    if (date > to)
        return {};

    std::vector<CDate> results;

        tm tm = from.GetTm();
        int day;

        if (m_Day < 0)
            day = MonthLength(from.GetMonth(), from.GetYear()) + m_Day + 1;
        else
            day = m_Day;

        tm.tm_mday = day;
        tm.tm_hour = date.GetHour();
        tm.tm_min = date.GetMinute();
        CDate current(tm);

        while(current <= to)
        {
            if (current >= date && current >= from)
            {
                if (m_Day < 0 && current.GetDay() == MonthLength(current.GetMonth(), current.GetYear()) + m_Day + 1)
                    results.push_back(current);
                else if (m_Day > 0 && current.GetDay() == m_Day)
                    results.push_back(current);
            }

            tm.tm_mon++;
            if (tm.tm_mon == 11)
            {
                tm.tm_mon = 0;
                tm.tm_year++;
            }

            if (m_Day < 0)
                tm.tm_mday = MonthLength(tm.tm_mon + 1, tm.tm_year + 1900) + m_Day + 1;
            else
                tm.tm_mday = m_Day;

            current = CDate(tm);
        }

    return results;
}

int CEventRepeatDayInMonth::MonthLength(int month, int year)
{
    switch(month)
    {
        case 1: return 31;
        case 2:
            if (year % 4 || (!(year % 100) && year % 400))
                return 28;
            else
                return 29;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: throw std::invalid_argument("Wrong month: " + toStr(month));
    }
}

std::string CEventRepeatDayInMonth::ToStr() const
{
    return toStr("month_day ") + toStr(m_Day);
}