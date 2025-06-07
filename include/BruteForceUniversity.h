#pragma once

#include <climits>

#include "University.h"
#include "TimeTable.h"

struct SchedulingResults {
    std::vector<TimeTable> timeTables{};
    int minPenalty{-1};
    long long timeTablesCount{-1};
    double timeTaken{-1};
};

class BruteForceUniversity : public University {
private:
    std::vector<TimeSlot> timeSlots; // usable timeSlots, timeSlots that have instructor
    int mintc; // min(timeSlots.size(), courses.size())
    int maxtc; // max(timeSlots.size(), courses.size())

    std::vector<std::vector<int>> slotInstructors; // for every timeSlot store the indexes of instructors who have timeSlot in their availability

    std::vector<std::vector<int>> constructAvailableInstructors(const std::vector<int>& indexes) const;

    static std::vector<std::vector<int>> cartesianProduct(const std::vector<std::vector<int>>& sets);

    TimeTable constructTimeTable(const std::vector<int>& indexes, const std::vector<int>& instIndexes) const;

    static std::vector<int> extractIndexes(const std::vector<int>& binaryVector);

    void constructSlotInstructors();

    void constructUsableTimeSlots();

public:
    BruteForceUniversity(const University& uni) : University(uni) {
        // some preprocessing
        constructUsableTimeSlots();
        constructSlotInstructors();
        mintc = std::min(timeSlots.size(), courses.size());
        maxtc = std::max(timeSlots.size(), courses.size());
    }

    SchedulingResults schedule() const;
};

