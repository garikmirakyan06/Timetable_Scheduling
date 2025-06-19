#include "BruteForceScheduler.h"


void BruteForceScheduler::constructUsableTimeSlots() {
    timeSlots.reserve(university.getTimeSlots().size());
    for (const auto& timeSlot : university.getTimeSlots()) {
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

std::vector<std::vector<int>> BruteForceScheduler::constructAvailableInstructors(const std::vector<int>& indexes) const {
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

void BruteForceScheduler::constructSlotInstructors() {
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

std::vector<int> BruteForceScheduler::extractIndexes(const std::vector<int>& binaryVector) {
    std::vector<int> indexes;
    for(int i = 0; i < binaryVector.size(); i++) {
        if(binaryVector[i]) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

TimeTable BruteForceScheduler::constructTimeTable(
    const std::vector<int>& indexes,
    const std::vector<int>& instIndexes
    ) const {
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
        Assignment assignment(
            university,
            courseInd,
            timeSlotInd,
            instructorInd
        );
        int penalty = assignment.countPenalty();
        // std::cout << courseInd << " " << timeSlotInd << " " << instructorInd << "\n";
        assignment.penalty = penalty;
        timeTable.addAssignment(assignment);
    }
    return timeTable;
}

std::vector<std::vector<int>> BruteForceScheduler::cartesianProduct(const std::vector<std::vector<int>>& sets) {
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

std::vector<TimeTable> BruteForceScheduler::schedule() {
    std::vector<TimeTable> resultTimeTables; // timeTables with most smaller penalty
    std::vector<int> binaryVector(maxtc, 0);
    std::fill(binaryVector.begin()+(maxtc-mintc), binaryVector.end(), 1); // add mintc ones at the end
    do { // C(maxtc, mintc)
        std::vector<int> indexes = BruteForceScheduler::extractIndexes(binaryVector); // indexes for permutations (note that vector indexes is already sorted, we will get all permutations)

        do {  // O(min(t,c)!) permute indexes
            // at this point we have something like this
            // { (course, timeSlot, {list of available instructors}), (course, timeSlot, {...}), (course, timeSlot, {...}), ... } size = mintc
            // we will write some algorithm that generate all valid combinations of timeTables
            // kind of Cartesian Product for n sets, we will choose some instructor from slotInstructors[timeSlotInd]
            std::vector<std::vector<int>> availableInstructors =
                    constructAvailableInstructors(indexes); // sets in cartesianProduct() function. [i] is vector of indexes of instructors that available for that timeSlot (i = timeSlotInd)

            std::vector<std::vector<int>> setOfInstIndexes = BruteForceScheduler::cartesianProduct(availableInstructors); // [i] is vector of size=mintc that contains indxes of instructors
            // constructing timeTables
            for (const std::vector<int>& instIndexes : setOfInstIndexes) {
                generatedTimeTablesCount++;
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

    return resultTimeTables;
}

void BruteForceScheduler::displaySchedulingResults(const std::vector<TimeTable>& timeTables,
    const double& timeTaken) const {
    Menu::clear();
    std::cout << "Time taken: " << "\033[4m" << timeTaken << "\033[0m" << " seconds" << std::endl;
    std::cout << "TimeTables combination considered: " << "\033[4m" << generatedTimeTablesCount << "\033[0m" << std::endl;
    std::cout << "Minimum penalty is: " << "\033[4m" << minPenalty << "\033[0m" << std::endl;
    std::cout << "Count of timeTables with minimum penalty: " << "\033[4m" << timeTables.size() << "\033[0m" << std::endl;
    for (const auto& timeTable : timeTables) {
        std::cout << std::endl;
        timeTable.print();
    }
    Menu::waitForEnter();
}

