//
// Created by matyas on 05/02/2018.
//

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "CEvent.h"
#include "../utils/utils.h"

CEvent::CEvent(int id,
               const std::string & title,
               const std::string & place,
               const std::string & summary,
               const CDate & start,
               const CDate & end,
               int priority,
               CEventRepeatBase * rp) :
                m_ID(id),
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

CEvent::~CEvent()
{
    delete m_Repeat;
}

std::chrono::minutes CEvent::GetDuration() const
{
    double diff = difftime(m_End.Count(), m_Start.Count());
    auto secs = std::chrono::seconds(dynamic_cast<int>(diff));

    return std::chrono::duration_cast<std::chrono::minutes>(secs);
}

CEvent * CEvent::InteractiveCreator(int ID)
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
            repeat = ReadRepetition(std::cin);
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Priority (1 - 10): " << std::endl;
    while(true)
    {
        try
        {
            std::string tmp;
            getline(std::cin, tmp);
            priority = parseInt(tmp);
            break;
        }
        catch (...)
        {
            std::cout << "Invalid input! Please type in number in the interval of 1 - 10 (including)." << std::endl;
        }
    }

    return new CEvent
            (
                    ID,
                    title,
                    place,
                    summary,
                    CDate::CombineDateTime(dateStart, timeStart),
                    CDate::CombineDateTime(dateEnd, timeEnd),
                    priority,
                    repeat
            );
}

std::ostream & operator<<(std::ostream & s, const CEvent & ev)
{
    s << "Title: " << ev.GetTitle() << std::endl;
    s << "Place: " << ev.GetPlace() << std::endl;
    s << "Summary: " << ev.GetSummary() << std::endl;
    s << "Starts on: " << ev.m_Start << std::endl;
    s << "Ends on: " << ev.m_End << std::endl;
    s << "Duration: " << ev.DurationString() << std::endl;
    s << "Priority: " << m_Priority << std::endl;
    s << "Repetition: " << m_Repeat->ToStr() << std::endl;

    return s;
}

std::string CEvent::DurationString() const
{
    return CDate::GetFormattedDuration(GetDuration().count());
}

std::ostream & operator<<(std::ostream & s, const CEvent * ev)
{
    if (ev == nullptr)
        return s << "null";
    else
        return s << *ev;
}

CEventRepeatBase * CEvent::ReadRepetition(std::istream & s)
{
    std::string line;
    getline(s, line);



}

std::vector<std::string> CEvent::GetSearchable::operator()(CEvent * const & ev) const
{
    return {ev->GetPlace(), ev->GetTitle()};
}
