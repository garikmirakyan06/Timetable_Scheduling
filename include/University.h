#pragma once

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "TimeSlot.h"
#include "Course.h"
#include "Instructor.h"

class University {
protected:
    std::vector<Course> courses;
    std::vector<Instructor> instructors;
    std::vector<TimeSlot> timeSlots;

public:
    University() = default;

    void addCourse(const Course& course) {
        courses.push_back(course);
    }
    void addInstructor(const Instructor& instructor) {
        instructors.push_back(instructor);
    }
    void addTimeSlot(const TimeSlot& timeSlot) {
        timeSlots.push_back(timeSlot);
    }

    // write class state into Json file
    void saveState(const std::string& filePath) const;

    // from Json file creates University
    void loadState(const std::string& filePath);


    void displayInfo() const;
};

