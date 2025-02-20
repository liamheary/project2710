/*
 * Name: Liam Heary
 * Auburn Banner ID: 904294574
 * Filename: project2_Heary_wjh0051_v1.cpp
 * How to compile: g++ project2_Heary_wjh0051_v1.cpp -o project2_v1
 *
 * Description:
 *   This program simulates "Truel of the Fates", a three-person duel among Aaron, Bob, and Charlie.
 *   The simulation uses randomization to determine whether a shooter hits based on given probabilities.
 *   Two strategies are compared:
 *      Strategy 1: Each shooter aims at the most accurate opponent alive.
 *      Strategy 2: Aaron intentionally misses his first shot (p = 0) to improve his odds.
 *   The simulation is run 10,000 times to compute winning percentages.
 *
 * Analysis of Strategy 2:
 *   In Strategy 2, Aaron intentionally misses his first shot so that his opponents, being more accurate,
 *   are more likely to eliminate each other first. This increases his chances of survival, making
 *   Strategy 2 statistically more favorable for Aaron.
 *
 * Technologies and Libraries Used:
 *   - C++ (for core programming)
 *   - <iostream> for input/output operations
 *   - <cstdlib> and <ctime> for random number generation and seeding
 *   - <cassert> for unit testing using assert()
 *   - Git for version control (ensuring proper versioning of code, including two versions: v1 without test drivers and v2 with test drivers)
 *
 * References/Help:
 *   - Course materials and slides (see Version Control.pdf and Project2 (3).pdf)
 *   - Git tutorials (refer to Tutorial_Git_2710.pdf)
 */

