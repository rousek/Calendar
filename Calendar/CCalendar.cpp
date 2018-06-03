//
// Created by matyas on 05/03/2018.
//

#include <vector>
#include "CCalendar.h"
#include "../utils/utils.h"

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

