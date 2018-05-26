//
// Created by matyas on 05/02/2018.
//

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "CEvent.h"
#include "../utils/utils.h"


CEvent::CEvent(const std::string & title, const std::string & place, const std::string & summary,
                       const CDate & start, const CDate & end, CEventTransferBase * tr, CEventRepeatBase * rp) :
        m_Title(title), m_Place(place), m_Summary(summary), m_Start(start), m_End(end), m_Transfer(tr), m_Repeat(rp)
{
    if (end <= start)
        throw std::invalid_argument("Event must end after it starts!");
}

std::chrono::minutes CEvent::GetDuration() const
{
    double diff = difftime(m_End.Count(), m_Start.Count());
    auto secs = std::chrono::seconds((int)diff);

    return std::chrono::duration_cast<std::chrono::minutes>(secs);
}

CEvent * CEvent::InteractiveCreator()
{
    CDate dateStart, dateEnd, timeStart, timeEnd;
    std::string title, place, summary;

    std::cout << "Date:" << std::endl;
    dateStart = CDate::RequestDateFromUser(CDate::ReadDate, true);

    std::cout << "End date (press enter if date is same):" << std::endl;
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
            std::cout << "Event must end after it starts!";
    }

    std::cout << "Title:" << std::endl;
    getline(std::cin, title);
    std::cout << std::cin.gcount() << std::endl;

    std::cout << "Summary: " << std::endl;
    getline(std::cin, summary);

    std::cout << "Place:" << std::endl;
    getline(std::cin, place);


    return new CEvent
            (
                    title,
                    place,
                    summary,
                    CDate::CombineDateTime(dateStart, timeStart),
                    CDate::CombineDateTime(dateEnd, timeEnd),
                    NULL,
                    NULL
            );
}

std::ostream & operator<<(std::ostream & s, const CEvent & ev)
{
    s << "Title: " << ev.getTitle() << std::endl;
    s << "Place: " << ev.getPlace() << std::endl;
    s << "Summary: " << ev.getSummary() << std::endl;
    s << "Starts on: " << ev.m_Start << std::endl;
    s << "Ends on: " << ev.m_End << std::endl;
    s << "Duration: ";
    ev.PrintDuration(s);

    s << std::endl;

    return s;
}

std::ostream & CEvent::PrintDuration(std::ostream & s) const
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

std::ostream & operator<<(std::ostream & s, const CEvent * ev)
{
    if (ev == NULL)
        return s << "null";
    else
        return s << *ev;
}

std::vector<std::string> CEvent::GetSearchable::operator()(CEvent * const & ev) const
{
    return {ev->getPlace(), ev->getTitle()};
}
