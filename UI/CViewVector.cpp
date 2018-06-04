//
// Created by matyas on 06/02/2018.
//

#include "CViewVector.h"
#include "../utils/utils.h"

const int CViewVector::RESULTS_ON_SCREEN = 5;

CViewVector::CViewVector(const std::vector<CEvent *> & events) :
        m_PageIndex(0),
        m_MaxIndex(static_cast<int>(std::ceil(events.size() / RESULTS_ON_SCREEN)) * RESULTS_ON_SCREEN)
{
    for (auto ev : events)
        m_Events.push_back(CEvent::Instance(ev));
}

void CViewVector::Update()
{
    int nextMilestone = m_PageIndex + RESULTS_ON_SCREEN;
    int maxIndexInArray = static_cast<int>(m_Events.size() - 1);
    const int maxShownIndex = MIN(nextMilestone, maxIndexInArray);

    std::cout << std::endl;

    for (int i = m_PageIndex; i <= maxShownIndex; i++)
    {
        CEvent * event = m_Events[i].GetEvent();

        std::cout << "***************************" << std::endl;
        std::cout << i + 1 << ")" << std::endl;
        std::cout << event;
    }

    std::cout << std::endl;
    std::cout << "Showing " << m_PageIndex + 1 << " - " << maxShownIndex + 1 << std::endl;
    std::cout << "Total " << m_Events.size() << std::endl;
}

void CViewVector::Previous()
{
    if (m_PageIndex == 0)
        throw std::invalid_argument("Cannot go back any further!");

    int newIndex = m_PageIndex - RESULTS_ON_SCREEN;
    m_PageIndex = MAX(newIndex, 0);
}

void CViewVector::Next()
{
    if (m_PageIndex == m_MaxIndex)
        throw std::invalid_argument("Cannot go forward any further!");

    int newIndex = m_PageIndex + RESULTS_ON_SCREEN;
    m_PageIndex = MIN(newIndex, m_MaxIndex);
}

CEvent::Instance CViewVector::Find(int ID) const
{
    size_t i = static_cast<size_t>(ID - 1);

    if (i < m_Events.size())
        return m_Events[i];

    throw std::invalid_argument("Invalid ID!");
}