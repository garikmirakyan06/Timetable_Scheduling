# University Timetable Scheduling System (C++)

This project implements a **University Timetable Scheduling System** in C++, currently using only a **brute-force** scheduling approach.



## Overview

The system attempts to generate a valid schedule by assigning courses to time slots and instructors, considering constraints such as availability, preferences, and course requirements.

Full problem statement and project requirements can be found [here](https://docs.google.com/document/d/1iGzcBMqbpLfBhPh7xrKGplsiqojhlKjDzB4THlBh2ho/edit?tab=t.0). Due to the exhaustive nature of the brute-force algorithm, this solution is only feasible for small problem instances. For larger cases, more optimized or heuristic-based approaches are recommended (e.g., backtracking, constraint programming, or metaheuristics).


## Time Complexity

The time complexity of the brute-force solution is:

$$
\mathbf{\large O\left(\min(T, C)! \times \binom{\max(T, C)}{\min(T, C)} \times I^{\min(T, C)}\right)}
$$


Where:

- `T` = number of available **TimeSlots**
- `C` = number of **Courses** to schedule
- `I` = number of **Instructors**

### Explanation:

1. $C(max(T, C), min(T, C))$ — Binomial coefficient for selecting time slots or courses to assign.
2. $min(T, C)!$ — All permutations of assigning courses to time slots (limited by whichever is fewer).
3. $I^{\min(T, C)}$ — All possible instructor assignments for each course (or slot).

For small problem sizes such as when `T`, `C`, and `I` are around 6 or 7, the brute-force scheduling typically completes in approximately **1 second or less** on modern hardware. This makes it practical for testing and demonstration on limited data sets.

