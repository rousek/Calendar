//
// Created by matyas on 05/05/2018.
//

#include <iostream>
#include "../utils/utils.h"
#include "CCommandInterpreter.h"

CCommandInterpreter::CCommandInterpreter()
{
    std::cout << "Welcome to Calendar!" << std::endl;
}

void CCommandInterpreter::PrintHelp()
{
    std::cout << "Available commands are:" << std::endl << std::endl;

    std::cout << "help" << std::endl;
    std::cout << "Prints this help." << std::endl << std::endl;

    std::cout << "add" << std::endl;
    std::cout << "This command runs interactive editor" << std::endl;
    std::cout << "which will help you create event and" << std::endl;
    std::cout << "add it to the calendar. Has no parameters." << std::endl << std::endl;

    std::cout << "edit event_id" << std::endl;
    std::cout << "Every event has a unique id by which" << std::endl;
    std::cout << "you can identify it. This runs" << std::endl;
    std::cout << "Pass this id as parameter." << std::endl << std::endl;

    std::cout << "delete event_id" << std::endl;
    std::cout << "Delete event with given id." << std::endl << std::endl;

    std::cout << "clear" << std::endl;
    std::cout << "Clears calendar. No parameters." << std::endl << std::endl;

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
    std::cout << "When there is ID collision, imported" << std::endl;
    std::cout << "event is assigned new ID." << std::endl;
    std::cout << "Supported modes are \"default\" and \"ics\"." << std::endl << std::endl;
}

void CCommandInterpreter::GetNext()
{
    std::string command;
    std::string params;

    std::cin >> command;
    getline(std::cin, params);

    Interpret(command, split(params, ' '));
}

void CCommandInterpreter::Interpret(const std::string & command, const std::vector<std::string> & params)
{
    if (command == "help")
    {
        PrintHelp();
    }
    else if (command == "add")
    {
        if (params.size() != 0)
            return PrintHelp();

        m_Calendar.CreateEvent();
    }
    else if (command == "edit")
    {
        int evtID;

        if (params.size() != 1)
            return PrintHelp();

        evtID = parseInt(params[0]);
        m_Calendar.EditEvent(evtID);
    }
    else if (command == "delete")
    {
        int evtID;

        if (params.size() != 1)
            return PrintHelp();

        evtID = parseInt(params[0]);
        m_Calendar.RemoveEvent(evtID);
    }
    else if (command == "clear")
    {
        if (params.size() != 0)
            return PrintHelp();

        m_Calendar.Clear();
    }
    else if (command == "zoom")
    {
        std::cout << "TODO" << std::endl;
    }
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
}