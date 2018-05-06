//
// Created by matyas on 05/02/2018.
//

#include "CDate.h"
#include <iomanip>

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

int CDate::getYear() const
{
    return m_Date.tm_year + 1900;
}

int CDate::getMonth() const
{
    return m_Date.tm_mon + 1;
}

int CDate::getDay() const
{
    return m_Date.tm_mday;
}

int CDate::getHour() const
{
    return m_Date.tm_hour;
}

int CDate::getMinute() const
{
    return m_Date.tm_min;
}

time_t CDate::Count() const
{
    return mktime(const_cast<tm*>(&m_Date));
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
    s >> std::get_time(&tm, DATE_FORMAT);

    if (s.fail())
    {
        s.clear();
        s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid date! Date format: DD. MM. YYYY");
    }

    return CDate(tm);
}

CDate CDate::ReadTime(std::istream & s)
{

    tm tm = {};
    s >> std::get_time(&tm, TIME_FORMAT);

    if (s.fail())
    {
        s.clear();
        s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid time! Supported time format: HH:MM");
    }

    return CDate(tm);
}

CDate CDate::RequestDateFromUser(std::function<CDate (std::istream &)> fn)
{
    CDate date;

    while(true)
    {
        try
        {
            date = fn(std::cin);
            break;
        } catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return date;
}

CDate CDate::CombineDateTime(const CDate & date, const CDate & time)
{
    tm tm = date.m_Date;
    tm.tm_hour = time.getHour();
    tm.tm_min = time.getMinute();

    return CDate(tm);
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