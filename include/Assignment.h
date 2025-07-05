#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iomanip>
#include <memory>

#include "TimeSlot.h"
#include "Course.h"
#include "Instructor.h"
#include "University.h"


class Assignment {
public:
    const University& uni; // to avoid holding Courses, TimeSlots and Instructors in memory
    int courseInd{-1};
    int timeSlotInd{-1};
    int instructorInd{-1};
    int penalty{-1};

    Assignment() = delete;
    Assignment(const University& uni_, int courseInd_, int timeSlotInd_, int instructorInd_) :
            uni(uni_), courseInd(courseInd_), timeSlotInd(timeSlotInd_), instructorInd(instructorInd_) {}

    // copy ctor
    Assignment(const Assignment& other) = default;

    // move ctor
    Assignment(Assignment&& other) = default;

    // move assign operator
    Assignment& operator=(Assignment&& other) {
        if (this == &other) {
            return *this;
        }
        courseInd = other.courseInd;
        timeSlotInd = other.timeSlotInd;
        instructorInd = other.instructorInd;
        penalty = other.penalty;
        return *this;
    }

    bool operator==(const Assignment& other) const;

    bool operator<(const Assignment& other) const;

    int countPenalty() const;

    void print() const;
};


#endif //ASSIGNMENT_H
