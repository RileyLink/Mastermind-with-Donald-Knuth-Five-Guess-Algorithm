//
// Created by riley on 10/23/2024.
//

#ifndef MMTEMPLATE_H
#define MMTEMPLATE_H
#include <string>
#include <iostream>
#include <random>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <chrono>  // for timing
using namespace std;

const char colors[] = {'R', 'W', 'Y', 'G', 'B', 'K'};
class mmTemplate {
public:
    mmTemplate(){
        CODELENGTH = 4;
    }

    mmTemplate(int codelength) : CODELENGTH(codelength){

    }

    template<typename T>
    T generateCombinations() {
        T result;
        recurGenerate("", result);  // Call recursive helper function
        return result;         // Return the vector of all combinations
    }

    template<typename T>
    void playBruteForce() {
        string secretCode;
        T guesses;

        cout << "Welcome to mmTemplate. Do you want to read the instructions? (Y/N)" << endl;
        string choice;
        cin >> choice;
        // If the user says 'yes', call the instructions function.
        if (choice == "y" || choice == "Y") {
            instructions();
        }

        do {
            cout << "Do you want to create the secret code or have it randomly generated? (choose/random)" << endl;
            cin >> choice;
        } while (((choice != "choose") && (choice != "random")));

        if (choice == "choose") {
            secretCode = chooseSecretCode();
        } else {
            secretCode = createSecretCode();
        }
        T combinations = generateCombinations<T>();
        string correctScore;
        correctScore.append(CODELENGTH, '@');
        try {
            for (const string& currentGuess : combinations) {
                guesses.insert(guesses.end(),currentGuess);
                if (score(secretCode, currentGuess) == correctScore) {
                    checkGuess(secretCode,guesses);
                    throw exception();
                }
            }
        } catch (const exception&) {
            cout << endl;
            cout << "The brute force approach took " << to_string(guesses.size())<< " guesses! Thanks for playing!" << endl;
        }
    }

    template<typename T>
    bool playDonaldKnuth() {
        string secretCode;
        string currentGuess;
        T guesses;
        string currentScore;
        string correctScore;
        correctScore.append(CODELENGTH, '@');

        cout << "Welcome to mmTemplate. Do you want to read the instructions? (Y/N)" << endl;
        string choice;
        cin >> choice;
        // If the user says 'yes', call the instructions function.
        if (choice == "y" || choice == "Y") {
            instructions();
        }

        do {
            cout << "Do you want to create the secret code or have it randomly generated? (choose/random)" << endl;
            cin >> choice;
        } while (((choice != "choose") && (choice != "random")));

        if (choice == "choose") {
            secretCode = chooseSecretCode();
        } else {
            secretCode = createSecretCode();
        }

        auto start = chrono::high_resolution_clock::now();
        T combinations = generateCombinations<T>(); // All possible guesses
        T candidateSolutions(combinations.begin(),combinations.end());
        //T candidateSolutions = combinations;  //TODO: change to linked list
        //TODO: Change the fucntions to templates to take any type of container

        // Fill with alternating colors to get a balanced first guess
        for (int i = 0; i < CODELENGTH; ++i) {
            currentGuess += colors[i / 2];  // Repeat each color twice
        }

        guesses.insert(guesses.end(),currentGuess);
        do {
            cout << "Candidates left: " << to_string(candidateSolutions.size()) << endl;

            // 1. Remove current guess from combinations and candidate solutions
            removeCode(combinations,currentGuess);
            removeCode(candidateSolutions,currentGuess);

            // 2. Play guess to get score
            currentScore = score(secretCode, currentGuess);

            // 3. If score is @@@@ then terminate
            if (currentScore == correctScore) {
                break;
            }

            // 4. Prune from candidate solutions any codes that would not give same response if it were the secret code
            for (auto it = candidateSolutions.begin(); it != candidateSolutions.end(); /* no increment here */) {
                if (score(*it, currentGuess) != currentScore) {
                    it = candidateSolutions.erase(it); // Erase returns the next iterator
                } else {
                    ++it; // Only increment if no erase happened
                }
            }

            // 5. Calculate minmax vector
            unordered_map<string,int> scoreCount;
            unordered_map<string,int> maxGuessVec;
            T minGuesses;
            for (const string& key : combinations) {
                // Count the scores for each possible guess
                for (const string& sol : candidateSolutions) {
                    string pegScore = score(key, sol);
                    scoreCount[pegScore]++;
                }
                if (key == "KKKB") {
                    cout << "";
                }
                // find max score
                int max = 0;
                for (const auto& pair : scoreCount) {
                    if (pair.second > max) {
                        max = pair.second;
                    }
                }
                // clear score count
                scoreCount.clear();

                // Label the current key with the max
                maxGuessVec[key] = max;
            }

            // Find minimum
            int min = numeric_limits<int>::max();
            for (const auto& element : maxGuessVec) {
                if (element.second < min) {
                    min = element.second;
                }
            }

            // Find all guesses with the minimum
            for (const auto& pair : maxGuessVec) {
                if (pair.second == min) {
                    minGuesses.insert(minGuesses.end(),pair.first);
                }
            }

            // 6. Choose next guess by first checking if its in candidate solutions and then combinations
            currentGuess = pickGuess(minGuesses, candidateSolutions);

            guesses.insert(guesses.end(),currentGuess);

        } while (currentScore != correctScore); //guess score doesn't match final

        checkGuess(secretCode, guesses);
        cout << "The secret code was guessed in " << to_string(guesses.size()) << " guesses!" << endl;

        // Record end time
        auto end = chrono::high_resolution_clock::now();
        // Calculate the duration in milliseconds
        chrono::duration<double, milli> duration = end - start;

        // Output the elapsed time
        cout << "Function execution time: " << duration.count() << " ms" << endl;

        return true;
    }

