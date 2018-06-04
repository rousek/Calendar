//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATBASE_H
#define SEM_CEVENTREPEATBASE_H


#include <set>
#include "../Date/CDate.h"

/**
 * Base class handling special cases and serving as interface.
 */
class CEventRepeatBase
{
protected:
    /**
     * Beginnings of additional instances of event.
     */
    std::set<CDate> m_Additional;
    /**
     * Beginnings of skipped instances of event.
     */
    std::set<CDate> m_Skipped;
    /**
     *
     * @param date Start of event.
     * @param interval Timeframe within which to look for matches.
     * @return Set of dates when event starts within interval.
     */
    virtual std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const = 0;
public:
    virtual ~CEventRepeatBase() = default;
    virtual std::string ToStr() const = 0;
    virtual CEventRepeatBase * Clone() const = 0;

    std::set<CDate> GetAdditional() const { return m_Additional; }
    std::set<CDate> GetSkipped() const { return m_Skipped; }
    void AddAdditional(const CDate & date) { m_Additional.insert(date); }
    void AddSkipped(const CDate & date) { m_Skipped.insert(date); }
    /**
     * @return Number of instances left.
     */
    virtual int InstancesLeft() const = 0;
    /**
     * Delete instance of event.
     * @param date Date of instance to be deleted.
     * @return True if there are no more instances of event.
     */
    virtual bool Delete(const CDate & date) = 0;
    /**
     * Transfers instance of event from one date to another.
     * @param from Start of event instance.
     * @param to New start of event instance.
     */
    void Transfer(const CDate & from, const CDate & to);
    /**
     * Calls TestRange and filters skipped dates while adding additional dates.
     */
    virtual std::set<CDate> TestRangeWithExceptions(const CDate::Interval & timeOfEvent, const CDate::Interval & interval);
    /**
     * Simply converts list of beginnings into list of intervals.
     * @param beginnings
     * @param duration Duration of event.
     * @return Set of intervals.
     */
    static std::set<CDate::Interval> MakeIntervals(const std::set<CDate> & beginnings, const CDuration & duration);

    friend std::ostream &operator<<(std::ostream & stream, const CEventRepeatBase & rp)
    {
        return stream << rp.ToStr();
    }
    friend std::ostream &operator<<(std::ostream & stream, const CEventRepeatBase * rp)
    {
        return stream << rp->ToStr();
    }
};


#endif //SEM_CEVENTREPEATBASE_H
