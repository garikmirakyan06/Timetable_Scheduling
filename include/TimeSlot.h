#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class TimeSlot {
private:
    std::string day;
    std::string startTime;
    std::string endTime;


    static int dayToInt(const std::string& d) {
        static const std::map<std::string, int> days = {
            {"Monday",    1},
            {"Tuesday",   2},
            {"Wednesday", 3},
            {"Thursday",  4},
            {"Friday",    5},
            {"Saturday",  6},
            {"Sunday",    7}
        };
        return days.at(d);
    }
    static int timeToMinutes(const std::string& t) {
        int hours = std::stoi(t.substr(0, 2));
        int minutes = std::stoi(t.substr(3, 2));
        return hours * 60 + minutes;
    }


public:
    TimeSlot() = default;
    TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime) : day(day), startTime(startTime), endTime(endTime) {}

    bool operator==(const TimeSlot& other) const {
        return ((day + startTime + endTime) == (other.day + other.startTime + other.endTime));
    }
    bool operator<(const TimeSlot& other) const {
        if (dayToInt(day) != dayToInt(other.day))
            return dayToInt(day) < dayToInt(other.day);
        if (timeToMinutes(startTime) != timeToMinutes(other.startTime))
            return timeToMinutes(startTime) < timeToMinutes(other.startTime);
        return timeToMinutes(endTime) < timeToMinutes(other.endTime);
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
