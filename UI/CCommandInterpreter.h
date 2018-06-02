//
// Created by matyas on 05/05/2018.
//

#ifndef SEM_CCOMMANDINTERPRETER_H
#define SEM_CCOMMANDINTERPRETER_H


#include <string>
#include <unordered_map>
#include "../Calendar/CCalendar.h"
#include "CViewTime.h"


/**
 * CLI interface for CCalendar instance.
 * Supports adding, selecting, deleting,
 * moving and changing events.
 */
class CCommandInterpreter
{
public:
    CCommandInterpreter();
    ~CCommandInterpreter();

    /**
     * Runs the main loop.
     */
    void Run();
    /**
     * Prints little welcome for user.
     */
    void Welcome();
    /**
     * Prints help.
     */
    void Help();
    /**
     * Exits main loop.
     */
    void Exit();
    /**
     * Runs interactive event creator.
     * @param params
     */
    void Add(const std::vector<std::string> & params);
    /**
     * Runs interactive event editor.
     * @param params Empty.
     */
    void Edit(const std::vector<std::string> & params);
    /**
     * Clears calendar.
     * @param params Empty.
     */
    void Clear(const std::vector<std::string> & params);
    /**
     * Deletes event with given id from m_List.
     * @param params {event_id}
     */
    void Delete(const std::vector<std::string> & params);
    /**
     * Searches calendar using title and location.
     * @param params keywords
     */
    void Search(const std::vector<std::string> & params);
    /**
     * Goes to next unit or page of m_List.
     * @param params
     */
    void Next(const std::vector<std::string> & params);
    /**
     * Goes to previous unit or page of m_List.
     * @param params
     */
    void Previous(const std::vector<std::string> & params);
    /**
     *
     * @param params First value always must be "in" or "out".
     * Second is ID of timeframe (optional).
     */
    void Zoom(const std::vector<std::string> & params);
    void Show(const std::vector<std::string> & params);
    void Export(const std::vector<std::string> & params);
    void Import(const std::vector<std::string> & params);
    CViewTime const * GetView();
private:
    typedef std::function<void (const std::vector<std::string> &)> command_function;
    typedef std::unordered_map<std::string, command_function> command_map;

    CCalendar m_Calendar;
    CDate m_Position;
    command_map m_Commands;
    bool m_Stopped;
    int m_ViewIndex;
    CViewTime * m_Views[3];

    /**
     * Calls command with given parameters if command exists.
     * Prints help otherwise.
     */
    void Interpret(const std::string & command, const std::vector<std::string> & params);
};


#endif //SEM_CCOMMANDINTERPRETER_H