//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWYEAR_H
#define SEM_CVIEWYEAR_H


#include "CViewTime.h"

class CViewYear : public CViewTime
{
public:
    using CViewTime::CViewTime;
    ~CViewYear() override = default;
    CEvent * Find(int ID) const override;
    void Update() override;
    void Previous() override;
    void Next() override;
};


#endif //SEM_CVIEWYEAR_H
