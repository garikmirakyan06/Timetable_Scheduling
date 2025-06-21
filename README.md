# University Timetable Scheduling System (C++)

This project implements a **University Timetable Scheduling System** in C++, currently using a **brute-force** and **heuristic** scheduling approach.



## Overview

The system attempts to generate a valid schedule by assigning courses to time slots and instructors, considering constraints such as availability, preferences, and course requirements.
The assignment involves managing both soft and hard constraints.
The scheduling algorithm must satisfy all hard constraints and as many soft constraints as possible.

### Hard constraints:
- Each course must be scheduled exactly once in an available time slot and assigned to an instructor
- An instructor can only be assigned to a course if they are available during the corresponding time slot
- An instructor cannot be scheduled to teach more than one course in the same time slot

### Soft constraints:
- Courses should be scheduled in preferred time slots if possible
- Instructors should be assigned to their preferred courses if possible

Full problem statement and project requirements can be found [here](https://docs.google.com/document/d/1iGzcBMqbpLfBhPh7xrKGplsiqojhlKjDzB4THlBh2ho/edit?tab=t.0).


## Brute Force Scheduler
###  Algorithm overview
In this solution, we generate all possible timetables and output the ones with the smallest penalty.
The number of assignments in a timetable will be equal to the minimum of the number of courses and the number of time slots.
First, we select the min(C, T) courses or time slots, where C is the total number of courses and T is the total number of time slots. This gives us the set of courses and time slots that will be used in the timetables.
Next, we generate all permutations of the selected courses or time slots.
Once the courses and time slots are paired, we need to assign instructors. For each (course, timeSlot) pair, we consider the list of instructors who are available during that time slot. From these lists, we must choose one instructor per pair.
To construct all possible combinations of instructors for the (course, timeSlot) pairs, we use the [Cartesian product](https://www.geeksforgeeks.org/python/cartesian-product-of-any-number-of-sets/) of the respective instructors sets.

### The time complexity of the Brute-Force solution

$$
\mathbf{\large O\left(\binom{\max(T, C)}{\min(T, C)}\times\min(T, C)! \times I^{\min(T, C)}\right)}
$$


Where:

- `T` = number of available **TimeSlots**
- `C` = number of **Courses** to schedule
- `I` = number of **Instructors**

Explanation:

1. $C(max(T, C), min(T, C))$ — Binomial coefficient for selecting time slots or courses to assign.
2. $min(T, C)!$ — All permutations of assigning courses to time slots (limited by whichever is fewer).
3. $I^{\min(T, C)}$ — All possible instructor assignments for each course (or slot).

For small problem sizes such as when `T`, `C`, and `I` are around 6 or 7, the brute-force scheduling typically completes in approximately **1 second or less** on modern hardware. This makes it practical for testing and demonstration on limited data sets.

## Dummy Scheduler
### Algorithm overview 
This algorithm does not produce the optimal solution, but it is fast and suitable for large datasets.
As in the previous algorithm, we first aim to assign pairs of (course, timeSlot).
To do this, we use a bipartite graph approach—specifically, the [Maximum Bipartite Matching](https://www.geeksforgeeks.org/dsa/maximum-bipartite-matching/) algorithm. Each course is matched with only one time slot, and each time slot is matched with only one course (see code comments for more details).
For mathematical proof of this algorithm can see [Berge's theorem](https://en.wikipedia.org/wiki/Berge%27s_theorem).
After establishing course-time slot pairs, we assign instructors from the lists of those available at the corresponding time slots. While doing this, we also attempt to satisfy the soft constraints.
This algorithm primarily focuses on the first soft constraint:
“Courses should be scheduled in preferred time slots if possible.”


### Time Complexity 
This algorithm is heuristic, so its time complexity is polynomial, making it suitable for large-scale data.
The approximate time complexity is O(T × C × I).


## Installation and Setup

This project uses **CMake** for building and supports both local and containerized development.

### Building Locally:

To build the project locally you can just run script `build.sh` in directory `scripts` 
   
### Docker:
there is also `Dockerfile` wich will install all necessary dependencies in new environment 
If you prefer using Docker you can run `./scripts/docker_run.sh`. You can also run `docker_install.sh` if you dont have it.

