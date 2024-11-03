#include <iostream>
#include "mastermind.h"
#include "mmTemplate.h"
#include <omp.h>
#include <chrono>

int main() {
//TODO: CLEAN THIS FILE
    omp_set_num_threads(6); // For example, use 4 threads

    mastermind game(4);
    //mmTemplate game(4);
    game.play();
    game.playBruteForce();
    game.playDonaldKnuth();
    game.playDonaldKnuthParallel();
    // game.playDonaldKnuth<list<string>>();
    // game.playDonaldKnuthParallel<list<string>>();
    // game.play<list<string>>();
    //
    //
    // auto sett = game.generateCombinations<vector<string>>();
    // cout << to_string(sett.size()) << endl;
    // auto start = chrono::high_resolution_clock::now();
    //
    // // Use OpenMP to parallelize the loop
    // #pragma omp parallel for               // TAKES ABOUT 4 MINUTES AND WE DONT WANT TO USE DYANMIC SCHEUDLING BC THATS SO MUCH SLOWER
    // for (int i = 0; i < sett.size(); ++i) {
    //     const string& combo = sett[i];
    //
    //     // Check if the result is greater than 5
    //     if (game.playDonaldKnuth<vector<string>>(combo) > 5) {
    //         // Print the combo - use a critical section to avoid race conditions
    //        #pragma omp critical
    //         {
    //             cout << combo << endl;
    //         }
    //     } else {
    //         // Print the combo - use a critical section to avoid race conditions
    //         #pragma omp critical
    //         {
    //             cout << to_string(i) << endl;
    //         }
    //     }
    // }
    // // Note: The "done" message should be printed by the master thread.
    // #pragma omp single
    // {
    //     cout << "done" << endl;
    // }
    //
    // // Record end time
    // auto end = chrono::high_resolution_clock::now();
    // // Calculate the duration in milliseconds
    // chrono::duration<double, milli> duration = end - start;
    // // Output the elapsed time
    // cout << "Function execution time: " << duration.count() << " ms" << endl;
    //






    // auto start2 = chrono::high_resolution_clock::now();
    // int j = 0;
    // for (const string& combo : sett) {
    //     if (game.playDonaldKnuth(combo) > 5) {
    //         cout << combo;
    //     } else {
    //         cout << to_string(j) << endl;
    //         j++;
    //     }
    //
    // }
    // cout << "done";
    // // Record end time
    // auto end2 = chrono::high_resolution_clock::now();
    // // Calculate the duration in milliseconds
    // chrono::duration<double, milli> duration2 = end2 - start2;
    // // Output the elapsed time
    // cout << "Function execution time: " << duration2.count() << " ms" << endl;

//
// #pragma omp parallel
//     {
//         int thread_id = omp_get_thread_num();
//         int num_threads = omp_get_num_threads();
// #pragma omp critical
//         {
//             cout << "Thread " << thread_id << " out of " << num_threads << " threads." << std::endl;
//         }
//     }
}
