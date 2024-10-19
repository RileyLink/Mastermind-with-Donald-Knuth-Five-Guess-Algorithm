//
// Created by riley on 10/7/2024.
//

#ifndef MASTERMIND_H
#define MASTERMIND_H
#include <string>

using namespace std;
#include <vector>


class mastermind {
public:
    void play();
    void instructions();
    mastermind();
    void playBruteForce();
    bool playDonaldKnuth();

    bool playDonaldKnuthParallel();

    int playDonaldKnuth(const string& secretCode);
    vector<string> generateCombinations();


private:
    int CODELENGTH;

    string createSecretCode();

    static string pickGuess(const vector<string>& guesses, vector<string> candidateSolutions, vector<string> combinations);

    static bool removeCode(vector<string> &v, const string &s);

    string chooseSecretCode();

    bool isValidCode(const string &code);

    void recurGenerate(string prefix, vector<string> &result);

    bool checkGuess(string &secretCode, vector<string> guesses);

    string score(string secretCode, string guess);

    vector<string> score(const string& secretCode, const vector<string>& guesses);
};



#endif //MASTERMIND_H
