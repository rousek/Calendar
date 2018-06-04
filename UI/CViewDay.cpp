//
// Created by matyas on 06/03/2018.
//

#include "CViewDay.h"

void CViewDay::Update()
{
    m_List.clear();


    std::cout << std::endl;

    CDate start(m_Date), end(m_Date);
    start.SetHour(0).SetMinute(0);
    end.SetHour(23).SetMinute(59);

    std::cout << "***************"
              << CDate::WeekdayStringLong(start.GetWeekDay())
              << ", " << start.ShortDateToStr()
              << "***************" << std::endl;

    CDate::Interval interval = std::make_pair(start, end);

    int total = 0;

    std::vector<CEvent::Instance> instances;

    for (auto & instance : m_Calendar.FindInInterval(interval))
        instances.push_back(instance);

    std::sort(instances.begin(), instances.end());

    for (auto & instance : instances)
    {
        total++;

        m_List.insert(std::make_pair(total, instance));

        std::cout << total << ")" << std::endl << instance << std::endl;

    }
    if (total == 0)
    {
        std::cout << "You do not have anything planned for this day!" << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Total " << total << std::endl;
    }
}

CEvent::Instance CViewDay::Find(int ID) const
{
    auto it = m_List.find(ID);
    if (it == m_List.end())
        throw std::invalid_argument("Invalid ID!");

    return (*it).second;
}

void CViewDay::Previous()
{
    m_Date -= CDuration::Days(1);
}

void CViewDay::Next()
{
    m_Date += CDuration::Days(1);
}