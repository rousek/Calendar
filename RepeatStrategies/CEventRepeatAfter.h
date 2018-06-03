//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATAFTER_H
#define SEM_CEVENTREPEATAFTER_H

#include "CEventRepeatBase.h"

/**
 * Repeats event after given time period.
 */
class CEventRepeatAfter : public CEventRepeatBase {
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const override;
public:
    explicit CEventRepeatAfter(const CDuration & duration) : m_Interval(duration) {}
    int InstancesLeft() const override { return std::numeric_limits<int>::max(); }
    bool Delete(const CDate & date) override;
    CEventRepeatBase * Clone() const override { return new CEventRepeatAfter(*this); }
    ~CEventRepeatAfter() override = default;
    std::string ToStr() const override;
private:
    CDuration m_Interval;
};


#endif //SEM_CEVENTREPEATAFTER_H
