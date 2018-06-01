//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATAFTER_H
#define SEM_CEVENTREPEATAFTER_H

#include "CEventRepeatBase.h"

class CEventRepeatAfter : public CEventRepeatBase {
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const override;
public:
    explicit CEventRepeatAfter(const CDuration & duration) : m_Interval(duration)
    {
    }
    CEventRepeatBase * Clone() const override { return new CEventRepeatAfter(*this); }
    ~CEventRepeatAfter() override = default;
    std::string ToStr() const override;
private:
    CDuration m_Interval;
};


#endif //SEM_CEVENTREPEATAFTER_H
