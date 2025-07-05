#include "../ExampleTests.h"


// course = 1, timeSlot = 2, instructor = 2
TimeTable ExampleTests::example1(University& uni) {
    uni.loadState("../test/resources/testData1.json");

    // hard code trueTimetable
    TimeTable timetable = constructTimetable(uni, {{0,0,0}});

    return timetable;
}

// course = 1, timeSlot = 1, instructor = 1
TimeTable ExampleTests::example2(University& uni) {
    uni.loadState("../test/resources/testData2.json");

    // hard code trueTimetable
    TimeTable timetable = constructTimetable(uni, {{0,0,0}});

    return timetable;
}

// course = 2, timeSlot = 2, instructor = 2
TimeTable ExampleTests::example3(University& uni) {
    uni.loadState("../test/resources/testData3.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,0}; // courseInd, timeSlotInd, instructorInd
    std::vector<int> indexes2 = {1,1,1};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2}); // adding assignments in timetable

    return timetable;
}

// course = 1, timeSlot = 3, instructor = 1
TimeTable ExampleTests::example4(University& uni) {
    uni.loadState("../test/resources/testData4.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,0};
    TimeTable timetable = constructTimetable(uni, {indexes1});

    return timetable;
}


// course = 2, timeSlot = 3, instructor = 3
TimeTable ExampleTests::example5(University& uni) {
    uni.loadState("../test/resources/testData5.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {1,0,1};
    std::vector<int> indexes2 = {0,2,0};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2});

    return timetable;
}

// course = 2, timeSlot = 3, instructor = 4
TimeTable ExampleTests::example6(University& uni) {
    uni.loadState("../test/resources/testData6.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,0};
    std::vector<int> indexes2 = {1,1,1};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2});

    return timetable;
}


// course = 4, timeSlot = 4, instructor = 2
TimeTable ExampleTests::example7(University& uni) {
    uni.loadState("../test/resources/testData7.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,0};
    std::vector<int> indexes2 = {1,1,1};
    std::vector<int> indexes3 = {2,2,0};
    std::vector<int> indexes4 = {3,3,1};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2, indexes3, indexes4});

    return timetable;
}

// course = 4, timeSlot = 5, instructor = 4
TimeTable ExampleTests::example8(University& uni) {
    uni.loadState("../test/resources/testData8.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,0};
    std::vector<int> indexes2 = {1,1,1};
    std::vector<int> indexes3 = {2,2,2};
    std::vector<int> indexes4 = {3,3,3};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2, indexes3, indexes4});

    return timetable;
}

// course = 2, timeSlot = 3, instructor = 2
TimeTable ExampleTests::example9(University& uni) {
    uni.loadState("../test/resources/testData9.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {1,0,0};
    std::vector<int> indexes2 = {0,2,1};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2});

    return timetable;
}

// course = 3, timeSlot = 3, instructor = 3
TimeTable ExampleTests::example10(University& uni) {
    uni.loadState("../test/resources/testData10.json");

    // hard code trueTimetable
    std::vector<int> indexes1 = {0,0,1};
    std::vector<int> indexes2 = {1,1,0};
    std::vector<int> indexes3 = {2,2,2};
    TimeTable timetable = constructTimetable(uni, {indexes1, indexes2, indexes3});

    return timetable;
}


std::vector<TimeTable> ExampleTests::schedule(University& uni, bool useDummyScheduler) {
    std::unique_ptr<IScheduler> scheduler;
    if (useDummyScheduler) { // use DummyScheduler
        scheduler = std::make_unique<DummyScheduler>(uni);
    } else { // use BruteForceScheduler
        scheduler = std::make_unique<BruteForceScheduler>(uni);
    }
    SchedulerContext schedulerContext(std::move(scheduler));
    std::vector<TimeTable> timetables = schedulerContext.schedule();
    return timetables;
}

TimeTable ExampleTests::constructTimetable(const University& uni, const std::vector<std::vector<int>>& indexesVec) {
    TimeTable timetable;
    for (const auto& indexes : indexesVec) {
        Assignment assignment1(uni, indexes[0], indexes[1], indexes[2]);
        assignment1.penalty = assignment1.countPenalty();
        timetable.addAssignment(assignment1);
    }

    return timetable;
}



