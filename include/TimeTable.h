#pragma once


#include "Assignment.h"

class TimeTable {
private:
    std::vector<Assignment> assignments;
    void printAssignments() const;

public:
    TimeTable() = default;

    bool operator==(const TimeTable& other) const;

    void addAssignment(const Assignment& assignment);

    const std::vector<Assignment>& getAssignments() const;

    int countPenalty() const;

    void print() const;

    void sortTimeTable();

};


