//
// Created by matyas on 05/05/2018.
//

#ifndef SEM_CCOMMANDINTERPRETER_H
#define SEM_CCOMMANDINTERPRETER_H


#include <string>
#include <unordered_map>
#include "../Calendar/CCalendar.h"
#include "CViewTime.h"
#include "CViewVector.h"


/**
 * CLI interface for CCalendar instance.
 * Supports adding, selecting, deleting,
 * moving and changing events.
 */
class CCommandInterpreter
{
public:
    CCalendar m_Calendar;

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
     * @param params Keywords.
     */
    void Search(const std::vector<std::string> & params);
    /**
     * Goes to next unit or page of view.
     * @param params Empty.
     */
    void Next(const std::vector<std::string> & params);
    /**
     * Goes to previous unit or page of view.
     * @param params Empty.
     */
    void Previous(const std::vector<std::string> & params);
    /**
     * Changes view between week, month and year.
     * @param params First value always must be "in" or "out".
     * Second is ID of timeframe (optional).
     */
    void Zoom(const std::vector<std::string> & params);
    /**
     * Goes to given date and shows it in current view mode.
     * @param params {date}
     */
    void Show(const std::vector<std::string> & params);
    void Export(const std::vector<std::string> & params);
    void Import(const std::vector<std::string> & params);
    CViewBase<CEvent *> * GetView();
private:
    typedef std::function<void (const std::vector<std::string> &)> command_function;
    typedef std::unordered_map<std::string, command_function> command_map;

    CDate m_Position;
    command_map m_Commands;
    bool m_Stopped;
    int m_ViewIndex;
    CViewTime * m_Views[3];
    std::vector<std::string> m_SearchQuery;
    CViewVector * m_SearchResults;

    /**
     * Calls command with given parameters if command exists.
     * Prints help otherwise.
     */
    void Interpret(const std::string & command, const std::vector<std::string> & params);

    void ClearSearch();
};


#endif //SEM_CCOMMANDINTERPRETER_H