//
// Created by matyas on 05/31/2018.
//

#include <algorithm>
#include "CEventRepeatBase.h"

std::set<CDate> CEventRepeatBase::TestRangeWithExceptions(const CDate & date, const CDate::Interval & interval)
{
    auto results = TestRange(date, interval);

    auto itSkippedEnd = m_Skipped.upper_bound(interval.second);
    auto itAddedEnd = m_Additional.upper_bound(interval.second);

    for (auto itSkipped = m_Skipped.lower_bound(interval.first); itSkipped != itSkippedEnd; itSkipped++)
    {
        auto it = results.find(*itSkipped);

        if (it != results.end())
            results.erase(it);
    }

    for (auto itAdded = m_Additional.lower_bound(interval.first); itAdded != itAddedEnd; itAdded++)
    {
        results.insert(*itAdded);
    }

    return results;
}

std::set<CDate::Interval> CEventRepeatBase::MakeIntervals(const std::set<CDate> & beginnings,
                                                          const CDuration & duration)
{
    std::set<CDate::Interval> intervals;
    long long int size = duration.GetSize();

    for (const CDate & beginning : beginnings)
    {
        CDate end = CDate(beginning.Count() + static_cast<time_t>(size));
        intervals.insert(std::make_pair(beginning, end));
    }

    return intervals;
}