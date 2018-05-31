//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDisabled.h"

std::vector<CDate> CEventRepeatDisabled::TestRange(const CDate & date, const CDate & from, const CDate & to) const
{
    if (date >= from && date <= to)
        return {date};
    else
        return {};
}

std::string CEventRepeatDisabled::ToStr() const
{
    return "none";
}