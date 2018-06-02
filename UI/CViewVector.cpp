//
// Created by matyas on 06/02/2018.
//

#include "CViewVector.h"
#include "../utils/utils.h"

const int CViewVector::RESULTS_ON_SCREEN = 3;

void CViewVector::Update()
{
    const int maxIndex = MIN(m_PageIndex + RESULTS_ON_SCREEN - 1, m_Events.size() - 1);

    for (int i = m_PageIndex; i <= maxIndex; i++)
    {
        CEvent * event = m_Events[i];

        std::cout << "***************************" << std::endl;
        std::cout << i + 1 << ")" << std::endl;
        std::cout << event;
    }

    std::cout << "***************************" << std::endl;
    std::cout << "Showing " << m_PageIndex + 1 << " - " << maxIndex + 1 << std::endl;
    std::cout << "Total " << m_Events.size() << std::endl;
}

void CViewVector::Previous()
{
    const int minIndex = 0;

    if (m_PageIndex == minIndex)
        std::invalid_argument("Cannot go back any further!");

    m_PageIndex = MAX(m_PageIndex - RESULTS_ON_SCREEN, 0);
}

void CViewVector::Next()
{
    const int maxIndex = static_cast<int>((std::ceil(m_Events.size() / RESULTS_ON_SCREEN) - 1) * RESULTS_ON_SCREEN);

    if (m_PageIndex == maxIndex)
        std::invalid_argument("Cannot go forward any further!");

    m_PageIndex = MIN(m_PageIndex + 10, maxIndex);
}

CEvent * CViewVector::Find(int ID) const
{
    int i = ID - 1;

    if (i < m_Events.size())
        return m_Events[i];

    throw std::invalid_argument("Invalid ID!");
}