#include <random>
#include <algorithm>
#include <climits>
#include <limits.h>

#include "IScheduler.h"
#include "University.h"
#include "TimeTable.h"
#include "Menu.h"


// using "Strategy" Design Pattern
class DummyScheduler : public IScheduler {
public:
    const University& university;
    std::vector<Course> courses;
    std::vector<Instructor> instructors;
    std::vector<TimeSlot> timeSlots;  // usable TimeSlots, that hase at least one instructor
    int minPenalty{INT_MAX};
    std::vector<std::vector<int>> timeSlotsInst; // for each timeSlot set of indexes of their instructors (instructors that availably at that time)
    std::vector<std::vector<int>> coursesInst; // for each course set of indexes of their instructors (instructors that prefer that course)

    void constructCoursesInst();

    void constructTimeSlotsInst();

    void constructUsableTimeSlots();

    // for traversing bipartite graph and flip augmenting paths
    bool dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<int>& matches) const;

    // "Maximum Bipartite Matches" algorithm.
    // We try to match to one Course only one TimeSlot (from its preferredTimeSlots),
    // and also one TimeSlot can be matched only with one Course, we want to
    // maximize the number of matched Courses.
    // The left side of bipartite graph is Courses, and in right side usableTimeSlots
    // at first we have connection from course to timeSlot if that timeSlot is in the
    // preferredTimeSlots of that course (can be directed graph).
    //
    // --------- Some Definitions can be useful ---------
    //   1) Matching in graph: Is a set of edges,
    // such that no two edges share one vertex.
    //
    //   2) Maximum matching: Is the matching that have
    // maximum number of edges.
    //
    //   3) Augmenting path in bipartite graph: Is a path in the graph that:
    // 1. Starts and ends at unmatched vertices.
    // 2. Alternates between edges not in the matching and in the matching.
    // 3. Has odd length (starts and ends with unmatched edges).
    //
    // Berge's theorem in Graph Theory says that: A matching M in graph
    // is maximum matching if and only if there is no augmenting path
    // in graph respect to M.
    //
    // This function works with indexes of courses and timeSlots
    std::vector<std::vector<int>> maximumMatching(const std::vector<std::vector<int>>& adj, int timeSlotsCount) const;

    std::vector<std::vector<int>> constructAdjList() const;

public:
    DummyScheduler(const University& uni) : university(uni), courses(uni.getCourses()), instructors(uni.getInstructors()) {
        constructUsableTimeSlots();
        constructTimeSlotsInst();
        constructCoursesInst();
    }

    std::vector<TimeTable> schedule() override;

    void displaySchedulingResults(const std::vector<TimeTable>& timeTables, const double& timeTaken) const override;
};

