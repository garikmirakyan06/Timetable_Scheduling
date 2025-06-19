#include "TimeTable.h"


void TimeTable::printAssignments() const {
    for (const auto& assignment : assignments) {
        assignment.print();
    }
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
