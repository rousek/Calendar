//
// Created by matyas on 05/03/2018.
//

#include <vector>
#include "CCalendar.h"
#include "../utils/utils.h"

CCalendar::CCalendar()
{
    m_EventCounter = 0;
}

CCalendar::~CCalendar()
{
    for (auto pair: m_Events)
        delete pair.second;
}

void CCalendar::AddEvent(CEvent * ev)
{
    int ID = ev->GetID();

    if (ID >= m_EventCounter)
        m_EventCounter = ID + 1;
    else
        ev->SetID(m_EventCounter++);

    m_Events.insert(std::make_pair(ID, ev));
    m_Suggestions.Insert(ev);
}

void CCalendar::CreateEvent()
{
    CEvent * ev = CEvent::InteractiveCreator(m_EventCounter);
    AddEvent(ev);
}

std::map<int, CEvent *>::const_iterator CCalendar::FindEvent(int ID) const
{
    auto it = m_Events.find(ID);

    if (it == m_Events.end())
        throw std::invalid_argument("Event with ID " + toStr(ID) + " does not exist!");

    return it;
}

void CCalendar::EditEvent(const std::map<int, CEvent *>::const_iterator & it)
{
    CEvent * ev = (*it).second;

    if (ev->InteractiveEditor())
        std::cout << "Event has been saved successfully!" << std::endl;
    else
        std::cout << "Event has not been saved." << std::endl;
}

void CCalendar::RemoveEvent(const std::map<int, CEvent *>::const_iterator & it)
{
    CEvent * ev = (*it).second;

    m_Events.erase(it);
    m_Suggestions.Remove(ev);
    delete ev;
}

void CCalendar::Clear()
{
    for (auto pair : m_Events)
    {
        delete pair.second;
    }

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

    for (auto pair : m_Events)
    {
        CEvent * ev = pair.second;

        for (auto instance : ev->FindInInterval(interval))
            results.insert(make_pair(instance, ev));
    }

    return results;
};

