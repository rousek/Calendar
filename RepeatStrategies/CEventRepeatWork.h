//
// Created by matyas on 06/04/2018.
//

#ifndef SEM_CEVENTREPEATWORK_H
#define SEM_CEVENTREPEATWORK_H


#include "CEventRepeatBase.h"

class CEventRepeatWork : public CEventRepeatBase {
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const override;
public:
    ~CEventRepeatWork() override = default;
    int InstancesLeft() const override { return std::numeric_limits<int>::max(); }
    bool Delete(const CDate & date) override;
    CEventRepeatBase * Clone() const override { return new CEventRepeatWork(*this); }
    std::string ToStr() const override;
};


#endif //SEM_CEVENTREPEATWORK_H
