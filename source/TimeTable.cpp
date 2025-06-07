#include "TimeTable.h"


void TimeTable::printAssignments() const {
    for (const auto& assignment : assignments) {
        std::cout << "| " << std::setw(27) << std::left << assignment.timeSlotPtr->getInfo()
                << "| " << std::setw(34) << std::left << assignment.coursePtr->getCourseName()
                << "| " << std::setw(34) << std::left << assignment.instructorPtr->getName()
                << "| " << std::setw(10) << std::left << assignment.penalty
                << "|\n";
    }
}

int TimeTable::countPenalty() {
    int penalty{0};
    for(auto& assignment : assignments) {
        int assignmentPenalty{0};
        const auto& prefTimeSlots = assignment.coursePtr->getPreferredTimeSlots();
        if (std::find(prefTimeSlots.begin(), prefTimeSlots.end(), *assignment.timeSlotPtr) == prefTimeSlots.end()) {
            assignmentPenalty += 1;
        }
        const auto& prefCourses = assignment.instructorPtr->getPreferredCourses();
        if(std::find(prefCourses.begin(), prefCourses.end(), *assignment.coursePtr) == prefCourses.end()) {
            assignmentPenalty += 2;
        }
        assignment.penalty = assignmentPenalty;
        penalty += assignmentPenalty;
    }
    return penalty;
}

void TimeTable::print() const {
    std::cout << "__________________________________________________________________________________________________________________\n";
    std::cout << "|         Time Slot          |            Course Name            |             Instructor            |  Penalty  |\n";
    std::cout << "|----------------------------|-----------------------------------|-----------------------------------|-----------|\n";

    printAssignments();

    std::cout << "|____________________________|___________________________________|___________________________________|___________|\n";
    std::cout << std::endl << std::endl;
}
