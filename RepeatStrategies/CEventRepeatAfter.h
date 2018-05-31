//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATAFTER_H
#define SEM_CEVENTREPEATAFTER_H

#include "CEventRepeatBase.h"

class CEventRepeatAfter : public CEventRepeatBase {
public:
    explicit CEventRepeatAfter(const std::chrono::minutes & mins) : m_After(mins)
    {
    }
    ~CEventRepeatAfter() override = default;
    std::vector<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const override;
    std::string ToStr() const override;
private:
    std::chrono::minutes m_After;
};


#endif //SEM_CEVENTREPEATAFTER_H
