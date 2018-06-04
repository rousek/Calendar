//
// Created by matyas on 06/03/2018.
//

#ifndef SEM_CEVENTEDITOR_H
#define SEM_CEVENTEDITOR_H


#include "../Calendar/CCalendar.h"

/**
 * Creating and editing events. Also resolves collisions.
 */
class CEventEditor
{
public:
    /**
     * Create event step by step and add it into calendar.
     * @param calendar
     */
    static void Create(CCalendar & calendar);
    /**
     * Edit event instance (or whole event if it has only one instance)
     * @param calendar
     * @param instance
     */
    static void Edit(CCalendar & calendar, const CEvent::Instance & instance);
    /**
     * Edit whole event. It first needs to be removed from calendar and added afterwards.
     * @param calendar
     * @param ev Event that is not part of calendar.
     */
    static void Edit(CCalendar & calendar, CEvent * ev);
    /**
     * Simple collision resolving mechanism. Offers user dates after the date they picked
     * in the first place and allows them to choose. This mechanism does not guarantee
     * there will not be collisions if event in parameter repeats itself!
     * @param calendar
     * @param ev Event that is not part of calendar.
     */
    static void ResolveCollisions(CCalendar & calendar, CEvent * ev);
    /**
     * Parses string into CEventRepeatBase pointer.
     * @param str
     * @return
     */
    static CEventRepeatBase * ParseRepeat(const std::string &str);
private:
    /**
     * Merge overlapping intervals.
     * @param intervals Vector of intervals.
     * @return
     */
    static std::vector<CDate::Interval> MergeIntervals(const std::vector<CDate::Interval> & intervals);
    /**
     * Flips intervals the other way around. Gaps between old intervals will be new intervals.
     * @param intervals Vector of intervals.
     * @param beginning CDate where the intervals should begin.
     * @param end CDate where the intervals should end.
     * @return Flipped intervals.
     */
    static std::vector<CDate::Interval> FlipIntervals(const std::vector<CDate::Interval> & intervals,
                                                      const CDate & beginning, const CDate & end);
    /**
     * Shows user free time windows large enough to encompass the event. Lets him pick or deny.
     * @param freeTime Vector of intervals when user is free.
     * @param ev Event to pick free time for.
     * @return If true then new date was picked successfully. If false, then user does not like this day.
     */
    static bool PickAlternative(const std::vector<CDate::Interval> & freeTime, CEvent * ev);
};


#endif //SEM_CEVENTEDITOR_H
