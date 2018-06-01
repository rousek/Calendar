//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWBASE_H
#define SEM_CVIEWBASE_H


#include "../Date/CDate.h"
#include "../Calendar/CCalendar.h"

class CViewBase
{
public:
    virtual ~CViewBase() = default;
    virtual void Draw(const CCalendar & calendar, const CDate & date) const = 0;
    virtual CDate Previous(const CDate & date) const = 0;
    virtual CDate Next(const CDate & date) const = 0;
};


#endif //SEM_CVIEWBASE_H
