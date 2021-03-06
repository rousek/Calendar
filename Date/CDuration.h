//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CDURATION_H
#define SEM_CDURATION_H

#include <string>
#include <ostream>

/**
 * Representation of time duration. Keeps separated seconds, months and years,
 * because this is the only way of dealing with months of different lengths and
 * leap years.\n
 * All operators are commutative and associative.
 */
class CDuration
{
private:
    long long int m_Years, m_Months, m_Seconds;
public:
    /**
     * Separated components. Days cannot become months.
     */
    typedef struct Separated
    {
        long long int years, months, weeks, days, hours, minutes, seconds;
    } Separated;

    /**
     * All properties are set to zero.
     */
    CDuration();
    /**
     * @param str String of values separated by comma and space.
     */
    explicit CDuration(const std::string & str);
    long long int GetYears() const { return m_Years; }
    long long int GetMonths() const { return m_Months; }
    long long int GetSeconds() const { return m_Seconds; }
    /**
     * @return Approximate number of seconds this duration holds.
     */
    long long int GetSize() const { return m_Seconds + m_Months * SECS_IN_MONTH + m_Years * SECS_IN_YEAR; }
    /**
     * @return Duration separated into components.
     */
    CDuration::Separated Separate() const;

    bool operator==(const CDuration & d2) const;
    CDuration operator+(const CDuration & d2) const;
    CDuration operator-(const CDuration & d2) const;
    CDuration & operator+=(const CDuration & d2);
    CDuration & operator-=(const CDuration & d2);
    CDuration operator-() const;

    static CDuration Years(long long int value);
    static CDuration Months(long long int value);
    static CDuration Weeks(long long int value);
    static CDuration Days(long long int value);
    static CDuration Hours(long long int value);
    static CDuration Minutes(long long int value);
    static CDuration Seconds(long long int value);

    static const int SECS_IN_MINUTE;
    static const int MINUTES_IN_HOUR;
    static const int HOURS_IN_DAY;
    static const int DAYS_IN_WEEK;
    static const int MONTHS_IN_YEAR;
    static const int SECS_IN_HOUR;
    static const int SECS_IN_DAY;
    static const int SECS_IN_WEEK;
    static const int SECS_IN_MONTH;
    static const int SECS_IN_YEAR;

    friend std::ostream & operator<<(std::ostream & stream, const CDuration & duration);
};


#endif //SEM_CDURATION_H
