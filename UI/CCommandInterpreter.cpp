//
// Created by matyas on 05/05/2018.
//

#include <iostream>
#include "../utils/utils.h"
#include "CCommandInterpreter.h"
#include "CViewWeek.h"
#include "CViewMonth.h"
#include "CViewYear.h"
#include "CViewDay.h"
#include "../Event/CEventEditor.h"
#include "../Exporters/CCalendarExportDefault.h"

CCommandInterpreter::CCommandInterpreter() :
        m_Position(CDate::Now()),
        m_Views{
                new CViewDay(m_Calendar, m_Position),
                new CViewWeek(m_Calendar, m_Position),
                new CViewMonth(m_Calendar, m_Position),
                new CViewYear(m_Calendar, m_Position)
        },
        m_SearchResults(nullptr)

{
    // Week view is default
    m_ViewIndex = 0;
    m_Commands.insert(std::make_pair("help", [this](const std::vector<std::string> & params) { Help(); }));
    m_Commands.insert(std::make_pair("exit", [this](const std::vector<std::string> & params) { Exit(); }));
    m_Commands.insert(std::make_pair("add", [this](const std::vector<std::string> & params) { Add(params); }));
    m_Commands.insert(std::make_pair("edit", [this](const std::vector<std::string> & params) { Edit(params); }));
    m_Commands.insert(std::make_pair("clear", [this](const std::vector<std::string> & params) { Clear(params); }));
    m_Commands.insert(std::make_pair("delete", [this](const std::vector<std::string> & params) { Delete(params); }));
    m_Commands.insert(std::make_pair("search", [this](const std::vector<std::string> & params) { Search(params); }));
    m_Commands.insert(std::make_pair("next", [this](const std::vector<std::string> & params) { Next(params); }));
    m_Commands.insert(std::make_pair("previous", [this](const std::vector<std::string> & params) { Previous(params); }));
    m_Commands.insert(std::make_pair("zoom", [this](const std::vector<std::string> & params) { Zoom(params); }));
    m_Commands.insert(std::make_pair("show", [this](const std::vector<std::string> & params) { Show(params); }));
    m_Commands.insert(std::make_pair("export", [this](const std::vector<std::string> & params) { Export(params); }));
    m_Commands.insert(std::make_pair("import", [this](const std::vector<std::string> & params) { Import(params); }));
}

CCommandInterpreter::~CCommandInterpreter()
{
    ClearSearch();

    for (auto &view : m_Views)
        delete view;
}

void CCommandInterpreter::Interpret(const std::string & command, const std::vector<std::string> & params)
{
    auto it = m_Commands.find(command);
    if (it == m_Commands.end())
    {
        std::cout << "This command does not exist!" << std::endl;
        Help();
    }
    else
    {
        auto fn = (*it).second;
        fn(params);
    }
}

void CCommandInterpreter::Run()
{
    Welcome();
    std::cout << std::endl;
    GetView()->Update();

    m_Stopped = false;

    while (!m_Stopped)
    {
        std::string command;
        std::string params;

        std::cin >> command;
        getline(std::cin, params);

        Interpret(command, split(params, ' '));
    }
}

CViewBase<CEvent::Instance> * CCommandInterpreter::GetView()
{
    if (m_SearchResults != nullptr)
        return m_SearchResults;

    return m_Views[m_ViewIndex];
}

void CCommandInterpreter::UpdateView()
{
    if (m_SearchResults != nullptr)
        Search(m_SearchQuery);
    else
        GetView()->Update();
}

void CCommandInterpreter::ClearSearch()
{
    if (m_SearchResults != nullptr)
    {
        delete m_SearchResults;
        m_SearchResults = nullptr;
    }
}

void CCommandInterpreter::Welcome()
{
    std::cout << "Welcome to Calendar!" << std::endl;
    std::cout << "Today is " << CDate::Now() << std::endl;
    std::cout << "For help just type in \"help\" and press Enter." << std::endl;
}

void CCommandInterpreter::Help()
{
    std::cout << "Available commands are:" << std::endl << std::endl;

    std::cout << "help" << std::endl
              << "Prints this help." << std::endl << std::endl;

    std::cout << "exit" << std::endl
              << "Exits app when in calendar, exits search when searching. "
              << "\"exit\" when editing or creating event will have no effect." << std::endl << std::endl;

    std::cout << "add" << std::endl
              << "This command runs interactive editor "
              << "which will help you create event and "
              << "add it to the calendar. Has no parameters." << std::endl << std::endl;

    std::cout << "edit event_id" << std::endl
              << "Supported only in a few selected modes. "
              << "Pass this id as parameter." << std::endl << std::endl;

    std::cout << "delete event_id" << std::endl
              << "Delete event with given id." << std::endl << std::endl;

    std::cout << "clear" << std::endl
              << "Clears calendar." << std::endl << std::endl;

    std::cout << "next" << std::endl
              << "Goes to next page of used view. "
              << "For example if calendar is showing weeks, "
              << "Then this will go to next week." << std::endl << std::endl;

    std::cout << "previous" << std::endl
              << "Same as \"next\" but backwards." << std::endl << std::endl;

    std::cout << "zoom (in|out)" << std::endl
              << "Zooms into smaller or bigger timeframe. "
              << "For example \"zoom in\" when calendar "
              << "is showing a whole year would show a month instead." << std::endl << std::endl;

    std::cout << "show [date_to_show]" << std::endl
              << "Shows events for date_to_show. "
              << "Updates view if no parameter is passed. "
              << "Date format is dd. mm. yyyy" << std::endl << std::endl;

    std::cout << "export file_name" << std::endl
              << "Exports whole calendar into file." << std::endl << std::endl;

    std::cout << "import file_name" << std::endl
              << "Imports events from file. Does not "
              << "remove existing events (if there are any)." << std::endl << std::endl;
}

