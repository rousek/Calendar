//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATBASE_H
#define SEM_CEVENTREPEATBASE_H


#include <vector>
#include "../Date/CDate.h"

class CEventRepeatBase
{
public:
    virtual ~CEventRepeatBase() = default;
    virtual std::vector<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const = 0;
};


#endif //SEM_CEVENTREPEATBASE_H
