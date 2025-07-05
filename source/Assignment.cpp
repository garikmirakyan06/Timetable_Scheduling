#include "../include/Assignment.h"


int Assignment::countPenalty() const {
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

void Assignment::print() const {
    if (courseInd == -1 || timeSlotInd == -1 || instructorInd == -1) {
        throw std::runtime_error("Indexes not valid.");
    }
    std::cout << "| " << std::setw(27) << std::left << uni.getTimeSlots()[timeSlotInd].getInfo()
            << "| " << std::setw(34) << std::left << uni.getCourses()[courseInd].getCourseName()
            << "| " << std::setw(34) << std::left << uni.getInstructors()[instructorInd].getName()
            << "| " << std::setw(10) << std::left << penalty
            << "|\n";
}

// for sorting assignments in timetable
bool Assignment::operator<(const Assignment& other) const {
    return (uni.getTimeSlots()[timeSlotInd] < other.uni.getTimeSlots()[other.timeSlotInd]);
}

// for comparing timetables
bool Assignment::operator==(const Assignment& other) const {
    return ((courseInd == other.courseInd) && (timeSlotInd == other.timeSlotInd) && (instructorInd == other.instructorInd));
}