//
// Created by matyas on 06/01/2018.
//

#include <iomanip>
#include "CViewMonth.h"


void CViewMonth::Update()
{
    int month = m_Date.GetMonth();
    int year = m_Date.GetYear();

    // 01. XX. XXXX 00:00
    CDate start = CDate::StartOfMonth(month, year);
    CDate end = start + CDuration::Days(1);
    CDate endOfMonth = CDate::EndOfMonth(month, year);
    int total = 0;

    std::cout << "*************** -" << CDate::MonthStringLong(month) << " " << year << "- ***************" << std::endl;

    while (start < endOfMonth)
    {
        int count = m_Calendar.FindInInterval(std::make_pair(start, end)).size();
        int day = start.GetDay();
        int weekday = start.GetWeekDay();

        std::cout << std::setw(2) << day << ") " << CDate::WeekdayStringShort(weekday) << " - " << count << std::endl;

        start = end;
        end += CDuration::Days(1);
        total += count;
    }

    std::cout << "Total " << total << std::endl;
}


CEvent::Instance CViewMonth::Find(int ID) const
{
    throw std::invalid_argument("This view mode does not support this feature!");
}

void CViewMonth::Previous()
{
    m_Date -= CDuration::Months(1);
}

void CViewMonth::Next()
{
    m_Date += CDuration::Months(1);
}