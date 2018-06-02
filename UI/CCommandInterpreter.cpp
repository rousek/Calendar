//
// Created by matyas on 05/05/2018.
//

#include <iostream>
#include "../utils/utils.h"
#include "CCommandInterpreter.h"
#include "CViewWeek.h"
#include "CViewMonth.h"
#include "CViewYear.h"

CCommandInterpreter::CCommandInterpreter() :
        m_Position(CDate::Now()),
        m_Views
                {
                new CViewWeek(m_Calendar, m_Position)
                //new CViewMonth(m_Calendar, m_Position),
                //new CViewYear(m_Calendar, m_Position)
                }

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
    /*
    else if (command == "show")
    {
        std::cout << "TODO" << std::endl;
    }
    else if (command == "export")
    {
        std::cout << "TODO" << std::endl;
    }
    else if (command == "import")
    {
        std::cout << "TODO" << std::endl;
    }
     */
}

void CCommandInterpreter::Run()
{
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

void CCommandInterpreter::Welcome()
{
    std::cout << "Welcome to Calendar!" << std::endl;
    std::cout << "Today is " << CDate::Now() << std::endl;
    std::cout << "For help just type in \"help\" and press Enter." << std::endl;
}

void CCommandInterpreter::Help()
{
    std::cout << "Available commands are:" << std::endl << std::endl;

    std::cout << "help" << std::endl;
    std::cout << "Prints this help." << std::endl << std::endl;

    std::cout << "add" << std::endl;
    std::cout << "This command runs interactive editor" << std::endl;
    std::cout << "which will help you create event and" << std::endl;
    std::cout << "add it to the calendar. Has no parameters." << std::endl << std::endl;

    std::cout << "edit event_id" << std::endl;
    std::cout << "Supported only in a few selected modes." << std::endl;
    std::cout << "Pass this id as parameter." << std::endl << std::endl;

    std::cout << "delete event_id" << std::endl;
    std::cout << "Delete event with given id." << std::endl << std::endl;

    std::cout << "clear" << std::endl;
    std::cout << "Clears calendar." << std::endl << std::endl;

    std::cout << "next" << std::endl;
    std::cout << "Goes to next page of used view." << std::endl;
    std::cout << "For example if calendar is showing weeks,"<< std::endl;
    std::cout << "Then this will go to next week." << std::endl << std::endl;

    std::cout << "previous" << std::endl;
    std::cout << "Same as \"next\" but backwards." << std::endl << std::endl;

    std::cout << "zoom (in|out) [time_id]" << std::endl;
    std::cout << "Zooms into smaller timeframe." << std::endl;
    std::cout << "For example \"zoom in\" when calendar" << std::endl;
    std::cout << "is showing a whole year would show a month" << std::endl;
    std::cout << "instead. Optional parameter time_id would be" << std::endl;
    std::cout << "number of month in year (January is 1)." << std::endl << std::endl;

    std::cout << "show date_to_show [time_frame]" << std::endl;
    std::cout << "If time_frame is left blank, then shows" << std::endl;
    std::cout << "day which is given as parameter date_to_show." << std::endl;
    std::cout << "time_frame can be year, month, week or day (default)." << std::endl;
    std::cout << "Date format is dd. mm. yyyy" << std::endl << std::endl;

    std::cout << "export [mode] file_name" << std::endl;
    std::cout << "Exports whole calendar into file." << std::endl;
    std::cout << "Supported modes are \"default\" and \"ics\"." << std::endl << std::endl;

    std::cout << "import [mode] file_name" << std::endl;
    std::cout << "Imports events from file. Does not" << std::endl;
    std::cout << "remove existing events (if there are any)." << std::endl;
    std::cout << "Supported modes are \"default\" and \"ics\"." << std::endl << std::endl;
}

void CCommandInterpreter::Exit()
{
    m_Stopped = true;
}

void CCommandInterpreter::Add(const std::vector<std::string> &params)
{
    if (!params.empty())
        return Help();

    m_Calendar.CreateEvent();
}

void CCommandInterpreter::Edit(const std::vector<std::string> &params)
{
    int evtID;

    if (params.size() != 1)
        return Help();

    evtID = parseInt(params[0]);
    m_Calendar.EditEvent(evtID);
}

void CCommandInterpreter::Clear(const std::vector<std::string> &params)
{
    if (params.size() != 0)
        return Help();

    m_Calendar.Clear();
}

void CCommandInterpreter::Delete(const std::vector<std::string> &params)
{
    int evtID;

    if (params.size() != 1)
        return Help();

    evtID = parseInt(params[0]);

    m_Calendar.RemoveEvent(evtID);
}

void CCommandInterpreter::Zoom(const std::vector<std::string> &params)
{
    int id = 0;

    if (params.size() == 2)
    {
        try
        {
            id = parseInt(params[1]);
        }
        catch (...)
        {
            return Help();
        }
    }
    else if (params.size() != 1)
        return Help();

    if (params[1] == "in")
    {

        if (m_ViewIndex == 0)
            return;
    }
}

void CCommandInterpreter::Search(const std::vector<std::string> &params)
{

}

void CCommandInterpreter::Next(const std::vector<std::string> &params)
{

}

void CCommandInterpreter::Previous(const std::vector<std::string> &params)
{

}

void CCommandInterpreter::Import(const std::vector<std::string> &params)
{

}

void CCommandInterpreter::Export(const std::vector<std::string> &params)
{

}

void CCommandInterpreter::Show(const std::vector<std::string> &params)
{

}