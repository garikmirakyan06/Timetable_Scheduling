#pragma once

#include "TimeTable.h"

// using "Strtegy" Design Pattern
class IScheduler {
public:
    virtual std::vector<TimeTable> schedule() = 0;
    virtual void displaySchedulingResults(const std::vector<TimeTable>& timeTables, const double& timeTaken) const = 0;
    virtual ~IScheduler() = default;
};
