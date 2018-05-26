//
// Created by matyas on 05/05/2018.
//

#ifndef SEM_CCOMMANDINTERPRETER_H
#define SEM_CCOMMANDINTERPRETER_H


#include <string>
#include "../Calendar/CCalendar.h"


/**
 * CLI interface for CCalendar instance.
 * Supports adding, selecting, deleting,
 * moving and changing events.
 */
class CCommandInterpreter
{
public:
    /**
     * Reads a word from cin and then rest of the line.
     * Runs Interpret on it.
     */
    void GetNext();
    /**
     *
     * @param command
     * @param params
     */
    void Interpret(const std::string & command, const std::string & params);
private:
    CCalendar m_Calendar;
};


#endif //SEM_CCOMMANDINTERPRETER_H