    template<typename T>
    bool playDonaldKnuthParallel() {
        string secretCode;
        string currentGuess;
        T guesses;
        string currentScore;
        string correctScore;
        correctScore.append(CODELENGTH, '@');

        cout << "Welcome to mmTemplate. Do you want to read the instructions? (Y/N)" << endl;
        string choice;
        cin >> choice;
        // If the user says 'yes', call the instructions function.
        if (choice == "y" || choice == "Y") {
            instructions();
        }

        do {
            cout << "Do you want to create the secret code or have it randomly generated? (choose/random)" << endl;
            cin >> choice;
        } while (((choice != "choose") && (choice != "random")));

        if (choice == "choose") {
            secretCode = chooseSecretCode();
        } else {
            secretCode = createSecretCode();
        }

        auto start = chrono::high_resolution_clock::now();
        T combinations = generateCombinations<T>(); // All possible guesses
        T candidateSolutions = combinations;

        // Fill with alternating colors to get a balanced first guess
        for (int i = 0; i < CODELENGTH; ++i) {
            currentGuess += colors[i / 2];  // Repeat each color twice
        }

        guesses.insert(guesses.end(),currentGuess);
        do {
            cout << "Candidates left: " << to_string(candidateSolutions.size()) << endl;

            // 1. Remove current guess from combinations and candidate solutions
            removeCode(combinations,currentGuess);
            removeCode(candidateSolutions,currentGuess);

            // 2. Play guess to get score
            currentScore = score(secretCode, currentGuess);

            // 3. If score is @@@@ then terminate
            if (currentScore == correctScore) {
                break;
            }

            // 4. Prune from candidate solutions any codes that would not give same response if it were the secret code
            for (auto it = candidateSolutions.begin(); it != candidateSolutions.end(); /* no increment here */) {
                if (score(*it, currentGuess) != currentScore) {
                    it = candidateSolutions.erase(it); // Erase returns the next iterator
                } else {
                    ++it; // Only increment if no erase happened
                }
            }

            // 5. Calculate minmax vector
            //unordered_map<string,int> scoreCount;
            unordered_map<string,int> maxGuessVec;
            T minGuesses;

            #pragma omp parallel for
            // for (auto it = combinations.begin(); it != combinations.end(); it++) {
            for (auto key : combinations) {
                //const auto key = *it;
                unordered_map<string, int> scoreCount;  // Private to each thread

                // Count the scores for each possible guess
                for (auto it2 = begin(candidateSolutions); it2 != end(candidateSolutions); ++it2) {
                    auto sol = *it2;
                    string pegScore = score(key, sol);  // Use the memoized scoring function
                    ++scoreCount[pegScore];
                }

                // Find the maximum score for the current guess
                int max = 0;
                for (const auto& pair : scoreCount) {
                    if (pair.second > max) {
                        max = pair.second;
                    }
                }

                #pragma omp critical  // Protect shared resource access
                {
                    maxGuessVec[key] = max;
                }
            }

            // Find minimum
            int min = numeric_limits<int>::max();
            for (const auto& element : maxGuessVec) {
                if (element.second < min) {
                    min = element.second;
                }
            }

            // Find all guesses with the minimum
            for (const auto& pair : maxGuessVec) {
                if (pair.second == min) {
                    minGuesses.insert(minGuesses.end,pair.first);
                }
            }

            // 6. Choose next guess by first checking if its in candidate solutions and then combinations
            currentGuess = pickGuess(minGuesses, candidateSolutions);

            guesses.insert(guesses.end(),currentGuess);

        } while (currentScore != correctScore); //guess score doesn't match final

        checkGuess(secretCode, guesses);
        cout << "The secret code was guessed in " << to_string(guesses.size()) << " guesses!" << endl;

        // Record end time
        auto end = chrono::high_resolution_clock::now();
        // Calculate the duration in milliseconds
        chrono::duration<double, milli> duration = end - start;
        // Output the elapsed time
        cout << "Function execution time: " << duration.count() << " ms" << endl;

        return true;
    }

