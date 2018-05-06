//
// Created by matyas on 05/02/2018.
//

#include <string>
#include <vector>
#include "CDate.h"
#include "CEventBase.h"


CEventBase::CEventBase(const std::string & title, const std::string & place, const std::string & summary,
                       const CDate & start, const CDate & end) :
        m_Title(title), m_Place(place), m_Summary(summary), m_Start(start), m_End(end)
{
    if (end <= start)
        throw std::invalid_argument("Event must end after it starts!");
}

std::chrono::minutes CEventBase::GetDuration() const
{
    double diff = difftime(m_End.Count(), m_Start.Count());
    auto secs = std::chrono::seconds((int)diff);

    return std::chrono::duration_cast<std::chrono::minutes>(secs);
}

bool CEventBase::TestDay(const CDate & date) const
{

}

std::vector<CDate> CEventBase::TestRange(const CDate & from, const CDate & to) const
{

}


CEventBase * CEventBase::InteractiveCreator()
{
    CDate date, timeStart, timeEnd;
    std::string title, place, summary;

    std::cout << "Date:" << std::endl;
    date = CDate::RequestDateFromUser(CDate::ReadDate);

    std::cout << "Start time:" << std::endl;
    timeStart = CDate::RequestDateFromUser(CDate::ReadTime);

    std::cout << "End time:" << std::endl;
    while(true)
    {
        timeEnd = CDate::RequestDateFromUser(CDate::ReadTime);

        if (timeEnd > timeStart)
            break;
        else
            std::cout << "Event must end after it starts!";
    }

    std::cout << "Title:" << std::endl;
    getline(std::cin, title);
    std::cout << std::cin.gcount() << std::endl;

    std::cout << "Summary: " << std::endl;
    getline(std::cin, summary);

    std::cout << "Place:" << std::endl;
    getline(std::cin, place);


    return new CEventBase
            (
                    title,
                    place,
                    summary,
                    CDate::CombineDateTime(date, timeStart),
                    CDate::CombineDateTime(date, timeEnd)
            );
}

std::ostream & operator<<(std::ostream & s, const CEventBase & ev)
{
    s << "Title: " << ev.getTitle() << std::endl;
    s << "Place: " << ev.getPlace() << std::endl;
    s << "Summary: " << ev.getSummary() << std::endl;
    s << "Starts on: " << ev.m_Start << std::endl;
    s << "Ends on: " << ev.m_End << std::endl;
    s << "Duration: ";
    ev.PrintDuration(s);

    s << std::endl;

    if (!ev.m_People.empty())
    {
        s << "Participants:";

        for (const std::string & part: ev.m_People)
            s << " " << part;

        s << std::endl;
    }

    return s;
}

void CEventBase::PrintDuration(std::ostream & s) const
{
    auto duration = GetDuration();
    auto days = duration.count() / (60 * 24);
    auto hours = duration.count() / 60 - days * 24;
    auto mins = duration.count() % 60;

    if (days > 0)
    {
        s << days << ((days == 1) ? " day, " : " days, ");
    }

    if (hours > 0)
    {
        s << hours << ((hours == 1) ? " hour, " : " hours, ");
    }

    if (mins > 0)
    {
        s << mins << ((mins == 1) ? " minute" : " minutes");
    }
}

std::ostream & operator<<(std::ostream & s, const CEventBase * ev)
{
    if (ev == NULL)
        return s << "null";
    else
        return s << *ev;
}

std::vector<std::string> CEventBase::GetSearchable::operator()(CEventBase * const & ev) const
{
    return {ev->getPlace(), ev->getTitle()};
}
