#pragma once

#include <iomanip>
#include <memory>

#include "TimeSlot.h"
#include "Course.h"
#include "Instructor.h"


struct Assignment {
    std::shared_ptr<TimeSlot> timeSlotPtr{};
    std::shared_ptr<Course> coursePtr{};
    std::shared_ptr<Instructor> instructorPtr{};
    int penalty{-1};
};


class TimeTable {
private:
    std::vector<Assignment> assignments;

    void printAssignments() const;

public:
    void addAssignment(const Assignment& assignment) {
        assignments.push_back(assignment);
    }

    const std::vector<Assignment>& getAssignments() const {
        return assignments;
    }

    int countPenalty();

    void print() const;
};


