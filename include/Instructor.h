#pragma once

#include <iostream>

#include "TimeSlot.h"
#include "Course.h"


class Instructor {
private:
    std::string name;
    std::vector<TimeSlot> availability;
    std::vector<Course> preferredCourses;

public:
    void displayInfo(int nestedLevel = 0, int spaceCount = 4) const;

    // getters
    const std::string& getName() const { return name; }
    const std::vector<TimeSlot>& getAvailability() const { return availability; }
    const std::vector<Course>& getPreferredCourses() const { return preferredCourses; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Instructor, name, availability, preferredCourses);
};

