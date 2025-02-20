/*
 * Name: Liam Heary
 * Auburn Banner ID: 904294574
 * Filename: project2_Heary_wjh0051_v2.cpp
 * How to compile: g++ project2_Heary_wjh0051_v2.cpp -o project2_v2 -Wall
 *
 * Description:
 *   This program simulates "Truel of the Fates," a three-person duel among Aaron, Bob,
 *   and Charlie. The simulation uses random numbers to decide whether each shooter hits
 *   based on given probabilities. Two strategies are simulated:
 *     - Strategy 1: Every shooter aims at the most accurate opponent still alive.
 *     - Strategy 2: Aaron intentionally misses his first shot (p = 0) and then shoots normally.
 *   Each simulation runs 10,000 truels to determine the winning percentages.
 *
 * Analysis of Strategy 2:
 *   By intentionally missing his first shot, Aaron lets his more accurate opponents (Bob and Charlie)
 *   target each other. This increases Aaron's survival chances compared to Strategy 1.
 *
 * Technologies and Libraries Used:
 *   - C++ (with <iostream>, <cstdlib>, <ctime>, <limits>, <cassert>)
 *   - Random number generation (rand(), srand())
 *   - Git for version control
 *
 * References/Help:
 *   - Course materials and slides (Version Control.pdf, Project2 (3).pdf)
 *   - Tutorial_Git_2710.pdf for Git usage
 *
 * Note:
 *   This is Version 2 of the project, which includes unit test drivers. Version 1 (without test drivers)
 *   is a subset of this file so that merging v2 into v1 produces no conflicts.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cassert>
using namespace std;

// Define constants
const int TOTAL_RUNS = 10000;
const int AARON_HIT_PERCENT = 33;   // 33% chance for Aaron in Strategy 1
const int BOB_HIT_PERCENT   = 50;     // 50% chance for Bob

// Function prototypes for simulation functions
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool &B_alive, bool &C_alive);
void Bob_shoots(bool &A_alive, bool &C_alive);
void Charlie_shoots(bool &A_alive, bool &B_alive);
void Aaron_shoots2(bool &B_alive, bool &C_alive);

// Helper: Pause until Enter is pressed (only between major sections)
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Returns true if at least two gunmen are alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    int count = 0;
    if (A_alive) count++;
    if (B_alive) count++;
    if (C_alive) count++;
    return (count >= 2);
}

// Aaron shoots using Strategy 1
void Aaron_shoots1(bool &B_alive, bool &C_alive) {
    int shoot_result = rand() % 100;
    if (C_alive) {  // Charlie is more accurate; target him.
        if (shoot_result < AARON_HIT_PERCENT) {
            C_alive = false;
        }
    } else { // Only Bob is alive.
        if (shoot_result < AARON_HIT_PERCENT) {
            B_alive = false;
        }
    }
}

// Bob shoots; targets Charlie if alive, otherwise Aaron.
void Bob_shoots(bool &A_alive, bool &C_alive) {
    int shoot_result = rand() % 100;
    if (C_alive) {
        if (shoot_result < BOB_HIT_PERCENT) {
            C_alive = false;
        }
    } else { // Only Aaron is alive.
        if (shoot_result < BOB_HIT_PERCENT) {
            A_alive = false;
        }
    }
}

// Charlie shoots; he never misses.
void Charlie_shoots(bool &A_alive, bool &B_alive) {
    if (B_alive) {
        B_alive = false;
    } else if (A_alive) {
        A_alive = false;
    }
}

// Aaron's shooting for Strategy 2: intentionally miss on the first shot.
// (This function is only called on Aaron's first turn in Strategy 2.)
void Aaron_shoots2(bool &B_alive, bool &C_alive) {
    // Intentionally miss: do nothing.
    // (No output here to avoid flooding the simulation output.)
}

// Simulation for Strategy 1
void simulate_strategy1(int &aaronWins, int &bobWins, int &charlieWins) {
    for (int i = 0; i < TOTAL_RUNS; i++) {
        bool A_alive = true, B_alive = true, C_alive = true;
        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive) {
                Aaron_shoots1(B_alive, C_alive);
            }
            if (at_least_two_alive(A_alive, B_alive, C_alive) && B_alive) {
                Bob_shoots(A_alive, C_alive);
            }
            if (at_least_two_alive(A_alive, B_alive, C_alive) && C_alive) {
                Charlie_shoots(A_alive, B_alive);
            }
        }
        if (A_alive) aaronWins++;
        else if (B_alive) bobWins++;
        else if (C_alive) charlieWins++;
    }
}

// Simulation for Strategy 2
void simulate_strategy2(int &aaronWins, int &bobWins, int &charlieWins) {
    // Print a single note indicating the intentional miss
    cout << "\nNote: In Strategy 2, Aaron intentionally misses his first shot." << endl;
    for (int i = 0; i < TOTAL_RUNS; i++) {
        bool A_alive = true, B_alive = true, C_alive = true;
        bool aaronFirstShot = true;
        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive) {
                if (aaronFirstShot) {
                    Aaron_shoots2(B_alive, C_alive); // intentionally miss
                    aaronFirstShot = false;
                } else {
                    Aaron_shoots1(B_alive, C_alive);
                }
            }
            if (at_least_two_alive(A_alive, B_alive, C_alive) && B_alive) {
                Bob_shoots(A_alive, C_alive);
            }
            if (at_least_two_alive(A_alive, B_alive, C_alive) && C_alive) {
                Charlie_shoots(A_alive, B_alive);
            }
        }
        if (A_alive) aaronWins++;
        else if (B_alive) bobWins++;
        else if (C_alive) charlieWins++;
    }
}

//
// Unit Test Drivers (using assert) - these tests are basic and for demonstration.
// In a real test, you might simulate fixed conditions to test functions deterministically.
//

// Test driver for at_least_two_alive()
void test_at_least_two_alive() {
    cout << "\nUnit Testing 1: Function – at_least_two_alive()\n";
    
    cout << "Case 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(true, true, true));
    cout << "Case passed ...\n";
    
    cout << "Case 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(false, true, true));
    cout << "Case passed ...\n";
    
    cout << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(at_least_two_alive(true, false, true));
    cout << "Case passed ...\n";
    
    cout << "Case 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(at_least_two_alive(true, true, false));
    cout << "Case passed ...\n";
    
    cout << "Case 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(!at_least_two_alive(false, false, true));
    cout << "Case passed ...\n";
    
    cout << "Case 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(!at_least_two_alive(false, true, false));
    cout << "Case passed ...\n";
    pause();
}

// Test driver for Aaron_shoots1()
// Note: Since outcomes are random, this test is basic.
void test_Aaron_shoots1() {
    cout << "\nUnit Testing 2: Function – Aaron_shoots1()\n";
    {
        bool B_alive = true, C_alive = true;
        Aaron_shoots1(B_alive, C_alive);
        // After shooting, at least one opponent may be killed.
        // We check that at least one remains false if shooting succeeds.
        if (!B_alive || !C_alive) {
            cout << "Case passed ...\n";
        } else {
            cout << "Case inconclusive due to miss; run test multiple times.\n";
        }
    }
    pause();
}

// Test driver for Bob_shoots()
void test_Bob_shoots() {
    cout << "\nUnit Testing 3: Function – Bob_shoots()\n";
    {
        bool A_alive = true, C_alive = true;
        Bob_shoots(A_alive, C_alive);
        if (!C_alive || !A_alive) {
            cout << "Case passed ...\n";
        } else {
            cout << "Case inconclusive due to miss; run test multiple times.\n";
        }
    }
    pause();
}

// Test driver for Charlie_shoots()
void test_Charlie_shoots() {
    cout << "\nUnit Testing 4: Function – Charlie_shoots()\n";
    {
        bool A_alive = true, B_alive = true;
        Charlie_shoots(A_alive, B_alive);
        // Charlie always kills one target. At least one must be false.
        if (!A_alive || !B_alive) {
            cout << "Case passed ...\n";
        } else {
            cout << "Case failed (should never happen with Charlie_shoots())\n";
        }
    }
    pause();
}

// Test driver for Aaron_shoots2()
void test_Aaron_shoots2() {
    cout << "\nUnit Testing 5: Function – Aaron_shoots2()\n";
    {
        bool B_alive = true, C_alive = true;
        Aaron_shoots2(B_alive, C_alive);
        // Since Aaron intentionally misses, both should remain true.
        assert(B_alive && C_alive);
        cout << "Case passed ...\n";
    }
    pause();
}

int main() {
    // Initialize random seed
    srand(time(0));

    cout << "*** Welcome to Liam Heary's Truel of the Fates Simulator ***" << endl;
    pause();

    // Simulation for Strategy 1
    int aaronWins1 = 0, bobWins1 = 0, charlieWins1 = 0;
    cout << "\nStarting simulation for Strategy 1 (each shooter targets the most accurate opponent)..." << endl;
    simulate_strategy1(aaronWins1, bobWins1, charlieWins1);
    cout << "\nResults for Strategy 1:" << endl;
    cout << "Aaron won " << aaronWins1 << "/" << TOTAL_RUNS << " truels or " << (aaronWins1 * 100.0 / TOTAL_RUNS) << "%" << endl;
    cout << "Bob won " << bobWins1 << "/" << TOTAL_RUNS << " truels or " << (bobWins1 * 100.0 / TOTAL_RUNS) << "%" << endl;
    cout << "Charlie won " << charlieWins1 << "/" << TOTAL_RUNS << " truels or " << (charlieWins1 * 100.0 / TOTAL_RUNS) << "%" << endl;
    pause();

    // Simulation for Strategy 2
    int aaronWins2 = 0, bobWins2 = 0, charlieWins2 = 0;
    cout << "\nStarting simulation for Strategy 2 (Aaron intentionally misses his first shot)..." << endl;
    simulate_strategy2(aaronWins2, bobWins2, charlieWins2);
    cout << "\nResults for Strategy 2:" << endl;
    cout << "Aaron won " << aaronWins2 << "/" << TOTAL_RUNS << " truels or " << (aaronWins2 * 100.0 / TOTAL_RUNS) << "%" << endl;
    cout << "Bob won " << bobWins2 << "/" << TOTAL_RUNS << " truels or " << (bobWins2 * 100.0 / TOTAL_RUNS) << "%" << endl;
    cout << "Charlie won " << charlieWins2 << "/" << TOTAL_RUNS << " truels or " << (charlieWins2 * 100.0 / TOTAL_RUNS) << "%" << endl;
    pause();

    // Compare strategies for Aaron
    cout << "\nComparison for Aaron:" << endl;
    if (aaronWins2 > aaronWins1)
        cout << "Strategy 2 is better for Aaron." << endl;
    else if (aaronWins2 < aaronWins1)
        cout << "Strategy 1 is better for Aaron." << endl;
    else
        cout << "Both strategies are equally effective for Aaron." << endl;
    pause();

    // Run unit test drivers
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    return 0;
}

