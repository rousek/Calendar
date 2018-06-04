//
// Created by matyas on 05/06/2018.
//

#ifndef SEM_UTILS_H
#define SEM_UTILS_H

#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

static inline void trimLeft(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
    {
        return !std::isspace(ch);
    }));
}

static inline void trimRight(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

/**
 * Trims string from both sides.
 * @param s String to be trimmed.
 * @return Trimmed string.
 */
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

/**
 * Splits string into vector of strings.
 * @param s String to be split.
 * @param delim Delimiter.
 * @return Vector of trimmed substrings.
 */
static inline std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        trim(item);
        if (!item.empty())
            result.push_back(item);
    }
    return result;
}

/**
 * Joins vector of strings into one string.
 * @param vec Vector to be joined.
 * @param delim Delimiter to be used.
 * @return Joined string.
 */
static inline std::string join(const std::vector<std::string> & vec, const std::string & delim)
{
    std::stringstream ss;

    for (int i = 0; i < vec.size(); i++)
    {
        ss << vec[i];
        if (i != vec.size() - 1)
            ss << delim;
    }

    return ss.str();
}

/**
 * Reads string as decimal integer.
 * @param str String to be read.
 * @return Integer.
 */
static inline int parseInt(const std::string & str)
{
    std::string::size_type sz;

    try
    {
        return std::stoi(str, &sz);
    }
    catch (...)
    {
        throw std::invalid_argument("This is not a valid integer!");
    }
}

/**
 * Asks a boolean question with Y/n as valid answers.
 * @param msg Question to be asked. Without Y/n.
 * @return User's answer.
 */
bool requestConfirm(const std::string & msg);

/**
 * Reads number from input.
 * @param min Lower boundary. Inclusive.
 * @param max Upper boundary. Inclusice.
 * @param required If false, then EmptyLineException is raised.
 * @return Integer >= min X <= max from cin.
 */
int requestIntInInterval(int min, int max, bool required);

/**
 * Thrown in some cases when stream has empy line in it.
 */
class EmptyLineException
{
};
#endif //SEM_UTILS_H
