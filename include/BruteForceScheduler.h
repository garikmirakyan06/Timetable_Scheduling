#pragma once

#include <climits>

#include "University.h"
#include "TimeTable.h"
#include "IScheduler.h"
#include "Menu.h"

class BruteForceScheduler : public IScheduler {
public:
    const University& university;
    std::vector<Course> courses;
    std::vector<TimeSlot> timeSlots; // usable timeSlots, timeSlots that have instructor
    std::vector<Instructor> instructors;
    long long generatedTimeTablesCount{0};
    int minPenalty{INT_MAX};
    int mintc{-1}; // min(timeSlots.size(), courses.size())
    int maxtc{-1}; // max(timeSlots.size(), courses.size())

    std::vector<std::vector<int>> slotInstructors; // for every timeSlot store the indexes of instructors who have timeSlot in their availability

    std::vector<std::vector<int>> constructAvailableInstructors(const std::vector<int>& indexes) const;

    // Cartesian Product for n sets, for choosing instructor
    static std::vector<std::vector<int>> cartesianProduct(const std::vector<std::vector<int>>& sets);

    TimeTable constructTimeTable(const std::vector<int>& indexes, const std::vector<int>& instIndexes) const;

    static std::vector<int> extractIndexes(const std::vector<int>& binaryVector);

    void constructSlotInstructors();

    void constructUsableTimeSlots();

public:
    BruteForceScheduler(const University& uni) : university(uni), courses(university.getCourses()), instructors(university.getInstructors()) {
        // some preprocessing
        constructUsableTimeSlots();
        constructSlotInstructors();
        mintc = std::min(timeSlots.size(), courses.size());
        maxtc = std::max(timeSlots.size(), courses.size());
    }

    std::vector<TimeTable> schedule() override;

    void displaySchedulingResults(const std::vector<TimeTable>& timeTables, const double& timeTaken) const override;
};