void CCommandInterpreter::Exit()
{
    if (m_SearchResults != nullptr)
    {
        ClearSearch();
        GetView()->Update();
    }
    else
    {
        m_Stopped = true;
    }
}

void CCommandInterpreter::Add(const std::vector<std::string> &params)
{
    if (!params.empty())
        return Help();

    CEventEditor::Create(m_Calendar);
    UpdateView();
}

void CCommandInterpreter::Edit(const std::vector<std::string> &params)
{
    int evtID;

    if (params.size() != 1)
        return Help();

    try
    {
        evtID = parseInt(params[0]);
        CEvent::Instance ev = GetView()->Find(evtID);
        CEventEditor::Edit(m_Calendar, ev);
        UpdateView();
    }
    catch (const std::invalid_argument & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CCommandInterpreter::Clear(const std::vector<std::string> &params)
{
    if (params.size() != 0)
        return Help();

    m_Calendar.Clear();

    std::cout << "Calendar is now clear." << std::endl;
}

void CCommandInterpreter::Delete(const std::vector<std::string> &params)
{
    int evtID;

    if (params.size() != 1)
        return Help();

    try
    {
        evtID = parseInt(params[0]);
        CEvent::Instance ev = GetView()->Find(evtID);
        m_Calendar.DeleteEvent(ev);
        UpdateView();
    }
    catch (const std::invalid_argument & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CCommandInterpreter::Zoom(const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return Help();

    else if (m_SearchResults != nullptr)
    {
        std::cout << "This view mode does not support this feature!" << std::endl;
        return;
    }

    if (params[0] == "in")
    {

        if (m_ViewIndex == 0)
        {
            std::cout << "You cannot zoom in any further!" << std::endl;
            return;
        }
        m_ViewIndex--;
    }
    else if (params[0] == "out")
    {
        if (m_ViewIndex == sizeof(m_Views) / sizeof(m_Views[0]) - 1)
        {
            std::cout << "You cannot zoom out any further!" << std::endl;
            return;
        }
        m_ViewIndex++;
    }
    else
        return Help();

    GetView()->Update();
}

void CCommandInterpreter::Search(const std::vector<std::string> &params)
{
    if (params.empty())
    {
        std::cout << "Please type in at least one keyword." << std::endl;
        return;
    }

    std::string query = join(params, " ");
    std::vector<CEvent *> results = m_Calendar.SearchEvents(query);
    if (!results.empty())
    {
        ClearSearch();
        m_SearchQuery = params;
        m_SearchResults = new CViewVector(results);
        m_SearchResults->Update();
    }
    else
    {
        std::cout << "No matching events were found!" << std::endl;
    }
}

void CCommandInterpreter::Next(const std::vector<std::string> &params)
{
    if (!params.empty())
        return Help();

    try
    {
        GetView()->Next();
        GetView()->Update();
    }
    catch (const std::invalid_argument & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CCommandInterpreter::Previous(const std::vector<std::string> &params)
{
    if (!params.empty())
        return Help();

    try
    {
        GetView()->Previous();
        GetView()->Update();
    }
    catch (const std::invalid_argument & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CCommandInterpreter::Show(const std::vector<std::string> &params)
{
    if (params.empty())
    {
        ClearSearch();
        GetView()->Update();
        return;
    }

    std::string str = join(params, " ");
    std::stringstream ss(str);

    try
    {
        CDate d = CDate::ReadDate(ss);
        m_Position = d;
        ClearSearch();
        GetView()->Update();
    }
    catch (const std::invalid_argument & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CCommandInterpreter::Import(const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return Help();

    std::ifstream file;
    file.open(params[0]);

    if (!file.is_open())
    {
        std::cout << "File " << params[0] << " could not be opened." << std::endl;
    }
    else
    {
        CCalendarExportDefault importer;
        try
        {
            importer.Import(file, m_Calendar);
            std::cout << "File has been imported successfully!" << std::endl;
            UpdateView();
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }

        file.close();
    }
}

void CCommandInterpreter::Export(const std::vector<std::string> &params)
{
    if (params.size() != 1)
        return Help();

    std::ofstream file;
    file.open(params[0]);

    if (!file.is_open())
    {
        std::cout << "File " << params[0] << " could not be opened." << std::endl;
    }
    else
    {
        CCalendarExportDefault exporter;
        exporter.Export(m_Calendar, file);
        std::cout << "File has been exported successfully!" << std::endl;
        file.close();
    }
}