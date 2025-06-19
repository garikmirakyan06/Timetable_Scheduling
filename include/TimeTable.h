#pragma once

#include <iomanip>
#include <memory>

#include "TimeSlot.h"
#include "Course.h"
#include "Instructor.h"
#include "University.h"


struct Assignment {
    const University& uni;
    int courseInd{-1};
    int timeSlotInd{-1};
    int instructorInd{-1};
    int penalty{-1};

    Assignment() = delete;
    Assignment(const University& uni_, int courseInd_, int timeSlotInd_, int instructorInd_) :
            uni(uni_), courseInd(courseInd_), timeSlotInd(timeSlotInd_), instructorInd(instructorInd_) {}

    int countPenalty() const {
        if (courseInd == -1 || timeSlotInd == -1 || instructorInd == -1) {
            return -1;
        }
        int assignmentPenalty{0};
        const auto& course = uni.getCourses()[courseInd];
        const auto& timeSlot = uni.getTimeSlots()[timeSlotInd];
        const auto& prefTimeSlots = course.getPreferredTimeSlots();

        if (std::find(prefTimeSlots.begin(), prefTimeSlots.end(), timeSlot) == prefTimeSlots.end()) {
            assignmentPenalty += 1;
        }
        const auto& prefCourses = uni.getInstructors()[instructorInd].getPreferredCourses();
        if(std::find(prefCourses.begin(), prefCourses.end(), course) == prefCourses.end()) {
            assignmentPenalty += 2;
        }
        return assignmentPenalty;
    }

    void print() const {
        if (courseInd == -1 || timeSlotInd == -1 || instructorInd == -1) {
            throw std::runtime_error("Indexes not valid.");
        }
        std::cout << "| " << std::setw(27) << std::left << uni.getTimeSlots()[timeSlotInd].getInfo()
                << "| " << std::setw(34) << std::left << uni.getCourses()[courseInd].getCourseName()
                << "| " << std::setw(34) << std::left << uni.getInstructors()[instructorInd].getName()
                << "| " << std::setw(10) << std::left << penalty
                << "|\n";
    }
};


class TimeTable {
private:
    std::vector<Assignment> assignments;
    void printAssignments() const;

public:
    TimeTable() = default;

    void addAssignment(const Assignment& assignment) {
        assignments.push_back(assignment);
    }

    const std::vector<Assignment>& getAssignments() const {
        return assignments;
    }

    int countPenalty() const;

    void print() const;
};


