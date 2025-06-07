#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "TimeSlot.h"

class Course {
private:
    std::string courseName;
    std::vector<TimeSlot> preferredTimeSlots;

public:
    bool operator==(const Course& other) const {
        return (courseName == other.courseName);
    }

    void displayInfo(int nestedLevel = 0, int spaceCount = 4) const;

    // getters
    const std::string& getCourseName() const { return courseName; }
    const std::vector<TimeSlot>& getPreferredTimeSlots() const { return preferredTimeSlots; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Course, courseName, preferredTimeSlots);
};