    template<typename T>
    int playDonaldKnuth(const string& secret) {
        string secretCode = secret;
        string currentGuess;
        T guesses;
        string currentScore;
        string correctScore;
        correctScore.append(CODELENGTH, '@');

        T combinations = generateCombinations<T>(); // All possible guesses
        T candidateSolutions = combinations;

        // Fill with alternating colors to get a balanced first guess
        for (int i = 0; i < CODELENGTH; ++i) {
            currentGuess += colors[i / 2];  // Repeat each color twice
        }

        guesses.insert(guesses.end(),currentGuess);
        do {
            // 1. Remove current guess from combinations and candidate solutions
            removeCode(combinations,currentGuess);
            removeCode(candidateSolutions,currentGuess);

            // 2. Play guess to get score
            currentScore = score(secretCode, currentGuess);

            // 3. If score is @@@@ then terminate
            if (currentScore == correctScore) {
                break;
            }

            // 4. Prune from candidate solutions any codes that would not give same response if it were the secret code
            for (auto it = candidateSolutions.begin(); it != candidateSolutions.end(); /* no increment here */) {
                if (score(*it, currentGuess) != currentScore) {
                    it = candidateSolutions.erase(it); // Erase returns the next iterator
                } else {
                    ++it; // Only increment if no erase happened
                }
            }

            // 5. Calculate minmax vector
            unordered_map<string,int> scoreCount;
            unordered_map<string,int> maxGuessVec;
            T minGuesses;
            for (const string& key : combinations) {
                // Count the scores for each possible guess
                for (const string& sol : candidateSolutions) {
                    string pegScore = score(key, sol);
                    scoreCount[pegScore]++;
                }

                // find max score
                int max = 0;
                for (const auto& pair : scoreCount) {
                    if (pair.second > max) {
                        max = pair.second;
                    }
                }
                // clear score count
                scoreCount.clear();

                // Label the current key with the max
                maxGuessVec[key] = max;
            }

            // Find minimum
            int min = numeric_limits<int>::max();
            for (const auto& element : maxGuessVec) {
                if (element.second < min) {
                    min = element.second;
                }
            }

            // Find all guesses with the minimum
            for (const auto& pair : maxGuessVec) {
                if (pair.second == min) {
                    minGuesses.insert(minGuesses.end(),pair.first);
                }
            }

            // 6. Choose next guess by first checking if its in candidate solutions and then combinations
            currentGuess = pickGuess(minGuesses, candidateSolutions);

            guesses.insert(guesses.end(),currentGuess);

        } while (currentScore != correctScore); //guess score doesn't match final

        return static_cast<int>(guesses.size());
    }

