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

    std::cout << std::endl;

    int weekday = 1;
    // Go from Monday to another Monday
    do
    {
        CDate end(start);
        end.SetHour(23).SetMinute(59);

        std::stringstream title;

        std::cout << "*************** -"
                  << CDate::WeekdayStringShort(weekday)
                  << ", " << start.ShortDateToStr()
                  << "- ***************" << std::endl;

        CDate::Interval interval = std::make_pair(start, end);
        std::vector<CEvent::Instance> instances;

        for (auto instance : m_Calendar.FindInInterval(interval))
            instances.push_back(instance);

        std::sort(instances.begin(), instances.end());

        for (auto & instance : instances)
        {
            CDate::Interval time = instance.GetTime();
            CEvent * event = instance.GetEvent();

            total++;

            m_List.insert(std::make_pair(total, instance));

            std::cout << total << ") "
                      << "[" << time.first.TimeToStr()
                      << " - " << time.second.TimeToStr()
                      << "]: " << event->GetTitle() << std::endl;
        }
        std::cout << std::endl;

        weekday++;
        weekday %= 7;
        start += CDuration::Days(1);
    }
    while (weekday != 1);

    std::cout << "Total " << total << std::endl;
}

CEvent::Instance CViewWeek::Find(int ID) const
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