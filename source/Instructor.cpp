#include "Instructor.h"

void Instructor::displayInfo(int nestedLevel, int spaceCount) const {
    std::cout << std::string(nestedLevel*spaceCount, ' ');
    std::cout << "Instructor name: " << name << "\n";
    std::cout << std::string((nestedLevel+1)*spaceCount, ' ');
    std::cout << "Availability: " << "\n";
    for (const auto& timeSlot : availability) {
        timeSlot.displayInfo(nestedLevel+2);
    }
    std::cout << std::string((nestedLevel+1)*spaceCount, ' ');
    std::cout << "Preferred Courses: " << "\n";
    for (const auto& course : preferredCourses) {
        course.displayInfo(nestedLevel+3);
    }
}
