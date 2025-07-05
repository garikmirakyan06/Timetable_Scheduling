#include "TimeTable.h"


void TimeTable::printAssignments() const {
    for (const auto& assignment : assignments) {
        assignment.print();
    }
}

void TimeTable::addAssignment(const Assignment& assignment) {
    assignments.push_back(assignment);
}

const std::vector<Assignment>& TimeTable::getAssignments() const {
    return assignments;
}

int TimeTable::countPenalty() const {
    int penalty{0};
    for(const auto& assignment : assignments) {
        penalty += assignment.penalty;
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

bool TimeTable::operator==(const TimeTable& other) const {
    return (assignments == other.assignments);
}

void TimeTable::sortTimeTable() {
    std::sort(assignments.begin(), assignments.end());
}
