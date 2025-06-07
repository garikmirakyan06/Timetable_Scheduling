
#include "University.h"

void University::saveState(const std::string &filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath + " for writing.");
    }
    nlohmann::json jsonUni;
    jsonUni["courses"] = courses;
    jsonUni["instructors"] = instructors;
    jsonUni["timeSlots"] = timeSlots;
    file << jsonUni.dump(4);

    file.close();
}

void University::loadState(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath + " for reading.");
    }
    nlohmann::json jsonUni;
    file >> jsonUni;
    courses = jsonUni["courses"];
    instructors = jsonUni["instructors"];
    timeSlots = jsonUni["timeSlots"];

    file.close();
}

void University::displayInfo() const {
    std::cout << "Courses: " << "\n";
    for (const auto& course : courses) {
        course.displayInfo(1);
    }
    std::cout << "\nInstructors: " << "\n";
    for (const auto& instructor : instructors) {
        instructor.displayInfo(1);
    }
    std::cout << "\nTime Slots: " << "\n";
    for (const auto& timeSlot : timeSlots) {
        timeSlot.displayInfo(1);
    }
}