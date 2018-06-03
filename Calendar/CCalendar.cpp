//
// Created by matyas on 05/03/2018.
//

#include <vector>
#include "CCalendar.h"
#include "../utils/utils.h"
#include "../RepeatStrategies/CEventRepeatUtils.h"

CCalendar::~CCalendar()
{
    for (auto ev: m_Events)
        delete ev;
}

void CCalendar::AddEvent(CEvent * ev)
{
    m_Events.insert(ev);
    m_Suggestions.Insert(ev);
}

void CCalendar::CreateEvent()
{
    CDate dateStart, dateEnd, timeStart, timeEnd;
    std::string title, place, summary;
    int priority;
    CEventRepeatBase * repeat;

    std::cout << "Date:" << std::endl;

    dateStart = CDate::RequestDateFromUser(CDate::ReadDate, true);

    std::cout << "End date (optional):" << std::endl;
    try
    {
        dateEnd = CDate::RequestDateFromUser(CDate::ReadDate, false);
    }
    catch (const EmptyLineException & e)
    {
        dateEnd = dateStart;
    }

    std::cout << "Start time:" << std::endl;
    timeStart = CDate::RequestDateFromUser(CDate::ReadTime, true);

    std::cout << "End time:" << std::endl;
    while(true)
    {
        timeEnd = CDate::RequestDateFromUser(CDate::ReadTime, true);

        if (timeEnd > timeStart)
            break;
        else
            std::cout << "Event must end after it starts!" << std::endl;
    }

    std::cout << "Title:" << std::endl;
    getline(std::cin, title);

    std::cout << "Summary: " << std::endl;
    getline(std::cin, summary);

    std::cout << "Place:" << std::endl;
    getline(std::cin, place);

    std::cout << "Repetition: " << std::endl;
    while(true)
    {
        try
        {
            std::string line;
            getline(std::cin, line);
            repeat = RepetitionFromStr(line);
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Priority " << CEvent::MIN_PRIORITY << " - " << CEvent::MAX_PRIORITY << " (including): " << std::endl;
    priority = requestIntInInterval(CEvent::MIN_PRIORITY, CEvent::MAX_PRIORITY, true);

    CEvent * event = new CEvent
            (
                    title,
                    place,
                    summary,
                    CDate::CombineDateTime(dateStart, timeStart),
                    CDate::CombineDateTime(dateEnd, timeEnd),
                    priority,
                    repeat
            );

    AddEvent(event);
}

void CCalendar::EditEvent(CEvent * ev)
{
}

void CCalendar::EditEvent(const CEvent::Instance &instance)
{
    CEvent * event = instance.GetEvent();

    if (event->InstancesLeft() > 1)
    {
        std::stringstream ss;
        ss << "This event repeats itself " << event->GetRepeat() << "." << std::endl
           << "Do you want to edit all instances?" << std::endl
           << "If you press \"n\", this instance of " << std::endl
           << "event will be edited separately.";

        if (requestConfirm(ss.str()))
        {
            EditEvent(event);
        }
        else
        {
            CEvent * cpy = new CEvent(*event);
            event->DeleteInstance(instance.GetTime().first);
            EditEvent(cpy);
            AddEvent(cpy);
        }
    }
    else
    {
        EditEvent(event);
    }
}

void CCalendar::DeleteEvent(CEvent * ev)
{
    auto it = m_Events.find(ev);

    m_Events.erase(it);
    m_Suggestions.Remove(ev);
    delete ev;
}

void CCalendar::DeleteEvent(const CEvent::Instance & instance)
{
    if (instance.IsInstance())
    {
        CEvent * event = instance.GetEvent();
        CDate date = instance.GetTime().first;
        bool allDeleted = event->DeleteInstance(date);

        if (!allDeleted)
        {
            std::stringstream ss;
            ss << "This event repeats itself " << event->GetRepeat() << "." << std::endl
               << "Do you want to delete all instances?";

            allDeleted = requestConfirm(ss.str());
        }

        if (allDeleted)
            DeleteEvent(event);

    }
}

void CCalendar::Clear()
{
    for (auto ev : m_Events)
        delete ev;

    m_Events.clear();
    m_Suggestions.Clear();
}

std::vector<CEvent *> CCalendar::SearchEvents(const std::string & name) const
{
    return m_Suggestions.Suggest(name);
}

std::vector<CEvent::Instance> CCalendar::FindInInterval(const CDate::Interval & interval) const
{
    std::vector<CEvent::Instance> results;

    for (auto ev : m_Events)
    {
        auto instances = ev->FindInInterval(interval);
        for (auto instance : instances)
            results.push_back(instance);
    }

    return results;
};

