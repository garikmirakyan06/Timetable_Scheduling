#pragma once

#include "../include/TimeTable.h"
#include "../include/University.h"
#include "../include/BruteForceScheduler.h"
#include "../include/DummyScheduler.h"
#include "../include/SchedulerContext.h"
#include "../include/IScheduler.h"


class ExampleTests {
private:
    static TimeTable constructTimetable(const University& uni, const std::vector<std::vector<int>>& indexesVec);

public:
    // construct university and return trueTimetable

    // course = 1, timeSlot = 2, instructor = 2
    static TimeTable example1(University& uni);

    // course = 1, timeSlot = 1, instructor = 1
    static TimeTable example2(University& uni);

    // course = 2, timeSlot = 2, instructor = 2
    static TimeTable example3(University& uni);

    // course = 1, timeSlot = 3, instructor = 1
    static TimeTable example4(University& uni);

    // course = 2, timeSlot = 3, instructor = 3
    static TimeTable example5(University& uni);

    // course = 2, timeSlot = 3, instructor = 4
    static TimeTable example6(University& uni);

    // course = 4, timeSlot = 4, instructor = 2
    static TimeTable example7(University& uni);

    // course = 4, timeSlot = 5, instructor = 4
    static TimeTable example8(University& uni);

    // course = 2, timeSlot = 3, instructor = 2
    static TimeTable example9(University& uni);

    // course = 3, timeSlot = 3, instructor = 3
    static TimeTable example10(University& uni);


    // schedule university
    static std::vector<TimeTable> schedule(University& uni, bool useDummyScheduler);
};
