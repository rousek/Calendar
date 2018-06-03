//
// Created by matyas on 06/03/2018.
//

#include "CEventEditor.h"
#include "../utils/utils.h"
#include "../RepeatStrategies/CEventRepeatDisabled.h"
#include "../RepeatStrategies/CEventRepeatDayInMonth.h"
#include "../RepeatStrategies/CEventRepeatAfter.h"

void CEventEditor::Create(CCalendar &calendar)
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
        while(true)
        {
            dateEnd = CDate::RequestDateFromUser(CDate::ReadDate, false);

            if (dateStart <= dateEnd)
                break;
            else
                std::cout << "Event must end after it starts!" << std::endl;
        }
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

        if (dateStart < dateEnd || timeEnd > timeStart)
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
            repeat = ParseRepeat(line);
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Priority " << CEvent::MIN_PRIORITY << " - " << CEvent::MAX_PRIORITY << " (including): " << std::endl;
    priority = requestIntInInterval(CEvent::MIN_PRIORITY, CEvent::MAX_PRIORITY, true);

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

    calendar.AddEvent(event);
}

void CEventEditor::Edit(CCalendar &calendar, CEvent *ev)
{

}

void CEventEditor::Edit(CCalendar &calendar, const CEvent::Instance &instance)
{
    CEvent * event = instance.GetEvent();

    if (event->InstancesLeft() > 1)
    {
        std::stringstream ss;
        ss << "This event repeats itself " << event->GetRepeat() << "." << std::endl
           << "Do you want to edit all instances?" << std::endl
           << "If you press \"n\", this instance of " << std::endl
           << "event will be edited separately.";

        if (requestConfirm(ss.str()))
        {
            Edit(calendar, event);
        }
        else
        {
            CEvent * cpy = new CEvent(*event);
            event->DeleteInstance(instance.GetTime().first);
            Edit(calendar, event);
            calendar.AddEvent(cpy);
        }
    }
    else
    {
        Edit(calendar, event);
    }
}


CEventRepeatBase * CEventEditor::ParseRepeat(const std::string &str)
{
    auto parts = split(str, ' ');

    try
    {
        if (parts.empty())
            throw 0;

        if (parts.size() == 1)
        {
            if (parts[0] == "none")
                return new CEventRepeatDisabled();

            throw 0;
        }
        else if (parts.size() == 2)
        {
            if (parts[0] == "month_day")
            {
                int day = parseInt(parts[1]);
                return new CEventRepeatDayInMonth(day);
            }

            throw 0;
        }
        else
        {
            if (parts[0] == "after")
            {
                const int offset = 6; // Offset in str after string "after "
                CDuration duration = CDuration(str.substr(offset));
                return new CEventRepeatAfter(duration);
            }

            throw 0;
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
