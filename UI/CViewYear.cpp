//
// Created by matyas on 06/01/2018.
//

#include "CViewYear.h"


void CViewYear::Draw(const CCalendar &calendar, const CDate &date) const
{
    int year = date.GetYear();
    int total = 0;

    std::cout << "*************** -" << year << "- ***************" << std::endl;

    for (int month = 1; month <= 12; month++)
    {
        int count = 0;

        auto interval = std::make_pair(CDate::StartOfMonth(month, year), CDate::EndOfMonth(month, year));
        count = calendar.FindInInterval(interval).size();
        total += count;

        std::cout << month << ") " << CDate::MonthStringShort(month) << " - " << count << " events" << std::endl;
    }
    std::cout << "Total " << total << std::endl;
}

CDate CViewYear::Next(const CDate &date) const
{
    return date + CDuration::Years(1);
}

CDate CViewYear::Previous(const CDate &date) const
{
    return date - CDuration::Years(1);
}
