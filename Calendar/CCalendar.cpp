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

    if (requestConfirm("Do you want to save changes?"))
        std::cout << "Changes saved!" << std::endl;
    else
        std::cout << "Changes not saved." << std::endl;
}

void CCalendar::DeleteEvent(CEvent * ev)
{
    auto it = m_Events.find(ev);

    m_Events.erase(it);
    m_Suggestions.Remove(ev);
    delete ev;
}

void CCalendar::DeleteEvent(CEvent *event, const CDate &date)
{
    bool allDeleted = event->DeleteInstance(date);

    if (!allDeleted)
    {
        std::stringstream ss;
        ss << "This event repeats itself: " << event->GetRepeat() << "." << std::endl
           << "Do you want to delete all instances?" << std::endl;

        allDeleted = requestConfirm(ss.str());
    }

    if (allDeleted)
        DeleteEvent(event);
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

std::map<CDate::Interval, CEvent *> CCalendar::FindInInterval(const CDate::Interval & interval) const
{
    std::map<CDate::Interval, CEvent *> results;

    for (auto ev : m_Events)
    {
        for (auto instance : ev->FindInInterval(interval))
            results.insert(make_pair(instance, ev));
    }

    return results;
};

