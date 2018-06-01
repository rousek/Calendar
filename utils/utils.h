//
// Created by matyas on 05/06/2018.
//

#ifndef SEM_UTILS_H
#define SEM_UTILS_H

#include <algorithm>
#include <string>
#include <sstream>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

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

static inline std::string & trim(std::string & s)
{
    trimLeft(s);
    trimRight(s);
    return s;
}


// Stolen from Progtest
template <typename _T>
static inline std::string toStr(const _T & it)
{
    std::stringstream ss;
    ss << it;

    return ss.str();
}

static inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        trim(item);
        result.push_back(item);
    }
    return result;
}


static inline int parseInt(const std::string & str)
{
    std::string::size_type sz;

    return std::stoi(str, &sz);
}

bool requestConfirm(const std::string & msg);

/**
 * Thrown in some cases when stream has empy line in it.
 */
class EmptyLineException
{
};

#endif //SEM_UTILS_H
