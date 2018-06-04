//
// Created by matyas on 05/03/2018.
//

#include <vector>
#include "CCalendar.h"
#include "../utils/utils.h"

const int CCalendar::WAKE_UP_HOUR = 6;
const int CCalendar::SLEEPING_HOUR = 20;

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


void CCalendar::DeleteEvent(CEvent * ev)
{
    auto it = m_Events.find(ev);

    m_Events.erase(it);
    m_Suggestions.Remove(ev);
}

void CCalendar::DeleteEvent(const CEvent::Instance & instance)
{
    CEvent * event = instance.GetEvent();
    if (instance.IsInstance())
    {
        CDate date = instance.GetTime().first;
        bool allDeleted = event->DeleteInstance(date);

        if (!allDeleted)
        {
            std::stringstream ss;
            ss << "This event repeats itself " << event->GetRepeat() << ". "
               << "Do you want to delete all instances?";

            allDeleted = requestConfirm(ss.str());
        }

        if (allDeleted)
        {
            DeleteEvent(event);
            delete event;
        }
    }
    else
    {
        DeleteEvent(event);
        delete event;
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
}
