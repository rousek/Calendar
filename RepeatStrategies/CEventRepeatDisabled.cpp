//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDisabled.h"

std::set<CDate> CEventRepeatDisabled::TestRange(const CDate & date, const CDate::Interval & interval) const
{
    if (date >= interval.first && date <= interval.second)
        return {date};
    else
        return {};
}

std::string CEventRepeatDisabled::ToStr() const
{
    return "none";
}