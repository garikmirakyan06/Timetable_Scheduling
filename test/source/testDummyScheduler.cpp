#include <gtest/gtest.h>

#include "../../include/DummyScheduler.h"
#include "../ExampleTests.h"


// course = 1, timeSlot = 2, instructor = 2
TEST(DummyScheduler, example1) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example1(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    // check that trueTimetable exists in predictedTimetables
    EXPECT_NE(findIter, predictedTimetables.end());
}

// course = 1, timeSlot = 1, instructor = 1
TEST(DummyScheduler, example2) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example2(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    // check that trueTimetable exists in predictedTimetables
    EXPECT_NE(findIter, predictedTimetables.end());
}

// course = 2, timeSlot = 2, instructor = 2
TEST(DummyScheduler, example3) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example3(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}

// course = 1, timeSlot = 3, instructor = 1
TEST(DummyScheduler, example4) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example4(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}

// course = 2, timeSlot = 3, instructor = 3
TEST(DummyScheduler, example5) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example5(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}

// course = 2, timeSlot = 3, instructor = 4
TEST(DummyScheduler, example6) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example6(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);
    std::cout << predictedTimetables.size() << std::endl;
    EXPECT_NE(findIter, predictedTimetables.end());
}


// course = 4, timeSlot = 4, instructor = 2
TEST(DummyScheduler, example7) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example7(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}



// course = 4, timeSlot = 5, instructor = 4
TEST(DummyScheduler, example8) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example8(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}


// course = 3, timeSlot = 3, instructor = 3
TEST(DummyScheduler, example10) {
    University uni;

    TimeTable trueTimetable = ExampleTests::example10(uni); // loadState in university, and return answer
    std::vector<TimeTable> predictedTimetables = ExampleTests::schedule(uni, 1); // schedule
    auto findIter = std::find(predictedTimetables.begin(), predictedTimetables.end(), trueTimetable);

    EXPECT_NE(findIter, predictedTimetables.end());
}

