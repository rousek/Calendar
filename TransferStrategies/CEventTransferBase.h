//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTTRANSFERBASE_H
#define SEM_CEVENTTRANSFERBASE_H


#include "../Date/CDate.h"

class CEventTransferBase
{
public:
    virtual ~CEventTransferBase() = default;
    virtual bool TransferPossible(const CDate & from, const CDate & to) const = 0;
};


#endif //SEM_CEVENTTRANSFERBASE_H
