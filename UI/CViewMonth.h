//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWMONTH_H
#define SEM_CVIEWMONTH_H


#include "CViewTime.h"

class CViewMonth : public CViewTime
{
public:
    using CViewTime::CViewTime;
    ~CViewMonth() override = default;
    CEvent * Find(int ID) const override;
    void Update() override;
    void Previous() override;
    void Next() override;
};


#endif //SEM_CVIEWMONTH_H
