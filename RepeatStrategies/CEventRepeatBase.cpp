//
// Created by matyas on 05/31/2018.
//

#include <algorithm>
#include "CEventRepeatBase.h"

void CEventRepeatBase::Transfer(const CDate &from, const CDate &to)
{
    auto it = m_Additional.find(from);
    if (it != m_Additional.end())
        m_Additional.erase(it);

    m_Skipped.insert(from);
    m_Additional.insert(to);
}

std::set<CDate> CEventRepeatBase::TestRangeWithExceptions(const CDate::Interval & timeOfEvent,
                                                          const CDate::Interval & interval)
{
    auto eventDuration = timeOfEvent.second - timeOfEvent.first;
    CDate::Interval cpy(interval);
    cpy.first = CDate(interval.first - eventDuration + CDuration::Minutes(1));
    auto results = TestRange(timeOfEvent.first, cpy);

    auto itSkippedEnd = m_Skipped.upper_bound(cpy.second);
    auto itAddedEnd = m_Additional.upper_bound(cpy.second);

    for (auto itSkipped = m_Skipped.lower_bound(cpy.first); itSkipped != itSkippedEnd; itSkipped++)
    {
        auto it = results.find(*itSkipped);

        if (it != results.end())
            results.erase(it);
    }

    for (auto itAdded = m_Additional.lower_bound(cpy.first); itAdded != itAddedEnd; itAdded++)
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