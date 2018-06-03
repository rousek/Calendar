//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATNONE_H
#define SEM_CEVENTREPEATNONE_H


#include "CEventRepeatBase.h"

/**
 * Event has only one instance.
 */
class CEventRepeatDisabled : public CEventRepeatBase
{
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const override;
public:
    ~CEventRepeatDisabled() override = default;
    int InstancesLeft() const override { return 1 - m_Skipped.size() + m_Additional.size(); }
    bool Delete(const CDate & date) override;
    CEventRepeatBase * Clone() const override { return new CEventRepeatDisabled(*this); }
    std::string ToStr() const override;
};


#endif //SEM_CEVENTREPEATNONE_H
