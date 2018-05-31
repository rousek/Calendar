//
// Created by matyas on 05/02/2018.
//

#include "CDate.h"
#include "../utils/utils.h"
#include <iomanip>
#include <sstream>

const char CDate::TIME_FORMAT[] = "%H:%M";
const char CDate::DATE_FORMAT[] = "%d. %m. %Y";

CDate::CDate()
{
    m_Date = {0};
    m_Date.tm_isdst = -1;
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

CDate CDate::nextMonth() const
{
    tm cpy = m_Date;

    cpy.tm_mon++;

    if (cpy.tm_mon == 12)
    {
        cpy.tm_mon = 0;
        cpy.tm_year++;
    }

    return CDate(cpy);
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
    date.PrintDate(stream);
    stream << " ";
    date.PrintTime(stream);

    return stream;
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
