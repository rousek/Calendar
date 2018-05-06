//
// Created by matyas on 05/06/2018.
//

#ifndef SEM_UTILS_H
#define SEM_UTILS_H

#include <algorithm>
#include <string>

// Stolen from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start (in place)
static inline void trimLeft(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
    {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void trimRight(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string & s)
{
    trimLeft(s);
    trimRight(s);
}

#endif //SEM_UTILS_H
