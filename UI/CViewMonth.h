//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWMONTH_H
#define SEM_CVIEWMONTH_H


#include "CViewBase.h"

class CViewMonth : public CViewBase {
public:
    ~CViewMonth() = default;
    void Draw(const CCalendar & calendar, const CDate & date) const override;
    CDate Previous(const CDate & date) const override;
    CDate Next(const CDate & date) const override;
};


#endif //SEM_CVIEWMONTH_H
