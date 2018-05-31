//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATAFTER_H
#define SEM_CEVENTREPEATAFTER_H

#include "CEventRepeatBase.h"

class CEventRepeatAfter : public CEventRepeatBase {
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const override;
public:
    explicit CEventRepeatAfter(const std::chrono::minutes & mins) : m_After(mins)
    {
    }
    CEventRepeatBase * Clone() const override { return new CEventRepeatAfter(*this); }
    ~CEventRepeatAfter() override = default;
    std::string ToStr() const override;
private:
    std::chrono::minutes m_After;
};


#endif //SEM_CEVENTREPEATAFTER_H
