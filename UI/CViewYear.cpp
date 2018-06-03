//
// Created by matyas on 06/01/2018.
//

#include "CViewYear.h"


void CViewYear::Update()
{
    int year = m_Date.GetYear();
    int total = 0;

    std::cout << std::endl;
    std::cout << "*************** -" << year << "- ***************" << std::endl;

    for (int month = 1; month <= 12; month++)
    {
        int count = 0;

        auto interval = std::make_pair(CDate::StartOfMonth(month, year), CDate::EndOfMonth(month, year));
        count = m_Calendar.FindInInterval(interval).size();
        total += count;

        std::cout << month << ") " << CDate::MonthStringShort(month) << " - " << count << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Total " << total << std::endl;
}

CEvent::Instance CViewYear::Find(int ID) const
{
    throw std::invalid_argument("This view mode does not support this feature!");
}

void CViewYear::Previous()
{
    m_Date -= CDuration::Years(1);
}

void CViewYear::Next()
{
    m_Date += CDuration::Years(1);
}