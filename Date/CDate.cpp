//
// Created by matyas on 05/02/2018.
//

#include "CDate.h"
#include "../utils/utils.h"
#include <iomanip>
#include <sstream>

const char CDate::TIME_FORMAT[] = "%H:%M";
const char CDate::DATE_FORMAT[] = "%d. %m. %Y";
const char CDate::WHOLE_FORMAT[] = "%d. %m. %Y %H:%M";

CDate::CDate()
{
    m_Date = {0};
    m_Date.tm_isdst = -1;
}

CDate::CDate(const std::string &str)
{
    m_Date = {0};

    std::stringstream ss(str);
    ss >> std::get_time(&m_Date, WHOLE_FORMAT);
    m_Date.tm_isdst = -1;

    if (mktime(&m_Date) == -1)
        throw std::invalid_argument("Invalid date!");
}

CDate::CDate(const tm & tm)
{
    m_Date = tm;
    m_Date.tm_isdst = -1;
    m_Date.tm_sec = 0;

    if (mktime(&m_Date) == -1)
        throw std::invalid_argument("Invalid date!");
}

CDate::CDate(time_t number) : CDate(*gmtime(&number))
{
}

int CDate::GetYear() const
{
    return m_Date.tm_year + 1900;
}

int CDate::GetMonth() const
{
    return m_Date.tm_mon + 1;
}

int CDate::GetDay() const
{
    return m_Date.tm_mday;
}

int CDate::GetHour() const
{
    return m_Date.tm_hour;
}

int CDate::GetMinute() const
{
    return m_Date.tm_min;
}

time_t CDate::Count() const
{
    return mktime(const_cast<tm*>(&m_Date));
}

tm CDate::GetTm() const
{
    return m_Date;
}

bool CDate::operator == (const CDate & d2) const
{
    return Count() == d2.Count();
}

bool CDate::operator <= (const CDate & d2) const
{
    return Count() <= d2.Count();
}

bool CDate::operator < (const CDate & d2) const
{
    return Count() < d2.Count();
}

CDate CDate::ReadDate(std::istream & s)
{
    tm tm = {};
    std::string line;
    getline(s, line);
    std::stringstream ss(line);

    if (line.empty())
        throw EmptyLineException();

    ss >> std::get_time(&tm, DATE_FORMAT);

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    if (ss.fail())
        throw std::invalid_argument("Invalid date! Date format: DD. MM. YYYY");

    return CDate(tm);
}

CDate CDate::ReadTime(std::istream & s)
{

    tm tm = {};
    std::string line;
    getline(s, line);
    std::stringstream ss(line);

    if (line.empty())
        throw EmptyLineException();

    ss >> std::get_time(&tm, TIME_FORMAT);

    tm.tm_sec = 0;
    tm.tm_mon = 0;
    tm.tm_mday = 1;
    tm.tm_year = 70; // 1970

    if (ss.fail())
        throw std::invalid_argument("Invalid time! Supported time format: HH:MM");

    return CDate(tm);
}

CDate CDate::RequestDateFromUser(std::function<CDate (std::istream &)> fn, bool required)
{
    CDate date;

    while(true)
    {
        try
        {
            date = fn(std::cin);
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const EmptyLineException & e)
        {
            if (required)
                std::cout << "This information is required!" << std::endl;
            else
                throw e;
        }
    }

    return date;
}

CDate CDate::CombineDateTime(const CDate & date, const CDate & time)
{
    tm tm = date.m_Date;
    tm.tm_hour = time.GetHour();
    tm.tm_min = time.GetMinute();

    return CDate(tm);
}

std::string CDate::GetFormattedDuration(long long int minutesCount)
{
    std::stringstream ss;
    auto days = minutesCount / (60 * 24);
    auto hours = minutesCount / 60 - days * 24;
    auto mins = minutesCount % 60;

    std::string delim("");

    if (days > 0)
    {
        ss << days << ((days == 1) ? " day" : " days");
        delim = ", ";
    }

    if (hours > 0)
    {
        ss << delim;
        ss << hours << ((hours == 1) ? " hour" : " hours");
        delim = ", ";
    }

    if (mins > 0)
    {
        ss << delim;
        ss << mins << ((mins == 1) ? " minute" : " minutes");
    }

    return ss.str();
}

std::ostream & CDate::PrintDate(std::ostream & stream) const
{
    return stream << std::put_time(&m_Date, DATE_FORMAT);
}

std::ostream & CDate::PrintTime(std::ostream & stream) const
{
    return stream << std::put_time(&m_Date, TIME_FORMAT);
}

std::ostream & operator << (std::ostream & stream, const CDate & date)
{
    return stream << std::put_time(&date.m_Date, CDate::WHOLE_FORMAT);
}

std::chrono::minutes CDate::DurationToMinutes(std::string duration) {
    std::chrono::minutes mins(0);
    using namespace std;

    std::vector<std::string> parts = split(duration, ',');

    for (auto part : parts)
    {
        std::stringstream ss(part);
        int number;
        std::string unit;

        if (!(ss >> number) || !(ss >> unit))
            throw std::invalid_argument("Invalid duration string!");

        if (unit == "month" || unit == "months")
            mins += std::chrono::duration_cast<std::chrono::minutes>(CDate::Months(number));
        else if (unit == "week" || unit == "weeks")
            mins += std::chrono::duration_cast<std::chrono::minutes>(CDate::Weeks(number));
        else if (unit == "day" || unit == "days")
            mins += std::chrono::duration_cast<std::chrono::minutes>(CDate::Days(number));
        else if (unit == "hour" || unit == "hours")
            mins += std::chrono::duration_cast<std::chrono::minutes>(std::chrono::hours(number));
        else if (unit == "minute" || unit == "minutes")
            mins += std::chrono::minutes(number);
        else
            throw std::invalid_argument("Invalid duration string!");
    }

    return mins;
}


int CDate::MonthLength(int month, int year)
{
    switch(month)
    {
        case 1: return 31;
        case 2:
            if (year % 4 || (!(year % 100) && year % 400))
                return 28;
            else
                return 29;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: throw std::invalid_argument("Wrong month: " + toStr(month));
    }
}
