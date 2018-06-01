//
// Created by matyas on 05/02/2018.
//

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "CEvent.h"
#include "../utils/utils.h"
#include "../RepeatStrategies/CEventRepeatDisabled.h"
#include "../RepeatStrategies/CEventRepeatDayInMonth.h"
#include "../RepeatStrategies/CEventRepeatAfter.h"

int CEvent::MIN_PRIORITY = 1;
int CEvent::MAX_PRIORITY = 10;

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

CDuration CEvent::GetDuration() const
{
    double diff = difftime(m_End.Count(), m_Start.Count());
    return CDuration::Seconds(static_cast<int>(diff));
}

std::set<CDate::Interval> CEvent::FindInInterval(const CDate::Interval & interval) const
{
    auto beginnings = m_Repeat->TestRangeWithExceptions(m_Start, interval);

    return CEventRepeatBase::MakeIntervals(beginnings, GetDuration());
}

bool CEvent::InteractiveEditor()
{

    if (requestConfirm("Do you want to save changes?"))
    {

    }
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

    std::cout << "Priority " << MIN_PRIORITY << " - " << MAX_PRIORITY << " (including): " << std::endl;
    while(true)
    {
        try
        {
            std::string tmp;
            getline(std::cin, tmp);
            priority = parseInt(tmp);
            if (priority < MIN_PRIORITY || priority > MAX_PRIORITY)
                throw 0;
            break;
        }
        catch (...)
        {
            std::cout << "Invalid input! Please type in number in the interval of "
                      << MIN_PRIORITY << " - " << MAX_PRIORITY << "." << std::endl;
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

CEventRepeatBase * CEvent::ReadRepetition(std::istream & s)
{
    std::string line;
    getline(s, line);

    auto parts = split(line, ' ');

    try
    {
        if (parts.empty())
            throw 0;

        if (parts.size() == 1)
        {
            if (parts[0] == "none")
                return new CEventRepeatDisabled();
        }
        else if (parts.size() == 2)
        {
            if (parts[0] == "month_day")
            {
                int day = parseInt(parts[1]);
                return new CEventRepeatDayInMonth(day);
            }
        }
        else
        {
            if (parts[0] == "after")
            {
                const int offset = 6; // Offset in line after string "after "
                CDuration duration = CDuration(line.substr(offset));
                return new CEventRepeatAfter(duration);
            }
        }
    }
    catch (...)
    {
        const char help[] =
                "Invalid input!\n"
                "Valid options are:\n"
                "\"none\"\n"
                "\"month_day day\" where day is day of month. Negative values are also accepted.\n"
                "\"after duration\" where duration is string representation of duration i.e. \"1 day, 1 month, 2 hours\"\n";

        throw std::invalid_argument(help);
    }
}

std::vector<std::string> CEvent::GetSearchable::operator()(CEvent * const & ev) const
{
    return {ev->GetPlace(), ev->GetTitle()};
}
