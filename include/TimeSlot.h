#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class TimeSlot {
private:
    std::string day;
    std::string startTime;
    std::string endTime;

public:
    TimeSlot() = default;
    TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime) : day(day), startTime(startTime), endTime(endTime) {}

    bool operator==(const TimeSlot& other) const {
        return ((day + startTime + endTime) == (other.day + other.startTime + other.endTime));
    }

    std::string getInfo() const {
        return (day + ", " + startTime + " - " + endTime);
    }

    void displayInfo(int nestedLevel = 0, int spaceCount = 4) const;

    // getters
    const std::string& getDay() const { return day; }
    const std::string& getStartTime() const { return startTime; }
    const std::string& getEndTime() const { return endTime; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TimeSlot, day, startTime, endTime);

};
