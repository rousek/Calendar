//
// Created by matyas on 06/02/2018.
//

#ifndef SEM_CVIEWVECTOR_H
#define SEM_CVIEWVECTOR_H


#include "../Event/CEvent.h"
#include "CViewBase.h"

/**
 * CView printing events and allowing pagination.
 */
class CViewVector : public CViewBase<CEvent *>
{
public:
    CViewVector(const std::vector<CEvent *> & events);
    ~CViewVector() override = default;
    CEvent * Find(int ID) const override;
    void Update() override;
    void Previous() override;
    void Next() override;

    static const int RESULTS_ON_SCREEN;
private:
    int m_PageIndex;
    const int m_MaxIndex;
    std::vector<CEvent *> m_Events;
};


#endif //SEM_CVIEWVECTOR_H
