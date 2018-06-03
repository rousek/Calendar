//
// Created by matyas on 05/02/2018.
//

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "CEvent.h"
#include "../utils/utils.h"

const int CEvent::MIN_PRIORITY = 1;
const int CEvent::MAX_PRIORITY = 10;

CEvent::CEvent(
               const std::string & title,
               const std::string & place,
               const std::string & summary,
               const CDate & start,
               const CDate & end,
               int priority,
               CEventRepeatBase * rp) :
                m_Title(title),
                m_Place(place),
                m_Summary(summary),
                m_Start(start),
                m_End(end),
                m_Priority(priority),
                m_Repeat(rp)
{
    if (end <= start)
        throw std::invalid_argument("Event must end after it starts!");
}

CEvent::CEvent(const CEvent *ev) :
m_Title(ev->m_Title),
m_Place(ev->m_Place),
m_Summary(ev->m_Summary),
m_Start(ev->m_Start),
m_End(ev->m_End),
m_Priority(ev->m_Priority),
m_Repeat(ev->m_Repeat->Clone())
{
}

CEvent::~CEvent()
{
    delete m_Repeat;
}

CDuration CEvent::GetDuration() const
{
    double diff = difftime(m_End.Count(), m_Start.Count());
    return CDuration::Seconds(static_cast<int>(diff));
}

std::vector<CEvent::Instance> CEvent::FindInInterval(const CDate::Interval & interval) const
{
    std::vector<CEvent::Instance> result;
    auto beginnings = m_Repeat->TestRangeWithExceptions(m_Start, interval);

    for (auto & beginning : beginnings)
        result.push_back(Instance(const_cast<CEvent *>(this), beginning));

    return result;
}

bool CEvent::DeleteInstance(const CDate &date)
{
    return m_Repeat->Delete(date);
}

std::ostream & operator<<(std::ostream & s, const CEvent & ev)
{
    s << "Title: " << ev.GetTitle() << std::endl;
    s << "Place: " << ev.GetPlace() << std::endl;
    s << "Summary: " << ev.GetSummary() << std::endl;
    s << "Starts on: " << ev.m_Start << std::endl;
    s << "Ends on: " << ev.m_End << std::endl;
    s << "Duration: " << ev.GetDuration() << std::endl;
    s << "Priority: " << ev.m_Priority << std::endl;
    s << "Repetition: " << ev.m_Repeat->ToStr() << std::endl;

    return s;
}


std::ostream & operator<<(std::ostream & s, const CEvent * ev)
{
    if (ev == nullptr)
        return s << "null";
    else
        return s << *ev;
}

std::vector<std::string> CEvent::GetSearchable::operator()(CEvent * const & ev) const
{
    return {ev->GetPlace(), ev->GetTitle()};
}
