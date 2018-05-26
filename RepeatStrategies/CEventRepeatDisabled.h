//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATNONE_H
#define SEM_CEVENTREPEATNONE_H


#include "CEventRepeatBase.h"

class CEventRepeatDisabled : public CEventRepeatBase
{
public:
    virtual ~CEventRepeatDisabled() override {}
    virtual std::vector<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const override;
};


#endif //SEM_CEVENTREPEATNONE_H
