#include "DummyScheduler.h"



void DummyScheduler::constructCoursesInst() {
    coursesInst.resize(courses.size());
    for (int i = 0; i < courses.size(); i++) {
        for (int j = 0; j < instructors.size(); j++) {
            const auto& instPrefCourses = instructors[j].getPreferredCourses();
            if (std::find(instPrefCourses.begin(), instPrefCourses.end(), courses[i]) != instPrefCourses.end()) {
                coursesInst[i].push_back(j);
            }
        }
    }
}

void DummyScheduler::constructTimeSlotsInst() {
    timeSlotsInst.resize(timeSlots.size());
    for (int i = 0; i < timeSlots.size(); i++) {
        for (int j = 0; j < instructors.size(); j++) {
            const auto& instAvailability = instructors[j].getAvailability();
            if (std::find(instAvailability.begin(), instAvailability.end(), timeSlots[i]) != instAvailability.end()) {
                timeSlotsInst[i].push_back(j);
            }
        }
    }

}

void DummyScheduler::constructUsableTimeSlots() {
    timeSlots.reserve(university.getTimeSlots().size());
    for (const auto& timeSlot : university.getTimeSlots()) {
        bool usable{false};
        for (const auto& instructor : instructors) {
            const auto& instAvailability = instructor.getAvailability();
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

bool DummyScheduler::dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited,
    std::vector<int>& matches) const {
    for(int v : adj[u]) {
        if(!visited[v]) {
            visited[v] = 1;
            if(matches[v] == -1 || dfs(matches[v], adj, visited, matches)) { // flip
                matches[v] = u;
                return true;
            }
        }
    }
    return false;
}

std::vector<std::vector<int>> DummyScheduler::maximumMatching(const std::vector<std::vector<int>>& adj,
    int timeSlotsCount) const {
    int n = adj.size();
    int shuffleCount = 50;
    std::vector<std::vector<int>> matchings;
    std::vector<int> U(n); // holds left side nodes for shuffling
    for (int i = 0; i < n; i++) U[i] = i; // initialize
    std::random_device rd;
    std::mt19937 rng(rd());
    for (int i = 0; i < shuffleCount; i++) { // shuffling for getting more than one maximum matching
        // shuffling
        std::shuffle(U.begin(), U.end(), rng);
        std::vector<int> matching(timeSlotsCount, -1); // matching[v] = u (set U is left side, V right side)
        // go throw all nodes in left side (courses indexes)
        for(int ind = 0; ind < U.size(); ind++) {
            int u = U[ind]; // choose node
            std::vector<bool> visited(timeSlotsCount, false);
            dfs(u, adj, visited, matching);
        }
        matchings.push_back(matching);
    }
    return matchings;
}

std::vector<std::vector<int>> DummyScheduler::constructAdjList() const {
    std::vector<std::vector<int>> adjList(courses.size());
    for (int i = 0; i < courses.size(); i++) {
        for (const auto& timeSlot : courses[i].getPreferredTimeSlots()) {
            int timeSlotIndex = std::find(timeSlots.begin(), timeSlots.end(), timeSlot) - timeSlots.begin();
            if (timeSlotIndex >= 0 && timeSlotIndex < timeSlots.size()) {
                adjList[i].push_back(timeSlotIndex);
            }
        }
    }
    return adjList;
}

std::vector<TimeTable> DummyScheduler::schedule() {
    std::vector<TimeTable> timeTables;
    std::vector<std::vector<int>> adjList = constructAdjList();
    std::vector<std::vector<int>> matchings = maximumMatching(adjList, timeSlots.size()); // matching[timeSlotIndex] = courseIndex

    // take only distinct matchings (for having distinct timeTables)
    std::sort(matchings.begin(), matchings.end());
    auto tail = std::unique(matchings.begin(), matchings.end());
    matchings.erase(tail, matchings.end());

    // iterate throw matchings and construct timeTables
    for (const auto& matching : matchings) {
        TimeTable timeTable;
        int timeTablePenalty{0};
        for (int timeSlotIndex = 0; timeSlotIndex < timeSlots.size(); timeSlotIndex++) {
            if (matching[timeSlotIndex] == -1) { // that timeSlot have no matching to any course
                continue;
            }
            int courseIndex = matching[timeSlotIndex];
            const auto& timeSlotInstructors  = timeSlotsInst[timeSlotIndex];
            const auto& courseInstructors = coursesInst[courseIndex];
            std::vector<int> intersection; // intersection of timeSlotInstructors and courseInstructors (if they have the same instructor we take that)
            std::set_intersection(
                timeSlotInstructors.begin(), timeSlotInstructors.end(),
                courseInstructors.begin(), courseInstructors.end(),
                std::back_inserter(intersection)
            );
            int instructorIndex{-1};
            if (intersection.empty()) { // if no intersection we take random instructor from timeSlotInstructors
                instructorIndex = timeSlotInstructors[0];
            }
            else {
                instructorIndex = intersection[0];
            }

            // at this point we already choose course, timeSlot and instructor
            Assignment assignment(university, courseIndex, timeSlotIndex, instructorIndex);
            int assignmentPenalty = assignment.countPenalty();
            timeTablePenalty += assignmentPenalty;
            assignment.penalty = assignmentPenalty;
            timeTable.addAssignment(assignment);
        }
        minPenalty = std::min(minPenalty, timeTablePenalty);
        timeTable.sortTimeTable(); // sort assignments
        timeTables.push_back(timeTable);
    }
    return timeTables;
}

void DummyScheduler::displaySchedulingResults(const std::vector<TimeTable>& timeTables,
    const double& timeTaken) const {
    Menu::clear();
    std::cout << "Time taken: " << "\033[4m" << timeTaken << "\033[0m" << " seconds" << std::endl;
    std::cout << "Count of timeTables: " << "\033[4m" << timeTables.size() << "\033[0m" << std::endl;
    std::cout << "Minimum penalty is: " << "\033[4m" << minPenalty << "\033[0m" << std::endl;
    for (const auto& timeTable : timeTables) {
        std::cout << std::endl;
        timeTable.print();
    }
    Menu::waitForEnter();
}


