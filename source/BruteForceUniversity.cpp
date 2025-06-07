#include "BruteForceUniversity.h"


void BruteForceUniversity::constructUsableTimeSlots() {
    timeSlots.reserve(University::timeSlots.size());
    for (const auto& timeSlot : University::timeSlots) {
        bool usable = false;
        for (const auto& instructor : instructors) {
            auto instAvailability = instructor.getAvailability();
            if (std::find(instAvailability.begin(), instAvailability.end(), timeSlot) != instAvailability.end()) {
                usable = true;
                break;
            }
        }
        if (usable) {
            timeSlots.push_back(timeSlot);
        }
    }
}

std::vector<std::vector<int>> BruteForceUniversity::constructAvailableInstructors(const std::vector<int>& indexes) const {
    std::vector<std::vector<int>> availableInstructors(mintc, std::vector<int>());
    for (int i = 0; i < mintc; i++) { // constructing availableInstructors
        int timeSlotInd = i; // choose timeSlot
        if (timeSlots.size() == maxtc) { // checking if t > c
            timeSlotInd = indexes[i];
        }
        availableInstructors[i] = slotInstructors[timeSlotInd];
    }
    return availableInstructors;
}

void BruteForceUniversity::constructSlotInstructors() {
    slotInstructors.resize(timeSlots.size());
    for(int i = 0; i < slotInstructors.size(); i++) {
        const auto& timeSlot = timeSlots[i];
        for(int j = 0; j < instructors.size(); j++) {
            const auto& instructor = instructors[j];
            const auto& instAvailability = instructor.getAvailability();
            if(std::find(instAvailability.begin(), instAvailability.end(), timeSlot) != instAvailability.end()) {
                slotInstructors[i].push_back(j);
            }
        }
    }
}

std::vector<int> BruteForceUniversity::extractIndexes(const std::vector<int>& binaryVector) {
    std::vector<int> indexes;
    for(int i = 0; i < binaryVector.size(); i++) {
        if(binaryVector[i]) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

TimeTable BruteForceUniversity::constructTimeTable(const std::vector<int>& indexes,
    const std::vector<int> &instIndexes) const {
    TimeTable timeTable;
    for(int i = 0; i < mintc; i++) { // constructing timeTable
        int timeSlotInd = i; // choose timeSlot
        int courseInd = i; // choose course
        if (timeSlots.size() == maxtc) { // checking if t > c
            timeSlotInd = indexes[i];
        }
        else if (courses.size() == maxtc) { // checking if c > t
            courseInd = indexes[i];
        }
        int instructorInd = instIndexes[i]; // choose instructor from list of available instructors
        Assignment assignment{
            std::make_shared<TimeSlot>(timeSlots[timeSlotInd]),
            std::make_shared<Course>(courses[courseInd]),
            std::make_shared<Instructor>(instructors[instructorInd])
        };
        timeTable.addAssignment(assignment);
    }
    return timeTable;
}

std::vector<std::vector<int>> BruteForceUniversity::cartesianProduct(const std::vector<std::vector<int>>& sets) {
    std::vector<std::vector<int>> resultSets(1, std::vector<int>());
    for(int i = 0; i < sets.size(); i++) {
        std::vector<std::vector<int>> tempSets;
        for(int element : sets[i]) {
            for(std::vector<int> vec : resultSets) { // add elements to existing sets
                vec.push_back(element);
                tempSets.push_back(vec);
            }
        }
        resultSets = tempSets;
    }
    return resultSets;
}

SchedulingResults BruteForceUniversity::schedule() const {
    SchedulingResults results;
    std::vector<TimeTable> resultTimeTables; // timeTables with most smaller penalty
    long long timeTablesCount = 0;
    int minPenalty = INT_MAX;
    std::vector<int> binaryVector(maxtc, 0);
    std::fill(binaryVector.begin()+(maxtc-mintc), binaryVector.end(), 1); // add mintc ones at the end

    do { // C(maxtc, mintc)
        std::vector<int> indexes = BruteForceUniversity::extractIndexes(binaryVector); // indexes for permutations (note that vector indexes is already sorted, we will get all permutations)

        do {  // O(min(t,c)!) permute indexes
            // at this point we have something like this
            // { (course, timeSlot, {list of available instructors}), (course, timeSlot, {...}), (course, timeSlot, {...}), ... } size = mintc
            // we will write some algorithm that generate all valid combinations of timeTables
            // kind of Cartesian Product for n sets, we will choose some instructor from slotInstructors[timeSlotInd]

            std::vector<std::vector<int>> availableInstructors =
                    constructAvailableInstructors(indexes); // sets in cartesianProduct() function. [i] is vector of indexes of instructors that available for that timeSlot (i = timeSlotInd)

            std::vector<std::vector<int>> setOfInstIndexes = BruteForceUniversity::cartesianProduct(availableInstructors); // [i] is vector of size=mintc that contains indxes of instructors
            // constructing timeTables
            for (const std::vector<int>& instIndexes : setOfInstIndexes) {
                timeTablesCount++;
                TimeTable timeTable = constructTimeTable(indexes, instIndexes); // time table
                int currentPenalty = timeTable.countPenalty();
                if(currentPenalty < minPenalty) {
                    resultTimeTables.clear();
                    minPenalty = currentPenalty;
                }
                if(currentPenalty == minPenalty) {
                    resultTimeTables.push_back(timeTable);
                }
            }

        } while(std::next_permutation(indexes.begin(), indexes.end()));

    } while(std::next_permutation(binaryVector.begin(), binaryVector.end()));

    results.timeTables = resultTimeTables;
    results.minPenalty = minPenalty;
    results.timeTablesCount = timeTablesCount;
    return results;
}

