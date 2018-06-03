//
// Created by matyas on 06/03/2018.
//

#include "CCalendarExportDefault.h"
#include "../utils/utils.h"
#include "../Event/CEventEditor.h"

const std::string CCalendarExportDefault::CALENDAR_START = "CALENDAR_MODE_DEFAULT_START";
const std::string CCalendarExportDefault::CALENDAR_END = "CALENDAR_MODE_DEFAULT_END";
const std::string CCalendarExportDefault::EVENT_START = "EVENT_MODE_DEFAULT_START";
const std::string CCalendarExportDefault::EVENT_END = "EVENT_MODE_DEFAULT_END";


void CCalendarExportDefault::Export(const CCalendar &cal, std::ofstream &s) const
{
    s << CALENDAR_START << std::endl;

    for (CEvent * event : cal.GetEvents())
    {
        s << EVENT_START << std::endl;
        s << "Title: " << event->GetTitle() << std::endl;
        s << "Place: " << event->GetPlace() << std::endl;
        s << "Summary: " << event->GetSummary() << std::endl;
        s << "Start: " << event->GetStart() << std::endl;
        s << "End: " << event->GetEnd() << std::endl;
        s << "Priority: " << event->GetPriority() << std::endl;
        s << "Repeat: " << event->GetRepeat() << std::endl;

        std::vector<std::string> skipped;
        for (auto d : event->GetRepeat()->GetSkipped())
            skipped.push_back(toStr(d));

        s << "Skipped: " << join(skipped, ", ") << std::endl;

        std::vector<std::string> additional;
        for (auto d : event->GetRepeat()->GetAdditional())
            additional.push_back(toStr(d));

        s << "Additional: " << join(additional, ", ") << std::endl;
        s << EVENT_END << std::endl;
    }

    s << CALENDAR_END << std::endl;
}

void CCalendarExportDefault::Import(std::ifstream &s, CCalendar &cal) const
{
    int lineCount = 1;
    std::string word, line;

    if (!getline(s, line) || line != CALENDAR_START)
        ThrowError(lineCount);

    lineCount++;

    while(true)
    {
        std::string title, place, summary;
        CDate start, end;
        int priority;
        CEventRepeatBase * repeat;

        if (!getline(s, line))
            ThrowError(lineCount);

        if (line == CALENDAR_END)
            return;

        if (line != EVENT_START)
            ThrowError(lineCount);

        lineCount++;

        if (!(s >> word) || word != "Title:" || !(getline(s, title)))
            ThrowError(lineCount);
        lineCount++;

        if (!(s >> word) || word != "Place:" || !(getline(s, place)))
            ThrowError(lineCount);
        lineCount++;

        if (!(s >> word) || word != "Summary:" || !(getline(s, summary)))
            ThrowError(lineCount);
        lineCount++;

        if (!(s >> word) || word != "Start:" || !(getline(s, line)))
            ThrowError(lineCount);

        try
        {
            start = CDate(line);
        }
        catch (...)
        {
            ThrowError(lineCount);
        }
        lineCount++;

        if (!(s >> word) || word != "End:" || !(getline(s, line)))
            ThrowError(lineCount);

        try
        {
            end = CDate(line);
        }
        catch (...)
        {
            ThrowError(lineCount);
        }
        lineCount++;

        if (!(s >> word) || word != "Priority:" || !(s >> priority))
            ThrowError(lineCount);
        lineCount++;

        if (!(s >> word) || word != "Repeat:" || !(getline(s, line)))
            ThrowError(lineCount);

        try
        {
            repeat = CEventEditor::ParseRepeat(line);
        }
        catch (...)
        {
            ThrowError(lineCount);
        }
        lineCount++;

        if (!(s >> word) || word != "Skipped:" || !(getline(s, line)))
            ThrowError(lineCount);

        try
        {
            auto skipped = split(line, ',');
            for (const std::string & str : skipped)
                repeat->AddSkipped(CDate(str));
        }
        catch (...)
        {
            ThrowError(lineCount);
        }
        lineCount++;


        if (!(s >> word) || word != "Additional:" || !(getline(s, line)))
            ThrowError(lineCount);

        try
        {
            auto additional = split(line, ',');
            for (const std::string & str : additional)
                repeat->AddAdditional(CDate(str));
        }
        catch (...)
        {
            ThrowError(lineCount);
        }
        lineCount++;

        if (!getline(s, line) || line != EVENT_END)
            ThrowError(lineCount);
        lineCount++;

        trim(title);
        trim(place);
        trim(summary);

        cal.AddEvent(new CEvent(title, place, summary, start, end, priority, repeat));
    }

}

void CCalendarExportDefault::ThrowError(int line) const
{
    throw std::invalid_argument(toStr("Error on line: ") + toStr(line));
}