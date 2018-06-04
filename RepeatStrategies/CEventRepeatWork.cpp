//
// Created by matyas on 06/04/2018.
//

#include "CEventRepeatWork.h"

//
// Created by matyas on 05/09/2018.
//

#include <sstream>
#include "CEventRepeatWork.h"
#include "../utils/utils.h"

std::set<CDate> CEventRepeatWork::TestRange(const CDate &date, const CDate::Interval & interval) const
{
    std::set<CDate> results;

    if (date > interval.second)
        return {};

    CDate from = MAX(date, interval.first);
    CDate current(from);

    current -= CDuration::Days(1);
    current.SetHour(date.GetHour()).SetMinute(date.GetMinute()).SetSecond(0);

    while(current <= interval.second)
    {
        int weekday = current.GetWeekDay();

        if (current >= from && CDate::IsWorkDay(weekday))
            results.insert(current);

        current += CDuration::Days(1);
    }

    return results;
}

bool CEventRepeatWork::Delete(const CDate &date)
{
    m_Skipped.insert(date);
    return false;
}

std::string CEventRepeatWork::ToStr() const
{
    return "work_days";
}