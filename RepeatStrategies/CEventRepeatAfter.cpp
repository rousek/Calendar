//
// Created by matyas on 05/09/2018.
//

#include <cmath>
#include <sstream>
#include "CEventRepeatAfter.h"
#include "../utils/utils.h"

std::set<CDate> CEventRepeatAfter::TestRange(const CDate &date, const CDate::Interval & interval) const
{
    CDate from = MAX(interval.first, date);
    CDate to = interval.second;
    
    if (date > to) // Event starts after given interval
        return {};

    long long timeToStart = from.Count() - date.Count();
    long long intervalSecs = m_Interval.GetSize();
    // Get offset from date of event in seconds.
    long long offset = static_cast<int>(std::ceil(timeToStart / intervalSecs)) * intervalSecs;
    std::set<CDate> results;

    time_t timestamp = date.Count() + offset;
    CDate tmpDate = CDate(timestamp);

    while (tmpDate <= to)
    {

        if (tmpDate >= from)
            results.insert(tmpDate);

        timestamp += intervalSecs;
        tmpDate = CDate(timestamp);
    }

    return results;
}

std::string CEventRepeatAfter::ToStr() const
{
    return toStr("after ") + toStr(m_Interval);
}