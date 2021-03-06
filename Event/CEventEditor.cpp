//
// Created by matyas on 06/03/2018.
//

#include "CEventEditor.h"
#include "../utils/utils.h"
#include "../RepeatStrategies/CEventRepeatDisabled.h"
#include "../RepeatStrategies/CEventRepeatDayInMonth.h"
#include "../RepeatStrategies/CEventRepeatAfter.h"
#include "../RepeatStrategies/CEventRepeatWork.h"

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

    ResolveCollisions(calendar, event);
    calendar.AddEvent(event);
}

void CEventEditor::Edit(CCalendar &calendar, CEvent *ev)
{
    CDate dateStart, dateEnd, timeStart, timeEnd, start, end;
    std::string title, place, summary;
    int priority;
    CEventRepeatBase * repeat;

    // Start date was skipped.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Start date
    std::cout << "Date (" << ev->GetStart().DateToStr() << "):" << std::endl;
    try
    {
        dateStart = CDate::RequestDateFromUser(CDate::ReadDate, false);
    }
    catch (const EmptyLineException & e)
    {
        dateStart = ev->GetStart();
    }

    // End date
    std::cout << "End date (" << ev->GetEnd().DateToStr() << "):"<< std::endl;
    while(true)
    {
        try
        {
            dateEnd = CDate::RequestDateFromUser(CDate::ReadDate, false);
        }
        catch (const EmptyLineException & e)
        {
            dateEnd = ev->GetEnd();
        }

        if (   dateStart.GetYear() > dateEnd.GetYear()
            || dateStart.GetMonth() > dateEnd.GetMonth()
            || dateStart.GetDay() > dateEnd.GetDay())
            std::cout << "Event must end after it starts!" << std::endl;
        else
            break;
    }

    // Start time
    std::cout << "Start time (" << ev->GetStart().TimeToStr() << "):" << std::endl;
    try
    {
        timeStart = CDate::RequestDateFromUser(CDate::ReadTime, false);
    }
    catch (const EmptyLineException & e)
    {
        timeStart = ev->GetStart();
    }

    start = CDate::CombineDateTime(dateStart, timeStart);

    // End time
    std::cout << "End time (" << ev->GetEnd().TimeToStr() << "):"<< std::endl;
    while(true)
    {
        try
        {
            timeEnd = CDate::RequestDateFromUser(CDate::ReadTime, false);
        }
        catch (const EmptyLineException & e)
        {
            timeEnd = ev->GetEnd();
        }

        end = CDate::CombineDateTime(dateEnd, timeEnd);

        if (start < end)
            break;
        else
            std::cout << "Event must end after it starts!" << std::endl;
    }

    std::cout << "Title (" << ev->GetTitle() << "):" << std::endl;
    getline(std::cin, title);
    if (title.empty())
        title = ev->GetTitle();

    std::cout << "Summary (" << ev->GetSummary() << "):" << std::endl;
    getline(std::cin, summary);
    if (summary.empty())
        summary = ev->GetSummary();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Place (" << ev->GetPlace() << "):" << std::endl;
    getline(std::cin, place);
    if (place.empty())
        place = ev->GetPlace();

    std::cout << "Repetition (" << ev->GetRepeat() << "):" << std::endl;
    while(true)
    {
        try
        {
            std::string line;
            getline(std::cin, line);

            if (line.empty())
                repeat = ev->GetRepeat();
            else
            {
                repeat = ParseRepeat(line);
                delete ev->GetRepeat();
            }
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << "Priority (" << ev->GetPriority() << "):" << std::endl;
    try
    {
        priority = requestIntInInterval(CEvent::MIN_PRIORITY, CEvent::MAX_PRIORITY, false);
    }
    catch (const EmptyLineException & e)
    {
        priority = ev->GetPriority();
    }

    ev->m_Title = title;
    ev->m_Place = place;
    ev->m_Summary = summary;
    ev->m_Start = start;
    ev->m_End = end;
    ev->m_Priority = priority;
    ev->m_Repeat = repeat;

    ResolveCollisions(calendar, ev);
}

void CEventEditor::Edit(CCalendar &calendar, const CEvent::Instance &instance)
{
    CEvent * event = instance.GetEvent();

    if (!instance.IsInstance() && event->InstancesLeft() > 1)
    {
        std::stringstream ss;
        ss << "This event repeats itself " << event->GetRepeat() << ". "
           << "Do you want to edit all instances? "
           << "If you press \"n\", this instance of "
           << "event will be edited separately.";

        if (requestConfirm(ss.str()))
        {
            calendar.DeleteEvent(event);
            Edit(calendar, event);
            calendar.AddEvent(event);
        }
        else
        {
            CEvent * cpy = CEvent::CopyInstance(instance);

            // Add it to the skipped dates.
            event->DeleteInstance(instance.GetTime().first);

            Edit(calendar, cpy);
            calendar.AddEvent(cpy);
        }
    }
    else
    {
        calendar.DeleteEvent(event);
        Edit(calendar, event);
        calendar.AddEvent(event);
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
            if (parts[0] == "work_days")
                return new CEventRepeatWork();

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
                        "\"after duration\" where duration is string representation of duration i.e. \"1 day, 1 month, 2 hours\"\n"
                        "\"work_days\"";

        throw std::invalid_argument(help);
    }
}

void CEventEditor::ResolveCollisions(CCalendar &calendar, CEvent *ev)
{
    CDate eventStart = ev->GetStart();
    CDate eventEnd = ev->GetEnd();
    CDate::Interval time = std::make_pair(eventStart, eventEnd);
    auto collisions = calendar.FindInInterval(time);

    if (collisions.empty()) // no resolution needed
        return;

    CDuration maxDuration = CDuration::Hours(CCalendar::SLEEPING_HOUR - CCalendar::WAKE_UP_HOUR);

    if ((eventEnd - eventStart).GetSize() > maxDuration.GetSize())
    {
        std::cout << "Collision has been detected. However event is too long to use "
                  << "this algorithm on it. Event will be added to calendar and you "
                  << "have to find free date yourself and edit it afterwards." << std::endl;
        return;
    }

    CDate morning = eventStart;
    morning.SetHour(CCalendar::WAKE_UP_HOUR).SetMinute(0);

    CDate evening = morning;
    evening.SetHour(CCalendar::SLEEPING_HOUR);
    evening -= ev->GetDuration();

    std::cout << "Collision has been detected. You cannot add this event in this day and time. "
              << "Type in \"next\" for next day or time in \"HH:mm\" format to choose this day and time." << std::endl;
    std::cout << "You have free time at following times:" << std::endl << std::endl;

    while(true)
    {
        auto eventsOnDay = calendar.FindInInterval(std::make_pair(morning, evening));
        std::sort(eventsOnDay.begin(), eventsOnDay.end());

        std::vector<CDate::Interval> eventTimes;
        for (auto & instance : eventsOnDay)
            eventTimes.push_back(instance.GetTime());

        auto merged = MergeIntervals(eventTimes);
        auto flipped = FlipIntervals(merged, morning, evening);

        if (PickAlternative(flipped, ev))
            break;

        morning += CDuration::Days(1);
        evening += CDuration::Days(1);
    }
}

std::vector<CDate::Interval> CEventEditor::MergeIntervals(const std::vector<CDate::Interval> &intervals)
{
    if (intervals.empty())
        return intervals;

    std::vector<CDate::Interval> results;

    for (auto & interval : intervals)
    {
        if (results.empty() || results[results.size() - 1].second < interval.first)
            results.push_back(interval);
        else
            results[results.size() - 1].second = MAX(results[results.size() - 1].second, interval.second);
    }

    return results;
}

std::vector<CDate::Interval> CEventEditor::FlipIntervals(const std::vector<CDate::Interval> &intervals,
                                                         const CDate &beginning, const CDate &end)
{
    std::vector<CDate::Interval> results;

    CDate start = beginning;

    for (auto & interval : intervals)
    {
        // in case they're equal
        if (start < interval.first)
            results.push_back(std::make_pair(start, interval.first));

        start = interval.second;
    }

    if (start < end)
        results.push_back(std::make_pair(start, end));

    return results;
}

bool CEventEditor::PickAlternative(const std::vector<CDate::Interval> &freeTime, CEvent *ev)
{
    CDate eventStart = ev->GetStart();
    CDate eventEnd = ev->GetEnd();
    CDuration eventDuration = eventEnd - eventStart;

    bool atLeastOne = false;

    for (auto & time : freeTime)
    {
        CDuration timeDuration = time.second - time.first;
        // skip too small time windows.
        if (timeDuration.GetSize() < eventDuration.GetSize())
            continue;

        CDate day = freeTime[0].first;

        if (!atLeastOne)
            std::cout << "***************"
                      << day.DateToStr()
                      << "***************" << std::endl;

        atLeastOne = true;

        std::cout << time.first.TimeToStr() << "-"
                  << time.second.TimeToStr() << std::endl;
    }

    if (!atLeastOne)
        return false;

    while (true)
    {
        std::string line;
        getline(std::cin, line);
        trim(line);

        if (line == "next")
            return false;

        std::stringstream ss(line);
        CDate newTime;
        try
        {
            CDate day = freeTime[0].first;
            newTime = CDate::ReadTime(ss);
            CDate newStart = CDate::CombineDateTime(day, newTime);
            CDate newEnd = newStart + eventDuration;

            for (auto & time : freeTime)
            {
                if (newStart >= time.first && newEnd <= time.second)
                {
                    ev->m_Start = newStart;
                    ev->m_End = newEnd;
                    return true;
                }
            }

            throw std::invalid_argument("This time is not free!");
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
