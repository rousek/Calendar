//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATBASE_H
#define SEM_CEVENTREPEATBASE_H


#include <set>
#include "../Date/CDate.h"

class CEventRepeatBase
{
protected:
    virtual std::set<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const = 0;
public:
    std::set<CDate> m_Additional;
    std::set<CDate> m_Skipped;
    virtual ~CEventRepeatBase() = default;
    virtual std::string ToStr() const = 0;
    virtual CEventRepeatBase * Clone() const = 0;

    virtual std::set<CDate> TestRangeWithExceptions(const CDate & date, const CDate & from, const CDate & to);
    static std::set<std::pair<CDate, CDate>> MakeIntervals(const std::set<CDate> & beginnings, const std::chrono::minutes & duration);
};


#endif //SEM_CEVENTREPEATBASE_H
