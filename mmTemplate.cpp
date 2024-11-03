// //
// // Created by riley on 10/7/2024.
// //
//
// #include "mmTemplate.h"
// using namespace std;
// #include <iostream>
// #include <random>
// #include <iomanip>
// #include <unordered_map>
// #include <algorithm>
// #include <list>
// #include <chrono>  // for timing
//
// // TODO: Make colors a field probably by just making it an array or vector
//
// //TODO: make template functions and try different data structures for my combos and candidate solutions and time
// // const char colors[] = {'R', 'W', 'Y', 'G', 'B', 'K'};
//
// mmTemplate::mmTemplate(){
//     CODELENGTH = 4;
// }
//
// mmTemplate::mmTemplate(int codelength) : CODELENGTH(codelength){
//
// }
//
// // TODO: fix this so you can input length and colors
// // mmTemplate::mmTemplate(int codelength, const char colorsArr[]): CODELENGTH(codelength), colors(colorsArr) {
// //
// // }
//
// string mmTemplate::score(string secretCode, string guess) {
//     //converts to vector<char> because I am lazy and didnt change the original code I wrote
//     vector<char> vecSecretCode(secretCode.begin(),secretCode.end());
//     vector<char> vecGuess(guess.begin(),guess.end());
//
//     string score;
//     int atCount = 0; // Count for correct characters and positions
//     int oCount = 0; // Count for correct characters but wrong positions
//
//     // Create two vectors to track matched positions
//     vector<bool> secretMatched(CODELENGTH, false);
//     vector<bool> guessMatched(CODELENGTH, false);
//
//     // First pass: Count exact matches ('@')
//     for (int i = 0; i < CODELENGTH; i++) {
//         if (guess[i] == secretCode[i]) {
//             atCount++;
//             secretMatched[i] = true; // Mark this character as matched
//             guessMatched[i] = true;   // Mark this character as matched
//         }
//     }
//
//     // Second pass: Count color matches ('o')
//     for (int i = 0; i < CODELENGTH; i++) {
//         if (!guessMatched[i]) { // Only consider unmatched guesses
//             for (int j = 0; j < CODELENGTH; j++) {
//                 if (!secretMatched[j] && guess[i] == secretCode[j]) {
//                     oCount++;
//                     secretMatched[j] = true; // Mark this character as matched
//                     break; // Move to the next guess after finding a match
//                 }
//             }
//         }
//     }
//
//     // Build the score string with all '@' first, followed by 'o'
//     score.append(atCount, '@'); // Append '@' at count times
//     score.append(oCount, 'o');   // Append 'o' at count times
//
//     return score;
// }
//
// template<typename T>
// T mmTemplate::score(const string& secretCode, const T& guesses) {
//     T guessScores;
//     for (const auto & guess : guesses) {
//         guessScores.push_back(score(secretCode, guess));
//     }
//     return guessScores;
// }
//
// template<typename T>
// bool mmTemplate::checkGuess(string& secretCode, T guesses) {
//     T guessesStrings(guesses.size());
//     T scores = score(secretCode, guesses);
//
//     for (int i=0; i<guesses.size(); i++) {
//         guessesStrings[i] = string(guesses[i].begin(),guesses[i].end());
//     }
//
//     // Set the width for the columns
//     const int colWidth = 15;
//     // Print table header
//     cout << setw(colWidth) << left << "Guess"
//          << setw(colWidth) << left << "Score" << endl;
//     // Print separator
//     cout << setw(colWidth * 2) << setfill('-') << "" << setfill(' ') << endl;
//     // Print table rows (BLANK as a placeholder)
//     for (int i = 0; i < guesses.size(); ++i) {  // For demo, prints 3 rows
//         cout << setw(colWidth) << left << guessesStrings[i] << setw(colWidth) << left << scores[i] << endl;
//     }
//
//     string correctScore;
//     correctScore.append(CODELENGTH, '@');
//     // Check if the last guess matches the secret code
//     return scores.back() == correctScore; // Check last score against secret code
// }
//
// string mmTemplate::createSecretCode() {
//     vector<char> secretCode(CODELENGTH);
//
//     random_device rd; // Non-deterministic random device for seeding
//     mt19937 gen(rd()); // Mersenne Twister engine seeded with random device
//     uniform_int_distribution<> dist(0, 5); // Uniform distribution in the range [0, 5]
//
//     for (int i=0; i<CODELENGTH; i++) {
//         secretCode[i] = colors[dist(gen)];
//     }
//     return string(secretCode.begin(),secretCode.end());
// }
//
// template<typename T, typename K>
// string mmTemplate::pickGuess(const T& guesses, const K& candidateSolutions) {
//     for (string possibleGuess : guesses) {
//         if (find(candidateSolutions.begin(),candidateSolutions.end(),possibleGuess) != candidateSolutions.end()) {
//             return possibleGuess;
//         }
//     }
//
//     return guesses.at(0);
//
//     // for (string possibleGuess : guesses) {
//     //     if (find(combinations.begin(),combinations.end(),possibleGuess) != combinations.end()) {
//     //         return possibleGuess;
//     //     }
//     // }
//     //
//     // return "ERROR";
// }
//
// template<typename T>
// bool mmTemplate::removeCode(T& v, const string& s) {
//     auto it = find(v.begin(), v.end(), s); // Search for the string
//     if (it != v.end()) {
//         v.erase(it);
//         return true; // Indicate successful removal
//     }
//     return false; // Indicate that the string was not found
// }
//
// string mmTemplate::chooseSecretCode() {
//     string code;
//     do {
//         cout << "Please input your secret code as a " << to_string(CODELENGTH) << "-letter combination of the colors (R,W,Y,G,B,K)" << endl;
//         cin >> code;
//     } while (!(code.size() == CODELENGTH && isValidCode(code)));
//     return code;
// }
//
// bool mmTemplate::isValidCode(const string& code) {
//     if (code.size() != CODELENGTH) {
//         return false;
//     }
//     for (char c : code) {
//         if (c != 'R' && c != 'W' && c != 'Y' && c != 'G' && c != 'B' && c != 'K') {
//             return false; // Return false if any character is invalid
//         }
//     }
//     return true;
// }
//
// template<typename T>
// void mmTemplate::recurGenerate(string prefix, T& result) {
//     if (prefix.length() == CODELENGTH) {
//         result.push_back(prefix);  // Store the complete combination
//         return;
//     }
//
//     for (char c : colors) {  // Loop through available colors
//         recurGenerate(prefix + c, result);  // Recursively add next color
//     }
// }
//
// template<typename T>
// T mmTemplate::generateCombinations() {
//     T result;
//     recurGenerate("", result);  // Call recursive helper function
//     return result;         // Return the vector of all combinations
// }
//
// void mmTemplate::instructions() {
//     cout << endl;
//     cout << "The objective of the game is to guess a secret code consisting of colored pegs" << endl;
//     cout << "The secret code is a row of " << to_string(CODELENGTH) << " pegs that may be chosen (with repeats) from the colors: " << endl;
//     cout << "red (R), white (W), yellow (Y), green (G), blue (B), and black (K)" << endl;
//     cout << "Each guess of a possible secret code is scored to give some information about how close the guess is to the secret code" <<endl;
//     cout << "Specifically the guess is scored by, " << endl;
//     cout << "(1) How many of the code pegs in the guess are of the right color and right position." << endl;
//     cout << "(2) How many of the code pegs are of the right colors i.e. occur somewhere in the secret code." << endl;
//     cout << "\nThese two pieces of info are recorded in the form of @'s for item (1) and o's for item (2)" << endl;
//     cout << "The game ends when the secret code is correctly guessed, i.e. a score of " << to_string(CODELENGTH) << " @'s is given." << endl;
//     cout << endl;
// }
//
// // template<typename T>
// // void mmTemplate::play() {
// //     string secretCode;
// //     string currentGuess;
// //     T guesses; //TODO: THIS IS WHERE IT WILL CHANGE?
// //
// //     cout << "Welcome to mmTemplate. Do you want to read the instructions? (Y/N)" << endl;
// //     string choice;
// //     cin >> choice;
// //     // If the user says 'yes', call the instructions function.
// //     if (choice == "y" || choice == "Y") {
// //         instructions();
// //     }
// //
// //     do {
// //         cout << "Do you want to create the secret code or have it randomly generated? (choose/random)" << endl;
// //         cin >> choice;
// //     } while (((choice != "choose") && (choice != "random")));
// //
// //     if (choice == "choose") {
// //         secretCode = chooseSecretCode();
// //     } else {
// //         secretCode = createSecretCode();
// //     }
// //
// //     do {
// //         do {
// //             string guess;
// //             cout << "Guess a combination of secret code as a four-letter combination of the colors (R,W,Y,G,B,K)" << endl;
// //             cin >> guess;
// //             currentGuess = guess;
// //         } while(!isValidCode(currentGuess));
// //         guesses.push_back(currentGuess);
// //     } while(!checkGuess(secretCode, guesses));
// //
// //     cout << endl;
// //     cout << "You correctly guessed the secret code in "<< to_string(guesses.size()) << "! Thanks for playing!" << endl;
// //}
