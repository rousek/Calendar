//
// Created by matyas on 06/03/2018.
//

#ifndef SEM_CVIEWDAY_H
#define SEM_CVIEWDAY_H


#include "CViewTime.h"

class CViewDay : public CViewTime
{
public:
    using CViewTime::CViewTime;
    ~CViewDay() override = default;
    CEvent::Instance Find(int ID) const override;
    void Update() override;
    void Previous() override;
    void Next() override;
};


#endif //SEM_CVIEWDAY_H