    template<typename T>
    void play() {
        string secretCode;
        string currentGuess;
        T guesses; //TODO: THIS IS WHERE IT WILL CHANGE?

        cout << "Welcome to mmTemplate. Do you want to read the instructions? (Y/N)" << endl;
        string choice;
        cin >> choice;
        // If the user says 'yes', call the instructions function.
        if (choice == "y" || choice == "Y") {
            instructions();
        }

        do {
            cout << "Do you want to create the secret code or have it randomly generated? (choose/random)" << endl;
            cin >> choice;
        } while (((choice != "choose") && (choice != "random")));

        if (choice == "choose") {
            secretCode = chooseSecretCode();
        } else {
            secretCode = createSecretCode();
        }

        do {
            do {
                string guess;
                cout << "Guess a combination of secret code as a four-letter combination of the colors (R,W,Y,G,B,K)" << endl;
                cin >> guess;
                currentGuess = guess;
            } while(!isValidCode(currentGuess));
            guesses.insert(guesses.end(),currentGuess);
        } while(!checkGuess(secretCode, guesses));

        cout << endl;
        cout << "You correctly guessed the secret code in "<< to_string(guesses.size()) << "! Thanks for playing!" << endl;
    }


private:
    string score(string secretCode, string guess) {
        //converts to vector<char> because I am lazy and didnt change the original code I wrote
        vector<char> vecSecretCode(secretCode.begin(),secretCode.end());
        vector<char> vecGuess(guess.begin(),guess.end());

        string score;
        int atCount = 0; // Count for correct characters and positions
        int oCount = 0; // Count for correct characters but wrong positions

        // Create two vectors to track matched positions
        vector<bool> secretMatched(CODELENGTH, false);
        vector<bool> guessMatched(CODELENGTH, false);

        // auto guessIt = begin(guess);
        // auto secretIt = begin(secretCode);
        //
        // for (int i = 0; i < CODELENGTH && guessIt != end(guess) && secretIt != end(secretCode); ++i, ++guessIt, ++secretIt) {
        //     if (*guessIt == *secretIt) {
        //         atCount++;
        //         secretMatched[i] = true;  // Mark this character as matched
        //         guessMatched[i] = true;   // Mark this character as matched
        //     }
        // }

        // First pass: Count exact matches ('@')
        for (int i = 0; i < CODELENGTH; i++) {
            if (guess[i] == secretCode[i]) {
                atCount++;
                secretMatched[i] = true; // Mark this character as matched
                guessMatched[i] = true;   // Mark this character as matched
            }
        }

        // Second pass: Count color matches ('o')
        for (int i = 0; i < CODELENGTH; i++) {
            if (!guessMatched[i]) { // Only consider unmatched guesses
                for (int j = 0; j < CODELENGTH; j++) {
                    if (!secretMatched[j] && guess[i] == secretCode[j]) {
                        oCount++;
                        secretMatched[j] = true; // Mark this character as matched
                        break; // Move to the next guess after finding a match
                    }
                }
            }
        }

        // Build the score string with all '@' first, followed by 'o'
        score.append(atCount, '@'); // Append '@' at count times
        score.append(oCount, 'o');   // Append 'o' at count times

        return score;
    }

    template<typename T>
    T score(const string& secretCode, const T& guesses) {
        T guessScores;
        for (const auto & guess : guesses) {
            guessScores.insert(guessScores.end(),score(secretCode,guess));
        }
        return guessScores;
    }

    template<typename T>
    bool checkGuess(string& secretCode, T guesses) {
        T scores = score(secretCode, guesses);
        T guessesStrings = guesses;

        // T guessesStrings(guesses.size());
        // auto it = guessesStrings.begin(); // Iterator for guessesStrings
        //
        // for (const auto& guess : guesses) {
        //     *it = string(guess.begin(), guess.end());
        //     ++it; // Move to the next position in guessesStrings
        // }

        // Set the width for the columns
        const int colWidth = 15;
        // Print table header
        cout << setw(colWidth) << left << "Guess"
             << setw(colWidth) << left << "Score" << endl;
        // Print separator
        cout << setw(colWidth * 2) << setfill('-') << "" << setfill(' ') << endl;
        // Print table rows (BLANK as a placeholder)

        auto itg = guesses.begin();
        auto its = scores.begin();

        while (itg != guesses.end() && its != scores.end()) {
            cout << setw(colWidth) << left << *itg
                      << setw(colWidth) << left << *its << endl;

            ++itg; // Move to the next guess
            ++its; // Move to the next score
        }

        string correctScore;
        correctScore.append(CODELENGTH, '@');
        // Check if the last guess matches the secret code
        return scores.back() == correctScore; // Check last score against secret code
    }

