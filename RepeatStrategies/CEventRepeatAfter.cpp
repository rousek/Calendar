//
// Created by matyas on 05/09/2018.
//

#include <cmath>
#include "CEventRepeatAfter.h"
#include "../utils/utils.h"

std::vector<CDate> CEventRepeatAfter::TestRange(const CDate &date, const CDate &from, const CDate &to) const
{
    if (date > to) // Event starts after given interval
        return {};

    auto diffSecs = std::chrono::seconds(from.Count() - date.Count());
    auto diffMins = std::chrono::duration_cast<std::chrono::minutes>(diffSecs);

    // Get offset from date of event in minutes.
    int offset = dynamic_cast<int>(std::ceil(diffMins.count() / m_After.count()) * m_After.count());

    std::vector<CDate> results;

    time_t timestamp = date.Count() + offset * 60;
    CDate tmpDate = CDate(timestamp);
    long long interval = m_After.count() * 60;

    while (tmpDate <= to)
    {
        results.push_back(tmpDate);

        timestamp += interval;
        tmpDate = CDate(timestamp);
    }

    return results;
}

std::string CEventRepeatAfter::ToStr() const
{
    return toStr("after ") + CDate::GetFormattedDuration(m_After.count());
}