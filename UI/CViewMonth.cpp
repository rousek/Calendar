//
// Created by matyas on 06/01/2018.
//

#include "CViewMonth.h"


void CViewMonth::Draw(const CCalendar &calendar, const CDate &date) const
{
    int month = date.GetMonth();
    int year = date.GetYear();

    // 01. XX. XXXX 00:00
    CDate start = CDate::StartOfMonth(month, year);
    CDate end = start + CDuration::Days(1);
    CDate endOfMonth = CDate::EndOfMonth(month, year);
    int total = 0;

    std::cout << "*************** -" << CDate::MonthStringLong(month) << " " << year << "- ***************" << std::endl;

    while (start < endOfMonth)
    {
        int count = calendar.FindInInterval(std::make_pair(start, end)).size();

        start = end;
        end += CDuration::Days(1);
    }
}

CDate CViewMonth::Next(const CDate &date) const
{
    return date + CDuration::Months(1);
}

CDate CViewMonth::Previous(const CDate &date) const
{
    return date - CDuration::Months(1);
}