    string createSecretCode() {
        vector<char> secretCode(CODELENGTH);

        random_device rd; // Non-deterministic random device for seeding
        mt19937 gen(rd()); // Mersenne Twister engine seeded with random device
        uniform_int_distribution<> dist(0, 5); // Uniform distribution in the range [0, 5]

        for (int i=0; i<CODELENGTH; i++) {
            secretCode[i] = colors[dist(gen)];
        }
        return string(secretCode.begin(),secretCode.end());
    }

    template<typename T, typename K>
    string pickGuess(const T& guesses, const K& candidateSolutions) {
        for (string possibleGuess : guesses) {
            if (find(candidateSolutions.begin(),candidateSolutions.end(),possibleGuess) != candidateSolutions.end()) {
                return possibleGuess;
            }
        }

        return *begin(guesses);

        // for (string possibleGuess : guesses) {
        //     if (find(combinations.begin(),combinations.end(),possibleGuess) != combinations.end()) {
        //         return possibleGuess;
        //     }
        // }
        //
        // return "ERROR";
    }

    template<typename T>
    bool removeCode(T& v, const string& s) {
        auto it = find(v.begin(), v.end(), s); // Search for the string
        if (it != v.end()) {
            v.erase(it);
            return true; // Indicate successful removal
        }
        return false; // Indicate that the string was not found
    }

    string chooseSecretCode() {
        string code;
        do {
            cout << "Please input your secret code as a " << to_string(CODELENGTH) << "-letter combination of the colors (R,W,Y,G,B,K)" << endl;
            cin >> code;
        } while (!(code.size() == CODELENGTH && isValidCode(code)));
        return code;
    }

     bool isValidCode(const string& code) {
        if (code.size() != CODELENGTH) {
            return false;
        }
        for (char c : code) {
            if (c != 'R' && c != 'W' && c != 'Y' && c != 'G' && c != 'B' && c != 'K') {
                return false; // Return false if any character is invalid
            }
        }
        return true;
    }

    template<typename T>
    void recurGenerate(string prefix, T& result) {
        if (prefix.length() == CODELENGTH) {
            result.insert(result.end(),prefix); // Store the complete combination
            return;
        }

        for (char c : colors) {  // Loop through available colors
            recurGenerate(prefix + c, result);  // Recursively add next color
        }
    }

    void instructions() {
        cout << endl;
        cout << "The objective of the game is to guess a secret code consisting of colored pegs" << endl;
        cout << "The secret code is a row of " << to_string(CODELENGTH) << " pegs that may be chosen (with repeats) from the colors: " << endl;
        cout << "red (R), white (W), yellow (Y), green (G), blue (B), and black (K)" << endl;
        cout << "Each guess of a possible secret code is scored to give some information about how close the guess is to the secret code" <<endl;
        cout << "Specifically the guess is scored by, " << endl;
        cout << "(1) How many of the code pegs in the guess are of the right color and right position." << endl;
        cout << "(2) How many of the code pegs are of the right colors i.e. occur somewhere in the secret code." << endl;
        cout << "\nThese two pieces of info are recorded in the form of @'s for item (1) and o's for item (2)" << endl;
        cout << "The game ends when the secret code is correctly guessed, i.e. a score of " << to_string(CODELENGTH) << " @'s is given." << endl;
        cout << endl;
    }
    //
    int CODELENGTH;
    //
    // string score(string secretCode, string guess);
    //
    // template<class T>
    // T score(const string &secretCode, const T &guesses);
    //
    // template<class T>
    // bool checkGuess(string &secretCode, T guesses);
    //
    // string createSecretCode();
    //
    // template<class T, class K>
    // string pickGuess(const T &guesses, const K &candidateSolutions);
    //
    // template<class T>
    // bool removeCode(T &v, const string &s);
    //
    // string chooseSecretCode();
    //
    // bool isValidCode(const string &code);
    //
    // template<class T>
    // void recurGenerate(string prefix, T &result);
    //
    // void instructions();
};



#endif //MMTEMPLATE_H
