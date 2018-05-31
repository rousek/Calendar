//
// Created by matyas on 05/31/2018.
//

#include <algorithm>
#include "CEventRepeatBase.h"

std::set<CDate> CEventRepeatBase::TestRangeWithExceptions(const CDate & date, const CDate & from, const CDate & to)
{
    auto results = TestRange(date, from, to);

    auto itSkippedEnd = m_Skipped.upper_bound(to);
    auto itAddedEnd = m_Additional.upper_bound(to);

    for (auto itSkipped = m_Skipped.lower_bound(from); itSkipped != itSkippedEnd; itSkipped++)
    {
        auto it = results.find(*itSkipped);

        if (it != results.end())
            results.erase(it);
    }

    for (auto itAdded = m_Additional.lower_bound(from); itAdded != itAddedEnd; itAdded++)
    {
        results.insert(*itAdded);
    }

    return results;
}

std::set<CDate::Interval> CEventRepeatBase::MakeIntervals(const std::set<CDate> & beginnings,
                                                          const std::chrono::minutes & duration)
{
    std::set<CDate::Interval> intervals;
    time_t seconds = static_cast<time_t>(std::chrono::duration_cast<std::chrono::seconds>(duration).count());

    for (const CDate & beginning : beginnings)
    {
        CDate end = CDate(beginning.Count() + seconds);
        intervals.insert(std::make_pair(beginning, end));
    }

    return intervals;
}