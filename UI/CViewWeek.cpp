//
// Created by matyas on 06/01/2018.
//

#include <iomanip>
#include "CViewWeek.h"

void CViewWeek::Update()
{
    m_List.clear();

    CDate start(m_Date);
    start.SetHour(0).SetMinute(0);

    int total = 0;

    // Get to beginning of week (Monday is 1)
    while (start.GetWeekDay() != 1)
        start -= CDuration::Days(1);

    int weekday = 1;
    // Go from Monday to another Monday
    do
    {
        CDate end(start);
        end.SetHour(23).SetMinute(59);

        std::stringstream title;

        std::cout << "*************** -" << CDate::WeekdayStringShort(weekday) << " " << start.ShortDateToStr() << "- ***************" << std::endl;

        CDate::Interval interval = std::make_pair(start, end);

        for (auto pair : m_Calendar.FindInInterval(interval))
        {
            CDate timeStart = pair.first.first;
            CDate timeEnd = pair.first.second;
            CEvent * event = pair.second;

            total++;

            m_List.insert(std::make_pair(total, event));

            std::cout << total << ") "
                      << "[" << timeStart.TimeToStr()
                      << " - " << timeEnd.TimeToStr()
                      << "]: " << event->GetTitle() << std::endl;

        }

        weekday++;
        weekday %= 7;
        start += CDuration::Days(1);
    }
    while (weekday != 1);

    std::cout << "Total " << total << std::endl;
}

CEvent* CViewWeek::Find(int ID) const
{
    auto it = m_List.find(ID);
    if (it == m_List.end())
        throw std::invalid_argument("Invalid ID!");

    return (*it).second;
}

void CViewWeek::Previous()
{
    m_Date -= CDuration::Weeks(1);
}

void CViewWeek::Next()
{
    m_Date += CDuration::Weeks(1);
}