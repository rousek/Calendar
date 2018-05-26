//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTTRANSFERDISABLED_H
#define SEM_CEVENTTRANSFERDISABLED_H

#include "CEventTransferBase.h"

class CEventTransferDisabled : public CEventTransferBase {
public:
    ~CEventTransferDisabled() override {}
    bool TransferPossible(const CDate & from, const CDate & to) const override;
};


#endif //SEM_CEVENTTRANSFERDISABLED_H
