//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWWEEK_H
#define SEM_CVIEWWEEK_H


#include "CViewTime.h"

class CViewWeek : public CViewTime
{
public:
    using CViewTime::CViewTime;
    ~CViewWeek() override = default;
    CEvent * Find(int ID) const override;
    void Update() override;
    void Previous() override;
    void Next() override;
};


#endif //SEM_CVIEWWEEK_H
