//
// Created by matyas on 05/03/2018.
//

#include <vector>
#include "CCalendar.h"

CCalendar::~CCalendar()
{
    for (CEvent * ev: m_Events)
        delete ev;
}

void CCalendar::AddEvent(CEvent * ev)
{
    m_Events.push_back(ev);
    m_Suggestions.Insert(ev);
}

void CCalendar::RemoveEvent(CEvent * ev)
{
    for (auto it = m_Events.begin(); it != m_Events.end(); it++)
        if (*it == ev)
        {
            m_Events.erase(it);
            break;
        }

    m_Suggestions.Remove(ev);

    delete ev;
}

std::vector<CEvent *> CCalendar::Search(const std::string & name) const
{
    return m_Suggestions.Suggest(name);
}

