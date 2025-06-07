#include "Course.h"

void Course::displayInfo(int nestedLevel, int spaceCount) const {
    std::cout << std::string(nestedLevel*spaceCount, ' ');
    std::cout << "Course name: " << courseName << "\n";
    std::cout << std::string((nestedLevel+1)*spaceCount, ' ');
    std::cout << "Preferred Time Slots: " << "\n";
    for(const auto& timeSlot : preferredTimeSlots) {
        timeSlot.displayInfo(nestedLevel+2);
    }
}
