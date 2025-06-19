#pragma once
#include <memory>

#include "TimeTable.h"

// using "Strategy" Design Pattern
class SchedulerContext {
private:
    std::unique_ptr<IScheduler> scheduler{nullptr};

public:
    SchedulerContext(std::unique_ptr<IScheduler> scheduler) : scheduler(std::move(scheduler)) {}

    void displaySchedulingResults(const std::vector<TimeTable>& timeTables, const double& timeTaken) const {
        scheduler->displaySchedulingResults(timeTables, timeTaken);
    }
    std::vector<TimeTable> schedule() const {
        return scheduler->schedule();
    }

};

