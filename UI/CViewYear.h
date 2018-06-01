//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWYEAR_H
#define SEM_CVIEWYEAR_H


#include "CViewBase.h"

class CViewYear : public CViewBase
{
public:
    ~CViewYear() = default;
    void Draw(const CCalendar & calendar, const CDate & date) const override;
    CDate Previous(const CDate & date) const override;
    CDate Next(const CDate & date) const override;
};


#endif //SEM_CVIEWYEAR_H
