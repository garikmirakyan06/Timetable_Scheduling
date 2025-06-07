#include "TimeSlot.h"


void TimeSlot::displayInfo(int nestedLevel, int spaceCount) const {
    std::cout << std::string(nestedLevel*spaceCount, ' ');
    std::cout << "Day: " << day << ", Start Time: " << startTime << ", End Time: " << endTime << ".\n";
}